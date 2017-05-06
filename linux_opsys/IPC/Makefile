all: msgtest semtest shmreadtest shmwritetest

msgtest:
	gcc -g -o msgtest msgtest.c
semtest:
	gcc -g -o semtest semtest.c
shmreadtest:
	gcc -g -o shmreadtest shmreadtest.c
shmwritetest:
	gcc -g -o shmwritetest shmwritetest.c

clean:
	rm msgtest semtest shmreadtest shmwritetest
