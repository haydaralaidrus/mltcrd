#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mltcrd/mltcrd.h>
#include <mltcrd/ftr.h>
#include <mltcrd/pack.h>

static void
async_function(void *arg, ftr_t *future)
{
	char *result;

	(void) arg;

	sleep(1); // simulate long process
	result = malloc(sizeof(char) * 32);
	strcpy(result, "this is the result string");
	ftr_set(future, result, free);
}

static int
thrd_routine(void *arg)
{
	pack_t *pack = (pack_t *) arg;

	pack_execute(pack);

	return 0;
}

int
main(void)
{
	thrd_t  thrd;
	ftr_t   future;
	pack_t  pack;
	char   *result;

	/* simulate async call */
	ftr_create(&future);
	pack_create(&pack, async_function, NULL, &future);
	thrd_create(&thrd, thrd_routine, &pack);
	thrd_detach(thrd);

	/* wait for future result */
	printf("Waiting..."); fflush(stdout);
	ftr_wait(&future);
	printf("Done\n");

	/* assume future result ready for brevity */
	ftr_get(&future, (void **) &result);
	printf("%s\n", result);

	ftr_destroy(&future);
	pack_destroy(&pack);
}
