// Header files
#include "StringUtils.h"

// local constants
// none

// function implementations
/*
Name: compareString
Process: compares two strings with the following results:
         if left string < right string, return is less than 0
         if left string > right string, return is greater than 0
         if left string = right string, return is 0
Function Input/Parameters: left and right strings (char *)
Function Output/Parameters: none
Function OUtput/Returned: results as specifed (int)
Device Input/device: none
Device Output/device: none
Dependencies: getStringLength
*/
int compareString(const char *leftStr, const char *rightStr)
{
  // Initialize variables
  int diff, index = 0;

  // Loop to end of shortest string
  while (leftStr[index] != NULL_CHAR && rightStr[index] != NULL_CHAR &&
         index < MAX_STR_LEN)
  {
    // get difference in character
    diff = leftStr[index] - rightStr[index];

    // check for difference
    if (diff != 0)
    {
      // return difference
      return diff;
    }

    // increment index
    index++;
  }
  // end loop

  // return difference in length if any
  // function: getStringLength
  return getStringLength(leftStr) - getStringLength(rightStr);
}

/*
Name: concatenateString
Process: appends one string onto another
Function Input/Parameters: source string (char *)
Function Output/Parameters: destination string (char *)
Function OUtput/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: getStringLength
*/
void concatenateString(char *destStr, const char *sourceStr)
{
  // Initialize variables

  // set dest index
  // function: getStringLength
  int destIndex = getStringLength(destStr);

  // get source string length
  // function: getStringLength
  int sourceStrLen = getStringLength(sourceStr);

  // create tem string pointer
  char *tempStr;

  // create other variables
  int sourceIndex = 0;

  // copy source string in case of aliasing
  // function: malloc copyString
  tempStr = (char *)malloc(sizeof(sourceStrLen + 1));
  copyString(tempStr, sourceStr);

  // loop to end of source string
  while (tempStr[sourceIndex] != NULL_CHAR && destIndex < MAX_STR_LEN)
  {
    // assign characters to end of dest string
    destStr[destIndex] = tempStr[sourceIndex];

    // update indicies
    destIndex++;
    sourceIndex++;

    // set temporary end of dest string
    destStr[destIndex] = NULL_CHAR;
  }
  // end loop

  // release memory
  // function: free
  free(tempStr);
}

/*
Name: copyString
Process: copies one string into another,
         overwriting data in the destination string
Function Input/Parameters: source string (char *)
Function Output/Parameters: destination string (char *)
Function OUtput/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
void copyString(char *destStr, const char *sourceStr)
{
  // Initialize variables
  int index = 0;
  // check for source/destination not the same (aliasing)
  if (destStr != sourceStr)
  {
    // loop to end of source str
    while (sourceStr[index] != NULL_CHAR && index < MAX_STR_LEN)
    {
      // assign characters to end of destination string
      destStr[index] = sourceStr[index];

      // update index
      index++;

      // set temp end of dest string
      destStr[index] = NULL_CHAR;
    }
    // end loop
  }
}

/*
Name: findSubString
Process: linear search for given substring within another string
Function Input/Parameters: source test string (char *),
                           source search string (char *)
Function Output/Parameters: none
Function OUtput/Returned: index of found substring, or SUBSTRING_NOT_FOUND
if substring not found Device Input/device: none Device Output/device: none
Dependencies: getStringLength
*/
int findSubstring(const char *testStr, const char *searchSubStr)
{
  // Initialize variables
  // initialize test string length
  // function: getStringLength
  int testStrLen = getStringLength(testStr);

  // initialize a master index - location of substring stat point
  int masterIndex = 0;

  // initialize other variables
  int searchIndex, internalIndex;

  // loop across test string
  while (masterIndex < testStrLen)
  {
    // set internal loop index to current test string index
    internalIndex = masterIndex;

    // set internal search index to zero
    searchIndex = 0;

    // loop to end of test string
    // while test string/sub string characters are the same
    while (internalIndex <= testStrLen &&
           testStr[internalIndex] == searchSubStr[searchIndex])
    {
      // increment test string, substring indices
      internalIndex++;
      searchIndex++;

      // check for end of substring (sreach completed)
      if (searchSubStr[searchIndex] == NULL_CHAR)
      {
        // return beginning location of sub string
        return masterIndex;
      }
    }
    // end internal loop

    // increment current beginning location index
    masterIndex++;
  }
  // end across test loop

  // assume failure and substring not found
  return SUBSTRING_NOT_FOUND;
}

