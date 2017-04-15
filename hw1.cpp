/**
 * Heather Wensler
 * CPSC 5942
 * Homework 1
 * main.cpp
 */

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <fstream>

//tell how many threads there are
#define THREAD_COUNT 20

using namespace std;

int main() {
    //create thread ids
    pthread_t threads[THREAD_COUNT];

    //open filestream
    fstream file;

    //create character which will be read from file
    char character;

    //open file
    file.open("C:\\Users\\heath\\Documents\\Repositories\\20ThreadedHomework\\txt examples\\file1.txt");

    //initialize counts for all vowels
    int aCount = 0;
    int eCount = 0;
    int iCount = 0;
    int oCount = 0;
    int uCount = 0;

    //this is the function that counts vowels
    while(!file.eof())
    {
        file.get(character);
        if(tolower(character) == 'a'){
            aCount +=1;
        }
        else if(tolower(character) == 'e'){
            eCount +=1;
        }
        else if(tolower(character) == 'i'){
            iCount +=1;
        }
        else if(tolower(character) == 'o'){
            oCount +=1;
        }
        else if(tolower(character) == 'u'){
            uCount +=1;
        }
    }

    //close the file
    file.close();

    //create int to determine if creation was successful
    int errorCheck;

    //create 20 threads
    for (int i = 1; i <= THREAD_COUNT; i++)
    {
        cout << "creating thread, " << i << endl;
        errorCheck = pthread_create(&threads[i], NULL, NULL, (void *) i);

        if (errorCheck) {
            cout << "Error: unable to create thread," << errorCheck << endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}


