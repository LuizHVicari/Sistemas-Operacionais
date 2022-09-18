#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#define EVER ;;

int mult_result = 0;
int universal_while_handler = 1;

void sig6_handler(int sig){
    mult_result = sig;
    universal_while_handler = 0;
}

int main (void){
    pid_t child1 = 0, child2 = 0, num;
    int status1, s;
    
    // creates the first child
    child1 = fork();

    // father enters here
    if (child1 > 0){
        // creates the second child
        child2 = fork();
        
        if (child2 > 0){
            // stops the father until the first child is done
            num = wait(&status1);
            mult_result = WEXITSTATUS(status1);
            
            // sends a signal to the second child 
            kill(child2, mult_result);

            //TODO confirmar se isso torna um processo em zumbi
            while(1);
        }

        else if(child2 == 0){
            // handles the signal sent from the father to stop the while
            signal(6, sig6_handler);
            while(universal_while_handler);

            // prints the result from the exec on trabalho3_mult
            printf("2 * 3 == %d", mult_result); 
        }
        // enters here if it wasn't able to create the second child
        else
            exit(0);
    }

    // first child enters here
    else if (child1 == 0){
        // changes the child to the program trabalho3_mult
        execl("trabalho3_mult", "trabalho3_mult", NULL);
    }

    // enters here if it wasn't able to create the first child
    else
        exit(0);
}