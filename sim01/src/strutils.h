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
int str_cmp( char *str_a, char *str_b );

//void str_concat

/**
 * re-implementatoin of strstr, finds a string within
 * a string
 */
int str_substr(char *test_str,char *search_substr);

//void str_subget

/**
 * function for reading from input file stream give contraints
 */
_Bool str_cstr(FILE *inStream,
                    _Bool clearLeadingNonPrintable,
                    _Bool clearLeadingSpace,
                    _Bool stopAtNonPrintable,
                    char delimiter,
                    char *capturedString);

/**
 * re-implementation of strcpy()
 */
void str_cpy(char *dest_str, char *src_str);

/**
 * re-implementation of strlen()
 */
int str_len( char *str_a );

//_Bool str_delimeter

//_Bool str_endline

//void str_set



#endif

