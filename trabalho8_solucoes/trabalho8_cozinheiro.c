#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_HOGS 21
#define TIME_SLEEP 4

// Struct para guardar o numero de javalis na mesa
typedef struct pipe1_t{
    int num_hogs;
}pipe1_t;

// Struct para indicar quando é necessário rodar o cozinheiro
typedef struct pipe2_t{
    char controle;
} pipe2_t;

pipe1_t hogs_on_table;
pipe2_t table;

int fd[2];

void ini_pipe(){
    // Inicia o pipe
    mkfifo("take", 0666);
    mkfifo("put", 0666);

    fd[0] = open("take", O_RDONLY);
    fd[1] = open("put", O_WRONLY);
}

void ini_cooker(){
    // Inicia a mesa com os javalis e envia para o pipe
    hogs_on_table.num_hogs = MAX_HOGS;
    printf("Cozinheiro iniciou a mesa com %d javalis\n", hogs_on_table.num_hogs);
    write(fd[1], &hogs_on_table, sizeof(pipe1_t));
}

void cooker(){
    while(1){
        // Quando receber uma mensagem no pipe de controle, começa a rodar o processo
        read(fd[0], &table, sizeof(pipe2_t));
        // Se a mensagem for P, ele coloca os javalis na mesa
        if (table.controle == 'P'){
            hogs_on_table.num_hogs = MAX_HOGS;
            sleep(TIME_SLEEP);
            printf("Cozinheiro colocou %d javalis na mesa\n", hogs_on_table.num_hogs);
        }

        // Se a mensagem for T, ele diminui o número de javalis na mesa
        else if(table.controle == 'T'){
            hogs_on_table.num_hogs--;
        }

        // Atualiza o número de javalis na mesa pelo pipe
        write(fd[1], &hogs_on_table, sizeof(pipe1_t));
    }
}

int main(){
    ini_pipe();
    ini_cooker();
    cooker();
}
