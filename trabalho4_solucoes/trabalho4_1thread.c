#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

int soma = 0;

int is_prime(int num){
    int i;
    for(i = 2; i <= sqrt(num); i++){
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}

void primes_1_100000(){
    int i;
    for(i = 2; i <= 100000; i++)
        if(is_prime(i))
            soma += i;
}

int main(void){
    primes_1_100000();
    printf("Soma: %d", soma);
}