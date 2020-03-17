#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

pid_t pid, sid;

pid = fork();

if (pid < 0)
exit(EXIT_FAILURE);

if (pid > 0)
exit(EXIT_SUCCESS);

umask(0);

sid = setsid();
if (sid < 0)
exit(EXIT_FAILURE);

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

time_t timer = time(NULL);
struct tm *tm= localtime(&timer);

int hour,minute,second;
int sc,mn,hr= -1;

if (argc!= 5)
{
printf ("Argument tidak valid\n");
return 0;
}

if (argv[1][0] !='*')
sc= atoi(argv[1]);
if (argv[2][0] !='*')
mn= atoi(argv[2]);
if (argv[3][0] !='*')
hr= atoi(argv[3]);

if(hr > 23 || hr < -1 || mn > 59 || mn < -1 || sc > 59 || sc < -1)
{
printf("Range waktu salah\n");
return 0;
}

while (1)
{
time_t timer = time(NULL);
struct tm *tm= localtime(&timer);

hour= tm->tm_hour;
minute= tm->tm_min;
second= tm->tm_sec;

if ((hour== hr || hr== -1) &&
(minute== mn || mn== -1) &&
(second== sc || sc== -1))
{
if (fork()==0) {
char *argexec[] = {"bash", argv[4], NULL};
execv("/bin/bash", argexec);
}
sleep(1);
}
}
}

