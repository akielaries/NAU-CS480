#include "configUtil.h"


// Config read
    //Reads and Stores the Config Data
bool configRead(FILE *fh, config *configData, int lineCount)
    {
        char currentString[ARRAY_CAP];
        char endLine;
        // Check Line Count aka Check start line is true
        if (lineCount == ZERO)
        {
            fscanf(fh, "%[^\n]s ", currentString);
            if (compareStr(currentString, 
                        "Start Simulator Configuration File:") != ZERO)
                {
                    return false;
                }
            //jumps line
            endLine = fgetc(fh);
        }


        // Check Line Count aka Check end line is true
        else if (lineCount == MAX_CONFIG_COUNT)
        {
            fscanf(fh, "%[^\n]s ", currentString);
            if (compareStr(currentString, 
                        "End Simulator Configuration File. ") != ZERO)
                {
                    return false;
                }
            else
            {
                return true;
            }

        }
        
        
        fscanf(fh, "%[^:]s", currentString);
        endLine = fgetc(fh);
        endLine = fgetc(fh);


        // Check which Line was Read

        if (compareStr(currentString, 
                        "Version/Phase") == ZERO)
            {
                // Read Data
                fscanf(fh, "%f", &configData->version);
            }
        else if (compareStr(currentString, 
                        "File Path") == ZERO)
            {
                // Read Data
                fscanf(fh, "%s", configData->metaFile);

            }
        else if (compareStr(currentString, 
                        "CPU Scheduling Code") == ZERO)
            {
                // Read Data
                fscanf(fh, "%s", configData->CPUSS);
            }
        else if (compareStr(currentString, 
                        "Quantum Time (cycles)") == ZERO)
            {
                // Read Data
                fscanf(fh, "%d", &configData->quanTime);
            }
        else if (compareStr(currentString, 
                        "Memory Available (KB)") == ZERO)
            {
                // Read Data
                fscanf(fh, "%d", &configData->memAval);

            }
        else if (compareStr(currentString, 
                        "Memory Display (On/Off)") == ZERO)
            {
                // Read Data
                fscanf(fh, "%s", configData->memoryDisp);

            }
        else if (compareStr(currentString, 
                        "Processor Cycle Time (msec)") == ZERO)
            {
                // Read Data
                fscanf(fh, "%d", &configData->cycleRateP);

            }
        else if (compareStr(currentString, 
                        "I/O Cycle Time (msec)") == ZERO)
            {
                // Read Data
                fscanf(fh, "%d", &configData->cycleRateIO);
            }
        else if (compareStr(currentString, 
                        "Log To") == ZERO)
            {
                // Read Data
                fscanf(fh, "%s", configData->logTo);
            }
        else if (compareStr(currentString, 
                        "Log File Path") == ZERO)
            {
                // Read Data
                fscanf(fh, "%s", configData->logFile);
            }
        else 
            {
                //Wrong Line was read
                errorPrint();
                return false;
            }


        // Get End line
        endLine = fgetc(fh);
    
        // Catch Mac \r (P.S. Windows have \n, Mac has \r\n to represent endlines)
        if(endLine == '\r')
        {
            endLine = fgetc(fh);
        }

        // Checks if read over next line and its not the end of file
        if(!feof(fh))
        {
            //Ups the line count
            lineCount++;
            //Ungets the c incase it overwrote something
            //Recurse
            return configRead(fh, configData, lineCount);
        }
            

        return false;
    }


// Config print
    //Prints Config File
void configPrint(config *configData)
    {
        printf("\nConfig File Display\n-------------------");

        printf("\nVersion                 :  %f", configData->version);
        printf("\nProgram file name       :  %s", configData->metaFile);
        printf("\nCPU schedule selection  :  %s", configData->CPUSS); 
        printf("\nQuantum time            :  %d", configData->quanTime);
        printf("\nMemory Available        :  %d", configData->memAval); 
        printf("\nMemory Display (On/Off) :  %s", configData->memoryDisp);
        printf("\nProcess cycle rate      :  %d", configData->cycleRateP);
        printf("\nI/O cycle rate          :  %d", configData->cycleRateIO);
        printf("\nLog to selection        :  %s", configData->logTo);
        printf("\nLog file name           :  %s", configData->logFile);

        printf("\n\n\n");

    }


//Check Data
bool checkConfig(config *configData)
    {
        //Initlize Variables

        // Array Max Length Max Capacity [# of vals][# of Max Chars in Each Val]
        char CPUcode[5][10] = {"FCFS-N","SJF-N","SRTF-P", "FCFS-P", "RR-P"};
        char IO[2][4] = {"On", "Off"};
        char logTo[3][10] = {"Monitor", "File", "Both"};

        int index = ZERO;
        int result = DUMMY_VAL;


        //NOTE ALL LITERALS IN IF STATEMENTS ARE EXPLICITLY 
        //PROVIDED IN THE INSTRUCTIONS DOCUMENT AS MAX AND MINS 
        //FOR THE FOLLOWING VALUES:

        //Check for Version Correct
        if(configData->version > MAX_CONFIG_COUNT || configData->version < ZERO)
        {
            errorPrint();
            return false;
        }

        //Check for FilePath
        if(configData->metaFile == NULL)
        {
            errorPrint();
            return false;
        }

        //Check for  CPU code
        while (result != ZERO && index < 5)
        {
            result = compareStr(CPUcode[index], configData->CPUSS);
            index++;
        }
        if ( result != ZERO )
        {
            errorPrint();
            return false;
        }
    
        //Result Vals for NEXT LOOP
        result = DUMMY_VAL;
        index = ZERO;

        //Check Quantum time
        if(configData->quanTime > 100 || configData->quanTime < ZERO)
        {
            errorPrint();
            return false;
        }

        //Check Memory Available
        if(configData->memAval > 102400 || configData->memAval < 1024)
        {
            errorPrint();
            return false;
        }

        //Check Memory
        while (result != 0 && index < 2)
        {
            result = compareStr(IO[index], configData->memoryDisp);
            index++;
        }
        if ( result !=0 )
        {
            errorPrint();
            return false;
        }
        // Check Cycle time Process 
        if(configData->cycleRateP > 100 || configData->cycleRateP < 1)
        {
            errorPrint();
            return false;
        }

        // Check Cycle time IO
        if(configData->cycleRateIO > 1000 || configData->cycleRateIO < 1)
        {
            errorPrint();
            return false;
        }

        //Result Vals for Next LOOP
        result = DUMMY_VAL;
        index = ZERO;

        // Check Log to
        while (result != 0 && index < 4)
        {
            result = compareStr(logTo[index], configData->memoryDisp);
            index++;
        }
        if ( result !=0 )
        {
            errorPrint();
            return false;
        }

        // Check Log File Path
    
        if(configData->logFile == NULL)
        {
            errorPrint();
            return false;
        }

        //All data is correct
        return true;
    }
