#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define N 5
#define LEFT (phil+N-1)%N
#define RIGHT (phil+1)%N
#define THINKING 2
#define HUNGRY 1
#define EATING 0

int state[N];
int number[N]={0,1,2,3,4};

sem_t mutex;
sem_t s[N];


void test(int phil){
    if(state[phil]==HUNGRY && state[LEFT] !=EATING && state[RIGHT] !=EATING){
        state[phil]==EATING;

        sleep(2);

        printf("Il filosofo %d prende la forchetta %d e %d\n",phil+1,LEFT+1,phil+1);
        printf("Il filosofo %d sta mangiando\n",phil+1);

        sem_post(&s[phil]);
    }
}



void take_forks(int phil){

    sem_wait(&mutex);

    state[phil]=HUNGRY;

    printf("Il filososo %d e' affamato\n",phil+1);
    test(phil);
    sem_post(&mutex);
    sem_wait(&s[phil]);

    sleep(1);

}



void put_fork(int phil){

    sem_wait(&mutex);

    state[phil]=THINKING;
    printf("Il filosofo %d posa le posate %d e %d\n",phil+1,LEFT+1,phil+1);
    printf("Il filosofo %d sta pensando\n",phil+1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);

}



void* philosopher(void* phil){

    while(1){
      int *i=phil;
      sleep(1);
      take_forks(*i);
      put_fork(*i);
      pthread_exit(NULL);
    }



}


int main(){

    int phil;
    pthread_t thread_p[N];

    sem_init(&mutex,0,1);

    for(phil=0; phil<N; phil++){
      sem_init(&s[phil],0,0);
    }

    for(phil=0; phil<N; phil++){
      pthread_create(&thread_p[phil],NULL,philosopher,&number[phil]);
      printf("valore di i %d\n",phil);
    }

    for(phil=0; phil<N; phil++){
      pthread_join(thread_p[phil],NULL);
    }

}
