#include <stdlib.h>
#include "mltcrd.h"
#include "pack.h"

static int
_async_call_thrd_routine(void *arg);

int
async_call(async_t async, void *arg, ftr_t *future)
{
	thrd_t  thrd;
	pack_t *pack;

	pack = malloc(sizeof(pack_t));
	if (pack == NULL)
		return -1;

	if (pack_create(pack, async, arg, future) != 0) {
		free(pack);
		return -1;
	}

	if (thrd_create(&thrd, _async_call_thrd_routine, pack) != thrd_success) {
		pack_destroy(pack);
		free(pack);
		return -1;
	}

	thrd_detach(thrd);

	return 0;
}

static int
_async_call_thrd_routine(void *arg)
{
	pack_t *pack = (pack_t *) arg;

	pack_execute(pack);
	pack_destroy(pack);
	free(pack);

	return 0;
}
