/***********msgtest.c************/
/******** demo code for ********/
/***communication with msg *****/
/********************************/

#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

void msg_stat(int, struct msqid_ds);


void main()
{
	long msgtype = 1;
	int gflags, sflags, rflags;
	key_t key;
	int msgid;
	int reval;
	struct msgbuf{
		long mtype;
		char mtext[1];
	}msg_sbuf;
	struct msgmbuf{
		long mtype;
		char mtext[10];
	}msg_rbuf;
	struct msqid_ds msg_ginfo, msg_sinfo;
	char *msgpath="/tmp/msgqueue";
	key = ftok(msgpath, 'a');
	//gflags = IPC_CREAT|IPC_EXCL;
	gflags = IPC_CREAT;
	//gflags = IPC_EXCL;
	msgid = msgget(key, gflags|0666);
	if (msgid == -1)
	{
		printf("msg create error\n");
		return;
	}

	/*create a msg queue, and print it's default attribute*/
	msg_stat(msgid, msg_ginfo);
	sflags = IPC_NOWAIT;
	msg_sbuf.mtype = msgtype;
	msg_sbuf.mtext[0] = 'a';
	reval = msgsnd(msgid, (void *)&msg_sbuf, sizeof(msg_sbuf.mtext), sflags);
	if ( -1 == reval)
	{
		printf("message send error\n");
	}

	/*after send msg, print msg's attribute*/
	msg_stat(msgid, msg_ginfo);
	rflags = IPC_NOWAIT|MSG_NOERROR;
	msg_rbuf.mtype = 1;
	reval = msgrcv(msgid, (void *)&msg_rbuf, sizeof(msg_rbuf.mtext), msgtype, rflags);
	if ( -1 == reval )
	{
		perror("msgrcv");
	}
	else
	{
		printf("read from msg queue %d bytes\n", reval);
	}

	msg_stat(msgid, msg_ginfo);
	msg_sinfo.msg_perm.uid = 8;
	msg_sinfo.msg_perm.gid = 8;
	msg_sinfo.msg_qbytes = 16388;

	reval = msgctl(msgid, IPC_SET, &msg_sinfo);
	if ( -1 == reval )
	{
		perror("msg set info error\n");
		return;
	}
	msg_stat(msgid, msg_ginfo);

	reval = msgctl(msgid, IPC_RMID, NULL);
	if ( -1 == reval )
	{
		printf("unlink msg queue error\n");
		return;
	}
}

void msg_stat(int msgid, struct msqid_ds msg_info)
{
	int reval;
	sleep(1);
	reval = msgctl(msgid, IPC_STAT, &msg_info);
	if ( -1 == reval )
	{
		printf("get msg info error\n");
		return;
	}
	printf("\n");
	printf("current number of bytes on queue is %d\n", msg_info.msg_cbytes);
	printf("number of message in queue is %d\n", msg_info.msg_qnum);
	printf("max number of bytes on queue is %d\n", msg_info.msg_qbytes);

	printf("pid of last msgsnd is %d\n", msg_info.msg_lspid);
	printf("pid of last msgrcv is %d\n", msg_info.msg_lrpid);
	printf("last msgsnd time is %s\n", ctime(&(msg_info.msg_stime)));
	printf("last msgrcv time is %s\n", ctime(&(msg_info.msg_rtime)));
	printf("last change time is %s\n", ctime(&(msg_info.msg_ctime)));
	printf("msg uid is %d\n", msg_info.msg_perm.uid);
	printf("msg gid is %d\n", msg_info.msg_perm.gid);
}
