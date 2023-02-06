#ifndef STRUTILS_H
#define STRUTILS_H

#include "constants.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int compareString(const char *leftStr, const char *rightStr);

void concatenateString(char *destStr, const char *sourceStr);

void copyString(char *destStr, const char *sourceStr);

int findSubString(const char *testStr, const char *searchSubStr);

_Bool getStringConstrained(FILE *inStream, _Bool clearLeadingNonPrintable,
                           _Bool clearLeadingSpace,
                           _Bool stopAtNonPrintable, char delimiter,
                           char *capturedString);

int getStringLength(const char *testStr);

_Bool getStringToDelimiter(FILE *inStream, char delimiter,
                           char *capturedString);

_Bool getStringToLineEnd(FILE *inStream, char *capturedString);

void getSubString(char *destStr, const char *sourceStr, int startIndex,
                  int endIndex);

void setStrToLowerCase(char *destStr, const char *sourceStr);

int toLowerCase(char testChar);

#endif
