// Protect from multiple compiling
#ifndef DATATYPES_H
#define DATATYPES_H

#include "StandardConstants.h"
#include <stdbool.h>
#include <stdio.h>

// GLOBAL CONSTANTS... may be used in other variables
typedef struct ConfigDataTypeStruct
{
  int quantumCycles;
  int cpuSchedCode;
  int logToCode;
  bool memDisplay;
  int memAvailable;
  int procCycleRate;
  int ioCycleRate;
  char logToFileName[MAX_STR_LEN];
  char metaDataFileName[MAX_STR_LEN];
  double version;
} ConfigDataType;

typedef struct OpCodeStruct
{
  int pid;
  char command[MAX_STR_LEN];
  char inOutArg[MAX_STR_LEN];
  char strArg1[MAX_STR_LEN];
  int intArg2;
  int intArg3;
  double opEndTime;
  struct OpCodeStruct *nextNode;
} OpCodeType;

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

#endif // DATATYPES_H
