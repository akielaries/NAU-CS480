// header files 
#include "StringUtils.h"
#include <stdlib.h>

// local constants 
const char NON_PRINTABLE_CHAR = '\0';

// function implementations
int compareString(const char *oneStr, const char *otherStr)
{
   // initialize function / vairables 
   int diff, index = 0;

   // loop to end of shortest string, 
   // with overrun protection
   while (oneStr[ index] != NULL_CHAR 
            && otherStr[ index ] != NULL_CHAR
               && index < MAX_STR_LEN)
   {
      // get difference in characters 
      diff = oneStr[index] - otherStr[index]; 

      // check for difference between characters 
      if (diff != 0)
      {
         // return difference 
         return diff;
      }

      // increment index
      index++; 
   }

   // return difference in lengths, if any 
      // function: getStringLength
   return getStringLength(oneStr) - getStringLength(otherStr);
}

void concatenateString( char *destStr, const char *sourceStr)
{
   // initialize function/var
  
      // set dest index 
         // function: getStringLength
      int destIndex = getStringLength(destStr);

      // get source string length
         // function: getStringLength
      int sourceStrLen = getStringLength(sourceStr);

      // create temp string pointer 
      char *tempStr;

      // create other var
      int sourceIndex = 0; 

   // copy source string in case of aliasing 
      // function: malloc, copyString
   tempStr = (char *)malloc( sizeof(sourceStrLen + 1));
   copyString( tempStr, sourceStr);
 
   // loop to end of source string
   while( tempStr[sourceIndex] != NULL_CHAR && destIndex < MAX_STR_LEN) 
   {
      // assign characters to end of dest string
      destStr[destIndex] = tempStr[sourceIndex]; 

      // update indices 
      destIndex++; sourceIndex++;

      // set temp end of dest string
      destStr[destIndex] = NULL_CHAR; 
   }

   // release temp str memory 
      // function: free
   free(tempStr);

}

 
void copyString(char *destStr, const char *sourceStr)
{
   // initialize function/var
   int index = 0;

   // check for source/dest not same 
   if (destStr != sourceStr)
   {
      // loop to end of source string 
      while( sourceStr[index] != NULL_CHAR && index < MAX_STR_LEN)
      {
         // assign characters to end of dest string 
         destStr[index] = sourceStr[index];

         // update index 
         index++;

         // set temp end to dest string
         destStr[index] = NULL_CHAR; 
      }
   }
}

int findSubString( const char *testStr, const char *searchSubStr)
{
   // initialize function / variables 
   
      // initialize test string length 
         // function: getStringLength
      int testStrLen = getStringLength(testStr);

      // initialize master index - location of sub string starting point
      int masterIndex = 0;

      // initialize other variables 
      int searchIndex, internalIndex; 

   // loop across test string 
   while (masterIndex < testStrLen)
   {
      // set internal loop index to current test string index 
      internalIndex = masterIndex;

      // set internal search index to 0
      searchIndex = 0; 

      // loop to end of test string 
      // while test string/sub string char same 
      while(internalIndex <= testStrLen 
                && testStr[internalIndex] == searchSubStr[searchIndex])
      {
         // increment test string, substring indices 
         internalIndex++; searchIndex++;

         // check for end of substring 
         if( searchSubStr[searchIndex] == NULL_CHAR)
         {
            // return beginning location of sub string 
            return masterIndex;
         }
      }

      // increment curent beginning location index 
      masterIndex++;
   }

   // assume test failed, return SUBSTRING_NOT_FOUND
   return SUBSTRING_NOT_FOUND;
 
}

bool getStringConstrained(
                          FILE *inStream, 
                          bool clearLeadingNonPrintable,
                          bool clearLeadingSpace,
                          bool stopAtNonPrintable,
                          char delimiter, 
                          char *capturedString
                         )
 
