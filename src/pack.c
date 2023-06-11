#include "mltcrd.h"

struct pack_t {
	async_t  async;
	void    *arg;
	ftr_t   *future;
};

int
pack_create(pack_t *pack, async_t async, void *arg, ftr_t *future)
{
	if (pack == NULL || async == NULL || future == NULL)
		return -1;

	pack->async  = async;
	pack->arg    = arg;
	pack->future = future;

	return 0;
}

int
pack_destroy(pack_t *pack)
{
	if (pack == NULL)
		return -1;

	return 0;
}

int
pack_execute(pack_t *pack)
{
	if (pack == NULL)
		return -1;

	pack->async(pack->arg, pack->future);

	return 0;
}
