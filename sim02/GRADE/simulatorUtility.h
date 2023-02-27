#ifndef SIMULATOR_UTILITY_H
#define SIMULATOR_UTILITY_H

// headers
#include "myConstants.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// constants

// prototypes
int compareStrings(const char *leftStr, const char *rightStr);
void copyString(const char source[], char dest[]);
void print_error(char *error);
int stringToInt(char *intString);

#endif