/**
 * String utilities file. 
 */
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "constants.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * A series of re-implemented string operations seen in string.h
 */

/**
 * re-implementation of strcmp()
 */
int compareString(char *str_a, char *str_b);

/**
 * re-implementation of strcat() 
 */
void concatenateString(char *dest_str, char *src_str);

/**
 * re-implementatoin of strstr, finds a string within
 * a string
 */
int findSubString(char *str_a, char *search_substr);

/**
 * function for reading from input file stream give contraints
 */
_Bool getStringConstrained(FILE *inStream,
                    _Bool clearLeadingNonPrintable,
                    _Bool clearLeadingSpace,
                    _Bool stopAtNonPrintable,
                    char delimiter,
                    char *capturedString);

/**
 * re-implementation of strcpy()
 */
void copyString(char *dest_str, char *src_str);

/**
 * re-implementation of strlen()
 */
int getStringLength(char *str_a);

_Bool getStringToDelimiter(FILE *in_stream, 
                    char delimiter,
                    char *captured_str);

bool getStringToLineEnd(FILE *in_stream, char *captured_str);

void getSubString(char *dest_str,
                char *src_str,
                int startIndex,
                int endIndex);

//void str_set



#endif

