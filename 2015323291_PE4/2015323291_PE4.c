#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>

void main(int ac, char *av[])
{
	struct 	stat info;

	if(ac == 3)		//argc number check
	{
		if(!strcmp(basename(av[1]),basename(av[2])))
		{
			fprintf(stderr, "source and target is same\n");
			exit(0);
		}
		if(stat(av[2], &info) != 1)
		{
			if(S_ISDIR(info.st_mode))	//directory check
			{
				char buf[255] = ""; 
				char av2_dir[100] = ""; 
				char av2_base[100] = "";
				char av1_base[100] ="";

				strcpy(av2_base, basename(av[2]));
				strcpy(av1_base, basename(av[1]));
				strcpy(av2_dir, dirname(av[2]));
				
				strcat(buf, av2_dir);
				strcat(buf, "/");
				strcat(buf, av2_base);
				strcat(buf, "/");
				strcat(buf, av1_base);
				
				if(rename(av[1], buf) == 1) 	//directory mv
				{
					fprintf(stderr, "cannot move the file\n");
					exit(0);
				}
			}
			else
			{
				if(rename(av[1], av[2]) == 1)	//file mv
				{
					fprintf(stderr, "cannot move the file\n");
					exit(0);
				}					
			}
		}
		else
		{
                        fprintf(stderr, "%s is not a  file\n", av[2]);
                        exit(0);
          	}
	}
	else
	{
		fprintf(stderr, "input parameter mush be 3\n");
		exit(0);
	}
}
