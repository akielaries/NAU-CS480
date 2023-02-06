// Header files
#include "metadataops.h"
/*
Name: addNode
Process: adds metadata node to linked list recursively,
         handles empty list condition
Function Input/Parameters: pointer to head or next linked node
                           pointer to new node
Function Output/Parameters: none
Function OUtput/Returned: pointer to pervioud node
Device Input/device: none
Device Output/device: none
Dependencies: malloc, copyString
*/
OpCodeType *addNode(OpCodeType *localPtr, OpCodeType *newNode)
{
    // check for null
    if (localPtr == NULL)
    {
        // access memory for new link/node
        localPtr = (OpCodeType *) malloc(sizeof(OpCodeType));

        // assign values to new node
        localPtr->pid = newNode->pid;
        copyString(localPtr->command, newNode->command);
        copyString(localPtr->inOutArg, newNode->inOutArg);
        copyString(localPtr->strArg1, newNode->strArg1);
        localPtr->intArg2 = newNode->intArg2;
        localPtr->intArg3 = newNode->intArg3;
        localPtr->opEndTime = newNode->opEndTime;

        localPtr->nextNode = NULL;
        return localPtr;
    }   
    // assume end of list not found
    // recursion
    localPtr->nextNode = addNode(localPtr->nextNode, newNode);

    // return local ptr
    return localPtr;
}

/*
Name: clearMetaDataList
Process: recursively traverses list, frees dynamically allocated nodes
Function Input/Parameters: node op code (const OpcodeType *)
Function Output/Parameters:  none
Function OUtput/Returned: NULL (OpCodeType *)
Device Input/device: none
Device Output/device: none
Dependencies: tbd
*/
OpCodeType *clearMetaDataList(OpCodeType *localPtr)
{
    // check if not NULL
    if (localPtr != NULL)
    {
        // call recursive function with next ptr
        clearMetaDataList(localPtr->nextNode);

        // release memeory
        free(localPtr);
        localPtr = NULL;
    }
    return NULL;
}

/*
Name: displayMetaData
Process: data dump/display of all op code items
Function Input/Parameters: pointer to head of op code/metadata list 
                           (const OpCodeType *)
Function Output/Parameters: none
Function OUtput/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: tbd
*/
void displayMetaData(const OpCodeType *localPtr)
{
    // Display title
    printf("Meta-Data File Display\n");
    printf("----------------------\n\n");

    // loop to end of linked list
    while (localPtr != NULL)
    {
        printf("Op Code: ");
        printf("/pid: %d", localPtr->pid);
        printf("/cmd: %s", localPtr->command);
        if (compareString(localPtr->command, "dev") == STR_EQ)
        {
            printf("/io: %s", localPtr->inOutArg);
        }

        else
        {
            printf("/io: NA");
        }
        printf("\n\t /arg1: %s", localPtr->strArg1);
        printf("/arg 2: %d", localPtr->intArg2);
        printf("/arg 3: %d", localPtr->intArg3);
        printf("/op end time: %8.6f", localPtr->opEndTime);
        printf("\n\n");

        // assign local pointer to next node
        localPtr = localPtr->nextNode;
    }
}

