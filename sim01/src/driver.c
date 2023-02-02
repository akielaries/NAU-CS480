/**
 * Command Line Parser driver for sim01, sim.c contains the driver for
 * running the sim. 
 */
#include "driver.h"
#include <string.h>
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

int main( int argc, char **argv ) 
    {
    printf("Simulator Program\n");
    printf("=================\n\n");

    //_Bool input_arg;

    //CmdLineData cmdLineData;
    //ConfigDataType *config_dataptr = 0x0;

    // process the cmd line argument
    //input_arg = processCmdLine(argc,argv,&cmdLineData);

    //if ( input_arg == false ) 
    //    {
    //        // show usage of the simulator
            usage();
    //    }


    printf("\n\n<------ TESTS ------>\n\n");
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


    printf("\n\nSimulator Program End.\n\n");
    return 0;
}


