#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mltcrd/mltcrd.h>
#include <mltcrd/ftr.h>

static int
thrd_routine(void *arg)
{
	char *result;
	ftr_t *future = (ftr_t *) arg;

	sleep(1); // simulate long process
	result = malloc(sizeof(char) * 32);
	strcpy(result, "this is the result string");
	ftr_set(future, result, free);

	return 0;
}

int
main(void)
{
	thrd_t thrd;
	ftr_t future;
	char *result;

	/* simulate async call */
	ftr_create(&future);
	thrd_create(&thrd, thrd_routine, &future);
	thrd_detach(thrd);

	/* wait for future result */
	printf("Waiting..."); fflush(stdout);
	ftr_wait(&future);
	printf("Done\n");

	/* assume future result ready for brevity */
	ftr_get(&future, (void **) &result);
	printf("%s\n", result);

	ftr_destroy(&future);
}
