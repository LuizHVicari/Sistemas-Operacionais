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
#define N 16

int *soma;

// verifica se o número é primo
int is_prime(int num){
    int i;
    for(i = 2; i <= sqrt(num); i++)
        if(num % i == 0)
            return 0;
    return 1;
}

// cada função calcula os números primos do intervalo correspondente
void *prime_2_6250(){
    int i;
    for(i = 2; i <= 6250; i++)
        if(is_prime(i))
            soma[0] += i;
    pthread_exit(NULL);
}

void *prime_6251_12500(){
    int i;
    for(i = 6251; i <= 12500; i++)
        if(is_prime(i))
            soma[1] += i;
    pthread_exit(NULL);
}

void *prime_12501_18750(){
    int i;
    for(i = 12501; i <= 18750; i++)
        if(is_prime(i))
            soma[2] += i;
    pthread_exit(NULL);
}

void *prime_18751_25000(){
    int i;
    for(i = 18751; i <= 25000; i++)
        if(is_prime(i))
            soma[3] += i;
    pthread_exit(NULL);
}

void *prime_25001_31250(){
    int i;
    for(i = 25001; i <= 31250; i++)
        if(is_prime(i))
            soma[4] += i;
    pthread_exit(NULL);
}

void *prime_31251_37500(){
    int i;
    for(i = 31251; i <= 37500; i++)
        if(is_prime(i))
            soma[5] += i;
    pthread_exit(NULL);
}

void *prime_37501_43750(){
    int i;
    for(i = 37501; i <= 43750; i++)
        if(is_prime(i))
            soma[6] += i;
    pthread_exit(NULL);
}

void *prime_43751_50000(){
    int i;
    for(i = 43751; i <= 50000; i++)
        if(is_prime(i))
            soma[7] += i;
    pthread_exit(NULL);
}

void *prime_50001_56250(){
    int i;
    for(i = 50001; i <= 56250; i++)
        if(is_prime(i))
            soma[8] += i;
    pthread_exit(NULL);
}

void *prime_56251_62500(){
    int i;
    for(i = 56251; i <= 62500; i++)
        if(is_prime(i))
            soma[9] += i;
    pthread_exit(NULL);
}

void *prime_62501_68750(){
    int i;
    for(i = 62501; i <= 68750; i++)
        if(is_prime(i))
            soma[10] += i;
    pthread_exit(NULL);
}

void *prime_68751_75000(){
    int i;
    for(i = 68751; i <= 75000; i++)
        if(is_prime(i))
            soma[11] += i;
    pthread_exit(NULL);
}

void *prime_75001_81250(){
    int i;
    for(i = 75001; i <= 81250; i++)
        if(is_prime(i))
            soma[12] += i;
    pthread_exit(NULL);
}

void *prime_81251_87500(){
    int i;
    for(i = 81251; i <= 87500; i++)
        if(is_prime(i))
            soma[13] += i;
    pthread_exit(NULL);
}

void *prime_87501_93750(){
    int i;
    for(i = 87501; i <= 93750; i++)
        if(is_prime(i))
            soma[14] += i;
    pthread_exit(NULL);
}

void *prime_93751_100000(){
    int i;
    for(i = 93751; i < 100000; i++)
        if(is_prime(i))
            soma[15] += i;
    pthread_exit(NULL);
}

int main(void *arg){
    soma = (int *) calloc(16, sizeof(int));
    pthread_t threads[N];
    // cada variável armazena uma thread
    int i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;

    // cria as threads para calcular os primos
    i = pthread_create(&threads[0], NULL, prime_2_6250, NULL);
    j = pthread_create(&threads[1], NULL, prime_6251_12500, NULL);
    k = pthread_create(&threads[2], NULL, prime_12501_18750, NULL);
    l = pthread_create(&threads[3], NULL, prime_18751_25000, NULL);
    m = pthread_create(&threads[4], NULL, prime_25001_31250, NULL);
    n = pthread_create(&threads[5], NULL, prime_31251_37500, NULL);
    o = pthread_create(&threads[6], NULL, prime_37501_43750, NULL);
    p = pthread_create(&threads[7], NULL, prime_43751_50000, NULL);
    q = pthread_create(&threads[8], NULL, prime_50001_56250, NULL);
    r = pthread_create(&threads[9], NULL, prime_56251_62500, NULL);
    s = pthread_create(&threads[10], NULL, prime_62501_68750, NULL);
    t = pthread_create(&threads[11], NULL, prime_68751_75000, NULL);
    u = pthread_create(&threads[12], NULL, prime_75001_81250, NULL);
    v = pthread_create(&threads[13], NULL, prime_81251_87500, NULL);
    w = pthread_create(&threads[14], NULL, prime_87501_93750, NULL);
    x = pthread_create(&threads[15], NULL, prime_93751_100000, NULL);

    // espera as threads terminarem
    for(y = 0; y < N; y++)
        pthread_join(threads[y], NULL);


    // verifica as posições do vetor que são primos e soma elas
    int soma_primos = 0;
    for(i = 0; i < 16; i++)
        soma_primos += soma[i];
        

    printf("Soma dos primos: %d", soma_primos);
}