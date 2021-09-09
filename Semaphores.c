#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h>
#define SIZE 10000

sem_t semaa;
int array[SIZE - 1];

void swapf(int i, int k)
{
    int temp;
    temp = array[i];
    array[i] = array[k];
    array[k] = temp;

}
void *Sort_A(void *args)
{
    int i, j;
    sem_wait(&semaa);

    for(i = 1; i < SIZE; i++)
    {
        for( j = 0; j < SIZE - 1; j++)
        {
            if(array[j] > array[j+1])
                swapf(j, j+1);
        }
    }
    sem_post(&semaa);
}
void *Sort_D(void *args)
{
    int i, j;
   sem_wait(&semaa);
    for(i = 1; i < SIZE; i++)
    {
        for( j = 0; j < SIZE - 1; j++)
        {
            if(array[j] < array[j+1])
                swapf(j, j+1);
        }
    }
    sem_post(&semaa);
}


void printSortedDesc()
{
    int i;
       sem_wait(&semaa);
    for( i = SIZE - 1; i >= 0; i--)
    {
        printf("%d\n", array[i]);
    }
        sem_post(&semaa);
}

void printSortedAsc()
{
    int i;
    sem_wait(&semaa);
    for( i = 0; i < SIZE; i++)
    {
        printf("%d\n", array[i]);
    }
        sem_post(&semaa);
}


void init()
{
    int i;
    for( i = 0; i < SIZE; i++)
    {
        array[i] = rand()%10000;
    }
}

int main()
{
    init();
    sem_init(&semaa, 0,1);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, Sort_A, NULL);
    sleep(3);
    printf("\nAscending Order\n");
    printSortedAsc();
    sleep(3);
    pthread_create(&t2, NULL, Sort_D, NULL);
    printf("\nDecending Order\n");
    printSortedDesc();
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&semaa);

    return 0;
}