/*
Name: getCommand
Process: parses three letter command part of op code str
Function Input/Parameters: input op code str, 
                           starting index
Function Output/Parameters: parsed command
Function OUtput/Returned: updated starting index for use by calling func
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
int getCommand(char *cmd, const char *inputStr, int index)
{
    // initialize
    int lengthOfCommand = 3;
    
    // loop across command
    while (index <  lengthOfCommand)
    {   
        // assign char from input to buffer
        cmd[index] = inputStr[index];

        // increment index
        index++;

        // set next char to null
        cmd[index] = NULL_CHAR;
    }
    return index;
}

/*
Name: getMetaData
Process: main driver function to upload, parse, and store list
         of op code commands in a linked list
Function Input/Parameters: file name (const char *)
Function Output/Parameters: pointer to op code linked list head pointer 
                            (opCodeType **),
                            result message of funcitno state after completion
                            (char *)
Function OUtput/Returned: Boolean resuilt of operation (bool)
Device Input/device: op code list uploaded
Device Output/device: none
Dependencies: copyString, fopen, getStringToDelimiter, compareString, fclose,
              malloc, getOpCommand, updateStartCommand, updateEndCount,
              clearMetaDataList, free, addNode
*/
bool getMetaData(const char *filename, OpCodeType **opCodeDataHead, 
                                                              char *endStateMsg)
{
    // initialize

        // read only
        const char READ_ONLY_FLAG[] = "r";

        // variables
        int accessResult, startCount = 0, endCount = 0;
        char dataBuffer[MAX_STR_LEN];
        bool returnState = true;
        OpCodeType *newNodePtr;
        OpCodeType *localHeadPtr = NULL;
        FILE *fileAccessPtr;

    // intitialize op code ptr
    *opCodeDataHead = NULL;

    // end sate message
    copyString(endStateMsg, "Metadata file upload successful");

    // open file
    fileAccessPtr = fopen(filename, READ_ONLY_FLAG);
    if (fileAccessPtr == NULL)
    {
        copyString(endStateMsg, "Metadata file access error");
        return false;
    }

    // check first line for correct leader
    if (!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer)
        || compareString(dataBuffer, "Start Program Meta-data Code") != STR_EQ)
    {
        fclose(fileAccessPtr);
        copyString(endStateMsg, "Corrupt metadata leader line error");

        return false;
    }

    // allocate memory
    newNodePtr = (OpCodeType *) malloc(sizeof(OpCodeType));

    // get first command
    accessResult = getOpCommand(fileAccessPtr, newNodePtr);
    startCount = updateStartCount(startCount, newNodePtr->strArg1);
    endCount = updateEndCount(endCount, newNodePtr->strArg1);

    // check for failure for first op
    if (accessResult != COMPLETE_OPCMD_FOUND_MSG)
    {
        // close file
        fclose(fileAccessPtr);
        *opCodeDataHead = clearMetaDataList(localHeadPtr);
        free(newNodePtr);

        return false;
    }

    while (accessResult == COMPLETE_OPCMD_FOUND_MSG)
    {
        // add the new command
        localHeadPtr =  addNode(localHeadPtr, newNodePtr);

        // get  a new op command
        accessResult = getOpCommand(fileAccessPtr, newNodePtr);
        startCount = updateStartCount(startCount, newNodePtr->strArg1);
        endCount = updateEndCount(endCount, newNodePtr->strArg1);
    }
    
    // afterloop completion check for last command
    if (accessResult == LAST_OPCMD_FOUND_MSG)
    {
        if (startCount == endCount)
        {
            localHeadPtr = addNode(localHeadPtr, newNodePtr);
            accessResult = NO_ACCESS_ERR;
        }

        // check last line for incorrect end decriptor
        if (!getStringToDelimiter(fileAccessPtr, PERIOD, dataBuffer)
            || compareString(dataBuffer, "End Program Meta-Data Code")
                                                                != STR_EQ)
        {
            // set access result
            accessResult = MD_CORRUPT_DESCRIPTOR_ERR;

            // set end msg
            copyString(endStateMsg, "Metadata corrupted decriptor error");
        }
        else 
        {
            // close file
            fclose(fileAccessPtr);
            *opCodeDataHead = clearMetaDataList(localHeadPtr);
            free(newNodePtr);
            accessResult = UNBALANCED_START_END_ERR;
            copyString(endStateMsg, "Unbalanced start and end arguments in metadata");

            return false;
        }
    }

    else
    {
        copyString(endStateMsg, "Corrupted metadata op code");
        return false;
    }

    // check for any errors found
    if (accessResult != NO_ACCESS_ERR)
    {
        // clear list
        localHeadPtr = clearMetaDataList(localHeadPtr);

    }

    //close file
    fclose(fileAccessPtr);
    free(newNodePtr);
    *opCodeDataHead = localHeadPtr;

    return returnState;   
}

