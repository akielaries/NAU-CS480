// protect from multiple compliling
#ifndef DATATYPES_H
#define DATATYPES_H

#include "StandardConstants.h"
#include <stdbool.h>
#include <stdio.h>

// GLOBAL CONSTANTS - may be used in other files

typedef enum
{
  CMD_STR_LEN = 5,
  IO_ARG_STR_LEN = 5,
  STR_ARG_LEN = 15
} OpCodeArrayCapacity;

// Five state data structure for processes
typedef enum
{
  NEW_STATE,
  READY_STATE,
  RUNNING_STATE,
  BLOCKED_STATE,
  EXIT_STATE
} ProcessState;

typedef struct OpCodeStruct
{
  int pid;
  char command[MIN_STR_LEN];
  char inOutArg[MIN_STR_LEN];
  char strArg1[MIN_STR_LEN];
  int intArg2;
  int intArg3;
  double opEndTime;

  struct OpCodeStruct *nextNode;

} OpCodeType;

typedef struct ConfigStruct
{
  double version;
  char metaDataFileName[STD_STR_LEN];
  int cpuSchedCode;
  int quantumCycles;
  bool memDisplay;
  int memAvailable;
  int procCycleRate;
  int ioCycleRate;
  int logToCode;
  char logToFileName[STD_STR_LEN];
} ConfigDataType;

#endif