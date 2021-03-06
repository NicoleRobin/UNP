#include "unpipc.h"

#define SEM_NAME "mysem"

int main(int argc, char **argv)
{
	int fd, i, nloop;
	int *ptr;
	sem_t *mutex;

	if (argc != 2)
	{
		err_quit("usage: incr_dev_zero <#loops>");
	}

	nloop = atoi(argv[1]);
	
	/* open /dev/zero, map into memory */
	fd = Open("/dev/zero", O_RDWR);
	ptr = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	/* create, initialize, and unlink semaphore */
	mutex = Sem_open(SEM_NAME, O_CREAT | O_EXCL, FILE_MODE, 1);
	Sem_unlink(SEM_NAME);

	// stdout is unbuffered
	setbuf(stdout, NULL);
	if (Fork() == 0)
	{ // child process
		for (i = 0;i < nloop; ++i)
		{
			Sem_wait(mutex);
			printf("child:%d\n", (*ptr)++);
			Sem_post(mutex);
			sleep(1);
		}
		exit(0);
	}

	for (i = 0;i < nloop; ++i)
	{
		Sem_wait(mutex);
		printf("parent:%d\n", (*ptr)++);
		Sem_post(mutex);
		sleep(1);
	}

	exit(0);
}
