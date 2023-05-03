#include "metaUtil.h"




// Meta data Read
    //Reads and Stores Meta Data
bool metaRead(FILE *fh2, int recCount, opcode *meta)
    {
        //Intialize Variables
        char currentString[ARRAY_CAP];
        int currentInt;
        char dummy;
        char IO[3][4] = {" in", " out"};
        int result = DUMMY_VAL; 
        int index = ZERO;


        //Check if Resize is needed
            //using the size
        checkForResize(meta);

        //Catches BEGINNING LINE
        if( meta->size == DUMMY_VAL)
        {
            fscanf(fh2, "%[^:]s", currentString);
            dummy = fgetc(fh2);
            meta->size++;
        }

        //Switch Case
        switch(recCount)
        {
            case 0: // CMD
            //If recCount == ZERO
                fscanf(fh2, "%s", currentString);
                
                //check if reached the end
                result = compareStr("End", currentString);
                if (result == ZERO)
                {
                    return true;
                }

                //Store Cmd
                copyStr(meta->metaData[meta->size].cmd, currentString);
                recCount++;
            break;

            case 1: // IO or Argv1
            //If recCount == 1

                fscanf(fh2, "%[^,^\n]s", currentString);
                result = -1; 
                index = ZERO;
                //Check for IO
                while (result != ZERO && index < DOUBLE)
                {
                    result = compareStr(IO[index], currentString);
                    index++;
                }

                // STORE INTO ARGV1 IF IO FAILS
                if ( result !=ZERO )
                {
                    copyStr(meta->metaData[meta->size].arg1, currentString);

                    //If IO fails, recCount jumps to 3
                    //Preset Data

                    //IO will be an NA
                    copyStr(meta->metaData[meta->size].io, "NA");

                    //Argv 2 and 3 are ZERO just in case
                    meta->metaData[meta->size].arg2 = ZERO;
                    meta->metaData[meta->size].arg3 = ZERO;
                    recCount = 3; 

                }
                else
                {
                    //Store IO
                    copyStr(meta->metaData[meta->size].io, currentString);
                    recCount = 2;
                    dummy = fgetc(fh2);
                }
                //Catch the Comma
            break;

            case 2: //ARGV1
            //If recCount == 2
                fscanf(fh2, "%[^,^\n]s", currentString);
                //Store argv1

                copyStr(meta->metaData[meta->size].arg1, currentString);

                //Autoset Arg 2 and 3 incase empty
                meta->metaData[meta->size].arg2 = ZERO;
                meta->metaData[meta->size].arg3 = ZERO;

                //Just to ARGV 2
                recCount = 3;
            break;

            case 3: // ARGV 2
            //If recCount == 3
                fscanf(fh2, ", %d[^,^\n]", &currentInt);

                //Store argv2
                meta->metaData[meta->size].arg2 = currentInt;

                // Jump to ARGV 4
                recCount = 4;
            break;

            case 4: // ARGV3
            //If recCount == 4
                fscanf(fh2, ", %d[^,^\n]", &currentInt);

                //Store argv3
                meta->metaData[meta->size].arg3 = currentInt;

            break;

        }
        
        // Reads the End of line or Next Char
        dummy = fgetc(fh2);

        //CATCHES THE MAC ENDLINE
        if(dummy == '\r')
        {
            dummy = fgetc(fh2);
        }

        //Checks for End of Line, its not, recall with the same size
        if(dummy != '\n' && !feof(fh2))
        {
            //Unget the line
            ungetc(dummy, fh2);

            //Recurse
            return metaRead(fh2, recCount, meta);
        }
        
        // End of line is REACHED
        if(dummy == '\n' && !feof(fh2))
        {
            
            //Presents Dummy Vals
            meta->metaData[meta->size].endTime = ZERO;
            meta->metaData[meta->size].pid = ZERO;
            //One Full Line is Read, Size Adds by 1
            meta->size++;

            //Resets the Recursion
            return metaRead(fh2, ZERO, meta);
        }
        
        return false;
    }
// Meta Data Print
    //Prints Meta Data in Format
void metaPrint(opcode *metaData)
    {
        int index; 
        
        // Print Title 

        printf("\nMeta-Data File Display");
        printf("\n----------------------");
        
        // Loop through the size
       
        for(index = ZERO; index < metaData->size; index++)
        {
            printf("\nOp Code: ");

            printf("/pid: %d", metaData->metaData[index].pid);

            printf("/cmd: %s", metaData->metaData[index].cmd);

            printf("/io: %s", metaData->metaData[index].io);
            
            printf("\n/arg1: %s", metaData->metaData[index].arg1);

            printf("/arg2: %d", metaData->metaData[index].arg2);

            printf("/arg3: %d", metaData->metaData[index].arg3);

            printf("/op end time: %f \n", metaData->metaData[index].endTime);
        }
    }

// Meta Check
    // Check Data Within Meta to see if Data is Correct
bool metaCheck(opcode *metaData)
    {
        //Intialize Variables
        int outerIndex = ZERO;
        int innerIndex = ZERO;
        int result = DUMMY_VAL;
        //cmd options
        char cmd[5][3] = {"sys", "app", "dev", "cpu", "mem"};
        //io options
        char IO[3][5] = {" in", " out", "NA"};
        //argv1 options
        char argv1[13][20] = {" start", " end", " process", " allocate",
                                " access", " ethernet", " hard drive"," keyboard", 
                                " monitor", " serial"," sound signal", 
                                " usb", " video signal"};


        // For Loop to Check everything IN metadata
        for (outerIndex = ZERO; outerIndex < metaData->size; outerIndex++)
        {
            // Check Command
            while (result != ZERO && innerIndex < 5)
            {
                result = compareStr(cmd[innerIndex], metaData->metaData[outerIndex].cmd);
                innerIndex++;
            }
            if ( result != ZERO )
            {
                errorPrint();
                return false;
            }

            //reset Vals
            result = DUMMY_VAL;
            innerIndex = ZERO;

            // Check IO
            while (result != ZERO && innerIndex < 3)
            {
                result = compareStr(IO[innerIndex], metaData->metaData[outerIndex].io);
                innerIndex++;
            }
            if ( result != ZERO )
            {
                errorPrint();
                return false;
            }

            //reset Vals
            result = DUMMY_VAL;
            innerIndex = ZERO;

            // Check Arg1
            while (result != ZERO && innerIndex < 13)
            {
                result = compareStr(argv1[innerIndex], metaData->metaData[outerIndex].arg1);
                innerIndex++;
            }
            if ( result != ZERO )
            {
                errorPrint();
                return false;
            }
        }

        // All Data is correct
        return true;
    }
