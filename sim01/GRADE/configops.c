// Header files
#include "configops.h"

/*
Name: clearConfigData
Process: frees dynamically allocated config data structure if it has not
already been freed Function Input/Parameters: pointer to config data
structure (ConfigDataType *) Function Output/Parameters: none Function
OUtput/Returned: NULL (ConfigDataType *) Device Input/device: none Device
Output/device: none Dependencies: tbd
*/
ConfigDataType *clearConfigData(ConfigDataType *configData)
{
    // check that config data ptr is NOT null
    if (configData != NULL)
    {
        // free data struct memory
        // function: free
        free(configData);

        // set config pointer to null
        configData = NULL;
    }
    // set config data ptr to null

    return NULL;
}

/*
Name: congifCodeToString
Process: utility function converts config code numebr
         to the string they represent
Function Input/Parameters: config code (int)
Function Output/Parameters: resulting output string (char *)
Function OUtput/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: copyString
*/
void configCodeToString(int code, char *outString)
{
    // define array with eight items, and short (10) lengths
    char displayString[8][10] = {"SJF-N",
                                 "SRTF-P",
                                 "FCFS-P",
                                 "RR-P"
                                 "FCFS-N",
                                 "Monitor",
                                 "File",
                                 "BOTH"};

    // copy string to return param
    // function: copyString
    copyString(outString, displayString[code]);
}

/*
Name: displayConfigData
Process: screen dump/display of all config data
Function Input/Parameters: pointer to config data structure (ConfigDataType
*) Function Output/Parameters: none Function OUtput/Returned: none Device
Input/device: none Device Output/device: displayed as specified
Dependencies: tbd
*/
void displayConfigData(ConfigDataType *configData)
{
    // Initialize variables

    // print lines of display for all member values
    // function: printf, codeToString (translates coded items)
    char displayString[STD_STR_LEN];
    printf("Config File Display\n");
    printf("-------------------\n");
    printf("Version               : %3.2f\n", configData->version);
    printf("Program File Name     : %s\n", configData->metaDataFileName);
    configCodeToString(configData->cpuSchedCode, displayString);
    printf("CPU schedule slection : %s\n", displayString);
    printf("Quantum time          : %d\n", configData->quantumCycles);
    printf("Memory Display        : ");
    if (configData->memDisplay)
    {
        printf("On\n");
    }
    else
    {
        printf("Off\n");
    }
    printf("Memory Available      : %d\n", configData->memAvailable);
    printf("Process cycle rate    : %d\n", configData->procCycleRate);
    printf("I/O cycle rte         : %d\n", configData->ioCycleRate);
    configCodeToString(configData->logToCode, displayString);
    printf("Lof to selectoin      : %s\n", displayString);
    printf("Log file name         : %s\n\n", configData->logToFileName);
}

/*
Name: getConfigData
Process: driver function for caputring config data from config file
Function Input/Parameters: file name (const char *)
Function Output/Parameters: pointer to config data painter (configDataType
**), end/result state message pointer (char *) Function OUtput/Returned:
Boolean result of data access operation (bool) Device Input/device: config
data uploaded Device Output/device: none Dependencies: tbd
*/

