// header files
#include "simDriver.h"

int main(int argc, char **argv)
{
  ConfigDataType *configDataPtr = NULL;
  OpCodeType *metaDataPtr = NULL;
  char errorMessage[MAX_STR_LEN];
  CmdLineData cmdLineData;
  bool configureUploadSucess = false;

  printf("\nSimulator Program\n");
  printf("==================\n\n");

  if (processCmdLine(argc, argv, &cmdLineData))
  {
    if (getConfigData(cmdLineData.fileName, &configDataPtr, errorMessage))
    {
      if (cmdLineData.configDisplayFlag)
      {
        displayConfigData(configDataPtr);
      }
      configureUploadSucess = true;
    }
    else
    {
      printf("\nConfig Upload Error: %s, program aborted\n\n", errorMessage);
    }

    if (configureUploadSucess &&
        (cmdLineData.mdDisplayFlag || cmdLineData.runSimFlag))
    {
      if (getMetaData(configDataPtr->metaDataFileName, &metaDataPtr,
                      errorMessage))
      {
        if (cmdLineData.mdDisplayFlag)
        {
          displayMetaData(metaDataPtr);
        }
        if (cmdLineData.runSimFlag)
        {
          runSim(configDataPtr, metaDataPtr);
        }
      }
      else
      {
        printf("\nMetadat Upload Error: %s, program aborted\n", errorMessage);
      }
    }

    configDataPtr = clearConfigData(configDataPtr);

    metaDataPtr = clearMetaDataList(metaDataPtr);
  }

  else
  {
    showCommandLineFormat();
  }

  printf("\nSimulator Program End.\n\n");

  return 0;
}

void clearCmdLineStruct(CmdLineData *clDataPtr)
{
  clDataPtr->programRunFlag = false;
  clDataPtr->configDisplayFlag = false;
  clDataPtr->mdDisplayFlag = false;
  clDataPtr->runSimFlag = false;
  clDataPtr->fileName[0] = NULL_CHAR;
}

bool processCmdLine(int numArgs, char **strVector, CmdLineData *clDataPtr)
{
  clearCmdLineStruct(clDataPtr);

  bool atLeastOneSwitchFlag = false;
  bool correctConfigFileFlag = false;
  int argIndex = 1;
  int fileStrLen, fileStrSubLoc;

  if (numArgs >= MIN_NUM_ARGS)
  {
    while (argIndex < numArgs)
    {
      if (compareString(strVector[argIndex], "-dc") == STR_EQ)
      {
        clDataPtr->configDisplayFlag = true;
        atLeastOneSwitchFlag = true;
      }
      else if (compareString(strVector[argIndex], "-dm") == STR_EQ)
      {
        clDataPtr->mdDisplayFlag = true;
        atLeastOneSwitchFlag = true;
      }
      else if (compareString(strVector[argIndex], "-rs") == STR_EQ)
      {
        clDataPtr->runSimFlag = true;
        atLeastOneSwitchFlag = true;
      }
      else
      {
        fileStrLen = getStringLength(strVector[numArgs - 1]);
        fileStrSubLoc = findSubString(strVector[numArgs - 1], ".cnf");
        if (fileStrSubLoc != SUBSTRING_NOT_FOUND &&
            fileStrSubLoc == fileStrLen - LAST_FOUR_LETTERS)
        {
          copyString(clDataPtr->fileName, strVector[numArgs - 1]);
          correctConfigFileFlag = true;
        }
        else
        {
          clearCmdLineStruct(clDataPtr);
        }
      }
      argIndex++;
    }
  }

  return atLeastOneSwitchFlag && correctConfigFileFlag;
}

void showCommandLineFormat()
{
  printf("Command Line Format:\n");
  printf("     sim_01 [-dc] [-dm] [-rs] <config file name>\n");
  printf("     -dc [optional] display configuration data\n");
  printf("     -dm [optional] display meta data\n");
  printf("     -rs [optional] run simulator\n");
  printf("     required config file name\n");
}