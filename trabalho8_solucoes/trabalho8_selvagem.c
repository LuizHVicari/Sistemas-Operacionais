#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define NUM_SAVAGE 4
#define TIME_EAT 1

typedef struct pipe1_t{
    int num_hogs;
} pipe1_t;

typedef struct pipe2_t{
    char controle;
} pipe2_t;

pipe1_t hogs_on_table;
pipe2_t table;
sem_t sem_selvagem;

int fd[2];


char nome[4] = "Luiz";

void ini_pipe(){
    mkfifo("take", 0666);
    mkfifo("put", 0666);
    
    fd[0] = open("take", O_WRONLY);
    fd[1] = open("put", O_RDONLY);
}

void take_hog(int id){
    // Lê quantos javalis tem na mesa
    read(fd[1], &hogs_on_table, sizeof(pipe1_t));
    // Se tem pelo menos um, envia pipe dizendo que comeu o javali
    if (hogs_on_table.num_hogs > 0) {
        table.controle = 'T';
        printf("Selvagem %c(%d) comeu um javali, ainda restam %d javalis na mesa\n", nome[id], id, hogs_on_table.num_hogs - 1);
        write(fd[0], &table, sizeof(pipe2_t));
    }
    // Se a mesa está vazia, envia pipe para pedir para encher a mesa
    else if (hogs_on_table.num_hogs == 0){
        printf("Selvagem %c(%d) acordou o cozinheiro\n", nome[id], id);
        table.controle = 'P';
        write(fd[0], &table, sizeof(pipe2_t));
    }
}

void *savage(void *id){
    int selvagem_num = (int)id;
    while(1){
        // Vê se é possível comer e come
        // Se o arquivo de pipe não existe inicialmente, não precisa de semáforos
        sem_wait(&sem_selvagem);
        take_hog(selvagem_num);
        sem_post(&sem_selvagem);
        sleep(TIME_EAT);
    }
}

int main(){
    ini_pipe();
    sem_init(&sem_selvagem, 0, 1);

    pthread_t savages[NUM_SAVAGE];

    for(int i=0; i<NUM_SAVAGE; i++){
        pthread_create(&savages[i], NULL, savage, (void*)i);
    }

    for(int i=0; i<NUM_SAVAGE; i++){
        pthread_join(savages[i], NULL);
    }

    pthread_exit(NULL);
}