bool getConfigData(const char *filename, ConfigDataType **configData,
                   char *endStateMsg)
{
    // Initialize function

    // set constant number of data line
    const int NUM_DATA_LINES = 10;

    // set read only constant
    const char READ_ONLY_FLAG[] = "r";

    // create pointer for data input
    ConfigDataType *tempData;

    // declare other variables
    FILE *fileAccessPtr;
    char dataBuffer[MAX_STR_LEN], lowerCaseDataBuffer[MAX_STR_LEN];
    int intData, dataLineCode, lineCtr = 0;
    double doubleData;

    // set endStateMsg to success
    // function: copyString
    char testMsg[] = "Configuration file upload successful";
    copyString(endStateMsg, testMsg);

    // Initilaize config data pointer in case of return error
    *configData = NULL;

    // open file
    // function: fopen
    fileAccessPtr = fopen(filename, READ_ONLY_FLAG);

    // check for file open failure
    if (fileAccessPtr == NULL)
    {
        // set end state message to config file access error
        // function: copyString
        char testMsg[] = "Configuration file access error";
        copyString(endStateMsg, testMsg);

        // return file access error
        return false;
    }

    // get first line, check for failure
    // function: getStringToDelimiter, compareString
    if (!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer) ||
        compareString(dataBuffer, "Start Simulator Configuration File") !=
            STR_EQ)
    {
        // close file access
        // function: fclose
        fclose(fileAccessPtr);

        // set end message to corrupt leader line error
        // function: copyString
        copyString(endStateMsg, "Corrupt configuration leader line error");

        // return corrupt file data
        return false;
    }
    // create temporary pointer to configuration data structure
    // function: malloc
    tempData = (ConfigDataType *)malloc(sizeof(ConfigDataType));

    // loop to end of config data items
    while (lineCtr < NUM_DATA_LINES)
    {
        // get line leader, check for failure
        // function: getStringToDelimiter
        if (!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer))
        {
            // free temp struct memory
            // function: free
            free(tempData);

            // close file
            // function: fclose
            fclose(fileAccessPtr);

            // set end state message to line capture failure
            // function: copyString
            copyString(endStateMsg,
                       "Configuration data leader line capture error");

            // return incomplete file error
            return false;
        }

        // Strip trialing spaces of config leader lines
        // for user in other functions
        // function: stripTrailingSpaces
        stripTrailingSpaces(dataBuffer);

        // find correct data line code number from string
        // function: getDataLineCode
        dataLineCode = getDataLineCode(dataBuffer);

        // // check for data line found
        if (dataLineCode != CFG_CORRUPT_PROMPT_ERR)
        {
            printf("test 3\n\n"); // get data value

            // check for version number (double)
            if (dataLineCode == CFG_VERSION_CODE)
            {
                // get version number
                // function: fscanf
                fscanf(fileAccessPtr, "%lf", &doubleData);
            }
            // otherwise, check for metaData, file names,
            // CPU scheduling names, or momry display settings (strings)
            else if (dataLineCode == CFG_MD_FILE_NAME_CODE ||
                     dataLineCode == CFG_LOG_FILE_NAME_CODE ||
                     dataLineCode == CFG_CPU_SCHED_CODE ||
                     dataLineCode == CFG_LOG_TO_CODE ||
                     dataLineCode == CFG_MEM_DISPLAY_CODE)
            {
                // get string input
                // function: fscanf
                fscanf(fileAccessPtr, "%s", dataBuffer);

                // set string to lower case for testing in valueInRange
                // function: serStrToLowerCase
                setStrToLowerCase(lowerCaseDataBuffer, dataBuffer);
            }
            // otherwise assume int data
            else
            {
                // get int input
                // function: fscanf
                fscanf(fileAccessPtr, "%d", &intData);
            }
            // check for data value in range
            // function: valueInRange
            if (valueInRange(dataLineCode, intData, doubleData,
                             lowerCaseDataBuffer))
            {
                // assign to data pointer depending on config item
                // (all line possibilities)
                // function: copyString, getCpuSchedCode, compareString,
                //           getLogToCode, as needed
                switch (dataLineCode)
                {
                case CFG_VERSION_CODE:
                    tempData->version = doubleData;
                    break;
                case CFG_MD_FILE_NAME_CODE:
                    printf("\n%s\n", dataBuffer);
                    copyString(tempData->metaDataFileName, dataBuffer);
                    break;
                case CFG_CPU_SCHED_CODE:
                    tempData->cpuSchedCode =
                        getCpuSchedCode(lowerCaseDataBuffer);
                    break;
                case CFG_QUANT_CYCLES_CODE:
                    tempData->quantumCycles = intData;
                    break;
                case CFG_MEM_DISPLAY_CODE:
                    tempData->memDisplay =
                        compareString(lowerCaseDataBuffer, "on") == 0;
                    break;
                case CFG__MEM_AVAILABLE_CODE:
                    tempData->memAvailable = intData;
                    break;
                case CFG_PROC_CYCLES_CODE:
                    tempData->procCycleRate = intData;
                    break;
                case CFG_IO_CYCLES_CODE:
                    tempData->ioCycleRate = intData;
                    break;
                case CFG_LOG_TO_CODE:
                    tempData->logToCode =
                        getLogToCode(lowerCaseDataBuffer);
                    break;
                case CFG_LOG_FILE_NAME_CODE:
                    copyString(tempData->logToFileName, dataBuffer);
                    break;
                }
            }
            // otherwise assume not in range
            else
            {
                // free temp struct mem
                // function: free
                free(tempData);

                // close file access
                // function: fclose
                fclose(fileAccessPtr);

                // set end message to configuration data out of range
                // function: copyString
                copyString(endStateMsg, "Configuration item out of range");

                // return data out of range
                return false;
            }
        }
        // otherwise assume data line not found
        else
        {
            // free temp struct mem
            // function: free
            free(tempData);

            // close file access
            // function: fclose
            fclose(fileAccessPtr);

            // set end message to configuration data out of range
            // function: copyString
            copyString(endStateMsg, "Corrupted configuration prompt");

            // return corrupt config file code
            return false;
        }

        // increment line counter
        lineCtr++;
    }
    // end master loop

    // aquire end of sim config string
    // function: getStringToDelimiter, compareString
    if (!getStringToDelimiter(fileAccessPtr, PERIOD, dataBuffer) ||
        compareString(dataBuffer, "End Simolator Configuration file") !=
            STR_EQ)
    {
        // free temp struct mem
        // function: free
        free(tempData);

        // close file access
        // function: fclose
        fclose(fileAccessPtr);

        // set end message to configuration data out of range
        // function: copyString
        copyString(endStateMsg, "Configuration end line capture error");

        // return corrupt file data
        return false;
    }
    // test for file only uotput so memory diagnostics do not display
    tempData->memDisplay =
        tempData->memDisplay && tempData->logToCode != LOGTO_FILE_CODE;

    // assign temp ptr to parameter return ptr
    *configData = tempData;

    // close file access
    // function: fclose
    fclose(fileAccessPtr);

    // // return no error code
    return true;
}

