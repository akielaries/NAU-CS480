#include "simulator.h"

/*
Name: addLine
Process: adds a line to the log string linked list
Function Input/Parameters: output string (LogString *), line to be added (char
*) Function Output/Parameters: none Function Output/Returned: none Device
Input/device: none Device Output/device: none Dependencies: malloc, copyString
*/
void addLine(LogString **string, char *newLine)
{
  // Allocate memory for new node
  LogString *newNode = (LogString *)malloc(sizeof(LogString));
  LogString *current = *string;

  // Copy line string
  copyString(newNode->line, newLine);
  newNode->nextLine = NULL;

  // If linked list is empty
  if (*string == NULL)
  {
    *string = newNode;
  }

  // Otherwise, assume linked list is not empty
  else
  {
    // Loop to end of linked list
    while (current->nextLine != NULL)
    {
      current = current->nextLine;
    }

    // Add the new node to the end of the list
    current->nextLine = newNode;
  }
}

/*
Name: addProcess
Process: adds a process to the PCB linked list
Function Input/Parameters: pointer to linked list (PCBDataType **), process id
(int), execution time for process (int), state (int), pointer to start of op
code list (OpCodeType *) Function Output/Parameters: none Function
Output/Returned: pointer to current node in linked list (PCBDataType *) Device
Input/device: none Device Output/device: none Dependencies: malloc
*/
void addProcess(PCBDataType **PCBPtr, int process_id, int execution_time,
                int state, OpCodeType *start)
{
  // Allocate memory for new node
  PCBDataType *newNode = (PCBDataType *)malloc(sizeof(PCBDataType));
  PCBDataType *current = *PCBPtr;

  // Allocate memory for new memory linked list
  MemDataType *newMemory = (MemDataType *)malloc(sizeof(MemDataType));

  // Set memory default data
  newMemory->mem_start = MEM_START;
  newMemory->vmem_start = MEM_START;
  newMemory->vmem_end = MEM_START;
  newMemory->mem_end = MEM_START;
  newMemory->nextNode = NULL;

  // Set process data
  newNode->process_id = process_id;
  newNode->execution_time = execution_time;
  newNode->state = state;
  newNode->nextNode = NULL;
  newNode->start = start;
  newNode->memory = newMemory;

  // If linked list is empty
  if (*PCBPtr == NULL)
  {
    *PCBPtr = newNode;
  }

  // Otherwise, assume linked list is not empty
  else
  {
    // Loop to end of linked list
    while (current->nextNode != NULL)
    {
      current = current->nextNode;
    }

    // Add the new node to the end of the list
    current->nextNode = newNode;
  }
}

/*
Name: calcTime
Process: calculates the total amount of time a process will take
Function Input/Parameters: PCB ll pointer (PCBDataType *)
Function Output/Parameters: none
Function Output/Returned: calculated time (int)
Device Input/device: none
Device Output/device: none
Dependencies: compareString
*/
int calcTime(OpCodeType *metaDataPtr, ConfigDataType *configPtr)
{
  // Initialize variables
  int time = 0;

  // Loop through meta data until "app end"
  while (compareString(metaDataPtr->command, "app") != STR_EQ)
  {
    // Check if I/O operation
    if (compareString(metaDataPtr->command, "dev") == STR_EQ)
    {
      // Add operation time to total
      time += metaDataPtr->intArg2 * configPtr->ioCycleRate;
    }

    // Otherwise, check if CPU operation
    if (compareString(metaDataPtr->command, "cpu") == STR_EQ)
    {
      // Add operation time to total
      time += metaDataPtr->intArg2 * configPtr->procCycleRate;
    }

    // Move to next node
    metaDataPtr = metaDataPtr->nextNode;
  }

  // Return calculated time
  return time;
}

