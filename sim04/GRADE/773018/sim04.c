//Import utilities
#include "simulator.h"



// main 

int main(int argc, char **argv)
    {
        //initialize variables
        char *configFile;
        opcode meta; 
        config configData;
        char *currentInput;
        char arg[3][4] = {"-dc", "-dm", "-rs"};
        


        //malloc
        meta.metaData = (command *) malloc(ARRAY_CAP * sizeof(command));

        //set capacity
        meta.capacity = ARRAY_CAP;

        //set defeault size 
        meta.size = -1;

        if (argc < 1)
        {
            errorPrint();
            return ZERO;
        }
        //Define the Variable for Config

        configFile = argv[argc - 1];

        printf("\nSimulator Program");
        printf("\n=================\n\n");

        //Open Config File and Store Data
        
        FILE *fileHandle = fopen(configFile, "r");

        if(configRead(fileHandle, &configData, ZERO) == true)
        {
            //Close config file
            fclose(fileHandle);
           //Open MetaData and Store Data

            FILE *fileHandle2 = fopen(configData.metaFile, "r");
            
            if(!metaRead(fileHandle2, ZERO, &meta))
            {
                return ZERO;
            }

            fclose(fileHandle2);
        }

        //CHECK ALL DATA IS VALID
        if(checkConfig(&configData))
        {
        // Check What must be printed in What order

        int indexOut, indexIn;
        int result;

        for(indexOut = 1; indexOut < (argc - 1); indexOut++)
            {
            //Loop until argc - 1
                currentInput = argv[indexOut];
            //Compare to each and run as instructed
                indexIn = ZERO;
                result = -1;
                while(result != ZERO && indexIn < 4)
                {
                    result = compareStr(currentInput, arg[indexIn]);
                    indexIn++;
                }
                switch(indexIn)
                {
                    case 1: //-dc aka Display Config
                        configPrint(&configData);
                        break;

                    case 2: //-dm aka Display Meta
                        if (metaCheck(&meta))
                        {
                        metaPrint(&meta);
                        }
                        break;

                    case 3: //-rs aka Run sim
                        runSim(&meta, &configData);
                        break;

                    case 4: // Nothing Found
                        printf("Incorrect Arguments");
                        break;
                }

            }
        }
        free(meta.metaData);
        //end program
        printf("\nSimulation Program End.");
        return ZERO; 
    }