/*
Name: getCpuSchedCode
Process: converts cpu schedule string to code
Function Input/Parameters: lower case code string
Function Output/Parameters: none
Function OUtput/Returned: cpu schedule code
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
ConfigDataCodes getCpuSchedCode(const char *lowerCaseCodeStr)
{
    ConfigDataCodes returnVal = CPU_SCHED_FCFS_N_CODE;

    if (compareString(lowerCaseCodeStr, "sjf-n") == STR_EQ)
    {
        returnVal = CPU_SCHED_SJF_N_CODE;
    }
    if (compareString(lowerCaseCodeStr, "srtf-p") == STR_EQ)
    {
        returnVal = CPU_SCHED_SRTF_P_CODE;
    }
    if (compareString(lowerCaseCodeStr, "fcfs-p") == STR_EQ)
    {
        returnVal = CPU_SCHED_FCFS_P_CODE;
    }
    if (compareString(lowerCaseCodeStr, "rr-p") == STR_EQ)
    {
        returnVal = CPU_SCHED_RR_P_CODE;
    }
    return returnVal;
}

/*
Name: getDataLineCode
Process: converts leader line string to config code value
Function Input/Parameters: config leader line string (const char*)
Function Output/Parameters: none
Function OUtput/Returned: config code value (ConfigCodeMessages)
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
ConfigCodeMessages getDataLineCode(const char *dataBuffer)
{
    // return appropriate code depending on prompt string provided
    // function: compareString
    if (compareString(dataBuffer, "Version/Phase") == STR_EQ)
    {
        return CFG_VERSION_CODE;
    }
    if (compareString(dataBuffer, "File Path") == STR_EQ)
    {
        return CFG_MD_FILE_NAME_CODE;
    }
    if (compareString(dataBuffer, "CPU Scheduling Code") == STR_EQ)
    {
        return CFG_CPU_SCHED_CODE;
    }
    if (compareString(dataBuffer, "Quantum Time (cycles)") == STR_EQ)
    {
        return CFG_QUANT_CYCLES_CODE;
    }
    if (compareString(dataBuffer, "Memory Display (On/Off)") == STR_EQ)
    {
        return CFG_MEM_DISPLAY_CODE;
    }
    if (compareString(dataBuffer, "Memory Available (KB)") == STR_EQ)
    {
        return CFG__MEM_AVAILABLE_CODE;
    }
    if (compareString(dataBuffer, "Processor Cycle Time (msec)") == STR_EQ)
    {
        return CFG_PROC_CYCLES_CODE;
    }
    if (compareString(dataBuffer, "I/O Cycle Time (msec)") == STR_EQ)
    {
        return CFG_IO_CYCLES_CODE;
    }
    if (compareString(dataBuffer, "Log To") == STR_EQ)
    {
        return CFG_LOG_TO_CODE;
    }
    if (compareString(dataBuffer, "Log File Path") == STR_EQ)
    {
        return CFG_LOG_FILE_NAME_CODE;
    }
    // return corrupt leader line error code
    return CFG_CORRUPT_PROMPT_ERR;
}

/*
Name: getLogToCode
Process:
Function Input/Parameters:
Function Output/Parameters:
Function OUtput/Returned:
Device Input/device:
Device Output/device:
Dependencies:
*/
ConfigDataCodes getLogToCode(const char *lowerCaseLogToStr)
{
    // initialize variables

    // set default to log to monitor
    ConfigDataCodes returnVal = LOGTO_MONITOR_CODE;

    // check for BOTH
    // function: compareString
    if (compareString(lowerCaseLogToStr, "both") == STR_EQ)
    {
        // set return value to both code
        return LOGTO_BOTH_CODE;
    }
    // check for FILE
    // function: compareString
    if (compareString(lowerCaseLogToStr, "file") == STR_EQ)
    {
        // set return value to file code
        return LOGTO_FILE_CODE;
    }

    // return selected code
    return returnVal;
}