/*
Name: getNextProcess
Process: returns the next process according to the scheduling code
Function Input/Parameters: configuration data (ConfigDataType *), PCB ll pointer
(PCBDataType *), boolean indicating starting node (bool) Function
Output/Parameters: none Function Output/Returned: pointer to next process or
NULL if at the end Device Input/device: none Device Output/device: none
Dependencies: calcTime
*/
PCBDataType *getNextProcess(ConfigDataType *configPtr, PCBDataType *PCBPtr,
                            bool start)
{
  // Initialize variables
  PCBDataType *nextNode = NULL;
  PCBDataType *localPtr = PCBPtr;
  OpCodeType *metaDataStart;

  // Check if FCFS-N
  if (configPtr->cpuSchedCode == CPU_SCHED_FCFS_N_CODE)
  {
    // If start node
    if (start)
    {
      // Return original node
      nextNode = PCBPtr;
    }

    // Otherwise, assume not starting node
    else
    {
      // Move to next process
      nextNode = PCBPtr->nextNode;
    }
  }

  // Otherwise, check if SJF-N
  else if (configPtr->cpuSchedCode == CPU_SCHED_SJF_N_CODE)
  {
    // Loop through the linked list of processes
    while (localPtr != NULL)
    {
      // Calculate process time
      metaDataStart = localPtr->start->nextNode;
      localPtr->execution_time = calcTime(metaDataStart, configPtr);

      // Set first node to shortest job by default
      if ((nextNode == NULL) && (localPtr->state == READY_STATE))
      {
        nextNode = localPtr;
      }

      // If the current node is not NULL, then preform tests for shortest job
      if (nextNode != NULL)
      {
        // If the current node takes less time than the previous shortest job,
        // and is READY, then set to new shortest
        if ((localPtr->execution_time < nextNode->execution_time) &&
            (localPtr->state == READY_STATE))
        {
          nextNode = localPtr;
        }
      }

      // Traverse to next node
      localPtr = localPtr->nextNode;
    }
  }

  // Return the next node
  return nextNode;
}

/*
Name: logDump
Process: dumps contents of output string to file specified in config
Function Input/Parameters: configuration data (ConfigDataType *), output string
(LogString *) Function Output/Parameters: none Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: fopen, fprintf, fclose
*/
void logDump(ConfigDataType *configPtr, LogString *string)
{
  // Initialize variables
  const char WRITE_FLAG[] = "w";

  // Open file
  FILE *logFile = fopen(configPtr->logToFileName, WRITE_FLAG);

  // Add file header
  fprintf(logFile, "==================================================\n");
  fprintf(logFile, "Simulator Log File Header\n\n");
  fprintf(logFile, "File Name                       : %s\n",
          configPtr->metaDataFileName);
  fprintf(logFile, "CPU Scheduling                  : %s\n", "FCFS-N");
  fprintf(logFile, "Quantum Cycles                  : %d\n",
          configPtr->quantumCycles);
  fprintf(logFile, "Memory Available (KB)           : %d\n",
          configPtr->memAvailable);
  fprintf(logFile, "Processor Cycle Rate (ms/cycle) : %d\n",
          configPtr->procCycleRate);
  fprintf(logFile, "I/O Cycle Rate (ms/cycle)       : %d\n\n",
          configPtr->ioCycleRate);

  // Loop through linked list (LogString), writing to file
  while (string != NULL)
  {
    fprintf(logFile, string->line);
    string = string->nextLine;
  }

  // Close file
  fclose(logFile);
}

/*
Name: outputLine
Process: checks the config for output destination, prints given line to monitor
or stores it Function Input/Parameters: configuration data (ConfigDataType *),
output string (LogString *), line to add to output (char *), memory operation
indicator (bool) Function Output/Parameters: none Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: printf, addLine
*/
void outputLine(ConfigDataType *configPtr, LogString **string, char *line,
                bool memory_op)
{
  // Check if output is to monitor or both
  if (configPtr->logToCode == LOGTO_MONITOR_CODE ||
      configPtr->logToCode == LOGTO_BOTH_CODE)
  {
    // Print to monitor
    printf(line);
  }

  // Check if output is to file or both, and not a memory operation
  if ((configPtr->logToCode == LOGTO_FILE_CODE ||
       configPtr->logToCode == LOGTO_BOTH_CODE) &&
      !memory_op)
  {
    // Add line to the file
    addLine(string, line);
  }
}

