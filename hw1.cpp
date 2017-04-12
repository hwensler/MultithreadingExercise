/**
 * Heather Wensler
 * CPSC 5942
 * Homework 1
 * main.cpp
 */

#include <iostream>
#include <cstdlib>
#include <pthread.h>

//tell how many threads there are
#define THREAD_COUNT 20

int main(){
    //create thread ids
    pthread_t threads[THREAD_COUNT];

    //create int to determine if creation was successful
    int errorCheck;

    for(int i = 0; i < THREAD_COUNT; i++){
        cout << "creating thread, " << i << endl;
        rc = pthread_create(&threads[i], NULL, CountVowels, (void *)i);

        if (rc){
            cout << "Error: unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