/*
Name: getOpCommand
Process: aquireone op  command kube from a previously opened file,
         parse it, and sets varaious struct members according
         to the thee letter commmand
Function Input/Parameters: ptr to file
Function Output/Parameters: ptr to op code 
Function OUtput/Returned: coded result
Device Input/device: op code line uploaded
Device Output/device: none
Dependencies: getSringToDelimiter. getCommand, copyString, verifyValidCommand,
              compareString, getStringArg, verifyFirstSTringArg, getNumberArg
*/
OpCodeMessages getOpCommand(FILE *filePtr, OpCodeType *inData)
{
    // Initialize function

        // local consts
        const int MAX_CMD_LENGTH = 5;
        const int MAX_ARG_STR_LENGTH = 15;

        //others
        int numBuffer = 0;
        char strBuffer[STD_STR_LEN];
        char cmdBuffer[MAX_CMD_LENGTH];
        char argStrBuffer[MAX_ARG_STR_LENGTH];
        int runningStringIndex = 0;
        bool arg2FailureFlag = false;
        bool arg3FailureFlag = false;

        //get whole opCode as string (check for success)
        if (getStringToDelimiter(filePtr, SEMICOLON, strBuffer))
        {
            // get 3 letter command
            runningStringIndex = getCommand(cmdBuffer,
                                                strBuffer, runningStringIndex);

            // assign op command to node
            copyString(inData->command, cmdBuffer);
        }

        // otherwise assume unsuccessful
        else
        {
            // set ptr data to null
            inData = NULL;
            return OPCMD_ACCESS_ERR;
        }

        //verify opcmd
        if (!verifyValidCommand(cmdBuffer))
        {
            //return opcmd err
            return CORRUPT_OPCMD_ERR;
        }

        // set struct val to defaults
        inData->pid = 0;
        inData->inOutArg[0] = NULL_CHAR;
        inData->intArg2 = 0;
        inData->intArg3 = 0;
        inData->opEndTime= 0.0;
        inData->nextNode = NULL;

        // check for device cmd
        if (compareString(cmdBuffer, "dev") == STR_EQ)
        {
            // get arg
            runningStringIndex = getStringArg(argStrBuffer,
                                        strBuffer, runningStringIndex);

            // set device in/out arg
            copyString(inData->inOutArg, argStrBuffer);

            // check correct arg
            if (compareString(argStrBuffer, "in") != STR_EQ
                        && compareString(argStrBuffer, "out") != STR_EQ)
            {
                // return arg error
                return CORRUPT_OPCMD_ARG_ERR;
            }
        }
    
        // get first string arg
        runningStringIndex = getStringArg(argStrBuffer, strBuffer,
                                                            runningStringIndex);
        copyString(inData->strArg1, argStrBuffer);

        // check for legit arg
        if (!verifyFirstStringArg(argStrBuffer))
        {
            // return error
            return CORRUPT_OPCMD_ARG_ERR;
        }

        // check for last opcmd
        if (compareString(inData->command, "sys") == STR_EQ
                    && compareString(inData->strArg1, "end") == STR_EQ)
        {
            return LAST_OPCMD_FOUND_MSG;
        }

        // check for app start seconds arg
        if (compareString(inData->command, "app") == STR_EQ
                        && compareString(inData->strArg1, "start") == STR_EQ)
        {
            // get num arg
            runningStringIndex = getNumberArg(&numBuffer, strBuffer,
                                                            runningStringIndex);

            // check for failed access
            if (numBuffer <= BAD_ARG_VAL)
            {
                arg2FailureFlag = true;
            }
            inData->intArg2 = numBuffer;
        }
        // check for cpu cycle time
        else if (compareString(inData->command, "cpu") == STR_EQ)
        {
            // get num arg
            runningStringIndex = getNumberArg(&numBuffer, strBuffer,
                                                    runningStringIndex);

            // check for failed access
            if (numBuffer <= BAD_ARG_VAL)
            {
                // set failure flag
                arg2FailureFlag = true;
            }
            inData->intArg2 = numBuffer;
        }
         else if (compareString(inData->command, "dev") == STR_EQ)
        {
            // get num arg
            runningStringIndex = getNumberArg(&numBuffer, strBuffer,
                                                    runningStringIndex);

            // check for failed access
            if (numBuffer <= BAD_ARG_VAL)
            {
                // set failure flag
                arg2FailureFlag = true;
            }
            inData->intArg2 = numBuffer;
        }
         else if (compareString(inData->command, "mem") == STR_EQ)
        {
            // get num arg
            runningStringIndex = getNumberArg(&numBuffer, strBuffer,
                                                    runningStringIndex);

            // check for failed access
            if (numBuffer <= BAD_ARG_VAL)
            {
                // set failure flag
                arg2FailureFlag = true;
            }
            inData->intArg2 = numBuffer;

            // get 2nd num
            runningStringIndex = getNumberArg(&numBuffer, strBuffer,
                                                    runningStringIndex);

            // check for failed access
            if (numBuffer <= BAD_ARG_VAL)
            {
                // set failure flag
                arg2FailureFlag = true;
            }
            inData->intArg2 = numBuffer;
        }
        
        // check int args for failure
        if (arg2FailureFlag || arg3FailureFlag)
        {
            // return corrupt opcmd
            return CORRUPT_OPCMD_ARG_ERR;
        }
        // return complete opcmd found
        return COMPLETE_OPCMD_FOUND_MSG;
}

