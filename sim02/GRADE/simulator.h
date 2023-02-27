#ifndef SIMULATOR_H
#define SIMULATOR_H

// headers
#include "simulatorUtility.h"
#include <pthread.h>

// structs

struct ControlBlockData
{
  char strArg[MIN_STR_LEN];
  char ioArg[MIN_STR_LEN];

  struct ControlBlockData *nextData;
};
typedef struct ControlBlockData controlBlockData;

struct ProcessControlBlock
{
  int idNum;
  char state[MAX_STR_LEN]; // enumurate
  int timeRemaining;

  struct ControlBlockData *dataStart;
  struct ProcessControlBlock *nextBlock;
};
typedef struct ProcessControlBlock controlBlock;

struct FileData
{
  char lineString[MAX_STR_LEN];

  struct FileData *nextLine;
};
typedef struct FileData fileData;

// prototypes
controlBlockData *appendData(controlBlockData *data, char *op, char *io);
fileData *appendLine(fileData *line, char *currentLine);
controlBlock *appendPCB(controlBlock *block, int number, char *state);
controlBlock *cleanPCBs(controlBlock *block);
controlBlockData *createPCBDataNode(char *op, char *IO);
fileData *createLineNode(char *currentLine);
controlBlock *createPCBNode(int number, char *state);
void makePCBs(controlBlock **block, metaData *data);
void makeSim(configuration *config, metaData *data);
void runSim(bool monitor, bool file, controlBlock *block, configuration *config,
            fileData **line);
fileData *saveAndPrint(bool monitor, bool file, fileData *line,
                       char *activeLine);
controlBlock *setData(controlBlock *block, controlBlockData *data, int time);
void setUpTimer(configuration *config, char *ctString);
void writeToFile(configuration *config, metaData *data, fileData *line);
#endif