/*
Name: queueProcess
Process: queues processes in FCFS-N order, generating a linked list
Function Input/Parameters: configuration data (ConfigDataType *), output string
(LogString *), meta data (OpCodeType *), PCB ll pointer (PCBDataType *), current
time (char *) Function Output/Parameters: none Function Output/Returned: pointer
to head of PCB linked list (PCBDataType *) Device Input/device: none Device
Output/device: none Dependencies: compareString, addProcess, accessTimer,
sprintf, outputLine
*/
PCBDataType *queueProcess(ConfigDataType *configPtr, LogString *string,
                          OpCodeType *metaDataPtr, PCBDataType *PCBPtr,
                          char *clock)
{
  // Initialize variables, set initial process id to 0
  int pid = 0;
  char line[MAX_STR_LEN];

  // If so, loop through meta data
  while (metaDataPtr != NULL)
  {
    // Check if metadata starts a process
    if (compareString(metaDataPtr->command, "app") == STR_EQ &&
        compareString(metaDataPtr->strArg1, "start") == STR_EQ)
    {
      // If so, add process, set to ready state with default values
      addProcess(&PCBPtr, pid, 0, READY_STATE, metaDataPtr);

      accessTimer(LAP_TIMER, clock);
      sprintf(line, "  %s, OS: Process %d set to READY state from NEW state\n",
              clock, pid);
      outputLine(configPtr, &string, line, false);

      // Increment process id
      pid++;
    }

    // Move to next node in meta data
    metaDataPtr = metaDataPtr->nextNode;
  }

  // Return pointer to head of linked list
  return PCBPtr;
}

/*
Name: runCPU
Process: runs CPU operations
Function Input/Parameters: configuration data (ConfigDataType *), output string
(LogString *), meta data (OpCodeType *), process id (int), current time (char *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: accessTimer, sprintf, outputLine
*/
void runCPU(ConfigDataType *configPtr, LogString *string,
            OpCodeType *metaDataPtr, int process_id, char *clock)
{
  // Initialize variables
  char line[MAX_STR_LEN];

  // Start simulation
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, Process: %d, cpu process operation start\n", clock,
          process_id);
  outputLine(configPtr, &string, line, false);

  // Run timer
  runTimer(metaDataPtr->intArg2 * configPtr->procCycleRate);

  // End simulation
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, Process: %d, cpu process operation end\n", clock,
          process_id);
  outputLine(configPtr, &string, line, false);
}

/*
Name: runDev
Process: runs I/O operations, creates thread
Function Input/Parameters: configuration data (ConfigDataType *), output string
(LogString *), meta data (OpCodeType *), process id (int), current time (char *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: accessTimer, sprintf, outputLine, runTimer, pthread_create,
pthread_join
*/
void runDev(ConfigDataType *configPtr, LogString *string,
            OpCodeType *metaDataPtr, int process_id, char *clock)
{
  // Initialize variables
  pthread_t thread_id;
  char line[MAX_STR_LEN];

  // Multiple time by I/O cycle rate to get cycled time
  int time = metaDataPtr->intArg2 * configPtr->ioCycleRate;
  void *cycledTime = (void *)&time;

  // Start simulation
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, Process: %d, %s %sput operation start\n", clock,
          process_id, metaDataPtr->strArg1, metaDataPtr->inOutArg);
  outputLine(configPtr, &string, line, false);

  // Create thread to run timer
  pthread_create(&thread_id, NULL, startTimer, cycledTime);

  // Join thread with main upon completion
  pthread_join(thread_id, NULL);

  // End simulation
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, Process: %d, %s %sput operation end\n", clock,
          process_id, metaDataPtr->strArg1, metaDataPtr->inOutArg);
  outputLine(configPtr, &string, line, false);
}

