// Airline
// The purpose of this program is take passengers through
// an airline process and ensure they are all seated in
// the end. This is done using multiple threads for each
// the passengers and the baggage, security, and boarding.

#include <stdio.h>
#include <pthread.h>
#include <string>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

// semaphors
sem_t baggage;
sem_t security;
sem_t boarding;
sem_t passenger;

// all passengers are seated
sem_t allSeated;

// counters
int countBag = 0;
int countSec = 0;
int countBoa = 0;
int countPas = 0;

// argument value passenger
int pasVal;

// mutex lock
pthread_mutex_t bufLock;

void *baggageHandler(void *) {
    // while bag checks do not exceed passengers
    while (countBag < pasVal) {
        sem_wait(&baggage);
        // functions start
        pthread_mutex_lock(&bufLock);
        countBag++;

        printf("Passenger #%d is waiting baggage\n", countBag);
        // functions end
        pthread_mutex_unlock(&bufLock);
        sem_post(&security);
    }
}
void *securityScreener(void *) {
    // while screenings dont exceed passengers
    while (countSec < pasVal) {
        sem_wait(&security);
        pthread_mutex_lock(&bufLock);
        countSec++;
        printf("Passenger #%d waiting to be screened\n", countSec);
        pthread_mutex_unlock(&bufLock);
        sem_post(&boarding);
    }
}
void *attendantBoarding(void *) {
    // while seatings dont exceed passengers
    while (countBoa < pasVal) {
        sem_wait(&boarding);
        pthread_mutex_lock(&bufLock);
        countBoa++;
        printf("Passenger #%d boards and gets seated by attendant\n", countBoa);
        pthread_mutex_unlock(&bufLock);
    }

    // all have been seated, process can end
    sem_post(&allSeated);
}
void *passengerArrive(void *) {
    countPas++;
    printf("Passenger #%d arrived at terminal\n", countPas);
    sem_post(&baggage);
}



// main method
int main(int argc, char *argv[]) {
    pthread_t thread_id[atoi(argv[1])];

    pasVal = atoi(argv[1]);

    // if not 5 arguments
    if (argc != 5) {
        printf("ERROR: Please input amount of passengers, baggage handlers, security screeners, and flight attendants. Exit\n");
        return -1;
    }
    else {

        // initialize semaphors
        sem_init(&baggage, 0, 0);
        sem_init(&security, 0, 0);
        sem_init(&boarding, 0, 0);
        sem_init(&passenger, 0, 0);

        // initialize threads
        pthread_t baggage_id[atoi(argv[2])];
        pthread_t security_id[atoi(argv[3])];
        pthread_t attendant_id[atoi(argv[4])];
        pthread_t passenger_id[atoi(argv[1])];

        // baggage threads
        for (int i = 0; i < atoi(argv[2]); i++) {
            pthread_create(&baggage_id[i], NULL, &baggageHandler, NULL);
        }

        // security threads
        for (int i = 0; i < atoi(argv[3]); i++) {
            pthread_create(&security_id[i], NULL, &securityScreener, NULL);
        }

        // flight attendants
        for (int i = 0; i < atoi(argv[4]); i++) {
            pthread_create(&attendant_id[i], NULL, &attendantBoarding, NULL);
        }

        // passenger threads
        for (int i = 0; i < atoi(argv[1]); i++) {
            pthread_create(&passenger_id[i], NULL, &passengerArrive, NULL);
        }

        // join passengers
        for (int i = 0; i < atoi(argv[1]); i++) {
            pthread_join(passenger_id[i], NULL);
        }

        // prevents ending before all passengers have finished the process
        sem_wait(&allSeated);
        return 0;
    }
}