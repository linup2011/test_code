/*********cursestest.c******************/
/****test code for curses *************/
/*************************************/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <curses.h>


void main()
{
	initscr();
	move(10,20);
	attron(A_BOLD);
	addstr("Hello,");
	refresh();
	sleep(1);
	attron(A_UNDERLINE);
	addstr("world!");
	refresh();
	sleep(1);
	move(11,20);
	attroff(A_BOLD);
	addstr("Hello,");
	refresh();
	sleep(1);
	attroff(A_UNDERLINE);
	addstr("world!");
	refresh();
	sleep(1);
	move(12,20);
	standout();
	addstr("Hello, world!");
	standend();
	refresh();
	sleep(1);

	sleep(10);
	endwin();
	return ;
}
