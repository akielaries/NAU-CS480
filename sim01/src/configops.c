/**
 * Configuration Data Operations
 */
#include "configops.h"


/**
 * Display configuration data
 */
void displayConfigData(ConfigDataType *configData)
{
    char displayString[STD_STR_LEN];
    printf("Config File Display\n");
    printf("-------------------\n");
    printf("Version                : %3.2f\n", configData->version);
    printf("Program File Name      : %s\n", configData->metaDataFileName);
    configCodeToString(configData->cpuSchedCode, displayString);
    printf("CPU Schedule Selection : %s\n", displayString);
    printf("Quantum Time           : %d\n", configData->quantumCycles);
    printf("Memory Display         : ");
    if(configData->memDisplay)
    {
        printf("On\n");
    }
    else
    {
        printf("Off\n");
    }
    printf("Memory Available       : %d\n", configData->memAvailable);
    printf("Process Cycle Rate     : %d\n", configData->procCycleRate);
    printf("I/O Cycle Rate         : %d\n", configData->ioCycleRate);
    configCodeToString(configData->logToCode, displayString);
    printf("Log to Selection       : %s\n", displayString);
    printf("Log File Name          : %s\n\n", configData->logToFileName);
}

/**
 * Clear config data struct
 */
ConfigDataType *clearConfigData(ConfigDataType *configData)
{
    if (configData != NULL) 
    {
        free(configData);
        configData = NULL;
    }
    return NULL;
}

/**
 * Retrieves configuration data described in a .cnf file
 */
_Bool getConfigData(const char *fileName,
                    ConfigDataType **configData,
                    char *endStateMsg) 
{
    const int NUM_DATA_LINES = 10;
    const char READ_ONLY_FLAG[] = "r";
    ConfigDataType *tempData;

    FILE *fileAccessPtr;
    char dataBuffer[MAX_STR_LEN], lowerCaseDataBuffer[MAX_STR_LEN];
    int intData, dataLineCode, lineCtr = 0;
    double doubleData;

    char testMsg[] = "Configuration file upload successful";
    copyString(endStateMsg, testMsg);
    *configData = NULL;

    fileAccessPtr = fopen(fileName, READ_ONLY_FLAG);
    if(fileAccessPtr == NULL)
    {
        char testMsg[] = "Configuration file access error";
        copyString(endStateMsg, testMsg);
        return false;
    }

    if(!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer) ||
           compareString(dataBuffer, "Start Simulator Configuration File") 
           != STR_EQ)
    {
        fclose(fileAccessPtr);
        copyString(endStateMsg, "Corrupt configuration leader line error");
        return false;
    }
    tempData = (ConfigDataType *)malloc(sizeof(ConfigDataType));

    while(lineCtr < NUM_DATA_LINES)
    {
        if(!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer))
        {
            free(tempData);
            fclose(fileAccessPtr);
            copyString(endStateMsg,
                        "Configuration data leader line capture error");
            return false;
        }
        stripTrailingSpaces(dataBuffer);
        dataLineCode = getDataLineCode(dataBuffer);

        if(dataLineCode != CFG_CORRUPT_PROMPT_ERR)
        {
            if(dataLineCode == CFG_VERSION_CODE)
            {
                fscanf(fileAccessPtr, "%lf", &doubleData);
            }
            else if (dataLineCode == CFG_MD_FILE_NAME_CODE ||
                    dataLineCode == CFG_LOG_FILE_NAME_CODE ||
                    dataLineCode == CFG_CPU_SCHED_CODE ||
                    dataLineCode == CFG_LOG_TO_CODE ||
                    dataLineCode == CFG_MEM_DISPLAY_CODE)
            {
                 fscanf(fileAccessPtr, "%s", dataBuffer);
                 setStrToLowerCase(lowerCaseDataBuffer, dataBuffer);
            }
            else
            {
                fscanf(fileAccessPtr, "%d", &intData);
            }

            // Check for data value in range
            if(valueInRange(dataLineCode,
                            intData,
                            doubleData,
                            lowerCaseDataBuffer))
            {
                // Assign to data pointer depending on config item
                switch(dataLineCode)
                {
                    case CFG_VERSION_CODE:
                        tempData->version = doubleData;
                        break;

                    case CFG_MD_FILE_NAME_CODE:
                        copyString(tempData->metaDataFileName, dataBuffer);
                        break;

                    case CFG_CPU_SCHED_CODE:
                        tempData->cpuSchedCode
                                = getCPUSchedCode(lowerCaseDataBuffer);
                        break;

                    case CFG_QUANT_CYCLES_CODE:
                        tempData->quantumCycles = intData;
                        break;

                    case CFG_MEM_DISPLAY_CODE:
                        tempData->memDisplay
                              = compareString(lowerCaseDataBuffer, "on") == 0;
                        break;

                    case CFG_MEM_AVAILABLE_CODE:
                        tempData->memAvailable = intData;
                        break;

                    case CFG_PROC_CYCLES_CODE:
                        tempData->procCycleRate = intData;
                        break;

                    case CFG_IO_CYCLES_CODE:
                        tempData->ioCycleRate = intData;
                        break;

                    case CFG_LOG_TO_CODE:
                        tempData->logToCode
                            = getLogToCode(lowerCaseDataBuffer);
                        break;

                    case CFG_LOG_FILE_NAME_CODE:
                        copyString(tempData->logToFileName, dataBuffer);
                }
            }
            // assume data value not in range 
            else
            {
                free(tempData);
                fclose(fileAccessPtr);
                copyString( endStateMsg, "Configuration item out of range" );

                return false;
            }
        }
        // Otherwise, assume data line not found
        else
        {
            free( tempData );
            fclose( fileAccessPtr );
            copyString( endStateMsg, "Corrupted configuration prompt" );
            return false;
        }
        lineCtr++;
    }

      // Acquire end of sim config string
      // Function: compareString, getStringToDelimiter
    if(!getStringToDelimiter(fileAccessPtr, PERIOD, dataBuffer) ||
            compareString(dataBuffer,"End Simulator Configuration File") 
            != STR_EQ)
    {
        free( tempData );
        fclose( fileAccessPtr );
        copyString( endStateMsg, "Configuration end line capture error" );
        return false;
    }
    tempData->memDisplay = tempData->memDisplay &&
                        tempData->logToCode != LOGTO_FILE_CODE;

    *configData = tempData;
    fclose(fileAccessPtr);
    return true;
}

