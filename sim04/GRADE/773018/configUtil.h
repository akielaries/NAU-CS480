//INclude
#include "simUtil.h"

//Prototypes


//Checks all of the Data is Correct and Present
bool checkConfig(config *configData);

//Prints the Config File
void configPrint(config *configData);

//Reads in the Data
bool configRead(FILE *fh, config *configData, int lineCount);
