#include        <stdio.h>
#include        <fcntl.h>
#include        <sys/types.h>
#include        <utmp.h>

#define NRECS   16
#define NULLUT  ((struct utmp *)NULL)
#define UTSIZE  (sizeof(struct utmp))

static  char    utmpbuf[NRECS * UTSIZE];                
static  int     num_recs;                               
static  int     cur_rec;                                
static  int     fd_utmp = -1;                          

utmp_open( char *filename )  /* open utmp file  */
{
        fd_utmp = open( filename, O_RDONLY );  // open fuction          
        cur_rec = num_recs = 0;   // init recusive var                      
        return fd_utmp;           // return file descriptor                      
}

struct utmp *utmp_next()   /* next utmp loading  */
{
        struct utmp *recp;   //utmp 

        if ( fd_utmp == -1 )        // null check                    
                return NULLUT;
        if ( cur_rec==num_recs && utmp_reload()==0 )    
                return NULLUT;
                                        
        recp = ( struct utmp *) &utmpbuf[cur_rec * UTSIZE]; // loading utmp
        cur_rec++; // recursive ++
        return recp;
}

int utmp_reload() // reloading utmp
{
        int     amt_read;

                                                
        amt_read = read( fd_utmp , utmpbuf, NRECS * UTSIZE );   

                                                
        num_recs = amt_read/UTSIZE;
                                               
        cur_rec  = 0;
        return num_recs;
}

utmp_close() // file closed
{
        if ( fd_utmp != -1 )                   
                close( fd_utmp );              
}
