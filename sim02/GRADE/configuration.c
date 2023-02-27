// headers
#include "configuration.h"

// constants

// functions
bool checkConfig(configuration *config)
{
  int index;
  char cpuCodes[5][10] = {"FCFS-N", "JF-N", "SRTF-P", "FCFS-P", "RR-P"};
  char onOff[2][5] = {"On", "Off"};
  char logTo[3][10] = {"Monitor", "Both", "File"};
  bool found = false;
  // check version
  if (config->version < 0 || config->version > 10)
  {
    return false;
  }

  // check cpuCode
  for (index = 0; index < 5 && !found; index++)
  {
    if (compareStrings(config->cpuCode, cpuCodes[index]) == 0)
    {
      found = true;
    }
  }
  if (!found)
  {
    return false;
  }

  // check qTime
  if (config->qTime < 0 || config->qTime > 100)
  {
    return false;
  }

  // check memoryAvailable
  if (config->memAvailable < 1024 || config->memAvailable > 102400)
  {
    return false;
  }

  // check mem display
  found = false;
  for (index = 0; index < 2 && !found; index++)
  {
    if (compareStrings(config->memory, onOff[index]) == 0)
    {
      found = true;
    }
  }
  if (!found)
  {
    return false;
  }

  // check processorCT
  if (config->processorCT < 0 || config->processorCT > 100)
  {
    return false;
  }

  // check IOcycle
  if (config->ioCT < 1 || config->ioCT > 100)
  {
    return false;
  }

  found = false;
  for (index = 0; index < 3 && !found; index++)
  {
    if (compareStrings(config->logTo, logTo[index]) == 0)
    {
      found = true;
    }
  }
  if (!found)
  {
    return false;
  }

  return true;
}

void display_config(configuration *config, bool displayFlag)
{
  // access data (function)
  if (!displayFlag)
  {
    print_error("Incorrect configuration file. Could not display data.");
  }
  else if (!checkConfig(config))
  {
    print_error("Data is out of bounds");
  }
  else
  {
    printf("Config File Display\n-------------------\n");
    printf("Version                 : %f\n", config->version);
    printf("Program File Name       : %s\n", config->filePath);
    printf("CPU schedule selection  : %s\n", config->cpuCode);
    printf("Quantum time            : %d\n", config->qTime);
    printf("Memory Available        : %d\n", config->memAvailable);
    printf("Memory Display (On/Off) : %s\n", config->memory);
    printf("Process cycle rate      : %d\n", config->processorCT);
    printf("I/O cycle rate          : %d\n", config->ioCT);
    printf("Log to selection        : %s\n", config->logTo);
    printf("Log file name           : %s\n", config->logFilePath);
  }
}

bool readConfiguration(configuration *config, char *fileName)
{
  char currentString[MAX_STR_LEN];
  // open file
  FILE *activeFile;

  if ((activeFile = fopen(fileName, "r")))
  {
    // get first line in file
    fgets(currentString, 100, activeFile);

    // check that we're in correct file
    if (compareStrings(currentString, "Start Simulator Configuration File:") ==
        0)
    {
      // we are reading the correct file
      // get data until end of file or read End
      while (!feof(activeFile) && !(compareStrings(currentString, "End") == 0))
      {
        // read line and put it in the right data
        fscanf(activeFile, "%s :", currentString);
        if (compareStrings(currentString, "Version/Phase") == 0)
        {
          fscanf(activeFile, "%f", &config->version);
        }
        else if (compareStrings(currentString, "File") == 0)
        {
          fscanf(activeFile, "Path : %s", config->filePath);
        }
        else if (compareStrings(currentString, "CPU") == 0)
        {
          fscanf(activeFile, "Scheduling Code : %s", config->cpuCode);
        }
        else if (compareStrings(currentString, "Quantum") == 0)
        {
          fscanf(activeFile, "Time (cycles) : %d", &config->qTime);
        }
        else if (compareStrings(currentString, "Memory") == 0)
        {
          fscanf(activeFile, "%s :", currentString);
          if (compareStrings(currentString, "Available") == 0)
          {
            fscanf(activeFile, "(KB) : %d", &config->memAvailable);
          }
          else if (compareStrings(currentString, "Display") == 0)
          {
            fscanf(activeFile, "(On/Off) : %s", config->memory);
          }
        }
        else if (compareStrings(currentString, "Processor") == 0)
        {
          fscanf(activeFile, "Cycle Time (msec) : %d", &config->processorCT);
        }
        else if (compareStrings(currentString, "I/O") == 0)
        {
          fscanf(activeFile, "Cycle Time (msec) : %d", &config->ioCT);
        }
        else if (compareStrings(currentString, "Log") == 0)
        {
          fscanf(activeFile, "%s :", currentString);
          if (compareStrings(currentString, "To") == 0)
          {
            fscanf(activeFile, "%s", config->logTo);
          }
          else if (compareStrings(currentString, "File") == 0)
          {
            fscanf(activeFile, "Path : %s", config->logFilePath);
          }
        }
      }
    }
    else // we're not in the correct file
    {
      print_error("Wrong Configuration File Type");
      return false;
    }
  }
  else // file couldn't open
  {
    print_error("Config file doesn't exist");
    return false;
  }

  // close file
  fclose(activeFile);
  return true;
}