/*
Name: getStringConstrained
Process: captures a string from the input stream with various constraints
Function Input/Parameters: input stream (FILE *)
                           clears leading non printable (bool),
                           clears leading space (bool),
                           stops at no printable (bool),
                           stops at specified delimiter (char),
                           Note: consumes delimiter
Function Output/Parameters: string returned (char *)
Function OUtput/Returned: success of operation (bool)
Device Input/device: none
Device Output/device: none
Dependencies: fgetc
*/
bool getStringConstrained(FILE *inStream, bool clearLeadingNonPrintable,
                          bool clearLeadingSpace, bool stopAtNonPrintable,
                          char delimiter, char *capturedString)
{
  // Initialize variables
  int intChar = EOF, index = 0;

  // initialize output string
  capturedString[index] = NULL_CHAR;

  // capture first value in stream
  // function: fgetc
  intChar = fgetc(inStream);

  // loop to clear non printable of space characters, if indicated
  while ((intChar != EOF) &&
         ((clearLeadingNonPrintable && intChar < (int)SPACE) ||
          (clearLeadingSpace && intChar == (int)SPACE)))
  {
    // get next char
    // function: fgetc
    intChar = fgetc(inStream);
  }
  // end loop

  // check for end of file found
  if (intChar == EOF)
  {
    // return failed operation
    return false;
  }

  // loop to capture input
  while (
      // continues in not at end of file and max string length not
      // reached
      (intChar != EOF && index < MAX_STR_LEN - 1)

      // AND
      // continued if not printable flag set and characters are printable
      // OR contines if not printable flag not set
      &&
      ((stopAtNonPrintable && intChar >= (int)SPACE) || (!stopAtNonPrintable))

      // AND
      // contines of specifeied delimiter is not found
      && (intChar != (char)delimiter))
  {
    // place character in array element
    capturedString[index] = (char)intChar;

    // increment array index
    index++;

    // set next element to null character
    capturedString[index] = NULL_CHAR;

    // get next character as integer
    // function: fgetc
    intChar = fgetc(inStream);
  }
  // end loop

  // return successful operation
  return true;
}

/*
Name: getStringLength
Process: finds the length of a string by counting characters up to the
NULL_CHAR Function Input/Parameters: c-style string (char *) Function
Output/Parameters: none Function OUtput/Returned: length of string Device
Input/device: none Device Output/device: none Dependencies: none
*/
int getStringLength(const char *testStr)
{
  // Initialize variables
  int index = 0;

  // Loop to end of string, protect from overflow
  while (index < STD_STR_LEN && testStr[index] != NULL_CHAR)

    // update index
    index++;

  // end loop

  // return index/length
  return index;
}

/*
Name: getStringToDelimiter
Process: captures a string from the input stream to a specified
         delimiter,
         Note: consumes delimiter
Function Input/Parameters: inpute stream (FILE *),
                           stops at specified delimiter (char),
Function Output/Parameters: string returned (char *)
Function OUtput/Returned: success of operation (bool)
Device Input/device: none
Device Output/device: none
Dependencies: getStringConstrained
*/
bool getStringToDelimiter(FILE *inStream, char delimiter, char *capturedString)
{
  // call engine function with delimiter
  // function: getStringConstrained
  return getStringConstrained(inStream, // file stream pointer
                              true,     // clears leading no printable character
                              true,     // bool clearLeadingSpace
                              true,     // stops at non printable
                              delimiter,     // stops at delimiter
                              capturedString // returns string
  );
}

