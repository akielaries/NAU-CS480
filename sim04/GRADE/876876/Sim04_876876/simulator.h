#ifndef SIMULATOR_H
#define SIMULATOR_H

// Header Files 
#include "datatypes.h"
#include "StandardConstants.h"
#include "StringUtils.h"
#include "simtimer.h"
#include "configops.h"
#include <pthread.h>
#include <stdint.h>

// Global Constants
#define MAX_NUM_PROCESSES 20
#define START -20
#define END -21
#define NOT_START_OR_END -25
#define NOT_MEM -1
#define NO_PROCESS 'x'
#define USED 0 
#define OPEN 1
#define MS_TO_SECONDS 1000.0
#define CPU_IDLE -2
#define ALL_EXIT -1
#define LEN_DEC_AND_DEC_POINT 7

// Function Prototypes 
StrLinkedListNode *addStrNode( char *strToAdd, StrLinkedListNode *localPtr);
MemLinkedListNode *clearMemLinkedList( MemLinkedListNode *wkgPtr);
void clearNode( MemLinkedListNode *nodeToClear);
StrLinkedListNode *clearStrLinkedList( StrLinkedListNode *headPtr);
MemLinkedListNode *compressionCheck( MemLinkedListNode *headPtr);
MemLinkedListNode *createMemNode( int lowerPhysical, int upperPhysical, 
                                   int lowerLogical, int upperLogical, 
                                    char pid, bool openOrUsed);
PCBBlock *getProcesses( OpCodeType *metaDataHeadPtr, ConfigDataType *configPtr );
PCBBlock getNextProcess( PCBBlock *processes, int *currentProcessIndex, ConfigDataType *configPtr);
OpCodeType *getOpCode( PCBBlock currentProcess);
MemLinkedListNode *insertMemNode( MemLinkedListNode *newNode, 
                                     MemLinkedListNode *headPtr);
bool interruptMgr(char *keyword, PCBBlock **ptrToProcessesArray);
PCBBlock prepareNextProcess( PCBBlock *processes, int *processIndexPtr, char *outputType,
                              StrLinkedListNode *headPtr, PCBBlock currentProcess, 
                              ConfigDataType *configPtr, bool segFaultFlag, 
                              MemLinkedListNode *memHeadPtr, bool interruptFlag);
void printMemLine(OpCodeType *memPtr, MemLinkedListNode *headPtr, 
                    char *operation);
void printSimLine( char *callingEntity, char *inputType, char *outputType,  
                    ProcessState start, ProcessState end, 
                    PCBBlock *process, StrLinkedListNode *headPtr,
                    int memStart, int memEnd, int startOrEnd, char *inOutArg,
                    char *memOpType);
bool processMemoryRequest(OpCodeType *memPtr, MemLinkedListNode **headPtr, 
				char *operation, ConfigDataType *configPtr,
                                PCBBlock currentProcess);
void runSim( ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr);
void strLinkedListToFile( StrLinkedListNode *headPtr, char *fileName);
float timeStrToFloat( char *timeStr);

#endif // SIMULATOR_H