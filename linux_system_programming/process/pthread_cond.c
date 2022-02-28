#include <stdio.h>
#include <pthread.h>

pthread_t tid[4];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread_test(void *arg)
{
    pthread_cond_wait(&cond, &mutex);
    printf("this is %d\n", *(int*)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(void)
{
    int id[4];

    for(int i=0; i<4; i++)
    {
        id[i] = i;
        pthread_create(&tid[i], NULL, thread_test, (void*)&id[i]);
    }

    //sleep(2);
    pthread_cond_signal(&cond);

    for(int i=0; i<4; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}