/*
Name: getStringToLineEnd
Process: captures a string form the input stream to the
         end of the line
Function Input/Parameters: input stream (FILE *)
Function Output/Parameters: string returned (char *)
Function OUtput/Returned: success of operation (bool)
Device Input/device: none
Device Output/device: none
Dependencies: getStringConstrained
*/
bool getStringToLineEnd(FILE *inStream, char *capturedString)
{
  // call engine function with delimiter
  // function: getStringConstrained
  return getStringConstrained(inStream, // file stream pointer
                              true,     // clears leading no printable character
                              true,     // bool clearLeadingSpace
                              true,     // stops at non printable
                              NON_PRINTABLE_CHAR, // stops at delimiter
                              capturedString      // returns string
  );
}

/*
Name: getSubstring
Process: captures sub string within larger string between two inclusive
indeces. returns empty string if either index is out of range, assumes
enough memory in dest string Function Input/Parameters: source string(char
*), start and end indices (int) Function Output/Parameters: dest string
(char *) Function OUtput/Returned: none Device Input/device: none Device
Output/device: none Dependencies: getStringLength, malloc, copyString, free
*/
void getSubString(char *destStr, const char *sourceStr, int startIndex,
                  int endIndex)
{
  // Initialize variables
  // set length of source string
  // function: getStringLength
  int sourceStrLen = getStringLength(sourceStr);

  // initialize the destination index to zero
  int destIndex = 0;

  // initialize  source index to start index (parameter)
  int sourceIndex = startIndex;

  // create pointer for temp string
  char *tempStr;

  // check for indices within limits
  if (startIndex >= 0 && startIndex <= endIndex && endIndex < sourceIndex)
  {
    // create temp sting
    // function: malloc, copyString
    tempStr = (char *)malloc(sourceStrLen + 1);
    copyString(tempStr, sourceStr);

    // loop across requested substring
    while (sourceIndex <= endIndex)
    {
      // assign aource characer to destination element
      destStr[destIndex] = tempStr[sourceIndex];

      // increment indices
      destIndex++;
      sourceIndex++;

      // set temp end of dest string
      destStr[destIndex] = NULL_CHAR;
    }
    // end loop

    // return memory for temp string
    // function: free
    free(tempStr);
  }
}

/*
Name: setStrToLowerCase
Process: iterates through string, sts any upper case letter to lower case
Function Input/Parameters: source string (char *)
Function Output/Parameters: dest string (char *)
Function OUtput/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: toLowerCase
*/
void setStrToLowerCase(char *destStr, const char *sourceStr)
{
  // Initialize function
  // get source string length
  // function: getStringLength
  int sourceStrLen = getStringLength(sourceStr);

  // create temp string pointer
  char *tempStr;

  // create other variables
  int index = 0;

  // copy source string in case of aliasing
  // function: malloc, copyString
  tempStr = (char *)malloc(sizeof(sourceStrLen + 1));

  // loop across src string
  while (tempStr[index] != NULL_CHAR && index < MAX_STR_LEN)
  {
    // set individual character to lowercase as needed
    // assign to desitnation stirng
    destStr[index] = toLowerCase(tempStr[index]);

    // update index
    index++;

    // set temp end of destination string
    destStr[index] = NULL_CHAR;
  }
  // end loop

  // release memory used
  // function: free
  free(tempStr);
}

/*
Name: toLowerCase
Process: if character is upper case, sets it to lower case,
         otherwise returns character with no change
Function Input/Parameters: test character (char)
Function Output/Parameters: none
Function OUtput/Returned: character set to lower case
Device Input/device: none
Device Output/device: none
Dependencies: none
*/
char toLowerCase(char testChar)
{
  // Initialize variables

  // check for upercase
  if (testChar >= 'A' && testChar <= 'Z')
  {
    // return lowercase letter
    return testChar - 'A' + 'a';
  }

  // otherwise, assume no upper case letter,
  // retrun character unchanged
  return testChar;
}