/*
Name: runMemAccess
Process: runs memory access operation
Function Input/Parameters: configuration data (ConfigDataType *), output string
(LogString *), meta data (OpCodeType *), process id (int), current time (char *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: accessTimer, sprintf, outputLine
*/
void runMemAccess(ConfigDataType *configPtr, LogString *string,
                  OpCodeType *metaDataPtr, PCBDataType *PCBPtr, char *clock)
{
  // Initialize Variables
  char line[MAX_STR_LEN];
  bool success = false;
  MemDataType *memory = PCBPtr->memory;
  MemDataType *head_memory = memory;

  // Start simulation
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, Process: %d, mem access request (%d, %d)\n", clock,
          PCBPtr->process_id, metaDataPtr->intArg2, metaDataPtr->intArg3);
  outputLine(configPtr, &string, line, false);

  // Loop through memory history to try accessing memory
  while (memory->nextNode != NULL)
  {
    // First, check if target is in between current virtual memory block
    // Second, check if not accessing out of bounds of page
    if ((metaDataPtr->intArg2 >= memory->nextNode->vmem_start) &&
        (metaDataPtr->intArg2 <= memory->nextNode->vmem_end) &&
        (metaDataPtr->intArg2 + metaDataPtr->intArg3 <=
         memory->nextNode->vmem_end + MEM_OFFSET))
    {
      // If passes tests, set success to true
      success = true;
    }

    // Loop to next node in memory linked list
    memory = memory->nextNode;
  }

  // If memory display flag is set, display memory operations if success
  if (configPtr->memDisplay && success)
  {
    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "After access success\n");
    outputLine(configPtr, &string, line, true);

    // Loop through memory history and display
    while (head_memory->nextNode != NULL)
    {
      // Traverse to the next node in memory
      head_memory = head_memory->nextNode;

      // Display used memory
      sprintf(line, "%d [ Used, P#: %d, %d-%d ] %d\n", head_memory->mem_start,
              PCBPtr->process_id, head_memory->vmem_start,
              head_memory->vmem_end, head_memory->mem_end - MEM_OFFSET);
      outputLine(configPtr, &string, line, true);
    }

    // Display open memory
    sprintf(line, "%d [ Open, P#: x, 0-0 ] %d\n", memory->mem_end,
            configPtr->memAvailable);
    outputLine(configPtr, &string, line, true);

    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);
  }

  // If memory display flag is set, display memory operations if failure
  else if (configPtr->memDisplay && !success)
  {
    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "After access failure\n");
    outputLine(configPtr, &string, line, true);

    // Loop through memory history and display
    while (head_memory->nextNode != NULL)
    {
      // Traverse to the next node in memory
      head_memory = head_memory->nextNode;

      // Display used memory
      sprintf(line, "%d [ Used, P#: %d, %d-%d ] %d\n", head_memory->mem_start,
              PCBPtr->process_id, head_memory->vmem_start,
              head_memory->vmem_end, head_memory->mem_end - MEM_OFFSET);
      outputLine(configPtr, &string, line, true);
    }

    // Display open memory to user
    sprintf(line, "%d [ Open, P#: x, 0-0 ] %d\n", memory->mem_end,
            configPtr->memAvailable - MEM_OFFSET);
    outputLine(configPtr, &string, line, true);

    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);
  }

  // End simulation with success
  if (success)
  {
    accessTimer(LAP_TIMER, clock);
    sprintf(line, "  %s, Process: %d, successful mem access request\n", clock,
            PCBPtr->process_id);
    outputLine(configPtr, &string, line, false);
  }

  // Otherwise, assume failure, end simulation with failure
  else
  {
    accessTimer(LAP_TIMER, clock);
    sprintf(line, "  %s, Process: %d, failed mem access request\n", clock,
            PCBPtr->process_id);
    outputLine(configPtr, &string, line, false);

    // Display seg fault notification
    accessTimer(LAP_TIMER, clock);
    sprintf(line, "\n  %s, OS: Segmentation fault, Process %d ended\n", clock,
            PCBPtr->process_id);
    outputLine(configPtr, &string, line, false);

    // Set process to exit
    PCBPtr->state = EXIT_STATE;
  }
}

