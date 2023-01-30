/**
 * String related utilities implementations many of which are from 
 */
#include "strutils.h"


// re-implementation of strcmp()
int str_cmp(char *str_a, char *str_b)
{
    int diff, index;

    for (index = 0; 
            ((str_a[index] != NULL_CHAR && 
              (str_b[index] != NULL_CHAR)) && 
             (index < MAX_STR_LEN )); index++) 
    {
        diff = (int)str_a[index] - (int)str_b[index];
        
        if (diff != 0) 
        {
            return diff;
        }
    }
    return (str_len(str_a) - str_len(str_a));
}

/**
 * re-implementatoin of strstr, finds a string within string 
 * returning the index
 */
int str_substr(char *test_str,char *search_substr)
{
  int iVar1;
  //int testStrLen;
  int internalIndex;
  int searchIndex;
  int masterIndex;
  
  iVar1 = str_len(test_str);
  masterIndex = 0;
  do 
  { 
      if (iVar1 <= masterIndex) {
          return SUBSTRING_NOT_FOUND;
    }
    internalIndex = masterIndex;
    searchIndex = 0;
    while ((internalIndex <= iVar1 && 
                (test_str[internalIndex] == 
                 search_substr[searchIndex]))) {
      internalIndex++;
      searchIndex++;
      if (search_substr[searchIndex] == NULL_CHAR) {
        return masterIndex;
      }
    }
    masterIndex = masterIndex + 1;
  } while( true );


}

// function for reading from input file stream give contraints
_Bool str_cstr(FILE *inStream,
                    _Bool clearLeadingNonPrintable,
                    _Bool clearLeadingSpace,
                    _Bool stopAtNonPrintable,
                    char delimiter,
                    char *capturedString)
{
    _Bool ret;
    int index;
    int intChar;

    index = 0;

    *capturedString = NULL_CHAR;
    intChar = fgetc((FILE *)inStream);
  
    while ((intChar != EOF &&
                (((clearLeadingNonPrintable != false && 
                    (intChar < MIN_STR_LEN)) ||
                ((clearLeadingSpace != false && 
                    (intChar == MIN_STR_LEN))))))) 
    {
        intChar = fgetc((FILE *)inStream);
    }
  
    if (intChar == EOF) 
    {
        ret = false;
    }
    else 
    {
        while ((((intChar != EOF && (index < MAX_STR_LEN - 1)) &&
                    (((stopAtNonPrintable != false && 
                        (MIN_STR_LEN < intChar)) || 
                    (stopAtNonPrintable != true))))
                        && (delimiter != intChar))) 
        {
            capturedString[index] = (char)intChar;
            index++;
            capturedString[index] = NULL_CHAR;
            intChar = fgetc((FILE *)inStream);
        }
        ret = true;
    }
    return ret;
}

// re-implementation of strcpy()
void str_cpy(char *dest_str, char *src_str) 
{
    int index = 0;

    if (dest_str != src_str)
    {
        while ((src_str[index] != NULL_CHAR && (index < MAX_STR_LEN))) 
        {
            dest_str[index] = src_str[index];
            index++;
            dest_str[index] = NULL_CHAR;
        }
    }
}

// re-implementation of strlen()
int str_len(char *str_a) 
{
    int index;

    for (index = 0; 
            (index < STD_STR_LEN && 
             (str_a[index] != NULL_CHAR)); 
            index++) 
    {
    }
    return index;
}

