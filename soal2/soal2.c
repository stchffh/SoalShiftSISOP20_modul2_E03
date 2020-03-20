#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/prctl.h>

void killfile(char mode[])
{
FILE *filee;
filee = fopen("killer.sh", "w");
fprintf(filee,"rm $0\n");
	if(strcmp(mode, "-a")==0) 
	fprintf(filee, "#!/bin/bash\nkill -9 -%d", getpid());
    	else if(strcmp(mode, "-b")==0) 
	fprintf(filee, "#!/bin/bash\nkill %d", getpid());
    
int status;
pid_t child_id;
child_id = fork();
    	if(child_id==0)
	{ 
        char *argv[] = {"chmod", "u+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
    	}

fclose(filee);
}

int main(int argc, char **argv) 
{
	
    pid_t pid, sid;        // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
    exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
    exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
    exit(EXIT_FAILURE);
    }


    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
  
  killfile(argv[1]);
  
time_t t1;
struct tm* tm_t1;
  
while(1)
{
t = time(NULL);
tm_t = localtime(&t);
char foldername[100];
strftime(foldername, 100, "%Y-%m-%d_%H:%M:%S", tm_t);

pid_t child;
child = fork();

int status;

	if (child < 0) 
      	exit(EXIT_FAILURE);

    	if (child == 0)
    	{ 
      		if (fork() == 0)
      		{
        	char *argv[] = {"mkdir", "-p", foldername, NULL};
        	execv("/bin/mkdir", argv);
      		}
          
          else 
      		{
        	while ((wait(&status)) > 0);
        	for (int i = 0; i < 20; i++)
        	{
          	if (fork() == 0)
          	{
            	chdir(foldername);
            	time_t t2;
            	struct tm* tm_t2;
        
            	t2 = time(NULL);
            	tm_t2 = localtime(&t2);
        
            	int t = (int)time(NULL);
            	t = (t % 1000) + 100;
            
            	char donlot[100];
            	sprintf(donlot, "https://picsum.photos/%d", t);

            	char filename[100];
           	  strftime(filename, 100, "%Y-%m-%d_%H:%M:%S", tm_t2);
            	char *argv[] = {"wget", donlot, "-qO", filename, NULL};
            	execv("/usr/bin/wget", argv);
          	  }
          	  sleep(5);
              }
        	    char foldernamezip[150];
        	    sprintf(foldernamezip, "%s.zip", foldername);
        	    char *argv[] = {"zip", "-qrm", foldernamezip, foldername, NULL};
        	    execv("/usr/bin/zip", argv);
      		    }
    		      }
    		      else
      		    sleep(30);
  	        }
}	


  
  
  
