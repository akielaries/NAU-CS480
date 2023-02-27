// headers
#include "metaData.h"

// constants

// functions
metaData *appendNode(metaData *data, char *command, int entryCycleTime,
                     char *ioArg, char *strArg, int intArgs[])
{
  metaData *newData;
  // if data isn't empty
  if (data != NULL)
  {
    // if next node isn't empty recurse
    if (data->nextData != NULL)
    {
      appendNode(data->nextData, command, entryCycleTime, ioArg, strArg,
                 intArgs);
    }
    else // if next node is empty put it there
    {
      newData = createDataNode(command, entryCycleTime, ioArg, strArg, intArgs);

      data->nextData = newData;
    }
  }
  else // if data is empty
  {
    newData = createDataNode(command, entryCycleTime, ioArg, strArg, intArgs);
    data = newData;
  }

  return data;
}

bool checkMetaDataNode(char *command, int entryCycleTime, char *ioArg,
                       char *strArg, int intArgs[3])
{
  int wordIndex;
  bool found;
  char commands[NUM_COMMANDS][MIN_STR_LEN] = {"sys", "app", "dev", "cpu",
                                              "mem"};
  char strArgs[NUM_OPS][MIN_STR_LEN] = {
      "start",        "end",        "process",     "allocate", "access",
      "ethernet",     "hard drive", "keyboard",    "monitor",  "serial",
      "sound signal", "usb",        "video signal"};

  // printf("command: %s\n", command);

  // check that command is correct
  found = false;
  for (wordIndex = 0; wordIndex < NUM_COMMANDS && !found; wordIndex++)
  {
    if (compareStrings(command, commands[wordIndex]) == 0)
    {
      found = true;
    }
  }

  if (!found)
  {
    print_error("Incorrect Command Read");
    return false;
  }

  // check that str arg is correct
  found = false;
  for (wordIndex = 0; wordIndex < NUM_OPS && !found; wordIndex++)
  {
    if (compareStrings(strArg, strArgs[wordIndex]) == 0)
    {
      found = true;
    }
  }

  if (!found)
  {
    print_error("Incorrect Operation Read");

    return false;
  }

  return true;
}

metaData *clearData(metaData *data)
{
  // loop till last dataNode
  if (data->nextData != NULL)
  {
    clearData(data->nextData);
  }

  // clear data
  free(data);
  return NULL;
}

metaData *createDataNode(char *command, int entryCycleTime, char *ioArg,
                         char *strArg, int intArgs[])
{
  metaData *newData;

  newData = (metaData *)malloc(sizeof(metaData));
  copyString(command, newData->command);
  newData->entryCycleTime = entryCycleTime;
  copyString(ioArg, newData->ioArg);
  copyString(strArg, newData->strArg);
  newData->intArgOne = intArgs[0];
  newData->intArgTwo = intArgs[1];

  newData->nextData = NULL;

  return newData;
}

void display_MD(metaData *data, bool displayFlag)
{
  // store meta data in data structure
  metaData *tempData;

  // If file was incorrect, display error
  if (!displayFlag)
  {
    print_error("Incorrect meta data file. Could not display data.");
  }
  else // display
  {
    tempData = data;
    while (tempData != NULL)
    {
      printf("OpCode: /pid: 0/cmd: %s/io: %s\n\t", tempData->command,
             tempData->ioArg);
      printf("/arg1: %s/arg 2: %d/arg 3: %d/op end time: 0.0000\n\n",
             tempData->strArg, tempData->intArgOne, tempData->intArgTwo);
      tempData = tempData->nextData;
    }
  }
}

