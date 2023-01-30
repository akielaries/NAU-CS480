/**
 * Custom data types needed for sim01
 */
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdio.h>
#include "constants.h"


/**
 * Config Data struct 
 */
typedef struct ConfigDataType 
{
        double version;
        // TODO : change this paramater to string length?
        char metaDataFileName[LARGE_STR_LENGTH];
        char logToFileName[LARGE_STR_LENGTH];
        // TODO : define specific bit types? int8_t?
        int cpuSchedCode;
        int quantumCycles;
        _Bool memDisplay;
        int memAvailable;
        int procCycleRate;
        int ioCycleRate;
        int logToCode;
} ConfigDataType;

/**
 * Command Line definitions for parsing
 */
typedef enum 
{ 
        CMD_STR_LEN = 5,
        IO_ARG_STR_LEN = 5,
        STR_ARG_LEN = 15 
} OpCodeArrayCapacity;

/**
 * Operation Code struct
 */
typedef struct OpCodeType
{
        int pid;
        char command[CMD_STR_LEN];
        char inOutArg[IO_ARG_STR_LEN];
        char strArg1[STR_ARG_LEN];
        int intArg2;
        int intArg3;
        double opEndTime;
        struct OpCodeType * nextNode;
} OpCodeType;

#endif

