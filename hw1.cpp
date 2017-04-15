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

//initialize counts for all vowels
struct vowelCount{
    string fileLocation;
    int aCount;
    int eCount;
    int iCount;
    int oCount;
    int uCount;
};

//this is the function that counts vowels
void * countTheVowels(void*arg){

    //*p is a pointer to this vowelCount struct
    struct vowelCount *p = (struct vowelCount *) arg;

    //open filestream
    fstream file;

    //create character which will be read from file
    char character;

    //open file
    file.open(p->fileLocation);

    //while the file is open
    while(!file.eof())
    {
        //read the next character
        file.get(character);

        //now see if it's a vowel. if it is, increment.
        if(tolower(character) == 'a'){
            p->aCount +=1;
        }
        else if(tolower(character) == 'e'){
            p->eCount +=1;
        }
        else if(tolower(character) == 'i'){
            p->iCount +=1;
        }
        else if(tolower(character) == 'o'){
            p->oCount +=1;
        }
        else if(tolower(character) == 'u'){
            p->uCount +=1;
        }
    }

    //close the file
    file.close();

    //free your variables
    delete p;

    //return
    return NULL;
}

int main() {
    //create thread ids
    pthread_t threads[THREAD_COUNT];


    //create an array of these counts for all 20 file
    vowelCount allCounts[THREAD_COUNT];

    //create an array of all the file locations
    string fileLocations[THREAD_COUNT];

    //load in file locations & initialize counts to 0
    for (int i = 0; i < THREAD_COUNT; i++){
        //later
        //allcounts[i].fileLocation = fileLocations[i];
        allCounts[i].fileLocation = "C:\\Users\\heath\\Documents\\Repositories\\20ThreadedHomework\\txt examples\\file1.txt";
        allCounts[i].aCount = 0;
        allCounts[i].eCount = 0;
        allCounts[i].iCount = 0;
        allCounts[i].oCount = 0;
        allCounts[i].uCount = 0;
    }

    //create int to determine if creation was successful
    int errorCheck;

    //create 20 threads (0 - 19)
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        //create a pointer to be sent to the thread
        vowelCount *tempCount;

        //assign the pointer to the correct struct in allCounts
        tempCount = &allCounts[i];

        //create the threads
        cout << "creating thread, " << i << endl;
        errorCheck = pthread_create(&threads[i], NULL, &countTheVowels, (void *) tempCount);

        if (errorCheck) {
            cout << "Error: unable to create thread," << errorCheck << endl;
            exit(-1);
        }
    }
}


