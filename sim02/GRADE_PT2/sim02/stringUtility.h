#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include "StandardConstants.h"

int compareString( const char *oneStr, const char *otherStr );

void concatenateString( char *destStr, const char *sourceStr );

void copyString( char *destStr, const char *sourceStr );

int findSubString( const char *testStr, const char *searchSubStr );

bool getStringConstrained( FILE *inStream, bool clearLeadingNonPrintable,
                                bool clearLeadingSpace, bool stopAtNonPrintable,
                                            char delimiter, char *capturedStr );

int getStringLength( const char *testStr );

bool getStringToDelimiter( FILE *inStream, char delimiter, char *capturedStr );

bool getStringToLineEnd( FILE *inStream, char *capturedStr );

void getSubString( char *destStr, const char *sourceStr,
	                                              int startIndex, int endIndex );

void setStrToLowerCase( char *destStr, const char *sourceStr );

char toLowerCase( char testChar );

#endif // STRING_UTILITY_H