/*
Name: runMemAllocate
Process: runs memory allocate operation
Function Input/Parameters: configuration data (ConfigDataType *), output string
(LogString *), meta data (OpCodeType *), process id (int), current time (char *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: accessTimer, sprintf, outputLine, malloc
*/
void runMemAllocate(ConfigDataType *configPtr, LogString *string,
                    OpCodeType *metaDataPtr, PCBDataType *PCBPtr, char *clock)
{
  // Initialize Variables
  char line[MAX_STR_LEN];
  bool success = true;
  MemDataType *memory = PCBPtr->memory;
  MemDataType *head_memory = memory;
  MemDataType *previous_memory;
  MemDataType *newMemoryNode = (MemDataType *)malloc(sizeof(MemDataType));

  // Start simulation
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, Process: %d, mem allocate request (%d, %d)\n", clock,
          PCBPtr->process_id, metaDataPtr->intArg2, metaDataPtr->intArg3);
  outputLine(configPtr, &string, line, false);

  // Loop through memory history to find virtual memory conflicts
  while (memory != NULL)
  {
    // First, test for overlaping virtual memory inside data
    // Second, test for overwriting data inside bounds
    // Third, test for overwriting data upper bound
    if (((metaDataPtr->intArg2 >= memory->vmem_start) &&
         (metaDataPtr->intArg2 <= memory->vmem_end)) ||
        ((metaDataPtr->intArg2 + metaDataPtr->intArg3 >= memory->vmem_start) &&
         (metaDataPtr->intArg2 + metaDataPtr->intArg3 <= memory->vmem_end)) ||
        ((metaDataPtr->intArg2 <= memory->vmem_start) &&
         (metaDataPtr->intArg2 + metaDataPtr->intArg3 >= memory->vmem_start)))
    {
      // If these conditions are met, memory allocate request has failed
      success = false;
    }

    // Loop to next node in memory linked list
    previous_memory = memory;
    memory = memory->nextNode;
  }

  // Restore memory pointer to previous position in linked list
  memory = previous_memory;

  // Test for any physical memory conflicts
  if ((memory->mem_start + metaDataPtr->intArg3) > configPtr->memAvailable)
  {
    // If any conflicts, set success to false
    success = false;
  }

  // If successful memory op, set new bounds for virtual memory
  if (success)
  {
    newMemoryNode->vmem_start = metaDataPtr->intArg2;
    newMemoryNode->vmem_end =
        metaDataPtr->intArg2 + metaDataPtr->intArg3 - MEM_OFFSET;
    newMemoryNode->mem_start = memory->mem_end;
    newMemoryNode->mem_end = memory->mem_end + metaDataPtr->intArg3;

    memory->nextNode = newMemoryNode;
  }

  // If memory display flag is set, display memory operations if success
  if (configPtr->memDisplay && success)
  {
    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "After allocate success\n");
    outputLine(configPtr, &string, line, true);

    // Loop through memory history
    while (head_memory->nextNode != NULL)
    {
      // Display used memory
      sprintf(line, "%d [ Used, P#: %d, %d-%d ] %d\n",
              head_memory->nextNode->mem_start, PCBPtr->process_id,
              head_memory->nextNode->vmem_start,
              head_memory->nextNode->vmem_end,
              head_memory->nextNode->mem_end - MEM_OFFSET);
      outputLine(configPtr, &string, line, true);

      head_memory = head_memory->nextNode;
    }

    // Display open memory
    sprintf(line, "%d [ Open, P#: x, 0-0 ] %d\n", memory->nextNode->mem_end,
            configPtr->memAvailable - MEM_OFFSET);
    outputLine(configPtr, &string, line, true);

    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);
  }

  // If memory display flag is set, display memory operations if failure
  else if (configPtr->memDisplay && !success)
  {
    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "After allocate overlap failure\n");
    outputLine(configPtr, &string, line, true);

    // Loop through memory history
    while (head_memory->nextNode != NULL)
    {
      // Display used memory
      sprintf(line, "%d [ Used, P#: %d, %d-%d ] %d\n",
              head_memory->nextNode->mem_start, PCBPtr->process_id,
              head_memory->nextNode->vmem_start,
              head_memory->nextNode->vmem_end,
              head_memory->nextNode->mem_end - MEM_OFFSET);
      outputLine(configPtr, &string, line, true);

      head_memory = head_memory->nextNode;
    }

    // Display open memory
    sprintf(line, "%d [ Open, P#: x, 0-0 ] %d\n", memory->mem_end,
            configPtr->memAvailable - MEM_OFFSET);
    outputLine(configPtr, &string, line, true);

    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);
  }

  // End simulation with success
  if (success)
  {
    accessTimer(LAP_TIMER, clock);
    sprintf(line, "  %s, Process: %d, successful mem allocate request\n", clock,
            PCBPtr->process_id);
    outputLine(configPtr, &string, line, false);
  }

  // Otherwise, assume failure, end simulation with failure
  else
  {
    accessTimer(LAP_TIMER, clock);
    sprintf(line, "  %s, Process: %d, failed mem allocate request\n", clock,
            PCBPtr->process_id);
    outputLine(configPtr, &string, line, false);

    // Display seg fault notification
    accessTimer(LAP_TIMER, clock);
    sprintf(line, "\n  %s, OS: Segmentation fault, Process %d ended\n", clock,
            PCBPtr->process_id);
    outputLine(configPtr, &string, line, false);

    // Set process to exit
    PCBPtr->state = EXIT_STATE;
  }
}

