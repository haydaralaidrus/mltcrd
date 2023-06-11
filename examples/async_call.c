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

int
main(void)
{
	ftr_t  future;
	char  *result;

	ftr_create(&future);
	async_call(async_function, NULL, &future);

	printf("Waiting..."); fflush(stdout);
	ftr_wait(&future);
	printf("Done\n");
	ftr_get(&future, (void **) &result);
	printf("%s\n", result);
	ftr_destroy(&future);

	return 0;
}
