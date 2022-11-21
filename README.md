# Lista de Sistemas Operacionais

Esse repostitório foi desenvolvido para a disciplina de Sistemas Operacionais, ministrada pelo professor [Dalcimar Casanova](https://github.com/dalcimar), na Universidade Tecnológica Federal do Paraná, campus Pato Branco

## Trabalhos

A seguir, estão os enunciados dos trabalhos desenvolvidos:
Os códigos não seguem à risca o enunciado, pois houve modificações por simplicidade ou para melhorar o debbuging.

### Trabalho 1

Escreva um programa que realiza tratamento de sinais POSIX. O programa deve:
1. Capturar os sinais SIGINT, SIGTSTP e SIGPIPE mudando suas operações para:
    - O sinal SIGING deve ser ignorado

    - Contar quantas vezes o sinal SIGTSTP é gerado pelo usuário

    - O SIGPIPE deve zera o contador do SIGTSTP

1. Utilize um for(EVER) para manter o processo vivo enquanto gera sinais

1. Gerar os seguintes sinais de teste

    - CTRL+C, no terminal (número indefinido)

    - SIGPIPE pelo comando kill no terminal

    - SIGTSTP a cada 10 segundo

1. Se o contador de SIGTSTP chegar a 12, o processo deve gerar um sinal a ele mesmo cuja ação default seja seu término

### Trabalho 2

Faça um programa em que três processos executam paralelamente as seguintes ações:

- Pai - Imprime os números de 1 a 50, com um intervalo de 2 segundos entre cada número.

    Após imprimir todos os números, imprime a frase “Processo pai vai morrer”.

- Filho1 - Imprime os números de 100 a 200, com um intervalo de 1 segundo entre cada número.

    Antes de imprimir os números, imprime a frase “Filho 1 foi criado”.

    Após imprimir todos os números, imprime a frase “Filho 1 vai morrer”.

- Filho 2 - Inicia apeas após o pai morrer, imprime os números de 51 a 99

Importante, em cada printf os processos devem imprimir o seu pid e o pid do seu pai.

### Trabalho 3

Faça um programa em 2 processos são iniciados utilizando fork cada um com as seguintes ações:

1. O filho 1 irá executar cálculo 2*3, e retornar ao pai, via exit() o resultado da equação (utilize exec() para fazer isso)

1. O filho 2 irá entrar em looping infinito

1. O pai, após receber o resultado do filho 1, irá terminar o looping infinito do filho 2. Para isso o pai deve enviar um sinal ao filho 2, esse deve capturar e mudar o valor de iteração do while() ou for())

1. Agora com o filho 2 acordado, o pai deve imprimir o resultado

1. Filho 2 deve virar zoobies

### Trabalho 4

Faca um programa que imprima os nros primos existentes entre 0 e 99999, o programa deve dividir o espaço de cálculo uniformemente entre as N threads da forma que vc achar mais efetivo do ponto de vista computacional, e.x. 1bilhão de termos com 2 threads = 500milhões de termos em cada thread;

- Cada thread efetua uma soma parcial de forma autônoma;

- Para evitar o uso de mecanismos de sincronização, cada thread T[i] deve depositar seu resultado parcial na posição result[i] de um vetor de resultados parciais.

- Após o término das threads de cálculo, o programa principal soma os números primos encontrados

- Execute as soluções com N = {1, 2, 4, 8 e 16} threads

- Marque o tempo necessário para calcular Pi para cada N e faça um gráﬁco de linhas (NxTempo) apresentado os resultados.

Os 2 que conseguirem o melhor resultado de tempo ganharão 1 ponto extra na prova 1

### Trabalho 5

Uma tribo gaulesa janta em comunidade a par r de uma mesa enorme com espaço para M javalis grelhados. Quando um gaulês quer comer, serve-se e re ra um javali da mesa a menos que esta já esteja vazia. Nesse caso o gaulês acorda o cozinheiro e aguarda que este reponha javalis na mesa. O código seguinte representa o código que implementa o gaulês e o cozinheiro.

```
void Gaules(){

    while(true){
    Javali j = RetiraJavali();
    ComeJavali(j);
    }
}

void Cozinheiro(){

    while(true){
        ColocaJavalis(M);
    }
}
```

Implemente o código das funções RetiraJavali() e ColocaJavalis() incluindo código de sincronização que previna deadlock e acorde o cozinheiro apenas quando a mesa está vazia.

Lembre que existem muitos gauleses e apenas um cozinheiro.

Identiﬁque regiões críticas na vida do gaules e do cozinheiro.

A solução deve aceitar um numero N de gauleses igual ao número de letras de seu primeiro nome e 1 único cozinheiro.

Cada gaules terá um nome, dado pela letra correspondente 

– Ex: dalcimar = 8 gauleses

Cada gaules deve imprimir na tela seu nome (dado pela letra) quando come e quando acorda o cozinheiro.

– Ex: Gaules d(0) comendo

– Ex: Gaules a(1) acordou cozinheiro

A quantidade javalis grelhados M deve ser igual ao número dos dois primeiros dígitos de seu RA 

A solução não deve ter nenhum comentário

### Trabalho 6

Implemente o problema do Jantar de Gauleses usando shared memory 

- Pode usar funções da shmem (system V) ou mmap (POSIX), escolha livre. Recomendo padrão POSIX

- Deve, obrigatóriamente ter um executável, código fonte separado para o produtor e outro para o consumidor

- Os programas podem ser lançados em background (&) ou u lizando fork/exec

### Trabalho 7

Implemente o problema do Jantar de Gauleses usando MPI (família mpi_send) ou POSIX (famílio mk_send) escolha livre.

Recomendo padrão POSIX, pois foi a ensinada nos vídeos e está na vamente instalada. Para quem quiser usar MPI tem slides, e vc irá precisar instalar o pacote.

Deve, obrigatóriamente ter um único executável, código fonte o produtor e para o consumidor no mesmo arquivo

### Trabalho 8

Implemente o problema do Jantar de Gauleses usando pipes 

- Usar pipes ou named pipes

- Deve, obrigatóriamente ter um executável, código fonte separado para o produtor e outro para o consumidor

- Os programas podem ser lançados u lizando fork/exec

- Controlar o tamanho do buﬀer usando pipes é problemá, já que o pipe tem um tamanho ﬁxo dado pelo sistema operacional. Sugestões de solução para ‘emular’ um buﬀer usando pipes 

- Não fazer nada (terá um pequeno desconto na loja) 

- Descobrir o tamanho do pipe e mandar dados de tamanho correto. Ex, pipe 100kb total, buﬀer de 5 elementos, cada ‘write’ ou ‘read’ no pipe feito com 20kb (100/5)

- Utilizar um esquema de passagem de mensagens (consumidor envia 5 mensagens vazias para produtor)

Desenvolva uma estratégia para comunicar 1 produtor (cozinheiro) e N consumidores (gauleses). Sugestão: utlizar threads no processo gaules.