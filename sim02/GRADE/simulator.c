// headers
#include "simulator.h"
#include "configuration.h"
#include "metaData.h"
#include "simtimer.h"

// functions
controlBlockData *appendData(controlBlockData *data, char *op, char *io)
{
  controlBlockData *newData;
  // if data isn't empty
  if (data != NULL)
  {
    // if next node isn't empty
    if (data->nextData != NULL)
    {
      appendData(data->nextData, op, io);
    }
    else // if next node is empty put it there
    {
      newData = createPCBDataNode(op, io);

      data->nextData = newData;
    }
  }
  else // if data is empty
  {
    newData = createPCBDataNode(op, io);
    data = newData;
  }

  return data;
}

fileData *appendLine(fileData *line, char *currentLine)
{
  fileData *newLine;

  if (line != NULL)
  {
    // if next node isn't empty
    if (line->nextLine != NULL)
    {
      appendLine(line->nextLine, currentLine);
    }
    else // if next node is empty put it there
    {
      newLine = createLineNode(currentLine);

      line->nextLine = newLine;
    }
  }
  else // if data is empty
  {
    newLine = createLineNode(currentLine);
    line = newLine;
  }

  return line;
}

controlBlock *appendPCB(controlBlock *block, int number, char *state)
{
  controlBlock *newBlock;
  // if data isn't empty
  if (block != NULL)
  {
    // if next node isn't empty
    if (block->nextBlock != NULL)
    {
      appendPCB(block->nextBlock, number, state);
    }
    else // if next node is empty put it there
    {
      newBlock = createPCBNode(number, state);

      block->nextBlock = newBlock;
    }
  }
  else // if data is empty
  {
    newBlock = createPCBNode(number, state);
    block = newBlock;
  }

  return block;
}

controlBlock *cleanPCBs(controlBlock *block)
{
  // loop until at last node
  if (block->nextBlock != NULL)
  {
    block->nextBlock = cleanPCBs(block->nextBlock);
  }

  // free data
  free(block->dataStart);
  free(block);

  return NULL;
}

controlBlockData *createPCBDataNode(char *op, char *IO)
{
  controlBlockData *data;

  data = (controlBlockData *)malloc(sizeof(controlBlockData));
  copyString(op, data->strArg);
  copyString(IO, data->ioArg);

  data->nextData = NULL;

  return data;
}

fileData *createLineNode(char *currentLine)
{
  fileData *line;

  line = (fileData *)malloc(sizeof(fileData));
  copyString(currentLine, line->lineString);

  line->nextLine = NULL;

  return line;
}

controlBlock *createPCBNode(int number, char *state)
{
  controlBlock *block;

  block = (controlBlock *)malloc(sizeof(controlBlock));

  block->idNum = number;
  copyString(state, block->state);
  block->timeRemaining = 0;

  block->dataStart = NULL;
  block->nextBlock = NULL;

  return block;
}

controlBlock *getProcess(controlBlock *block, char *cpuCode)
{
  // FCFS-N
  if (compareStrings(cpuCode, "FCFS-N") == 0)
  {
    // start at beginning, get first pcb that's set to ready
    while (compareStrings(block->state, "READY") != 0)
    {
      block = block->nextBlock;
      if (block == NULL)
      {
        return NULL;
      }
    }
  }

  return block;
}

void makePCBs(controlBlock **block, metaData *data)
{
  int index = 0, time;
  controlBlock *headBlock = NULL;
  controlBlockData *tempData;

  // loop through all of data
  while (data->nextData != NULL)
  {
    // check that we're at app start
    if (compareStrings(data->command, "app") == 0 &&
        compareStrings(data->strArg, "start") == 0)
    {
      time = 0;
      data = data->nextData;
      tempData = NULL;

      // set start data
      headBlock = appendPCB(headBlock, index, "NEW");

      // loop until end of app
      while ((compareStrings(data->command, "app") != 0 ||
              compareStrings(data->strArg, "end") != 0))
      {
        // get data and put it into the pcb
        if (compareStrings(data->ioArg, "in") == 0)
        {
          tempData = appendData(tempData, data->strArg, "input");
        }
        else if (compareStrings(data->ioArg, "out") == 0)
        {
          tempData = appendData(tempData, data->strArg, "output");
        }
        else
        {
          if (compareStrings(data->command, "mem") != 0)
          {
            tempData = appendData(tempData, data->command, data->strArg);
          }
        }

        // calculate time
        time = time + data->intArgOne;

        data = data->nextData;
      }

      // set the data and time
      headBlock = setData(headBlock, tempData, time);
      index++;
    }
    else
    {
      data = data->nextData;
    }
  }

  *block = headBlock;
}

void makeSim(configuration *config, metaData *data)
{
  controlBlock *block;
  fileData *line;
  bool monitor = false, file = false;

  // create PCB's
  makePCBs(&block, data);

  // get monitor and file bools
  monitor = (compareStrings(config->logTo, "Both") == 0 ||
             compareStrings(config->logTo, "Monitor") == 0);

  file = (compareStrings(config->logTo, "Both") == 0 ||
          compareStrings(config->logTo, "File") == 0);

  // run sim
  runSim(monitor, file, block, config, &line);

  // if file is true, print to file
  if (file)
  {
    writeToFile(config, data, line);
  }
}

