/**
 * Main driver for sim01
 */
#include <stdio.h>
#include "types.h"


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

    _Bool _var1;
    config_datatype *config_dataptr = 0x0;

    usage();

    printf("Simulator Program End.\n\n");
    return 0;
}


