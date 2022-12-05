#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <signal.h>

#define NUM_SAVAGE 4
#define TIME_EAT 1

char name[4] = "LUIZ";

typedef struct shmbuf{
    int hogs_on_table;
    // semáforo para poder ir na mesa pegar javalis
    sem_t take_hog;
    // semáforo para acordar o cozinheiro
    sem_t cook;
    // semáforo para avisar que o cozinheiro terminou de preparar javalis
    sem_t ready;
}shm_t;

shm_t *shared_mem;


void ini_shm(){
    int fd = shm_open("/trabalho_6_smh", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    ftruncate(fd, sizeof(shm_t));
    shared_mem = mmap(NULL, sizeof(shm_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
}

void take_hog(long gaules){
    // verifica se tem javalis na mesa
    if(shared_mem->hogs_on_table > 0){
        // come os javalis
        shared_mem->hogs_on_table--;
        printf("Selvagem %c (%ld) comeu um javali, javali na mesa: %d\n", name[gaules], gaules, shared_mem->hogs_on_table);
    }
    else{
        // se não tiver javalis na mesa, acorda o cozinheiro
        sem_post(&shared_mem->cook);
        printf("Acabaram os javalis, selvagem %c (%ld) acordou o cozinheiro.\n", name[gaules], gaules);
        sem_wait(&shared_mem->ready);
    }
}

void *savage(void *num_savage){
    long savage = (int)num_savage;
    while(1){
        // espera para poder ir na mesa pegar javalis
        sem_wait(&shared_mem->take_hog);
        // pega o javali e libera para outro poder pegar
        take_hog(savage);
        sem_post(&shared_mem->take_hog);
        // tempo para comer
        sleep(TIME_EAT);
    }
    pthread_exit(NULL);
}

int main(){
    // inicia a memória compartilhada
    ini_shm();
    // cria as trheads
    pthread_t savages[NUM_SAVAGE];
    for(int i = 0; i < NUM_SAVAGE; i++)
        pthread_create(&savages[i], NULL, savage, (void*)i);

    // fehca as threads
    for(int i = 0; i < NUM_SAVAGE; i++)
        pthread_join(savages[i], NULL);
    pthread_exit(NULL);
}

