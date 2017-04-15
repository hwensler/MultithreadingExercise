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
#include <sstream>

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

//fix it so we can concatinate strings with ints
string to_string(int i){
    stringstream ss;
    ss << i;
    return ss.str();
}

//this is the function that counts vowels
void * countTheVowels(void*arg){

    //*p is a pointer to this vowelCount struct
    struct vowelCount *p = (struct vowelCount *) arg;

    //open filestream
    fstream file;
    ifstream streamedfile((p->fileLocation).c_str());

    //save the entire file to a string
    string entireFile((istreambuf_iterator<char>(streamedfile)), istreambuf_iterator<char>());

    //create character which will be read from file
    char character;

    //while the file is open
    for (string::iterator it = entireFile.begin(), end = entireFile.end(); it != end; ++it)
    {
        //read the next character
        character = *it;

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

    //write the file locations
    for(int i = 0; i < THREAD_COUNT; i++){
        //for later C:\Users\heath\Documents\Repositories\20ThreadedHomework\txtexamples\file

        fileLocations[i] = "/home/fac/lil/cpsc5042/hw1/file" + to_string(i+1) + ".txt";
    }

    //load in file locations & initialize counts to 0
    for (int i = 0; i < THREAD_COUNT; i++){

        allCounts[i].fileLocation = fileLocations[i];
        allCounts[i].aCount = 0;
        allCounts[i].eCount = 0;
        allCounts[i].iCount = 0;
        allCounts[i].oCount = 0;
        allCounts[i].uCount = 0;
    }

    //create int to determine if creation was successful
    int errorCheck;

    //make an int for the results
    int results;

    //create attributes
    pthread_attr_t attribute;

    //status of the thread
    void *status;

    // Initialize and set thread joinable
    pthread_attr_init(&attribute);
    pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_JOINABLE);

    //create 20 threads (0 - 19)
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        //create a pointer to be sent to the thread
        vowelCount *tempCount;

        //assign the pointer to the correct struct in allCounts
        tempCount = &allCounts[i];

        //create the threads
        cout << "creating thread, " << i << endl;
        errorCheck = pthread_create(&threads[i], &attribute, &countTheVowels, (void *) tempCount);

        if (errorCheck) {
            cout << "Error: unable to create thread," << errorCheck << endl;
            exit(-1);
        }
    }

    // free attribute and wait for the other threads
    pthread_attr_destroy(&attribute);

    //join the threads
    for (int i = 0; i < THREAD_COUNT; i++){
        //this waits for all the results to be completed
       results = pthread_join(threads[i], &status);

        if (results){
            cout << "Error:unable to join," << results << endl;
            exit(-1);
        }

        cout << "Main: completed thread id :" << i ;
        cout << "  exiting with status :" << status << endl;

    }

    //create an array for total vowel counts
    int totals[5];
    //initialize all initial counts to 0
    for(int i = 0; i < 5; i++){
        totals[i] = 0;
    }

    //iterate through the structs, tallying final counts
    for(int i = 0; i < 20; i++){
        totals[0] += allCounts[i].aCount;
        totals[1] += allCounts[i].eCount;
        totals[2] += allCounts[i].iCount;
        totals[3] += allCounts[i].oCount;
        totals[4] += allCounts[i].uCount;
    }

    //print results
    cout << "A: " << totals[0] << endl;
    cout << "E: " << totals[1] << endl;
    cout << "I: " << totals[2] << endl;
    cout << "O: " << totals[3] << endl;
    cout << "U: " << totals[4] << endl;

    cout << "Main: program exiting." << endl;

    cout.flush();
    pthread_exit(NULL);
}


