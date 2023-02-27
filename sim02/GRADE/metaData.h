#ifndef METADATA_H
#define METADATA_H

// headers
#include "simulatorUtility.h"

// structs
struct MetaData
{
  char command[MIN_STR_LEN];
  int entryCycleTime;
  char ioArg[MIN_STR_LEN];
  char strArg[MIN_STR_LEN];
  int intArgOne;
  int intArgTwo;

  struct MetaData *nextData;
};
typedef struct MetaData metaData;

// prototypes
metaData *appendNode(metaData *data, char *command, int entryCycleTime,
                     char *ioArg, char *strArg, int intArgs[]);
bool checkMetaDataNode(char *command, int entryCycleTime, char *ioArg,
                       char *strArg, int intArgs[]);
metaData *clearData(metaData *data);
metaData *createDataNode(char *command, int entryCycleTime, char *ioArg,
                         char *strArg, int intArgs[]);
void display_MD(metaData *data, bool displayFlag);
int getArgs(char *currentString, char *ioArg, char *strArg, int *intArgs);
void getCommand(char *currentString, char *command);
void getInts(char *currentString, int *intArgs, int index);
void getIntHelper(char *currentString, int *intArgs, int startIndex,
                  int intIndex);
bool readMetaData(metaData **data, char *fileName);

#endif