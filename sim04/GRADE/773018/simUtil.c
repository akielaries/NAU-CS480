// This File contains all Constants, All String Utilities and other files used by all of the files

//Structs included.

#include "simUtil.h"


//Error Print Function
    //prints an error and ends the function
void errorPrint()
    {
        printf("\nAn Error has Occured");
        printf("\nPlease Ensure all Files are correct");

    }

//Compare Strings

int compareStr( const char *str1, const char *str2 )
   {

     // Initialize Variables
      int difference = 0;
      int index = 0;

      // Loop while the index is less than the length of both states
      while( str1[index] != NULL_CHAR && str2[index] != NULL_CHAR )
         {
            // Calculate the difference between the letters at the current index
            difference = str1[index] - str2[index];

            // Check if the difference is not equal to 0
            if ( difference != 0 )
               {
                  // Return the difference
                  return difference;
               }

            index++;
         }

      // Return the difference
      return difference;
   }

//Combine strings
void combineStr( char desStr[], char str1[], char str2[] )
    {
        int index1, index2;
        for ( index1 = 0; str1[index1] != NULL_CHAR; index1++ )
        {
            desStr[index1] = str1[index1];
        }

        for ( index2 = 0; str2[index2] != NULL_CHAR; index2++, index1++ )
        {
            desStr[index1] = str2[index2];
        }

        desStr[index1] = NULL_CHAR;
    }

//Copy Strings
void copyStr( char destination[], char source[])
    {
        int index = ZERO;
        while (source[index] != NULL_CHAR)
            {
                destination[index] = source[index];
                index++;
            }
        while ( index < MAX_ARRAY_SIZE )
            {
                destination[index] = NULL_CHAR;
                index++;
            }

    }
//Expanding the Array
    //Resizes and allocates more memory
void checkForResize(opcode *meta)
    {
        command *tempArray;
        int index;
        //Check if Current Size = Capacity
        if (meta->size == meta->capacity)
        {
            // Double Capacity
            meta->capacity++;

            // Re-Allocate the Memory
            tempArray = (command *)malloc(meta->capacity * (sizeof(command)));

            for (index = 0; index < meta->size; index++)
            {
                tempArray[index] = meta->metaData[index];
            }
            
            meta->metaData = tempArray;
        }
    }



