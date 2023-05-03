#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdio.h>
#include <stdbool.h>
#include "StandardConstants.h"
#include "simtimer.h"

// Global Constants 
typedef enum{ CMD_STR_LEN = 5, 
              IO_ARG_STR_LEN = 5, 
              STR_ARG_LEN = 15}OpCodeArrayCapacity;

// Five state data structure for processes 
typedef enum { NEW_STATE, 
               READY_STATE, 
               RUNNING_STATE, 
               BLOCKED_STATE, 
               EXIT_STATE}ProcessState; 

// data structure for timer
typedef enum TIMER_CTRL_CODES { ZERO_TIMER, LAP_TIMER, STOP_TIMER }TimerCtrlCodes;

// Data Structures 
typedef struct OpCodeStruct {
   char command[ STD_STR_LEN];
   char inOutArg[STD_STR_LEN];
   char strArg1[STD_STR_LEN];
   int intArg2; 
   int intArg3; 
   int pid; 
   double opEndTime; 

   struct OpCodeStruct *nextNode;
   
                            } OpCodeType;

typedef struct ConfigDataStruct {
   char metaDataFileName[STD_STR_LEN];
   char logToFileName[STD_STR_LEN];
   double version;
   bool memDisplay; 
   int cpuSchedCode;
   int quantumCycles;
   int memAvailable;
   int procCycleRate; 
   int ioCycleRate;
   int logToCode; 
   
                                } ConfigDataType;

typedef struct StrLinkedListStruct {
   char lineStr[MAX_STR_LEN];
   struct StrLinkedListStruct *nextNode;

                                   } StrLinkedListNode;

typedef struct PCBBlockStruct {
   int pid; 
   int estTime; 
   float estFinishTime;
   ProcessState state;
   OpCodeType *appStartPtr;
   OpCodeType *currentOpCode;
                              } PCBBlock;

typedef struct timeThreadStruct {
   char timeString[STD_STR_LEN];
   TimerCtrlCodes code; 
                                } timeThreadArgs; 

typedef struct MemLinkedListStruct {
   int physicalStart; 
   int physicalEnd; 
   int logicalStart; 
   int logicalEnd; 
   char pid; 
   bool openOrUsed;
   struct MemLinkedListStruct *nextNode;
                                   } MemLinkedListNode;





#endif // DATATYPES_H