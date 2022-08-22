#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#define EVER ;;

int contador_sigtstp = 0;
int alarm_set = 0;

void sigalarm_handler(int sig){
    kill(getpid(), SIGTSTP);
    alarm_set = 0;
}

void sigint_handler(int sig){
    printf("Ignorando o sinal SIGINT\n");
}

void sigtstp_handler(int sig){
    contador_sigtstp++;
    printf("Sinal SIGTSTP pressionado %d vezes\n", contador_sigtstp);
    if(contador_sigtstp == 12){
        kill(getpid(), SIGKILL);
    }
}

void sigpipe_handler(int sig){
    contador_sigtstp = 0;
    printf("Contador do SIGTSTP zerada\n");
}

int main (void){
    printf("pid: %d\n", getpid());
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGPIPE, sigpipe_handler);
    signal(SIGALRM, sigalarm_handler);
    
    for(EVER){
        //printf("pid=%d\n",getpid());
        if(alarm_set == 0){
            alarm(10);
            alarm_set = 1;
        }
    }
}
