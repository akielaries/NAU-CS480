// Protect from multiple compiling
#ifndef OS_SIMDRIVER_H
#define OS_SIMDRIVER_H

// Header files
#include <stdio.h>
#include <stdbool.h>
#include "StandardConstants.h"
#include "datatypes.h"
#include "StringUtils.h"
#include "configops.h"
#include "metadataops.h"
#include "simulator.h"

// Program constants
typedef enum
{
    MIN_NUM_ARGS = 3,
    LAST_FOUR_LETTERS = 4
} PRGRM_CONSTANTS;

// Commandline struct for storing command line switch settings
typedef struct CmdLineDataStruct
{
    bool programRunFlag;
    bool configDisplayFlag;
    bool mdDisplayFlag;
    bool runSimflag;

    char fileName[STD_STR_LEN];
} CmdLineData;

// Function prototypes
void clearCmdLineStruct(CmdLineData *clDataPtr);

bool processCmdLine(int numArgs, char **strVector, CmdLineData *clDataPtr);

void showCommandLineFormat();

bool getConfigData(const char *filename, ConfigDataType **configData,
                   char *endStateMsg);

#endif // OS_SIMDRIVER_H