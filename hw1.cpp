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

using namespace std;

int main(){
    //create thread ids
    pthread_t threads[THREAD_COUNT];

    //create int to determine if creation was successful
    int ErrorCheck;

    for(int i = 0; i < THREAD_COUNT; i++){
        cout << "creating thread, " << i << endl;
        ErrorCheck = pthread_create(&threads[i], NULL, NULL, (void *)i);

        if (ErrorCheck){
            cout << "Error: unable to create thread," << ErrorCheck << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

