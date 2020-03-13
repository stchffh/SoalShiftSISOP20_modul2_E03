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

int main(int a,char *b[]){
	int hour,minute,second;
	int sc,mn,hr= -1;

	if(b[1][0]!='*')
		sc=atoi(b[1]);
	if (b[2][0]!='*')
		mn=atoi(b[2]);
	if(b[3][0]!='*')
		hr=atoi(b[3]);
	if(b!=5){
		printf("TIDAK VALID\n");}

	pid_t proses, session;
	child=fork();
	if(child<0)
		exit(EXIT_FAILURE);
	if(child>0)
		exit(EXIT_SUCCESS);

	umask(0);

	session=setsid();
	if(session<0)
		exit(EXIT_FAILURE);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while (1){
		time_t waktu=waktu(NULL);
		struct wkt *wkt=localtime(&waktu);

		hour=wkt->wkt_hour;
		minute=wkt->wkt_min;
		second=wkt->wkt_sec;
		if((hour==hr||hr==-1)&&(minute==mn||mn==-1)&&(second== sc||sc==-1)){
			if(fork()==0){
				char *c[] = {"bash", b[4], NULL};
					execv("/bin/bash", c);}
			sleep(1);
		}
	}
}
