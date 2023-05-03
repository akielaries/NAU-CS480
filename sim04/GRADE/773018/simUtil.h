//INCLUDE
#include <stdio.h> 
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "simtimer.h"

#define STRUCT_SIZE 100
#define ARRAY_CAP 200
#define TIME_LENGTH 12
#define FIVE 5

//CONSTANTS -----------------------
static const char NULL_CHAR = '\0';
static const int ZERO = 0;
static const int MAX_CONFIG_COUNT = 10;
static const int MAX_ARRAY_SIZE = 50;
static const int DOUBLE = 2;
static const int TRIPLE = 3;
static const int DUMMY_VAL = -1;
static const int MAX_VAL = 9999999;

//STRUCTS -------------

struct Config
    {
        float version;
        char metaFile[STRUCT_SIZE];
        char CPUSS[STRUCT_SIZE];
        int quanTime;
        int memAval;
        char memoryDisp[STRUCT_SIZE];
        int cycleRateP; 
        int cycleRateIO;
        char logTo[STRUCT_SIZE];
        char logFile[STRUCT_SIZE];

    };
    typedef struct Config config;
    
//Meta Data Inside Structure
    //Stores data for each command specifically 
struct Command
        {
            int pid;
            char cmd[ARRAY_CAP];
            char io[ARRAY_CAP];
            char arg1[ARRAY_CAP];
            int arg2;
            int arg3;
            double endTime;
        };
    typedef struct Command command ;

//Meta Data Outside Structure
    //Holds the array that will store each command
struct OpCode
        {
            command *metaData;
            int capacity; 
            int size;
        };
    typedef struct OpCode opcode;


//FUNCTIONS --------------


//Error Print Function
    //prints an error and ends the function
void errorPrint();

int compareStr( const char *str1, const char *str2 );

void combineStr( char desStr[], char str1[], char str2[]);

void copyStr( char destination[], char source[]);

void checkForResize(opcode *meta);

void runSim();
