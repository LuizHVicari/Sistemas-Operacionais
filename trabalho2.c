#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#define EVER ;;

// Faça um programa em que três processos executam paralelamente as seguintes ações:
// Pai - Imprime os números de 1 a 50, com um intervalo de 2 segundos entre cada número.
// Após imprimir todos os números, imprime a frase “Processo pai vai morrer”.
// Filho1 - Imprime os números de 100 a 200, com um intervalo de 1 segundo entre cada número.
// Antes de imprimir os números, imprime a frase “Filho 1 foi criado”.
// Após imprimir todos os números, imprime a frase “Filho 1 vai morrer”.
// Filho 2 - Inicia apeas após o pai morrer, imprime os números de 51 a 99
// • Importante, em cada printf os processos devem imprimir o seu pid e o pid do seu pai.

int main (void){
    pid_t child1 = 0, child2 = 0;
    
    // creates the first child
    child1 = fork();

    // father enters here
    if (child1 > 0){
        // creates the second child
        child2 = fork();

        // father enters here
        if (child2 > 0){
            for(int i = 0; i <= 50; i++){
                //TODO change the sleep to a SIGALARM handler
                // sleep(2);
                printf("\nSou o pai, meu pai e %d, meu pid é %d e estou na iteracao %d", getppid(), getpid(), i);
            }

            printf("\nProcesso pai vai morrer");
            exit(0);
        }

        // second child enters here
        else if (child2 == 0){
            printf("\nFilho 2 foi criado");
            
            pid_t pai =  getppid();

            // waits untill getppid returns it's grandfather's pid
            while(getppid() == pai);

            for(int i = 50; i < 100; i++)
                printf("\nSou o filho 2, meu pai e %d, meu pid é %d e estou na iteracao %d", getppid(), getpid(), i);
            
            printf("\nFilho 2 vai morrer");
            exit(0);
        }

        // enters here if it wasn't able to create the second child
        else
            printf("\nNão foi possível criar o filho 2");
            exit(0);
    }

    // first child enters here
    else if (child1 == 0){
        printf("\nFilho 1 foi criado");

        for(int i = 100; i <= 200; i++)
            printf("\nSou o filho 1, meu pai é %d, meu pid e %d e estou na iteracao %d", getppid(), getpid(), i);
        
        printf("\nFilho 1 vai morrer");
        exit(0);
    }

    // enters here if it wasn't able to create the first child
    else
        printf("\nNão foi possível criar o filho 1");
        exit(0);
}