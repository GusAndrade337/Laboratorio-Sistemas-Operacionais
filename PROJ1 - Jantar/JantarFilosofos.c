#include<stdio.h> //Cabecalho para entrada/saida
#include<stdlib.h> //bilbioteca padrao para funções como exit()
#include<semaphore.h> //Cabecalho para criacao/administracao de semaforos
#include<pthread.h> //Cabecalho para criacao/uso de threads
#include <unistd.h> //acesso a API POSIX (Para uso de processos)

#define N 5 //Definir constante para numero de Filosofos
#define PENSAR 0 //Definir constante para estado do FIlosofo
#define FOME 1 //Definir constante para estado do FIlosofo
#define COMER 2 //Definir constante para estado do FIlosofo
#define ESQUERDA (filosofo_n+4)%N //Pegar garfo da esquerda
#define DIREITA (filosofo_n+1)%N //Pegar garfo da direita

//Declaração dos metodos e variáveis
void *filosofo(void *num);
void agarraGarfo(int);
void deixaGarfo(int);
void testar(int);
sem_t mutex; //Definição do Semaforo como um lock
sem_t S[N]; //inicializacao do semáforo
int estado[N]; //Criação do vetor para acomodar cada estado (PENSAR,FOME,COMER)
int filosofo_n[N]={0,1,2,3,4}; //Definição de cada filosofo


//Acesso a um filosofo
void *filosofo(void *num) {
    int j =0;
    while(j != 10)  { //Limita quantas vezes cada filosofo pode acessar a memoria
        int *i = num;
        agarraGarfo(*i);
        deixaGarfo(*i);
        j++;
    }
}

//Pega um garfo apos verificacao, e faz um post para o semaforo
void agarraGarfo(int filosofo_n) {
    sem_wait(&mutex);
    estado[filosofo_n] = FOME;
    printf("Filosofo %d esta com fome.\n",filosofo_n+1);//+1 para imprimir filosofo 1 e nao filosofo 0
    testar(filosofo_n);
    sem_post(&mutex);
    sem_wait(&S[filosofo_n]);
}
//Deixa um garfo apos verificacao, e faz um post para o semaforo
void deixaGarfo(int filosofo_n) {
    sem_wait(&mutex);
    estado[filosofo_n]=PENSAR;
    printf("Filosofo %d deixou os garfos %d e %d.\n",filosofo_n+1,ESQUERDA+1,filosofo_n+1);
    printf("Filosofo %d esta pensando.\n",filosofo_n+1);
    sleep(rand() % 2);
    testar(ESQUERDA);
    testar(DIREITA);
    sem_post(&mutex);
}

void testar(int filosofo_n) {
    if(estado[filosofo_n]==FOME && estado[ESQUERDA]!=COMER && estado[DIREITA]!=COMER)  {
    estado[filosofo_n]=COMER;
    printf("Filosofo %d agarrou os garfos %d e %d.\n",filosofo_n+1,ESQUERDA+1,filosofo_n+1);
    printf("Filosofo %d esta comendo.\n",filosofo_n+1);
    sem_post(&S[filosofo_n]);
    sleep(rand() % 2);
    }
}

int main() {


    int i;
    pthread_t thread_id[N];  //identificadores das threads
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
    sem_init(&S[i],0,0);
    for(i=0;i<N;i++)  {
        pthread_create(&thread_id[i],NULL,filosofo,&filosofo_n[i]); //criar as threads
        printf("Filosofo %d chegou.\n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL); //para fazer a junção das threads


       return(0);
}