{
   // initialize variables 
   int intChar = EOF, index = 0;

   // initialize output string 
   capturedString[index] = NULL_CHAR;

   // capture first value in stream 
      // function: fgetc
   intChar = fgetc( inStream);

   // loop to clear non printable or space if indicated 
   while( (intChar != EOF) 
          && ( (clearLeadingNonPrintable && intChar < (int)SPACE)
             || (clearLeadingSpace && intChar == (int)SPACE) ))
   {
      // get next char 
         // function: fgetc
      intChar = fgetc( inStream);
   }

   // check for end of file found 
   if (intChar == EOF)
   {
      // return failed operation
      return false;  
   }

   // loop to capture input 
   while (
        // continues if not at end of file and max str len not reached 
        (intChar != EOF && index < MAX_STR_LEN - 1)

        // and continues if not printable flag set and char printable 
        // or continues if printable flag not set 
        && ( ( stopAtNonPrintable && intChar >= (int)SPACE) 
               || ( !stopAtNonPrintable ) )

        // and continues if specified delimiter is not found
        && (intChar != (char)delimiter)
         )

   {
      // place char in array element 
      capturedString[index] = (char)intChar;

      // increment array index 
      index++;

      // set next element to null char 
      capturedString[index] = NULL_CHAR;

      // get next char as int 
         // function: fgetc
      intChar = fgetc( inStream);
   }

   // return successful operation
   return true;
}





int getStringLength( const char *testStr)
{
   // initialize function / variables 
   int index = 0;

   // loop to end of string, protect from overflow 
   while (index < STD_STR_LEN && testStr [ index] != NULL_CHAR)
   {
      // update index
      index++; 
   }

   // end loop 

   // return index / length
   return index;
}

bool getStringToDelimiter(
                           FILE *inStream,
                           char delimiter, 
                           char *capturedString
                          )

{
   // call engine func with delimiter
      // function: getStringConstrained
   return getStringConstrained (
                        inStream,            // file stream pointer 
                        true,                // clears leading non printable character 
                        true,                // bool clearLeadingSpace
                        true,                // stops at non printable 
                        delimiter,           // stops at delimiter
                        capturedString       // return string 
                               );


}

bool getStringToLineEnd(
                        FILE *inStream, 
                        char *capturedString
                       )
{
   // call engine function with specified constraints
      // function: getStringConstrained
   return getStringConstrained (
                        inStream,            // file stream pointer 
                        true,                // clears leading non printable character 
                        true,                // bool clearLeadingSpace
                        true,                // stops at non printable 
                        NON_PRINTABLE_CHAR,  // non printable character
                        capturedString       // return string 
                               );


}


void getSubString( char *destStr, const char *sourceStr, 
                   int startIndex, int endIndex)
{
   // initialize func/var 

      // set len of source str
         // function: getStringLength
      int sourceStrLen = getStringLength(sourceStr);

      // initialize dest index to 0
      int destIndex = 0;

      // initialize source index to start index (param)
      int sourceIndex = startIndex;

      // create pointer for temp string 
      char *tempStr;

   // check for indices within limits 
   if (startIndex >= 0 && startIndex <= endIndex 
                                       && endIndex < sourceStrLen)
   {

      // create temp str
         // function: malloc, copyString
      tempStr = (char *)malloc( sourceStrLen + 1);
 
      // loop across requested substring (indicies)
      while( sourceIndex <= endIndex)
      {
         // assign source char to dest element 
         tempStr[destIndex] = sourceStr[sourceIndex];
   
         // increment indices 
         destIndex++; sourceIndex++;
      
         // set temp end of dest str 
         tempStr[destIndex] = NULL_CHAR; 
      }

      // copy temp to dest string 
         // function: copyString
      copyString(destStr, tempStr);

      // return mem for temp str 
         // function: free
      free(tempStr);
   }
}

void setStrToLowerCase( char *destStr, const char *sourceStr)
{
   // initialize function/variables 
   
      // create other var 
      int index = 0;

   // loop across src string 
   while (sourceStr[index ] != NULL_CHAR && index < MAX_STR_LEN)
   {
      // set individual char to lower case as needed, assign to dest string 
      destStr[index] = toLowerCase( sourceStr[index]);

      // update index 
      index++;
 
   }

   // set temp end of dest string
   destStr[index] = NULL_CHAR;

}

char toLowerCase( char testChar)
{
   // check for upper case 
   if (testChar >= 'A' && testChar <= 'Z')
   {
      // return lower case letter
      return testChar - 'A' + 'a'; 
   }

   // otherwise, not lower case, return same letter 
   return testChar;
}
