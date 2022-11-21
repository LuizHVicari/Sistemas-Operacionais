#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX_HOGS 21
#define TIME_COOK 5

typedef struct shmbuf{
    int hogs_on_table;
    sem_t take_hog;
    sem_t cook;
    sem_t ready;
}shm_t;

shm_t *shared_mem;

void set_shm(){
    // inicia os semáforos
    sem_init(&shared_mem->take_hog, 1, 1);
    sem_init(&shared_mem->cook, 1, 0);
    sem_init(&shared_mem->ready, 1, 0);

    // Prepara os javalis
    shared_mem->hogs_on_table = MAX_HOGS;
    printf("Memória compartilhada inicializada.\n");
}

void ini_shm(){
    int fd = shm_open("/trabalho_6_smh", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    ftruncate(fd, sizeof(shm_t));
    shared_mem = mmap(NULL, sizeof(shm_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
}

void *Cooker(){
    while(1){
        sem_wait(&shared_mem->cook);
        if(shared_mem->hogs_on_table == 0){
            printf("Cozinheiro preparando javalis.\n");
            shared_mem->hogs_on_table = MAX_HOGS;
            sleep(TIME_COOK);
            printf("Cozinheiro preparou %d javalis\n", shared_mem->hogs_on_table);
        }
        else
            printf("Erro de sincronização: cozinheiro acordado sem necessidade\n");
        sem_post(&shared_mem->ready);   
    }
    pthread_exit(NULL);
}

int main(){
    ini_shm();
    set_shm();
    pthread_t cooker;

    pthread_create(&cooker, NULL, Cooker, NULL);
    pthread_join(cooker, NULL);

    return 0;
}