void runSim(bool monitor, bool file, controlBlock *block, configuration *config,
            fileData **line)
{
  fileData *currentLine = NULL;
  controlBlock *tempBlock;
  char activeLine[MAX_STR_LEN];
  char simTime[MIN_STR_LEN];

  // if monitor is false, print waiting
  if (!monitor)
  {
    printf("Writing to file. Please wait.");
  }

  // print out start
  sprintf(activeLine, "Begin Simulation\n\n");
  currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

  // startTimer
  accessTimer(ZERO_TIMER, simTime);

  sprintf(activeLine, "%s, OS: Simulator start\n", simTime);
  currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

  // loop through pcb's setting them to ready
  tempBlock = block;
  while (tempBlock != NULL)
  {
    accessTimer(LAP_TIMER, simTime);
    sprintf(activeLine, "%s, OS: Process %d set to READY state from %s\n",
            simTime, tempBlock->idNum, tempBlock->state);
    currentLine = saveAndPrint(monitor, file, currentLine, activeLine);
    copyString("READY", tempBlock->state);
    tempBlock = tempBlock->nextBlock;
  }

  // get process based off cpuCode
  tempBlock = getProcess(block, config->cpuCode);
  while (tempBlock != NULL)
  {
    // print out pcb start
    accessTimer(LAP_TIMER, simTime);
    sprintf(activeLine, "%s, OS: Process %d selected with %d ms remaining\n",
            simTime, tempBlock->idNum, tempBlock->timeRemaining);
    currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

    // set pcb to running
    accessTimer(LAP_TIMER, simTime);
    sprintf(activeLine, "%s, OS: Process %d set from %s to RUNNING\n\n",
            simTime, tempBlock->idNum, tempBlock->state);
    currentLine = saveAndPrint(monitor, file, currentLine, activeLine);
    copyString("RUNNING", tempBlock->state);

    // loop through block data
    while (tempBlock->dataStart != NULL)
    {
      accessTimer(LAP_TIMER, simTime);
      sprintf(activeLine, "%s, Process: %d, %s %s operation start\n", simTime,
              tempBlock->idNum, tempBlock->dataStart->strArg,
              tempBlock->dataStart->ioArg);
      currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

      // simulate time wait
      setUpTimer(config, tempBlock->dataStart->ioArg);

      accessTimer(LAP_TIMER, simTime);
      sprintf(activeLine, "%s, Process: %d, %s %s operation end\n", simTime,
              tempBlock->idNum, tempBlock->dataStart->strArg,
              tempBlock->dataStart->ioArg);
      currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

      tempBlock->dataStart = tempBlock->dataStart->nextData;
    }

    accessTimer(LAP_TIMER, simTime);
    sprintf(activeLine, "\n%s, OS: Process %d ended\n", simTime,
            tempBlock->idNum);
    currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

    // set pcb to exit
    accessTimer(LAP_TIMER, simTime);
    sprintf(activeLine, "%s, OS: Process %d set to EXIT\n", simTime,
            tempBlock->idNum);
    currentLine = saveAndPrint(monitor, file, currentLine, activeLine);
    copyString("EXIT", tempBlock->state);

    tempBlock = getProcess(block, config->cpuCode);
  }

  // system end
  accessTimer(LAP_TIMER, simTime);
  sprintf(activeLine, "%s, OS: System stop\n", simTime);
  currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

  accessTimer(STOP_TIMER, simTime);
  sprintf(activeLine, "%s, OS: Simulation end\n\n", simTime);
  currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

  sprintf(activeLine, "End Simulation - Complete\n=========================");
  currentLine = saveAndPrint(monitor, file, currentLine, activeLine);

  *line = currentLine;

  // clear data
  block = cleanPCBs(block);
}

fileData *saveAndPrint(bool monitor, bool file, fileData *line,
                       char *activeLine)
{
  // print to monitor if monitor is true
  if (monitor)
  {
    printf(activeLine);
  }

  // add to file data if file is true
  if (file)
  {
    line = appendLine(line, activeLine);
  }

  return line;
}

controlBlock *setData(controlBlock *block, controlBlockData *data, int time)
{
  // go to last node and set data and time
  if (block->nextBlock != NULL)
  {
    setData(block->nextBlock, data, time);
  }
  else
  {
    block->timeRemaining = time;
    block->dataStart = data;
  }

  return block;
}

void setUpTimer(configuration *config, char *ctString)
{
  pthread_t ioThread;
  int runTime;

  // if IO op, run based off IO cycle time
  if ((compareStrings(ctString, "input") == 0) ||
      (compareStrings(ctString, "output") == 0))
  {
    runTime = config->ioCT;
  }

  // if process op, run based off process cycle time
  if (compareStrings(ctString, "process") == 0)
  {
    runTime = config->processorCT;
  }

  // thread
  pthread_create(&ioThread, NULL, runTimer, (void *)&runTime);
  pthread_join(ioThread, NULL);
}

void writeToFile(configuration *config, metaData *data, fileData *line)
{
  FILE *logFile = fopen(config->logFilePath, "w");

  // write to file with fprintf
  fprintf(logFile, "\n==================================================\n");
  fprintf(logFile, "Simulator Log File Header\n\n");
  fprintf(logFile, "File Name                       : %s\n", config->filePath);
  fprintf(logFile, "CPU Scheduling                  : %s\n", config->cpuCode);
  fprintf(logFile, "Quantum Cycles                  : %d\n", config->qTime);
  fprintf(logFile, "Memory Available (KB)           : %d\n",
          config->memAvailable);
  fprintf(logFile, "Processor Cycle Rate (ms/cycle) : %d\n",
          config->processorCT);
  fprintf(logFile, "I/O cycle rate (ms/cylce)       : %d\n", config->ioCT);
  fprintf(logFile, "\n================\n");

  // dump simulation data
  while (line != NULL)
  {
    fprintf(logFile, "%s", line->lineString);
    line = line->nextLine;
  }

  // close file
  fclose(logFile);
}
