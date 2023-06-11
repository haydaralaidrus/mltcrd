#include "mltcrd.h"

struct ftr_t {
	mtx_t      mtx;
	cnd_t      cnd;
	void      *res;
	dealloc_t  dealloc;
	int        state;
	char       __pad[__MLTCRD_PAD_FTR_T];
};

int
ftr_create(ftr_t *future)
{
	if (future == NULL)
		return -1;

	if (mtx_init(&(future->mtx), mtx_plain) != thrd_success)
		return -1;

	if (cnd_init(&(future->cnd)) != thrd_success) {
		mtx_destroy(&(future->mtx));
		return -1;
	}

	future->res = NULL;
	future->dealloc = NULL;
	future->state = ftr_unready;

	return 0;
}

int
ftr_destroy(ftr_t *future)
{
	if (future == NULL)
		return -1;

	if (future->state == ftr_destroyed)
		return -1;

	if (future->state == ftr_ready && future->dealloc != NULL)
		future->dealloc(future->res);

	mtx_destroy(&(future->mtx));
	cnd_destroy(&(future->cnd));
	future->state = ftr_destroyed;

	return 0;
}

int
ftr_set(ftr_t *future, void *result, dealloc_t dealloc)
{
	if (future == NULL)
		return -1;

	if (mtx_lock(&(future->mtx)) != thrd_success)
		return -1;

	if (future->state != ftr_unready) {
		mtx_unlock(&(future->mtx));
		return -1;
	}

	future->res = result;
	future->dealloc = dealloc;
	future->state = ftr_ready;

	/**
	 * signal while holding the mutex? pthreads implementation uses morphing
	 * optimization so, almost no performance impact on not doing so.
	 */

	cnd_signal(&(future->cnd));
	mtx_unlock(&(future->mtx));

	return 0;
}

int
ftr_fail(ftr_t *future)
{
	if (future == NULL)
		return -1;

	if (mtx_lock(&(future->mtx)) != thrd_success)
		return -1;

	if (future->state != ftr_unready) {
		mtx_unlock(&(future->mtx));
		return -1;
	}

	future->state = ftr_failed;

	cnd_signal(&(future->cnd));
	mtx_unlock(&(future->mtx));

	return 0;
}

int
ftr_wait(ftr_t *future)
{
	if (future == NULL)
		return -1;

	if (mtx_lock(&(future->mtx)) != thrd_success)
		return -1;

	if (future->state != ftr_unready) {
		mtx_unlock(&(future->mtx));
		return -1;
	}

	while (future->state == ftr_unready) /* potential spurious wake-ups */
		cnd_wait(&(future->cnd), &(future->mtx));

	mtx_unlock(&(future->mtx));

	return 0;
}

int
ftr_get(ftr_t *future, void **result)
{
	if (future == NULL)
		return -1;

	if (future->state != ftr_ready)
		return -1;

	*result = future->res;

	return 0;
}
