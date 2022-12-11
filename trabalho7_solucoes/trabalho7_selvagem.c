/*Implemente o problema do Jantar de Gauleses usando MPI (família mpi_send) ou 
POSIX (famílio mk_send) escolha livre.

Recomendo padrão POSIX, pois foi a ensinada nos vídeos e está na vamente instalada. 
Para quem quiser usar MPI tem slides, e vc irá precisar instalar o pacote.

Deve, obrigatóriamente ter um único executável, código fonte o produtor e 
para o consumidor no mesmo arquivo*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <mqueue.h>
#include <sys/stat.h>

#define MAX_HOGS 21
#define NUM_SAVAGE 4
#define TIME_EAT 1

typedef struct messbuf {
    int hogs_on_table;
}messbuf_t;

struct mq_attr attr; 
int javalis;
char name[NUM_SAVAGE] = "Luiz";

messbuf_t w, t; 
messbuf_t *wake_up = &w, *take = &t;
mqd_t fd[2];
sem_t sem_1;

void ini_mqd(){
    attr.mq_maxmsg = 1; // capacidade para 1 mensagem
	attr.mq_msgsize = sizeof(messbuf_t);  // tamanho de cada mensagem
	attr.mq_flags = 0;

	fd[1] = mq_open("/t", O_RDWR); // abre ou cria a fila com permissoes 0666
	fd[0] = mq_open("/w", O_RDWR); // abre ou cria a fila com permissoes 0666
}

void take_hog(long g)
{
    if(take->hogs_on_table == 0)
    {
        printf("Selvagem %c(%ld) acordou o cozinheiro\n", name[g], g);
        // envia uma mensagem para o cozinheiro preparar os javalis e espera a resposta
        mq_send(fd[0], (void*)wake_up, sizeof(messbuf_t), 0);
		mq_receive(fd[1], (void*)take, sizeof(messbuf_t), 0);
    }

    if(take->hogs_on_table)
    {
        // come os javalis
        take->hogs_on_table--;
        printf("Selvagem %c(%ld) comeu um javali, javalis na mesa: %d\n", name[g], g, take->hogs_on_table);
    }
}

void *selvagens(void *id)
{
    long num = (long)id;

    while(1)
    {
        // espera os outros na fila se servirem, se serve e libera o semáforo
        sem_wait(&sem_1);
        take_hog(num);
        sem_post(&sem_1);

        sleep(TIME_EAT);
    }
    exit(0);
}

int main()
{
    // inicia a fila de mensagens e o semáforo para coordenar os selvagens
    ini_mqd();
    sem_init(&sem_1, 0, 1);

    javalis = MAX_HOGS;

    pthread_t selvagem[NUM_SAVAGE];
    wake_up->hogs_on_table = 1;

    // espera o cozinheiro ter sido iniciado
    mq_receive(fd[1], (void*)take, sizeof(messbuf_t), 0);
    
    // inicia os selvagens
    for(int i = 0; i < NUM_SAVAGE; i++)
        pthread_create(&selvagem[i], NULL, selvagens,(void*)i);

    // encerra os selvagens
    for(int i = 0; i < NUM_SAVAGE; i++)
        pthread_join(selvagem[i], NULL);

    exit(0);
}