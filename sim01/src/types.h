/**
 * Custom data types needed for sim01
 */
#ifndef TYPES_H
#define TYPES_H

#include "constants.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum
{
    CMD_STR_LEN = 5,
    IO_ARG_STR_LEN = 5,
    STR_ARG_LEN = 15
} OpCodeArrayCapacity;

// Struct for different process states
typedef enum
{
    NEW_STATE,
    READY_STATE,
    RUNNING_STATE,
    BLOCKED_STATE,
    EXIT_STATE
} ProcessState;

// Struct for op code command data structure
typedef struct OpCodeTypeStruct
{
    int pid;
    char command[CMD_STR_LEN];
    char inOutArg[IO_ARG_STR_LEN];
    char strArg1[STR_ARG_LEN];
    int intArg2;
    int intArg3;
    double opEndTime;
    struct OpCodeTypeStruct *nextNode;
} OpCodeType;

// Struct for config data type data structure
typedef struct ConfigDataTypeStruct
{
    char metaDataFileName[STD_STR_LEN];
    int cpuSchedCode;
    int ioCycleRate;
    int memAvailable;
    int logToCode;
    char logToFileName[STD_STR_LEN];
    bool memDisplay;
    int procCycleRate;
    double version;
    int quantumCycles;
} ConfigDataType;

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

#endif
