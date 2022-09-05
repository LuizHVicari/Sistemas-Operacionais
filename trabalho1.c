#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#define EVER ;;

int contador_sigtstp = 0;
// verificador se já há um alarme setado
int alarm_set = 0;

// envia um SIGTSTP e valida para um novo alarme
void sigalarm_handler(int sig){
    kill(getpid(), SIGTSTP);
    alarm_set = 0;
}

void sigint_handler(int sig){
    printf("Ignorando o sinal SIGINT\n");
}

// conta quantas vezes o programa recebeu um SIGTSTP, se chegar em 12, encerra o programa
void sigtstp_handler(int sig){
    contador_sigtstp++;
    printf("Sinal SIGTSTP pressionado %d vezes\n", contador_sigtstp);
    if(contador_sigtstp == 12){
        kill(getpid(), SIGKILL);
    }
}

// zera o contador de SIGTSTP
void sigpipe_handler(int sig){
    contador_sigtstp = 0;
    printf("Contador do SIGTSTP zerada\n");
}

int main (void){
    int timer;
    // imprime o número do programa
    printf("pid: %d\n", getpid());

    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    signal(SIGPIPE, sigpipe_handler);
    signal(SIGALRM, sigalarm_handler);

    printf("Informe o tempo de delay para o SIGALARM: ");
    scanf("%d", &timer);
    
    // mantém o programa funcionando cria um alarm de 10 segundos para enviar um SIGTSTP automaticamente
    for(EVER){
        if(alarm_set == 0){
            alarm(timer); // tempo para o sigalarm reduzido para teste
            alarm_set = 1;
        }
    }
}
