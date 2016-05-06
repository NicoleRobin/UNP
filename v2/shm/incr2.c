#include <stdlib.h>

#define SEM_NAME "mysem"
int main(int argc, char **argv)
{
	int fd, i, nloop, zero = 0;
	int *ptr;
	sem_t *mutex;

	if (argc !=3)
	{
		printf("Usage: incr2 <pathname> <#loops>");
		return -1;
	}

	nloop = atoi(argv[2]);
	
	/* */

	return 0;
}
