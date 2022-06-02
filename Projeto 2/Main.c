//g++ -pthread main.c -w  -o main && ./main
#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>


// Para fazer uso do semáforo, eh necessário cria-lo externamente a qualquer função
sem_t Semaforo;

// 64kB stack (tamanho máximo da pilha de execução(?))
#define FIBER_STACK 1024*64

struct c {
    int saldo;
};

typedef struct c conta;
conta from, to;
int valor;

// The child thread will execute this function
int transferencia(void *arg){
    if (from.saldo >= valor){ // 2
		sem_wait(&Semaforo); // Coloca o semaforo imediatamente como wait. Impede que outros processos facam uso do recurso (lock)
        from.saldo -= valor;
        to.saldo += valor;
		sem_post(&Semaforo); // Coloca o semaforo imediatamente como livre, o recurso pode ser acessado novamente
	}else if(to.saldo >= valor){
        sem_wait(&Semaforo);
        to.saldo -= valor;
        from.saldo += valor;
        sem_post(&Semaforo);
    }
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    return 0;
  }


int main()
{
    void* stack;
    int Nu_Threads;
    printf("Digite o Número de Threads (transferências): ");
    scanf("%d", &Nu_Threads);
    int Vetor_thread_pid[Nu_Threads]; //Criado um vetor para armazenar os IDs de cada thread individualmente, para poder fazer uso do waitpid (wait, mas sofisticado)
    int i;
    int status; //variável para notificar que a thread foi encerrada
    sem_init(&Semaforo, 0, 1); //iniciando o semaforo

    // Allocate the stack
    stack = malloc( FIBER_STACK );
    if ( stack == 0 )
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }
    // Todas as contas começam com saldo 100
    from.saldo = 1000;
    to.saldo = 0;

    valor = 10;
    for (i = 0; i < Nu_Threads; i++) {
        // Call the clone system call to create the child thread
        Vetor_thread_pid[i] = clone( &transferencia, (char*) stack + FIBER_STACK, SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
        printf( "\nTransferindo 10 para a conta c2\n" );
        pid_t pid = waitpid(Vetor_thread_pid[i], &status, 0);
        if ( pid == -1 )
        {
            perror( "clone" );
            exit(2);
        }
    }
    // Free the stack
    free( stack );
    printf("Transferências concluídas e memória liberada.\n");
    return 0;
};
