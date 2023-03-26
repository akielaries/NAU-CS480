// protect from multiple compliling
#ifndef METADATAOPS_H
#define METADATAOPS_H

#include "StringUtils.h"
#include "datatypes.h"
#include <stdbool.h>

typedef enum
{
  BAD_ARG_VAL = -1,
  NO_ACCESS_ERR,
  MD_FILE_ACCESS_ERR,
  MD_CORRUPT_DESCRIPTOR_ERR,
  OPCMD_ACCESS_ERR,
  CORRUPT_OPCMD_ERR,
  CORRUPT_OPCMD_ARG_ERR,
  UNBALANCED_START_END_ERR,
  COMPLETE_OPCMD_FOUND_MSG,
  LAST_OPCMD_FOUND_MSG
} OpCodeMessages;

OpCodeType *addNode(OpCodeType *localPtr, OpCodeType *newNode);
OpCodeType *clearMetaDataList(OpCodeType *localPtr);
void displayMetaData(const OpCodeType *localPtr);
int getCommand(char *cmd, const char *inputStr, int index);
bool getMetaData(const char *fileName, OpCodeType **opCodeDataHead,
                 char *endStateMsg);
int getNumberArg(int *number, const char *inputStr, int index);
OpCodeMessages getOpCommand(FILE *filePtr, OpCodeType *inData);
int getStringArg(char *strArg, const char *inputStr, int index);
bool isDigit(char testChar);
int updateEndCount(int count, const char *opString);
int updateStartCount(int count, const char *opString);
bool verifyFirstStringArg(const char *strArg);
bool verifyValidCommand(char *testCmd);

#endif