/*
Name: runProcess
Process: runs a given process until completion
Function Input/Parameters: configuration data (ConfigDataType *), output string
(LogString *), PCB ll pointer (PCBDataType *), current time (char *) Function
Output/Parameters: none Function Output/Returned: none Device Input/device: none
Device Output/device: none
Dependencies: accessTimer, sprintf, outputLine, compareString, runCPU, runDev,
runMemAllocate, runMemAccess
*/
void runProcess(ConfigDataType *configPtr, LogString *string,
                PCBDataType *PCBPtr, char *clock)
{
  // Initialize variables
  OpCodeType *metaDataPtr = PCBPtr->start->nextNode;
  int process_id = PCBPtr->process_id;
  char line[MAX_STR_LEN];

  // Calculate execution time
  OpCodeType *metaDataStart = PCBPtr->start->nextNode;
  PCBPtr->execution_time = calcTime(metaDataStart, configPtr);
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, OS: Process %d selected with %d ms remaining\n", clock,
          process_id, PCBPtr->execution_time);
  outputLine(configPtr, &string, line, false);

  // Switch process from READY to RUNNING
  PCBPtr->state = RUNNING_STATE;
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, OS: Process %d set from READY to RUNNING\n\n", clock,
          process_id);
  outputLine(configPtr, &string, line, false);

  // Run op code lines until reaching "app end", make sure state is not set to
  // exit
  while ((compareString(metaDataPtr->command, "app") != STR_EQ) &&
         (PCBPtr->state != EXIT_STATE))
  {
    // Check if cpu op
    if (compareString(metaDataPtr->command, "cpu") == STR_EQ)
    {
      runCPU(configPtr, string, metaDataPtr, process_id, clock);
    }

    // Check for dev op
    else if (compareString(metaDataPtr->command, "dev") == STR_EQ)
    {
      runDev(configPtr, string, metaDataPtr, process_id, clock);
    }

    // Check for mem op
    else if (compareString(metaDataPtr->command, "mem") == STR_EQ)
    {
      // Check for allocate request
      if (compareString(metaDataPtr->strArg1, "allocate") == STR_EQ)
      {
        runMemAllocate(configPtr, string, metaDataPtr, PCBPtr, clock);
      }

      // Check for access request
      else if (compareString(metaDataPtr->strArg1, "access") == STR_EQ)
      {
        runMemAccess(configPtr, string, metaDataPtr, PCBPtr, clock);
      }
    }

    // Move to next node
    metaDataPtr = metaDataPtr->nextNode;
  }

  // If not seg fault, display process ended as normal
  if (PCBPtr->state != EXIT_STATE)
  {
    // End process
    accessTimer(LAP_TIMER, clock);
    sprintf(line, "\n  %s, OS: Process %d ended\n", clock, PCBPtr->process_id);
    outputLine(configPtr, &string, line, false);
  }

  // If memory display is enabled, display free-ing of memory
  if (configPtr->memDisplay)
  {
    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "After clear process %d success\n", PCBPtr->process_id);
    outputLine(configPtr, &string, line, true);

    sprintf(line, "0 [ Open, P#: x, 0-0 ] %d\n",
            configPtr->memAvailable - MEM_OFFSET);
    outputLine(configPtr, &string, line, true);

    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);
  }

  // Set process to EXIT state
  PCBPtr->state = EXIT_STATE;
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, OS: Process %d set to EXIT\n", clock,
          PCBPtr->process_id);
  outputLine(configPtr, &string, line, false);
}

