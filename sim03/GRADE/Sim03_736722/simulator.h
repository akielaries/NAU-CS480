// protect from multiple compliling
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "configops.h"
#include "datatypes.h"
#include "simTimer.h"
#include <pthread.h>

// Memory data structure
typedef struct MemStruct
{
  int mem_start;
  int mem_end;
  int vmem_start;
  int vmem_end;
  struct MemStruct *nextNode;
} MemDataType;

// PCB data structure
typedef struct PCBStruct
{
  int process_id;
  int execution_time;
  int state;
  OpCodeType *start;
  MemDataType *memory;
  struct PCBStruct *nextNode;
} PCBDataType;

// Logfile output data structure
typedef struct LogStringStruct
{
  char line[MAX_STR_LEN];
  struct LogStringStruct *nextLine;
} LogString;

// Prototypes
void addLine(LogString **string, char *newLine);
void addProcess(PCBDataType **PCBPtr, int process_id, int execution_time,
                int state, OpCodeType *start);
int calcTime(OpCodeType *metaDataPtr, ConfigDataType *configPtr);
PCBDataType *getNextProcess(ConfigDataType *configPtr, PCBDataType *PCBPtr,
                            bool start);
void logDump(ConfigDataType *configPtr, LogString *string);
void outputLine(ConfigDataType *configPtr, LogString **string, char *line,
                bool memory_op);
PCBDataType *queueProcess(ConfigDataType *configPtr, LogString *string,
                          OpCodeType *metaDataPtr, PCBDataType *PCBPtr,
                          char *clock);
void runCPU(ConfigDataType *configPtr, LogString *string,
            OpCodeType *metaDataPtr, int process_id, char *clock);
void runDev(ConfigDataType *configPtr, LogString *string,
            OpCodeType *metaDataPtr, int process_id, char *clock);
void runMemAccess(ConfigDataType *configPtr, LogString *string,
                  OpCodeType *metaDataPtr, PCBDataType *PCBPtr, char *clock);
void runMemAllocate(ConfigDataType *configPtr, LogString *string,
                    OpCodeType *metaDataPtr, PCBDataType *PCBPtr, char *clock);
void runProcess(ConfigDataType *configPtr, LogString *string,
                PCBDataType *PCBPtr, char *clock);
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr);
void *startTimer(void *arg);

#endif