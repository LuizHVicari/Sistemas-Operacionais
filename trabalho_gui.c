#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define N_JAVALIS_GRELHADOS 15
#define N_GAULESES 8
#define N_COZINHEIROS 1

sem_t mutex, cozinhar, cheio; 
int contador = 0;

char nome[N_GAULESES] = "GUILHERME";

void inicializaSemaforos()
{
    sem_init(&mutex, 0, 1);
    sem_init(&cozinhar, 0, 0);
    sem_init(&cheio, 0, 0);
}

void ColocaJavali()
{
    sem_wait(&cozinhar); //mantem o cozinheiro em espera
    //sleep(8); //tempo para cozinhar quantidade x de javalis
    printf("\nCozinhando %d javalis\n",N_JAVALIS_GRELHADOS);
    contador = N_JAVALIS_GRELHADOS; //repoe os javalis
    sem_post(&cheio); //vai liberar os gauleses
}

void ComeJavali(long g)
{
    printf("Gaules %c(%ld) comendo\tJavalis restantes: %d\n",nome[g],g,contador);
    //sleep(3);
}

void RetiraJavali(long g)
{
    sem_wait(&mutex); // trava essa regiao pra ninguem mais ter acesso

    if(contador == 0)
    {
        sem_post(&cozinhar); //libera o cozinheiro
        printf("Guales %c(%ld) acordou o cozinheiro\t", nome[g],g);
        sem_wait(&cheio); //segura os gauleses para o coiznheiro cozinhar
    }
    contador--;

    ComeJavali(g);
    /*printf("Gaules %c(%ld) comendo\tJavalis restantes: %d\n",nome[g],g,contador);
    sleep(3);*/

    sem_post(&mutex);
}

void* Gaules(void* g)
{
    long aux = (long)g;

    while(1)
    {
        RetiraJavali(aux);
        //ComeJavali(aux);
        //sleep(2); //tempo para comer
    }
}

void* Cozinheiro(void* c)
{
    long aux = (long)c;

    while(1)
    {
        ColocaJavali();
    }
}

int main()
{
    long i = 0; 

    inicializaSemaforos();

    pthread_t gaules[N_GAULESES];
    pthread_t cozinheiro[N_COZINHEIROS];

    for(i = 0; i < N_COZINHEIROS; i++)
    {
        pthread_create(&cozinheiro[i], NULL, Cozinheiro, (void*)(i));
    }
    for(i = 0; i < N_GAULESES; i++)
    {
        pthread_create(&gaules[i], NULL, Gaules, (void*)(i));
    }

    while(1);
}