/*
Name: skipTrailingSpaces
Process: removes trailing spaces from input config leader lines
Function Input/Parameters: config leadre line string (char*)
Function Output/Parameters: updated config leadre line string (char *)
Function OUtput/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: getStringLength
*/
void stripTrailingSpaces(char *str)
{
    // Initialize index to length of string -1 to get highest array index
    int index = getStringLength(str) - 1;

    // loop while space is found at end of string
    while (str[index] == SPACE)
    {
        // set element to NULL
        str[index] = NULL_CHAR;

        // decrement index]
        index--;
    }
    // end loop
}

/*
Name: valueInRange
Process: checks for config data values in range. includeing string values
Function Input/Parameters: line code number for specific config value
(int), interger value, as needed (int), double value, as needed (double),
                           string value, as needed
Function Output/Parameters: none
Function OUtput/Returned: boolean result of range test
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
bool valueInRange(int lineCode, int intVal, double doubleVal,
                  const char *lowerCaseStringVal)
{
    // intialize function

    // set result to true, all tests are to find false
    bool result = true;

    // use line code to id prompt line
    switch (lineCode)
    {
    // for version code
    case CFG_VERSION_CODE:
        // check if limits of verision code are exceeded
        if (doubleVal < 0.00 || doubleVal > 10.00)
        {
            // ser bool result to false
            result = false;
        }
        // break
        break;

    // for cpu scheduling code
    case CFG_CPU_SCHED_CODE:

        // check for not finding one of the shceduling string
        // function: compareString
        if (compareString(lowerCaseStringVal, "fcfc-n") != STR_EQ &&
            compareString(lowerCaseStringVal, "sjf-n") != STR_EQ &&
            compareString(lowerCaseStringVal, "srtf-p") != STR_EQ &&
            compareString(lowerCaseStringVal, "fcfs-p") != STR_EQ &&
            compareString(lowerCaseStringVal, "rr-p") != STR_EQ)
        {
            // set bool to false
            result = false;
        }
        // break
        break;

    // for quantum cycles
    case CFG_QUANT_CYCLES_CODE:
        // check for quantum cycles limits exceeded
        // set bool result to false
        if (intVal < 0 || intVal > 100)
        {
            result = false;
        }
        // break
        break;

    // for mem display
    case CFG_MEM_DISPLAY_CODE:
        // check for not finding 'on' or 'off'
        // function: compareString
        // set bool to false
        if (compareString(lowerCaseStringVal, "on") != STR_EQ &&
            compareString(lowerCaseStringVal, "off") != STR_EQ)
        {
            result = false;
        }
        // break
        break;

    // for mem available
    case CFG__MEM_AVAILABLE_CODE:
        // check for available mem limits exceeded
        // set bool to false
        if (intVal < 1024 || intVal > 102400)
        {
            result = false;
        }
        // break
        break;

    // for procces cycles
    case CFG_PROC_CYCLES_CODE:
        // check for process cycles limits exeeded
        // set bool to false
        if (intVal < 1 || intVal > 100)
        {
            result = false;
        }
        // break
        break;

    // for IO cycles
    case CFG_IO_CYCLES_CODE:
        // check for IO cycles limits exceeded
        // set bool to false
        if (intVal < 1 || intVal > 1000)
        {
            result = false;
        }
        // break
        break;

    // for log to operation
    case CFG_LOG_TO_CODE:
        // check for not finding one of the lof to stirngs
        // function: compareString
        if (compareString(lowerCaseStringVal, "both") != STR_EQ &&
            compareString(lowerCaseStringVal, "monitor") != STR_EQ &&
            compareString(lowerCaseStringVal, "file") != STR_EQ)
        {
            // set boolean result to false
            result = false;
        }
        // break
        break;
    }
    return result;
}
