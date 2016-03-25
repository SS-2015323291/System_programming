#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST

show_info(struct utmp *); /* showing user information */
void showtime(long); /* showing conection time */
utmp_open( char *); /* open utmp file */
struct utmp *utmp_next(); /* next load */
int utmp_reload(); /* reload file contents */
utmp_close(); /* file closed */

int main()
{
        struct utmp     *utbufp; // buf struct
                        *utmp_next(); //next struct

        if(utmp_open(UTMP_FILE) == -1) //open utmp file
        {
                perror(UTMP_FILE);
                exit(1);
        }

        while((utbufp = utmp_next()) != ((struct utmp*) NULL) ) //recursive loading
                show_info(utbufp); //show user information
        utmp_close();
        return 0;
}

show_info(struct utmp *utbufp)
{
        if(utbufp->ut_type != USER_PROCESS)
                return;
        printf("%-8.8s", utbufp->ut_name);
        printf(" ");
        printf("%-8.8s", utbufp->ut_line);
        printf(" ");
        showtime(utbufp->ut_time);
        printf(" ");

#ifdef SHOWHOST
        if(utbufp->ut_host[0] != '\0')
                printf("(%s)", utbufp->ut_host);
#endif
        printf("\n");
}

void showtime(long timeval)
{
        char *cp;
        cp = ctime(&timeval);

        printf("%12.12s", cp+4);
}

