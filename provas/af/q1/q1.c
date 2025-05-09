#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
typedef struct {
    sem_t *semA, *semB, *semC, *semD, *semE, *semF;
} rdv_args;
void *thread1(void *_arg)
{ 
    rdv_args *args = _arg;
    printf("A\n");
    sem_post(arg->semA); 
    sem_post(arg->semA);    
    sem_post(arg->semA); 

    sem_wait(arg->semA);
    sem_wait(arg->semD);
    printf("B\n");
    sem_post(arg->semB); 
    sem_post(arg->semB); 

    sem_wait(arg->semB);
    sem_wait(arg->semE);
    sem_wait(arg->semF);
    printf("C\n");
    return NULL;
}

void *thread2(void *_arg)
{
    printf("D\n");
    sem_post(arg->semD); 
    sem_post(arg->semD);    
    sem_post(arg->semD); 

    sem_wait(arg->semA);
    sem_wait(arg->semD);
    printf("E\n");
    sem_post(arg->semE); 
    sem_post(arg->semE); 
    
    return NULL;
}

void *thread3(void *_arg)
{
    sem_wait(arg->semA);
    sem_wait(arg->semD);
    printf("F\n");
    sem_post(arg->semF); 
    sem_post(arg->semF); 
    return NULL;
}

void *thread4(void *_arg)
{
    sem_post(arg->semB); 
    sem_post(arg->semE);   
    sem_post(arg->semF); 

    printf("G\n");

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2, t3, t4;
    sem_t semA, semB, semC, semD, semE, semF;
    sem_init(&semA, 0, 0);
    sem_init(&semB, 0, 0);
    sem_init(&semC, 0, 0);
    sem_init(&semD, 0, 0);
    sem_init(&semE, 0, 0);
    sem_init(&semF, 0, 0);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);
    pthread_create(&t4, NULL, thread4, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);


    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);
    sem_destroy(&semD);
    sem_destroy(&semE);
    sem_destroy(&semF);
    return 0;
}
