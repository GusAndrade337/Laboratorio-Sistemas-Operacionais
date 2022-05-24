//Avaliar se necessario compilar com -lpthread -lrt ou se é possível usar -pthread
#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <semaphore.h>

//Primeira tentativa de resolução: Semaforos

// 64kB stack (tamanho máximo da pilha de execução(?))
#define FIBER_STACK 1024*64

struct c {
    int saldo;
};

typedef struct c conta;
conta from, to;
int valor;

// The child thread will execute this function
int transferencia(void *arg)
{
    if (from.saldo >= valor){ // 2
		sem_wait(Semaforo) // Coloca o semaforo imediatamente como wait. Impede que outros processos facam uso do recurso (lock)
        from.saldo -= valor;
        to.saldo += valor;
		sem_post(Semaforo) // Coloca o semaforo imediatamente como livre, o recurso pode ser acessado novamente
	}
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    return 0;
	else (
	printf("Não há dinheiro suficiente para realizar a transação\nValor Solicitado: %d",valor);
    printf("Saldo de c1: %d\n", from.saldo);

}
// Para fazer uso do semáforo, eh necessário cria-lo externamente a qualquer função
sem_t Semaforo

int main()
{
    void* stack;
    pid_t pid;
    int i;
    // Allocate the stack
    stack = malloc( FIBER_STACK );
    if ( stack == 0 )
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }
    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    printf( "Transferindo 10 para a conta c2\n" );
    valor = 10;
    for (i = 0; i < 10; i++) {
        // Call the clone system call to create the child thread
        pid = clone( &transferencia, (char*) stack + FIBER_STACK,
        SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
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
}
