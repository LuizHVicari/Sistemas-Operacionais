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
#define N 2

int prime[100000];

int is_prime(int num){
    int i;
    for(i = 2; i <= sqrt(num); i++)
        if(num % i == 0)
            return 0;
    return 1;
}

void *prime_2_50000(){
    int i;
    for(i = 2; i <= 50000; i++)
        if(is_prime(i))
            prime[i] = 1;
    pthread_exit(NULL);
}

void *prime_50001_100000(){
    int i;
    for(i = 50001; i <= 100000; i++)
        if(is_prime(i))
            prime[i] = 1;
    pthread_exit(NULL);
}

int main(void *arg){
    int soma = 0;
    pthread_t threads[N];
    int i, j, y, z;

    i = pthread_create(&threads[0], NULL, prime_2_50000, NULL);
    j = pthread_create(&threads[1], NULL, prime_50001_100000, NULL);

    for(y = 0; y < N; y++)
        pthread_join(threads[y], NULL);

    for (z = 0; z < 100000; z++)
        if(prime[z])
            soma+=z;

    printf("Soma dos primos: %d", soma);
}