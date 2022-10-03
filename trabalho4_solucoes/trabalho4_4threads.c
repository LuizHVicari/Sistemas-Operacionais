// Faca um programa que imprima os nros primos existentes entre 0 e 99999.
// O programa deve dividir o espaço de cálculo uniformemente entre as N threads da forma que vc achar mais efetivo do ponto de vista computacional.
// e.x. 1bilhão de termos com 2 threads = 500milhões de termos em cada thread;
// cada thread efetua uma soma parcial de forma autônoma;
// para evitar o uso de mecanismos de sincronização, cada thread T[i] deve depositar seu resultado parcial na posição result[i] de um vetor de resultados parciais.
// após o término das threads de cálculo, o programa principal soma os números primos encontrados
// execute as soluções com N = {1, 2, 4, 8 e 16} threads

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define N 4

int *soma;

int is_prime(int num){
    int i;
    for(i = 2; i <= sqrt(num); i++)
        if(num % i == 0)
            return 0;
    return 1;
}

void *prime_2_25000(){
    int i;
    for(i = 2; i <= 25000; i++)
        if(is_prime(i))
            soma[0] += i;
    pthread_exit(NULL);
}

void *prime_25001_50000(){
    int i;
    for(i = 25001; i <= 50000; i++)
        if(is_prime(i))
            soma[1] += i;
    pthread_exit(NULL);
}

void *prime_50001_75000(){
    int i;
    for(i = 50001; i <= 75000; i++)
        if(is_prime(i))
            soma[2] += i;
    pthread_exit(NULL);
}

void *prime_75001_100000(){
    int i;
    for(i = 75001; i <= 100000; i++)
        if(is_prime(i))
            soma[3] += i;
    pthread_exit(NULL);
}


int main(void *arg){
    soma = (int *) calloc(4, sizeof(int));
    
    pthread_t threads[N];
    int i, j, k, l, y, z;

    i = pthread_create(&threads[0], NULL, prime_2_25000, NULL);
    j = pthread_create(&threads[1], NULL, prime_25001_50000, NULL);
    k = pthread_create(&threads[2], NULL, prime_50001_75000, NULL);
    l = pthread_create(&threads[3], NULL, prime_75001_100000, NULL);

    for(y = 0; y < N; y++)
        pthread_join(threads[y], NULL);

    int soma_primos = 0;
    for(i = 0;i < N; i++){
        printf("%d ", soma[i]);
    }

    printf("Soma dos primos: %d", soma_primos);
}