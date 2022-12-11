#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <mqueue.h>
#include <sys/stat.h>

#define MAX_HOGS 21
#define TIME_COOK 4

typedef struct messbuf {
    int hogs_on_table;
}messbuf_t;

messbuf_t w, t;
messbuf_t *wake_up = &w, *take = &t;
mqd_t fd[2];
struct mq_attr attr;

void ini_mqd(){
    attr.mq_maxmsg = 1;
	attr.mq_msgsize = sizeof(messbuf_t);
	attr.mq_flags = 0;

    mq_unlink("/t");
    mq_unlink("/w");

    fd[1] = mq_open("/t", O_RDWR|O_CREAT, 0666, &attr);
    fd[0] = mq_open("/w", O_RDWR|O_CREAT, 0666, &attr);
}

void ini_cooker(){
    printf("\nCozinhando %d javalis\n", MAX_HOGS);
    take->hogs_on_table = MAX_HOGS;
    mq_send(fd[1], (void*)take, sizeof(messbuf_t), 0);
}

void cooker(){
    mq_receive(fd[0], (void*)wake_up, sizeof(messbuf_t), 0);

        if(wake_up->hogs_on_table == 1)
        {
            printf("\nCozinhando %d javalis\n", MAX_HOGS);
            mq_send(fd[1], (void*)take, sizeof(messbuf_t), 0);
            wake_up->hogs_on_table = 0;
        }
}

int main()
{
	// inicia a fila de mensagens e o cozinheiro
    ini_mqd();
    ini_cooker();
    
    // loop infinito para cozinhar
    while(1)
        cooker();
}