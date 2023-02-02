/**
 * Configuration Data Operations
 */
#ifndef CONFIGOPS_H
#define CONFIGOPS_h
#include <stdio.h>
#include "types.h"
#include "strutils.h"
#include "constants.h"

typedef enum 
{ 
    CFG_FILE_ACCESS_ERR,
    CFG_CORRUPT_DATA_DESCRIPTOR_ERR,
    CFG_DATA_OUT_OF_RANGE_ERR,
    CFG_CORRUPT_PROMPT_ERR,
    CFG_VERSION_CODE,
    CFG_MD_FILE_NAME_CODE,
    CFG_CPU_SCHED_CODE,
    CFG_QUANT_CYCLES_CODE,
    CFG_MEM_DISPLAY_CODE,
    CFG_MEM_AVAILABLE_CODE,
    CFG_PROC_CYCLES_CODE,
    CFG_IO_CYCLES_CODE,
    CFG_LOG_TO_CODE,
    CFG_LOG_FILE_NAME_CODE 
} ConfigCodeMessages;

typedef enum 
{ 
    CPU_SCHED_SJF_N_CODE,
    CPU_SCHED_SRTF_P_CODE,
    CPU_SCHED_FCFS_P_CODE,
    CPU_SCHED_RR_P_CODE,
    CPU_SCHED_FCFS_N_CODE,
    LOGTO_MONITOR_CODE,
    LOGTO_FILE_CODE,
    LOGTO_BOTH_CODE,
    NON_PREEMPTIVE_CODE,
    PREEMPTIVE_CODE 
} ConfigDataCodes;

/**
 * Display configuration data
 */
void displayConfigData( ConfigDataType *configData);

/**
 * Clear config data struct
 */
ConfigDataType * clearConfigData(ConfigDataType *configData);

/**
 * Retrieves configuration data described in a .cnf file
 */
_Bool getConfigData(const char *fileName,
                    ConfigDataType **configData,
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

#endif

