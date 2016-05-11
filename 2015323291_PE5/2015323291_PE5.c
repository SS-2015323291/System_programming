#include	<stdio.h>
#include	<termios.h>
#include	<unistd.h>
#include	<signal.h>

int getch(void);

main()
{
	void	f(int);			/* declare the handler	*/
	int	i;

	signal( SIGINT, f );		/* install the handler	*/
	for(i=0; i<5; i++ ){		/* do something else	*/
		printf("hello\n");
		sleep(1);
	}
}

void f(int signum)			/* this function is called */
{
	char q;
	printf("Interrupted! OK to quit (y/n)?");
	q = getch();
	
	switch(q)
	{
		case 'y':
			printf("\n");
			exit(0);
			break;
		case 'n':
			printf("\n");
			break;
	}
}

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