/**
 * Config code to string
 */
void configCodeToString(int code, char *outString)
{
    char displayStrings[ 8 ][ 10 ] = { "SJF", "SRTF-P", 
                                    "FCFS-P", "RR-P", 
                                    "FCFS-N", "Monitor",
                                    "File", "Both" };
    copyString(outString,(char *)displayStrings[code]);
}

/**
 * Retrieves the CPU Schedular Code
 */
ConfigDataCodes getCPUSchedCode(char *lowerCaseCodeStr)
{
    ConfigDataCodes returnVal = CPU_SCHED_FCFS_N_CODE;

    if (compareString(lowerCaseCodeStr,"sjf-n") == STR_EQ) 
    {
        returnVal = CPU_SCHED_SJF_N_CODE;
    }
    if (compareString(lowerCaseCodeStr,"srtf-p") == STR_EQ) 
    {
        returnVal = CPU_SCHED_SRTF_P_CODE;
    }
    if (compareString(lowerCaseCodeStr,"fcfs-p") == STR_EQ) 
    {
        returnVal = CPU_SCHED_FCFS_P_CODE;
    }
    if (compareString(lowerCaseCodeStr,"rr-p") == STR_EQ) 
    {
        returnVal = CPU_SCHED_RR_P_CODE;
    }
    return returnVal;
}

/**
 * strip spaces
 */
void stripTrailingSpaces(char *str)
{
    int index = getStringLength(str);
    while (index = index + -1, str[index] == SPACE) 
    {
        str[index] = NULL_CHAR;
    }
}



