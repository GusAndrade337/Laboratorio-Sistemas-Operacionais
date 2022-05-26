//g++ -pthread main.c -o main && ./main
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

//https://stackoverflow.com/questions/23250863/difference-between-pthread-and-lpthread-while-compiling
//https://www.geeksforgeeks.org/use-posix-semaphores-c/
//Primeira tentativa de resolução: Semaforos

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
	}else{
	printf("Não há dinheiro suficiente para realizar a transação\nValor Solicitado: %d",valor);
    printf("\nSaldo de c1: %d\n", from.saldo);
    return -1;
}
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    return 0;
  }


int main()
{
    void* stack;
    int Vetor_thread_pid[100]; //Criado um vetor para armazenar os IDs de cada thread individualmente, para poder fazer uso do waitpid (wait, mas sofisticado)
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
    from.saldo = 10;
    to.saldo = 100;
    printf( "Transferindo 10 para a conta c2\n" );
    valor = 1;
    for (i = 0; i < 100; i++) {
        // Call the clone system call to create the child thread
        Vetor_thread_pid[i] = clone( &transferencia, (char*) stack + FIBER_STACK,
        SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
        printf("\nId da thread criada: %d\n",Vetor_thread_pid[i]);
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
