/*********semtest.c****************/
/*******test code for sem in ipc *****/
/*******should be run as root*****/
/*********************************/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEM_PATH "/tmp/my_sem"
#define max_tries 3
#define IPC_INFO 3
int semid;

union semun {
	int              val;
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *__buf;
};

void main()
{
	int flag1, flag2, key, i, init_ok, temperrno;
	struct semid_ds sem_info;
	struct seminfo sem_info2;
	union semun arg;
	struct sembuf askfor_res, free_res;
	flag1 = IPC_CREAT | IPC_EXCL | 0666;
	flag2 = IPC_CREAT | 0666;
	key = ftok(SEM_PATH, 'a');

	init_ok = 0;
	semid = semget(key, 1, flag1);

	if (semid < 0)
	{
		perror("semget");
		return;
	}
	else
	{
		arg.val = 1;
		if (semctl(semid, 0, SETVAL, arg) == -1)
		{
			perror("semctl setval error");
		}
	}

	arg.buf = &sem_info;
	if (semctl(semid, 0, IPC_STAT, arg) == -1)
	{
		perror("semctl IPC_STAT error");
	}
	printf("owner's uid is %d\n", arg.buf->sem_perm.uid);
	printf("owner's gid is %d\n", arg.buf->sem_perm.gid);
	printf("creater's uid is %d\n", arg.buf->sem_perm.cuid);
	printf("creater's gid is %d\n", arg.buf->sem_perm.cgid);

	arg.__buf = &sem_info2;
	if (semctl(semid, 0, IPC_INFO, arg) == -1)
	{
		perror("semctl IPC_INFO error");
	}
	printf("the number of entries in semaphore map is %d\n", arg.__buf->semmap);

	askfor_res.sem_num = 0;
	askfor_res.sem_op = -1;
	askfor_res.sem_flg = SEM_UNDO;

	if (semop(semid, &askfor_res, 1) == -1)
	{
		perror("semop error");
	}

	sleep(3);
	printf("now free the resource\n");

	askfor_res.sem_num = 0;
	askfor_res.sem_op = 1;
	askfor_res.sem_flg = SEM_UNDO;
	if (semop(semid, &askfor_res, 1) == -1)
	{
		perror("semop error");
	}

	if (semctl(semid, 0, IPC_RMID) == -1)
	{
		perror("semctl IPC_RMID");
	}
	else
		printf("rm sem ok");
}
