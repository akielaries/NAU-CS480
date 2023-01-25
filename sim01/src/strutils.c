/**
 * String related utilities implementations
 */
#include "strutils.h"


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

_Bool str_constrained(FILE *inStream,
                    _Bool clearLeadingNonPrintable,
                    _Bool clearLeadingSpace,
                    _Bool stopAtNonPrintable,
                    char delimiter,
                    char *capturedString)
{
    _Bool _Var1;
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
        _Var1 = false;
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
        _Var1 = true;
    }
    return _Var1;
}

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



