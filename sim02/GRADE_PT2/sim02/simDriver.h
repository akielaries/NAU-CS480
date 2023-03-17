#ifndef SIM01_H
#define SIM01_H

// header files
#include <stdio.h>
//#include "datatypes.h"
#include "configops.h"
#include "metadataops.h"
#include "simulator.h"
#include "stringUtility.h"

// Program constants
typedef enum
{
  MIN_NUM_ARGS = 3,
  LAST_FOUR_LETTERS = 4
} PRGRM_CONSTANTS;

typedef struct CmdLineDataStruct
{
  bool programRunFlag;
  bool configDisplayFlag;
  bool mdDisplayFlag;
  bool runSimFlag;

  char fileName[STD_STR_LEN];
} CmdLineData;

void clearCmdLineStruct(CmdLineData *clDataPtr);
bool processCmdLine(int numArgs, char **strVector, CmdLineData *clDataPtr);
void showCommandLineFormat();

#endif // SIM01_H