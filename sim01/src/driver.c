/**
 * Command Line Parser driver for sim01, sim.c contains the driver for
 * running the sim. 
 */
#include "driver.h"
#include <string.h>
#include <assert.h>

/**
 * Function to return the usage of sim01
 */
void usage() {
    printf("Command Line Format:\n");
    printf("     sim_0x [-dc] [-dm] [-rs] <config file name>\n");
    printf("     -dc [optional] displays configuration data\n");
    printf("     -dm [optional] displays meta data\n");
    printf("     -rs [optional] runs simulator\n");
    printf("     required config file name\n");
}

void clearCmdLineStruct(CmdLineData *clDataPtr)
{
    clDataPtr->programRunFlag = false;
    clDataPtr->configDisplayFlag = false;
    clDataPtr->mdDisplayFlag = false;
    clDataPtr->runSimFlag = false;
    clDataPtr->fileName[ 0 ] = NULL_CHAR;
}

_Bool processCmdLine(int numArgs,
                    char **strVector,
                    CmdLineData *clDataPtr)
{
    clearCmdLineStruct(clDataPtr);
    _Bool atLeastOneSwitchFlag = false;
    _Bool correctConfigFileFlag = false;
    int argIndex = 1;
    int fileStrLen;
    int fileStrSubLoc;

    if (numArgs >= MIN_NUM_ARGS)
    {
        while (argIndex < numArgs)
        {
            // DISPLAY CONFIG
            if(compareString(strVector[argIndex], "-dc") == STR_EQ)
            {
                clDataPtr->configDisplayFlag = true;
                atLeastOneSwitchFlag = true;
            }
            // DISPLAY METADATA
            else if(compareString(strVector[argIndex], "-dm") == STR_EQ )
            {
                clDataPtr->mdDisplayFlag = true;
                atLeastOneSwitchFlag = true;
            }
            // RUN SIMULATOR
            else if(compareString( strVector[ argIndex ], "-rs") == STR_EQ )
            {
                clDataPtr->runSimFlag = true;
                atLeastOneSwitchFlag = true;
            }
            // READING .cnf FILE
            else
            {
                fileStrLen = getStringLength(strVector[numArgs - 1]);
                fileStrSubLoc = findSubString(strVector[numArgs - 1], ".cnf");

                if(fileStrSubLoc != SUBSTRING_NOT_FOUND &&
                    fileStrSubLoc == fileStrLen - LAST_FOUR_LETTERS)
                {
                    copyString(clDataPtr->fileName, strVector[numArgs - 1]);
                    correctConfigFileFlag = true;
                }
                else
                {
                    clearCmdLineStruct(clDataPtr);
                }
            }
            argIndex++;
        }
    }
    return atLeastOneSwitchFlag && correctConfigFileFlag;
}

int main( int argc, char **argv ) 
{
    ConfigDataType *configDataPtr = NULL;
    OpCodeType *metaDataPtr = NULL;
    char errorMessage[MAX_STR_LEN];
    CmdLineData cmdLineData;
    _Bool configUploadSuccess = false;

    printf("Simulator Program\n");
    printf("=================\n\n");

    _Bool _Var1 = processCmdLine(argc,argv,&cmdLineData);
    if (_Var1 == false) 
    {
        usage();
    }
    else 
    {
        printf("<------------->");
    }


    printf("\n\nSimulator Program End.\n\n");

    printf("\n\n<------ TESTS ------>\n\n");
    /**
    char leftStr[] = "STRING TEST";
    char rightStr[] = "g f g";

    // Using strcmp()
    int res = compareString(leftStr, rightStr);

    if (res==0)
        printf("Strings are equal");
    else
        printf("Strings are unequal");

    printf("\nValue returned by strcmp() is:  %d\n", res);
    int lenres = getStringLength(leftStr);
    printf("\nLength returned by strlen() is: %d\n", lenres);

    char testStr[] = "Hello, World!";
    char searchSubStr[] = "World";

    int result = findSubString( testStr, searchSubStr );

    if (result != SUBSTRING_NOT_FOUND) {
        printf("The substring '%s' was found in '%s' starting at index %d\n",
                searchSubStr, testStr, result);
    } else {
        printf("The substring '%s' was not found in '%s'\n", 
                searchSubStr, testStr);
    }

    char destStr[MAX_STR_LEN] = "Hello";
    char sourceStr[] = ", World!";

    concatenateString(destStr, sourceStr);
    printf("The concatenated string is: %s\n", destStr);

    char source[] = "Hello World";
   char dest[100];

   // Test 1: Test when startIndex is 0 and endIndex is 5
   getSubString(dest, source, 0, 5);
   //assert(strcmp(dest, "Hello") == 0);
   printf("%s   %s\n", dest, source);

   char sourceStr_A[] = "This is a sample string";
   char destStr_A[100];
   int startIndex = 4;
   int endIndex = 10;

   // Call the getSubString function
   getSubString(destStr_A, sourceStr_A, startIndex, endIndex);

   // Print the result
   printf("Substring of '%s' from index %d to %d: '%s'\n",
          sourceStr_A, startIndex, endIndex, destStr_A);

    char testChar = 'K';

    int lowerCaseChar = toLowerCase(testChar);

    printf("The lower case character is: %c\n", lowerCaseChar);

    char source_str_1[100] = "HELLO, World!, AGAIN";
    char dest_str_1[100];

    setStrToLowerCase(dest_str_1, source_str_1);

    printf("The lowercase string is: %s\n", dest_str_1);
    */
    printf("\n\n<------ TESTS ------>\n\n");

    return 0;
}


