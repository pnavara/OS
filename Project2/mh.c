/*
This program shows the daily assigned task of the mother and father taking care of 12 children.
Author: Pabasara Navaratne
*/
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int days;
//Parents Semaphore Declaration
sem_t motherSem;
sem_t fatherSem;

pthread_attr_t attr;

//Mother's Tasks
//Wakes up child > Feed Breakfast > Send to school > Give dinner > Give bath > Signal Father
void *mother(void *args){

        //Wakes up child 
        for(int i = 1; i < 13; i++){
            printf("Mother is waking child #%d up\n", i);
        }
        //Feed Breakfast
        for(int i = 1; i < 13; i++){
            printf("Mother is feeding breakfast to child #%d\n", i);
        }
        //Send to school
        for(int i = 1; i < 13; i++){
            printf("Mother is sending child #%d to school\n", i);
        }
        // Give dinner
        for(int i = 1; i < 13; i++){
            printf("Mother is feeding dinner to child #%d\n", i);
        }
        //Give bath
        for(int i = 1; i < 13; i++){
            printf("Mother is giving a bath to child #%d\n", i);
            //Slowing down after task for father.
            usleep(100);
            // Signal the father to wake up
            sem_post(&fatherSem);
        }
    return 0;

}

//Father's Tasks
//Reads book to a child while mom gives bath to a child > Tuck child into bed
//After tucking last child, father will go and wake mother up again
void *father(void *args){

        // Read book
        for(int i = 1; i < 13; i++){
            //Father is waiting
            sem_wait(&fatherSem);
            usleep(100);
            printf("Father is reading a book to child #%d\n", i);
        }
        // Tuck child into bed
        for(int i = 1; i < 13; i++){
            printf("Father is tucking child #%d into bed\n" ,i);
        }

        printf("Father is going to sleep and waking up mother to take care of children\n\n");
        // Signal mother when father tucks kids into bed. 
        sem_post(&motherSem);

}


int main(int argc, char *argv[]){
    int cycles = 1;
    if(argc !=2){
        printf ("Enter the number of days\n");
    }

    else{
       days = atoi(argv[1]);
       while(cycles <= days){
       printf("This is day #%d of a day in the life of Mother Hubbard\n", cycles);
       //Declaring semaphores
        sem_init(&motherSem,0,1);
        sem_init(&fatherSem,0,0);

       //Initializing thread for parents
	pthread_t motherThread;
	pthread_t fatherThread;
	pthread_attr_init(&attr);
	pthread_create(&motherThread,&attr, mother, NULL);
	pthread_create(&fatherThread,&attr, father, NULL);

	pthread_join(motherThread,NULL);
	pthread_join(fatherThread,NULL);
       cycles++;
       }
	exit(0);
    }
    return 0;
}
