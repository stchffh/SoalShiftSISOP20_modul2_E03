#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main (){
    pid_t anak;
    int tanda;

    anak=fork();
    if(anak == 0){
        char *buat[] = {"mkdir","-p","/home/oktarizka156/modul2/indomie",(char *)NULL};
        execv("/bin/mkdir",buat);}
    else{
        while(wait(&tanda)>0);
        anak=fork();
        if(anak==0){
            sleep(5);
            char *buat[] = {"mkdir","-p","/home/oktarizka156/modul2/sedaap",(char *)NULL};
            execv("/bin/mkdir",buat);}
        else{
            while(wait(&tanda)>0);
            anak=fork();
            if(anak==0){
                char *buat[] = {"unzip","/home/oktarizka156/Downloads/jpg.zip","-d","/home/oktarizka156/modul2",(char *)NULL};
                execv("/usr/bin/unzip",buat);}
            else{
                while(wait(&tanda)>0);
                anak=fork();
                if(anak==0){
                    char *buat[] = {"find","/home/oktarizka156/modul2/jpg/","-type","f","-exec","/bin/mv","-t","/home/oktarizka156/modul2/sedaap","{}",";",(char *)NULL};
                    execv("/usr/bin/find",buat);}
                else{
                    while(wait(&tanda)>0);
                    anak=fork();
                    if(anak == 0){
                        char *buat[] = {"find","/home/oktarizka156/modul2/jpg/","-mindepth","1","-type","d","-exec","/bin/mv","-t","/home/oktarizka156/modul2/indomie","{}",";",(char *)NULL};
                        execv("/usr/bin/find",buat);}
                    else{
                        while(wait(&tanda)>0);
                        anak=fork();
                        if(anak==0){
                            char *buat[] = {"find","/home/oktarizka156/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba1.txt","'\'",";",(char *)NULL};
                            execv("/usr/bin/find",buat);}
                        else{
                            while(wait(&tanda)>0);
                            sleep(3);
                            char *buat[] = {"find","/home/oktarizka156/modul2/indomie/","-mindepth","1","-type","d","-exec","touch","{}/coba2.txt","'\'",";",(char *)NULL};
                            execv("/usr/bin/find",buat);}
          }
        }
      } 
    }     
  }   
}
