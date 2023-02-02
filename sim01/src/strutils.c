/**
 * String related utilities implementations many of which are from 
 */
#include "strutils.h"


// re-implementation of strcmp()
int compareString(char *str_a, char *str_b)
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
    return (getStringLength(str_a) - getStringLength(str_a));
}

// re-implementation of strcat()
void concatenateString(char *dest_str, char *src_str) 
{
    int sourceIndex = 0;
    int destIndex = getStringLength(dest_str);

    while ((src_str[sourceIndex] != NULL_CHAR && 
                (destIndex < MAX_STR_LEN))) 
    {
        dest_str[destIndex] = src_str[sourceIndex];
        destIndex++; 
        sourceIndex++; 
        dest_str[destIndex] = '\0';
    }
}

/**
 * re-implementatoin of strstr, finds a string within string 
 * returning the index
 */
int findSubString(char *str_a,char *search_substr)
{
    int str_a_len = getStringLength(str_a);
    int masterIndex = 0;
    int internalIndex;
    int searchIndex;
        

    while (masterIndex < str_a_len)
    {    
        internalIndex = masterIndex;
        searchIndex = 0;

        while ((internalIndex <= str_a_len && 
                (str_a[internalIndex] == search_substr[searchIndex])))
        {
            internalIndex++;
            searchIndex++;

            if (search_substr[searchIndex] == NULL_CHAR) 
            { 
                return masterIndex;
            }
        }
        masterIndex++;
    }
    return SUBSTRING_NOT_FOUND;
}

// function for reading from input file stream give contraints
_Bool getStringConstrained(FILE *inStream,
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
void copyString(char *dest_str, char *src_str) 
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
int getStringLength(char *str_a) 
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

_Bool getStringToDelimter(FILE *in_stream,
                    char delimiter,
                    char *captured_str)
{
    _Bool delim = getStringConstrained(in_stream,
                    true,
                    true,
                    true,
                    delimiter,
                    captured_str);
    return delim;
}

_Bool getStringToLineEnd(FILE *in_stream,char *captured_str)
{
    _Bool line_end = getStringConstrained(in_stream,
                                        true,
                                        true,
                                        true,
                                        NON_PRINTABLE_CHAR,
                                        captured_str);
    return line_end;
}

void getSubString(char *dest_str,
                char *src_str,
                int startIndex,
                int endIndex)
{
    char *temp_str;
    int sourceIndex = startIndex;
    int src_str_len = getStringLength(src_str);
    int destIndex = 0;
  
    if (((startIndex < 0) || 
        (endIndex < startIndex)) || 
        (src_str_len <= endIndex)) 
    {
        *dest_str = NULL_CHAR;
    }
  
    else 
    {
        temp_str = (char *)malloc((long)(src_str_len + 1));
        copyString(temp_str, src_str);
        sourceIndex = startIndex;
        while (sourceIndex <= endIndex) 
        {
            dest_str[destIndex] = temp_str[sourceIndex];
            destIndex++;
            sourceIndex++;
            dest_str[destIndex] = NULL_CHAR;
        }
        free(temp_str);
    }
}


void setStrToLowerCase(char *dest_str, char *src_str) 
{
    char *temp_str;
    int index = 0;
  
    int src_str_len = getStringLength(src_str);
    temp_str = (char *)malloc((long)(src_str_len + 1));

    while ((src_str[index] != NULL_CHAR && (index < MAX_STR_LEN))) 
    {  
        temp_str[index] = toLowerCase(src_str[index]);
        index++;
        temp_str[index] = NULL_CHAR;
    }
    copyString(dest_str, temp_str);
    free(temp_str);
}

char toLowerCase(char str_a)
{
    if (str_a >= 'A' && str_a <= 'Z' )
    {
        return str_a - 'A' + 'a';
    }
    return str_a;
}




