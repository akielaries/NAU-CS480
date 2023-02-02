/**
 * Configuration Data Operations
 */
#ifndef CONFIGOPS_H
#define CONFIGOPS_h
#include "constants.h"
#include "strutils.h"
#include "types.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * Display configuration data
 */
void displayConfigData(ConfigDataType *configData);

/**
 * Clear config data struct
 */
ConfigDataType *clearConfigData(ConfigDataType *configData);

/**
 * Retrieves configuration data described in a .cnf file
 */
bool getConfigData(const char *fileName, ConfigDataType **configData,
                   char *endStateMsg);

/**
 * Retrieves the CPU Schedular Code
 */
ConfigDataCodes getCPUSchedCode(char *lowerCaseCodeStr);

/**
 * Convert config code to string
 */
void configCodeToString(int code, char *outString);

/**
 * Strip spaces
 */
void stripTrailingSpaces(char *str);

/**
 * Log to code
 */
ConfigDataCodes getLogToCode(const char *lowerCaseLogToStr);

/**
 * Retrieve data line code
 */
ConfigCodeMessages getDataLineCode(const char *dataBuffer);

/**
 * find a specific line number for a config based param
 */
bool valueInRange(int lineCode, int intVal, double doubleVal,
                  const char *lowerCaseStringVal);
#endif
