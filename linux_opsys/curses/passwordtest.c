/**********passwordtest.c********************/
/****code for test keyboard input ***********/
/********************************************/


#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>


int main()
{
	char name[20];
	char password[20];
	char *real_password = "123456";
	initscr();
	move(5,10);
	addstr("User name:");
	getnstr(name, sizeof(name));

	move(7,10);
	addstr("Password:");
	refresh();

	cbreak();
	noecho();
	memset(password, 0, sizeof(password));

	int len = sizeof(password);
	for (int i=0; i<len; i++)
	{
		password[i] = getch();
		move(7,20+i);
		addch('*');
		refresh();
		if(password[i] == '\n')
			break;
		if (strcmp(password, real_password) == 0)
		{
			break;
		}
	}

	echo();
	nocbreak();

	move(9,10);
	if (strcmp(password, real_password) == 0)
	{
		addstr("Correct");
	}
	else
	{
		addstr("Wrong");
	}
	refresh();

	sleep(10);
	endwin();

	return 0;

}
