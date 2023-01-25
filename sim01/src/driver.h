#ifndef DRIVER_H
#define DRIVER_h

#include <stdio.h>
#include "types.h"
//#include "configops.h"
#include "strutils.h"
//#include "metadataops.h"
#include "sim.h"


typedef enum { MIN_NUM_ARGS = 3, LAST_FOUR_LETTERS = 4 } PRGRM_CONSTANTS;

/**
 * Command Line Data struct
 */
struct CmdLineData
    {
        _Bool programRunFlag;
        _Bool configDisplayFlag;
        _Bool mdDisplayFlag;
        _Bool runSimFlag;
        char fileName[STD_STR_LEN];
    } CmdLineData;

/**
 * Command Line Usage
 */
void usage();

#endif

