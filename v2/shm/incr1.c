#include "unpipc.h"

#define SEM_NAME "mysem"

int count = 0;

int main(int argc, char **argv)
{
	int i, nloop;
	sem_t *mutex;

	if (argc != 2)
	{
		err_quit("Usage:incr1 <#loops>");
	}

	nloop = atoi(argv[1]);

	/* create,initialize,and unlink semaphore  */
	mutex = Sem_open(SEM_NAME, O_CREAT | O_EXCL, FILE_MODE, 1);
	/* 
	mutex = sem_open(SEM_NAME, O_CREAT | O_EXCL, FILE_MODE, 1);
	if (mutex == SEM_FAILED)
	{
		printf("sem_open failed for path[%s], errno[%d], error[%s]\n", SEM_NAME, errno, strerror(errno));
		exit(errno);
	}
	*/
	Sem_unlink(SEM_NAME);
	
	// stdout is unbuffered
	setbuf(stdout, NULL);
	if (fork() == 0)
	{ // child process
		for (i = 0; i < nloop; ++i)
		{
			Sem_wait(mutex);
			printf("child:%d\n", count++);
			Sem_post(mutex);
		}

		exit(0);
	}

	// parent process
	for (i = 0; i < nloop; ++i)
	{
		Sem_wait(mutex);
		printf("parent:%d\n", count++);
		Sem_post(mutex);
	}

	exit(0);
}
