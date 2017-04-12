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
    int errorCheck;

    //store all vowels
    string vowels [10] = {"A", "a", "E", "e", "I", "i", "O", "o", "U", "u"};


    for(int i = 0; i < THREAD_COUNT; i++){
        cout << "creating thread, " << i << endl;
        errorCheck = pthread_create(&threads[i], NULL, NULL, (void *)i);

        if (errorCheck){
            cout << "Error: unable to create thread," << errorCheck << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