int getArgs(char *currentString, char *ioArg, char *strArg, int *intArgs)
{
  int index, tempIndex;
  char tempString[MIN_STR_LEN];

  // save arg data, starting where args will start, looping until newline or
  // comma
  for (index = ARGS_START_POS, tempIndex = 0;
       currentString[index] != ',' && currentString[index] != '\n';
       index++, tempIndex++)
  {
    tempString[tempIndex] = currentString[index];
  }
  tempString[tempIndex] = NULL_CHAR;

  // check if the arg is in or out
  if (compareStrings(tempString, "in") == 0 ||
      compareStrings(tempString, "out") == 0)
  {
    // store as arg and get first str
    copyString(tempString, ioArg);

    for (index = index + 2, tempIndex = 0;
         currentString[index] != ',' && currentString[index] != '\n';
         index++, tempIndex++)
    {
      strArg[tempIndex] = currentString[index];
    }
    strArg[tempIndex] = NULL_CHAR;

    // get the integers that follow
    getInts(currentString, intArgs, index);
  }
  else
  {
    // store as first str
    copyString(NOT_AVAILABLE, ioArg);
    copyString(tempString, strArg);

    // check for start int
    if (compareStrings(strArg, "start") == 0)
    {
      if (currentString[index] == ',')
      {
        // store int differently
        index += 2;
        for (tempIndex = 0;
             currentString[index] != ',' && currentString[index] != '\n';
             index++, tempIndex++)
        {
          tempString[tempIndex] = currentString[index];
        }
        tempString[tempIndex] = NULL_CHAR;

        return stringToInt(tempString);
      }
    }

    // get integers that follow
    getInts(currentString, intArgs, index);
  }

  // no start integer return 0
  return 0;
}

void getCommand(char *currentString, char *command)
{
  int index;

  // start at beginning and get command
  for (index = 0; index < ARGS_START_POS - 1; index++)
  {
    command[index] = currentString[index];
  }

  command[index] = NULL_CHAR;
}

void getInts(char *currentString, int *intArgs, int startIndex)
{
  // default ints
  intArgs[0] = 0;
  intArgs[1] = 0;

  // call helper
  getIntHelper(currentString, intArgs, startIndex, 0);
}

void getIntHelper(char *currentString, int *intArgs, int startIndex,
                  int intIndex)
{
  char intString[MIN_STR_LEN];
  int index;

  if (intIndex < 2)
  {
    if (currentString[startIndex] == ',')
    {
      // move up 2, skipping comma and space
      startIndex += 2;

      // get numbers until comma or new line
      for (index = 0; currentString[startIndex] != ',' &&
                      currentString[startIndex] != '\n';
           index++)
      {
        intString[index] = currentString[startIndex];
        startIndex++;
      }

      intString[index] = NULL_CHAR;

      // convert string to int
      intArgs[intIndex] = stringToInt(intString);

      // go to next int if it exists
      getIntHelper(currentString, intArgs, startIndex, intIndex + 1);
    }
  }
}

bool readMetaData(metaData **data, char *fileName)
{
  char currentString[MAX_STR_LEN];
  metaData *headData = NULL;

  char command[MIN_STR_LEN], ioArg[MIN_STR_LEN], strArg[MIN_STR_LEN];
  int entryCycle, intArgs[3];

  // open file
  FILE *activeFile;

  if ((activeFile = fopen(fileName, "r")))
  {
    // read first line
    fgets(currentString, MAX_STR_LEN, activeFile);

    // check that we're in correct file
    if (compareStrings(currentString, "Start Program Meta-Data Code:") == 0)
    {
      // loop through file
      while (!feof(activeFile) && !(compareStrings("End", command) == 0))
      {
        fgets(currentString, MAX_STR_LEN, activeFile);
        getCommand(currentString, command);
        if (!(compareStrings("End", command) == 0))
        {
          entryCycle = getArgs(currentString, ioArg, strArg, intArgs);

          if (checkMetaDataNode(command, entryCycle, ioArg, strArg, intArgs))
          {
            headData = appendNode(headData, command, entryCycle, ioArg, strArg,
                                  intArgs);
          }
          else
          {
            headData = clearData(headData);
            print_error("Data is incorrect");
            return false;
          }
        }
      }
    }
    else
    {
      print_error("Wrong Meta Data File Type");
      return false;
    }
  }
  else
  {
    print_error("Meta Data File doesn't exist");
    return false;
  }

  // close file
  fclose(activeFile);
  *data = headData;
  return true;
}