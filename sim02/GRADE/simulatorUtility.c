// headers
#include "simulatorUtility.h"

// constants

// functions
int compareStrings(const char *leftStr, const char *rightStr)
{
  // variables
  int index;

  // compare left to right
  for (index = 0; leftStr[index] != NULL_CHAR && rightStr[index] != NULL_CHAR;
       index++)
  {
    // if it's not equal anymore return result
    if (leftStr[index] - rightStr[index] != 0)
    {
      return leftStr[index] - rightStr[index];
    }
  }

  return 0;
}

void copyString(const char source[], char dest[])
{
  int index;

  // set source to dest
  for (index = 0; source[index] != NULL_CHAR; index++)
  {
    dest[index] = source[index];
  }

  dest[index] = NULL_CHAR;
}

void print_error(char *error)
{
  printf("There has been an error: %s\n", error);
}
int stringToInt(char *intString)
{
  int index = 0, multiplier, solution = 0;

  // loop to end
  while (intString[index + 1] != NULL_CHAR)
  {
    index++;
  }

  // work backwards, calculating integer
  for (multiplier = 1; index >= 0; multiplier = multiplier * 10, index--)
  {
    solution = solution + (((int)intString[index] - CHAR_OFFSET) * multiplier);
  }
  return solution;
}
