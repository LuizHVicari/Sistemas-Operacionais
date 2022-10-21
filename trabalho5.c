#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QTDE_SELVAGENS 4
#define TAMANHO_MESA 21
#define TEMPO_COMER 1
#define TEMPO_COZINHAR 4

sem_t take_hog;
sem_t cooking;

int hogs_on_table = 21;

void cooker(void*name){
        // O cozinheiro é acordado pelo selvagem
    printf("Selvagem %s acordou o cozinheiro\n", (char*)name);
    if(hogs_on_table == 0){
         // O cozinheiro prepara os porcos
        // Acredito que esse semáforo não seja necessário
        sem_wait(&cooking);
        sleep(TEMPO_COZINHAR);
        hogs_on_table = 21;
        // Depois do porco estar pronto, o cozinheiro libera o semáforo
        sem_post(&cooking);
    }
    else
         // Se alguém chamar o cozinheiro enquanto ainda houver porcos, tem algo errado
        printf("Ainda tem porcos na mesa, o selvagem %s foi inconveniente\n", (char*)name);
}

void *savage(void *name){
    int i;
    // Os selvagens comem 100 vezes cada 1

    while(i < 100){
        // O selvagem tenta pegar um porco, se alguém estiver comendo, o selvagem espera
        sem_wait(&take_hog);
        if(hogs_on_table > 0){
            // Diminui o número de porcos na mesa
            hogs_on_table--;
            printf("Selvagem %s pegou um porco, porcos na mesa: %d\n", (char*)name, hogs_on_table);
            // Depois que se servir, libera para outros selvagens comerem
            sem_post(&take_hog);
            // O selvagem come
            sleep(TEMPO_COMER);
        }
        else{
            // Se o slevagem for se servir e não houver porcos, ele acorda o cozinheiro
           cooker(name);
           // Após o cozinheiro termianr, ele serve os porocos, a verificação é só para debug se algo deu errado
            if(hogs_on_table > 0){
                // Diminui o número de porcos na mesa
                hogs_on_table--;
                printf("Selvagem %s pegou um porco, porcos na mesa: %d\n", (char*)name, hogs_on_table);
                // Depois que se servir, libera para outros selvagens comerem
                sem_post(&take_hog);
                // O selvagem come
                sleep(TEMPO_COMER);
            }
            else
                // Apenas para debug
                printf("Não tem porcos na mesa, algo deu errado\n");
        }
        i++;
    }
    
}

int main(void){
    pthread_t selvagens[QTDE_SELVAGENS + 1];
    int threads[QTDE_SELVAGENS + 1];
    sem_init(&take_hog, 0, 1);
    sem_init(&cooking, 0, 1);

    threads[0] = pthread_create(&selvagens[0], NULL, savage, "Esse nao faz nada");
    threads[1] = pthread_create(&selvagens[1], NULL, savage, "L(1)");
    threads[2] = pthread_create(&selvagens[2], NULL, savage, "U(2)");
    threads[3] = pthread_create(&selvagens[3], NULL, savage, "I(3)");
    threads[4] = pthread_create(&selvagens[4], NULL, savage, "Z(4)");

    for(int i = 0; i < QTDE_SELVAGENS; i++)
        pthread_join(selvagens[i], NULL);

    return 0;
}

