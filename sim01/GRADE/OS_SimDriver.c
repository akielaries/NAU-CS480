// Header files
#include "OS_SimDriver.h"

int main(int argc, char **argv)
{
    // Initialize Program
    // Initialize variables
    ConfigDataType *configDataPtr = NULL;
    OpCodeType *metaDataPtr = NULL;
    char errorMessage[MAX_STR_LEN];
    CmdLineData cmdLineData;
    bool configUploadSuccess = false;

    // Show title
    // function: printf
    printf("\nSimulator Program\n");
    printf("=================\n\n");

    // Process command line, check for program run
    // at least one correct switch and config file name (at end)
    // function: processCmdLine
    if (processCmdLine(argc, argv, &cmdLineData))
    {
        // upload config file, check for success
        // function: getConfigData
        if (getConfigData(cmdLineData.fileName, &configDataPtr,
                          errorMessage))
        {
            // check config display flag
            if (cmdLineData.configDisplayFlag)
            {
                // display config data
                // function: displayConfigData
                displayConfigData(configDataPtr);
            }
            // set config upload success flag
            configUploadSuccess = true;
        }

        // otherwise, assume config file upload failure
        else
        {
            // show error message, end program
            // function: printf
            printf("\nConfig Upload Error: %s, program aborted\n\n",
                   errorMessage);
        }
        // check for config success and need for metadata
        if (configUploadSuccess &&
            (cmdLineData.mdDisplayFlag || cmdLineData.runSimflag))
        {
            // upload metadata file, check for success
            // function: getMetaData
            if (getMetaData(configDataPtr->metaDataFileName, &metaDataPtr,
                            errorMessage))
            {
                // check metadata display flag
                if (cmdLineData.mdDisplayFlag)
                {
                    // display metadata
                    // function: displayMetaData
                    displayMetaData(metaDataPtr);
                }
                // check run simulator flag
                if (cmdLineData.runSimflag)
                {
                    // run simulator
                    // function: runSim
                    runSim(configDataPtr, metaDataPtr);
                }
            }
            // otherwise, assume metadata upload failure
            else
            {
                // show error message, end program
                // function: printf
                printf("\nMetadata Upload Error: %s, program aborted\n",
                       errorMessage);
            }
        }
        // end check need for metadata upload

        // clean up config data as needed
        // function: clearConfigData
        configDataPtr = clearConfigData(configDataPtr);

        // clean up metadata as needed
        // function: clearMetaDataList
        metaDataPtr = clearMetaDataList(metaDataPtr);
    }
    // end check for good command line

    // otherwise assume command line failure
    else
    {
        // show command line argument requirements
        // function: showCommandLineFormat
        showCommandLineFormat();
    }
    // show program end
    // function: printf
    printf("\nSimulator Program End.\n");

    // return success
    return 0; // temp stub return TODO: remove when no longer temp
}

/*
Name: clearCmdLineStruct
Process: sets command line structure data to defaults
         Boolean to false, fileName to empty string
Funciton Input params: pointer to command line structure
Function Output params: pointer to command line strcture
                        with updated members
Function Output returned: none
Input: none
Output: none
Dependencies: none
*/
void clearCmdLineStruct(CmdLineData *clDataPtr)
{
    // Set all struct members to default
    clDataPtr->programRunFlag = false;
    clDataPtr->configDisplayFlag = false;
    clDataPtr->mdDisplayFlag = false;
    clDataPtr->runSimflag = false;
    clDataPtr->fileName[0] = NULL_CHAR;
}

/*
Name: processCmdLine
Process: checks for at least two arguments,
         then sets booleans depending on command line switches
         which can be in any order,
         also captures config file name which must be the last arguments
Function Input/Parameters: number of arguments (int),
                           vector of arguments (char **)
Function Output/Parameters: pointer to commandline stucture (CmdLineData *)
                            with updated members,
                            set to default values if failure
                            to capture arguments
Function OUtput/Returned: Boolean result of argument capture,
                          true if at least on swithc and config file name,
                          false otherwise
Device Input/device: none
Device Output/device: none
Dependencies: tbd
*/
bool processCmdLine(int numArgs, char **strVector, CmdLineData *clDataPtr)
{
    // Initialize function

    // Initialize structures to defaults
    // Function: clearStruct
    clearCmdLineStruct(clDataPtr);

    // Initialize success flag to false
    bool atLeastOneSwitchFlag = false;
    bool correctConfigFileFlag = false;

    // initialize first arg index to one
    int argIndex = 1;

    // declare other variables
    int fileStLen, fileStrSubLoc;

    // must have a prog name, at least one switch, and config file name
    if (numArgs >= MIN_NUM_ARGS)
    {
        // loop across args (starting at 1) and program run flag
        while (argIndex < numArgs)
        {
            // check for -dc
            if (compareString(strVector[argIndex], "-dc") == STR_EQ)
            {
                // set config display flag
                clDataPtr->configDisplayFlag = true;

                // set at least one switch flag
                atLeastOneSwitchFlag = true;
            }
            // otherwise, check for -dm
            else if (compareString(strVector[argIndex], "-dm") == STR_EQ)
            {
                // set metadata flag
                clDataPtr->mdDisplayFlag = true;

                // set at least one switch flag
                atLeastOneSwitchFlag = true;
            }
            // otherwise check for -rs
            else if (compareString(strVector[argIndex], "-rs") == STR_EQ)
            {
                // set run sim flag
                clDataPtr->runSimflag = true;

                // set at least one switch flag
                atLeastOneSwitchFlag = true;
            }
            // otherwise check for file name, ending in .cfg
            else
            {
                // find length to verfy name
                fileStLen = getStringLength(strVector[numArgs - 1]);
                fileStrSubLoc =
                    findSubstring(strVector[numArgs - 1], ".cnf");

                // check for file existence and correct format
                if (fileStrSubLoc != SUBSTRING_NOT_FOUND &&
                    fileStrSubLoc == fileStLen - LAST_FOUR_LETTERS)
                {
                    // set file name variable
                    copyString(clDataPtr->fileName,
                               strVector[numArgs - 1]);

                    // set success flag to true
                    correctConfigFileFlag = true;
                }
                // otherwise assume bad config file name
                else
                {
                    // reset struct
                    // funciton: clearStruct
                    clearCmdLineStruct(clDataPtr);
                }
            }

            // update arg loop
            argIndex++;
        }
        // end arg loop
    }
    // end test for min args

    // return verfication of at least one switch and correct file name
    return atLeastOneSwitchFlag && correctConfigFileFlag;
}

/*
Name: showCommandLineFormat
Process: displays command line format as assistance to user
Function Input/Parameters: none
Function Output/Parameters: none
Function OUtput/Returned: none
Device Input/device: none
Device Output/device: data displayed as specified
Dependencies: printf
*/
void showCommandLineFormat()
{
    // Display command line format
    // function: printf
    printf("Command Line Format:\n");
    printf("    sim_01 [-dc] [-dm] [-rs] <config file name>\n");
    printf("    -dc [optional] displays configuration data\n");
    printf("    -dm [optional] displays meta data\n");
    printf("    -rs [optional] runs simulator\n");
    printf("    required config file name\n");
}