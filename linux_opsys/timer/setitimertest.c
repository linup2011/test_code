/******setitimertest.c*****************/
/**test code for setitimer************/
/************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

void sigroutine(int signo)
{
	time_t now_time;
	time(&now_time);
	switch(signo){
		case SIGALRM:
			printf("catch a signal == SIGALRM, time:%s \n", asctime(localtime(&now_time)));
			signal(SIGALRM, sigroutine);
			break;
		case SIGVTALRM:
			printf("catch a signal -- SIGVTALRM, time:%s \n", asctime(localtime(&now_time)));
			signal(SIGVTALRM, sigroutine);
			break;
	}
	return;
}

void main()
{
	struct itimerval value, ovalue, value2;
	signal(SIGALRM, sigroutine);
	signal(SIGVTALRM, sigroutine);
	value.it_value.tv_sec = 1;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &value, &ovalue);

	value2.it_value.tv_sec = 0;
	value2.it_value.tv_usec = 500000;
	value2.it_interval.tv_sec = 0;
	value2.it_interval.tv_usec = 500000;

	setitimer(ITIMER_VIRTUAL, &value2, &ovalue);

	for(;;);
}