/*
Name: getNumberArg
Process: starts at given index, captures, and assembles int arg
         and return ptr
Function Input/Parameters: input string, starting index
Function Output/Parameters: ptr to captured in val
Function OUtput/Returned: updated index
Device Input/device: none
Device Output/device: nome
Dependencies: isDigit
*/
int getNumberArg(int *number, const char *inputString, int index)
{
    // initialize
    bool foundDigit = false;
    *number = 0;
    int multiplier = 1;

    // loop to skip white space
    while (inputString[index] <= SPACE || inputString[index] == COMMA)
    {
        index++;
    }

    // loop across string
    while (isDigit(inputString[index]) == true
                                        && inputString[index] != NULL_CHAR)
    {
        foundDigit = true;
        (*number) = (*number) * multiplier + inputString[index] - '0';

        index++; multiplier = 10;
    }
    if (!foundDigit)
    {
        *number = BAD_ARG_VAL;
    }

    // return index
    return index;
}

/*
Name: getStringArg
Process: starts at given index, captures and assembles string arg
         and returns as parameter
Function Input/Parameters: input strng, start index
Function Output/Parameters: ptr to captured string
Function OUtput/Returned: updated index
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
int getStringArg(char *strArg, const char *inputStr, int index)
{
    int localIndex = 0;

    while (inputStr[index] == SPACE || inputStr[index] == COMMA)
    {
        index++;
    }

    while(inputStr[index] != COMMA && inputStr[index] != NULL_CHAR)
    {
        strArg[localIndex] = inputStr[index];
        index++, localIndex++;
        strArg[localIndex] = NULL_CHAR;
    }

    return index;
}

/*
Name: isDigit
Process: true if number is between 0 and 9
Function Input/Parameters: test char
Function Output/Parameters: none
Function OUtput/Returned: bool
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
bool isDigit(char testChar)
{
    return (testChar >+ '0' && testChar <= '9');
}

/*
Name: updateEndCount
Process: managets cound of end arg to be compared at end
Function Input/Parameters: intital count, test string
Function Output/Parameters: none
Function OUtput/Returned: updated count
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
int updateEndCount(int count, const char *opString)
{
    // check for end
    if (compareString(opString, "end") == STR_EQ)
    {
        return count + 1;
    }

    return count;
}

/*
Name: updateStartCount
Process: managets count of end arg to be compared at end
Function Input/Parameters: intital count, test string
Function Output/Parameters: none
Function OUtput/Returned: updated count
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
int updateStartCount(int count, const char *opString)
{
    // check for end
    if (compareString(opString, "start") == STR_EQ)
    {
        return count + 1;
    }

    return count;
}

/*
Name: verifyFirstStringArg
Process: check for all possible first arg string 
Function Input/Parameters: test string
Function Output/Parameters: none
Function OUtput/Returned: bool
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
bool verifyFirstStringArg(const char *strArg)
{
    // check for string holding correct first arg, return
    return (compareString(strArg, "access") == STR_EQ
    || compareString(strArg, "allocate") == STR_EQ
    || compareString(strArg, "end") == STR_EQ
    || compareString(strArg, "ethernet") == STR_EQ
    || compareString(strArg, "hard drive") == STR_EQ
    || compareString(strArg, "keyboard") == STR_EQ
    || compareString(strArg, "monitor") == STR_EQ
    || compareString(strArg, "printer") == STR_EQ
    || compareString(strArg, "process") == STR_EQ
    || compareString(strArg, "serial1") == STR_EQ
    || compareString(strArg, "sound signal") == STR_EQ
    || compareString(strArg, "start") == STR_EQ
    || compareString(strArg, "usb") == STR_EQ
    || compareString(strArg, "video signal") == STR_EQ);
}

/*
Name: verifyValidCommand
Process: checks all possibilites of three letter op code
Function Input/Parameters: test str
Function Output/Parameters: none
Function OUtput/Returned: bool
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
bool verifyValidCommand(char *testCmd)
{
    // check for string holding 3 letter code
    return (compareString(testCmd, "sys") == STR_EQ
    || compareString(testCmd, "app") == STR_EQ
    || compareString(testCmd, "cpu") == STR_EQ
    || compareString(testCmd, "mem") == STR_EQ
    || compareString(testCmd, "dev") == STR_EQ);
}