/*
Name: runSim
Process: primary simulation driver
Function Input/Parameters: configuration data (ConfigDataType *),
                           metadata (OpCodeType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/device: none
Device Output/device: none
Dependencies: printf, sprintf, outputLine, queueProcess, runProcess,
accessTimer, logDump
*/
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr)
{
  // Initialize Program

  // Initialize variables
  OpCodeType *metaDataPtr = metaDataMstrPtr;
  PCBDataType *PCBPtr = NULL;
  char clock[STD_STR_LEN];
  char line[MAX_STR_LEN];
  LogString *string = NULL;
  PCBDataType *nextProcess;

  // Check if output is only to file
  if (configPtr->logToCode == LOGTO_FILE_CODE)
  {
    // If so, display notification to monitor
    printf("Simulator running for output to file only\n");
  }

  // Display title
  sprintf(line, "================\n");
  outputLine(configPtr, &string, line, false);
  sprintf(line, "Begin Simulation\n\n");
  outputLine(configPtr, &string, line, false);

  // START SIMULATOR

  // Start clock
  accessTimer(ZERO_TIMER, clock);
  sprintf(line, "  %s, OS: Simulator start\n", clock);
  outputLine(configPtr, &string, line, false);

  // Queue processes, returns as pointer to the head of the PCB linked list
  PCBPtr = queueProcess(configPtr, string, metaDataPtr, PCBPtr, clock);

  // If memory display is enabled, display memory initialization
  if (configPtr->memDisplay)
  {
    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "After memory initialization\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "0 [ Open, P#: x, 0-0 ] %d\n",
            configPtr->memAvailable - MEM_OFFSET);
    outputLine(configPtr, &string, line, true);

    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);
  }

  // Gets initial process based on scheduling
  nextProcess = getNextProcess(configPtr, PCBPtr, true);

  // While there is a next process
  while (nextProcess != NULL)
  {
    // Run the process
    runProcess(configPtr, string, nextProcess, clock);

    // Get the next process
    nextProcess = getNextProcess(configPtr, PCBPtr, false);
  }

  // END SIMULATOR

  // Display stop to user
  accessTimer(LAP_TIMER, clock);
  sprintf(line, "  %s, OS: System stop\n", clock);
  outputLine(configPtr, &string, line, false);

  // If memory display is enabled, display memory clear
  if (configPtr->memDisplay)
  {
    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "After clear all process sucess\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "No memory configured\n");
    outputLine(configPtr, &string, line, true);

    sprintf(line, "--------------------------------------------------\n");
    outputLine(configPtr, &string, line, true);
  }

  // Stop the timer, end program
  accessTimer(STOP_TIMER, clock);
  sprintf(line, "  %s, OS: Simulation end\n\n", clock);
  outputLine(configPtr, &string, line, false);
  sprintf(line, "End Simulation - Complete\n");
  outputLine(configPtr, &string, line, false);
  sprintf(line, "=========================\n");
  outputLine(configPtr, &string, line, false);

  // Check if write to file, if so, dump output string to file
  if (configPtr->logToCode == LOGTO_FILE_CODE ||
      configPtr->logToCode == LOGTO_BOTH_CODE)
  {
    logDump(configPtr, string);
  }
}

/*
Name: startTimer
Process: runs timer in thread for specified time (ms)
Function Input/Parameters: time in ms (void * -> int)
Function Output/Parameters: none
Function Output/Returned: NULL value (void *)
Device Input/device: none
Device Output/device: none
Dependencies: runTimer
*/
void *startTimer(void *time_ms)
{
  // Cast void * argument to int
  int time = *(int *)time_ms;

  // Run the timer for specified time
  runTimer(time);

  return NULL;
}
