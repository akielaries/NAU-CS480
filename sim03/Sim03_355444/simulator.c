/**
 * Driver code for running the simulator
 */

/**
 *TODO: FIXME: ETC.
 * - fix datatype names, go over declarations within loops, if/elses
 * - fix dump log to file?
 * - go thru comments, delete/add
 *
 *
 */
#include "simulator.h"

void copyConfigData(ConfigDataType *dest, ConfigDataType *src)
{
  dest->version = src->version;
  copyString(dest->metaDataFileName, src->metaDataFileName);
  dest->cpuSchedCode = src->cpuSchedCode;
  dest->quantumCycles = src->quantumCycles;
  dest->memDisplay = src->memDisplay;
  dest->memAvailable = src->memAvailable;
  dest->procCycleRate = src->procCycleRate;
  dest->ioCycleRate = src->ioCycleRate;
  dest->logToCode = src->logToCode;
  copyString(dest->logToFileName, src->logToFileName);
}

/* LOG node */
LOGnode *LOGnode_add(LOGnode *local_ptr, char *txt_input)
{
  LOGnode *new_ptr;
  if (local_ptr)
  {
    local_ptr->next_ptr = LOGnode_add(local_ptr->next_ptr, txt_input);
    return local_ptr;
  }
  else
  {
    new_ptr = (LOGnode *)malloc(sizeof(LOGnode));
    copyString(new_ptr->LOG_out, txt_input);
    new_ptr->next_ptr = NULL;
    return new_ptr;
  }

  /**
  if (local_ptr == NULL)
  {
    local_ptr = (LOGnode *)malloc(sizeof(LOGnode));
    copyString(local_ptr->LOG_out, txt_input);
    local_ptr->next_ptr = NULL;
    return local_ptr;
  }

  local_ptr->next_ptr = LOGnode_add(local_ptr->next_ptr, txt_input);
  return local_ptr;*/
}

LOGnode *LOGnode_del(LOGnode *local_ptr)
{
  if (!local_ptr)
  {
    return 0;
  }
  else
  {
    LOGnode_del(local_ptr->next_ptr);
  }

  free(local_ptr);
  return 0;
}

void LOGdump(int trigger, ConfigDataType *config_dataptr, char *txt_input)
{
  // TODO: GET THIS WORKING CORRECTLY, OUTPUT TO FILE
  char outputString[MAX_STR_LEN];
  char timeString[MIN_STR_LEN];
  char WRITE_FLAG[2];
  int temp_trigger; // = trigger;
  FILE *outFilePtr;
  // ConfigDataType *config_dataptr = NULL;
  LOGnode *log_ptr = NULL;
  LOGnode *wkg_log_ptr = NULL;

  copyString(WRITE_FLAG, "w");
  // check if start of line = OS:
  getSubString(outputString, txt_input, 0, 2);
  copyString(outputString, "\n ");

  if (trigger == INIT_LOG)
  {
    log_ptr = NULL;
    // config_dataptr = (ConfigDataType *)malloc(sizeof(ConfigDataType));
    // copyConfigData(config_dataptr, config_dataptr);
    accessTimer(LAP_TIMER, timeString);
    temp_trigger = 1;
    // trigger = 1;

    if (config_dataptr->logToCode == LOGTO_FILE_CODE)
    {
      printf("Simulator running with output to file\n");
    }
  }
  else
  {
    accessTimer(LAP_TIMER, timeString);
    temp_trigger = trigger;
  }

  if (temp_trigger == ADD_LOG)
  {
    concatenateString(outputString, timeString);
    concatenateString(outputString, ", ");
    concatenateString(outputString, txt_input);
    if (config_dataptr->logToCode == LOGTO_FILE_CODE ||
        config_dataptr->logToCode == LOGTO_BOTH_CODE)
    {
      log_ptr = LOGnode_add(log_ptr, outputString);
    }

    if (config_dataptr->logToCode == LOGTO_BOTH_CODE ||
        config_dataptr->logToCode == LOGTO_MONITOR_CODE)
    {
      printf(outputString);
    }
  }
  else
  {
    wkg_log_ptr = log_ptr;
    outFilePtr = fopen(config_dataptr->logToFileName, WRITE_FLAG);
    fprintf(outFilePtr,
            "\n==================================================\n");
    fprintf(outFilePtr, "Simulator Log File Header\n\n");
    fprintf(outFilePtr, "File Name                       : %s\n",
            config_dataptr->metaDataFileName);
    configCodeToString(config_dataptr->cpuSchedCode, outputString);
    fprintf(outFilePtr, "CPU Scheduling                  : %s\n", outputString);
    fprintf(outFilePtr, "Quantum Cycles                  : %d\n",
            config_dataptr->quantumCycles);
    fprintf(outFilePtr, "Memory Available (KB)           : %d\n",
            config_dataptr->memAvailable);
    fprintf(outFilePtr, "Processor Cycle Rate (ms/cycle) : %d\n",
            config_dataptr->procCycleRate);
    fprintf(outFilePtr, "I/O Cycle Rate (ms/cycle)       : %d\n\n",
            config_dataptr->ioCycleRate);
    fprintf(outFilePtr, "================\n");
    fprintf(outFilePtr, "Begin Simulation\n\n");

    while (wkg_log_ptr)
    {
      fprintf(outFilePtr, "%s\n", wkg_log_ptr->LOG_out);
      wkg_log_ptr = wkg_log_ptr->next_ptr;
    }

    fprintf(outFilePtr, "\nEnd Simulation - Complete\n");
    fprintf(outFilePtr, "=========================\n\n");

    fclose(outFilePtr);
  }
  log_ptr = LOGnode_del(log_ptr);
  // free(config_dataptr);
}

/* PCB node */
PCBdata *PCBnode_add(PCBdata *local_ptr, PCBdata *new_ptr)
{
  PCBdata *wkg_ptr;

  if (local_ptr && new_ptr->OClist->intArg2 >= local_ptr->OClist->intArg2)
  {
    for (wkg_ptr = local_ptr;
         wkg_ptr->next_ptr &&
         new_ptr->OClist->intArg2 >= wkg_ptr->next_ptr->OClist->intArg2;
         wkg_ptr = wkg_ptr->next_ptr)
    {
      ;
    }
    new_ptr->next_ptr = wkg_ptr->next_ptr;
    wkg_ptr->next_ptr = new_ptr;
  }
  else
  {
    new_ptr->next_ptr = local_ptr;
    return new_ptr;
  }
  return local_ptr;
}

PCBdata *PCBnode_del(PCBdata *local_ptr)
{
  if (local_ptr)
  {
    PCBnode_del(local_ptr->next_ptr);
    free(local_ptr);
  }
  return 0;
}

PCBdata *PCBnode_pid(PCBdata *local_ptr, int PCB_PID)
{
  while (local_ptr)
  {
    if (local_ptr->pid == PCB_PID)
    {
      return local_ptr;
    }
    local_ptr = local_ptr->next_ptr;
  }
  return 0;
}

PCBdata *PCBcreate(ConfigDataType *config_dataptr, OpCodeType *md_head_ptr)
{
  PCBdata *new_ptr;
  PCBdata *head_ptr = NULL;

  int pidSet = NEW_STATE;
  if (compareString(md_head_ptr->command, "sys") ||
      compareString(md_head_ptr->strArg1, "start"))
  {
    return 0;
  }
  for (md_head_ptr = md_head_ptr->next_ptr;
       compareString(md_head_ptr->command, "sys") &&
       compareString(md_head_ptr->strArg1, "end");
       md_head_ptr = md_head_ptr->next_ptr)
  {
    if (!compareString(md_head_ptr->command, "app") &&
        !compareString(md_head_ptr->strArg1, "start"))
    {
      new_ptr = (PCBdata *)malloc(sizeof(PCBdata) + 1);
      new_ptr->pid = pidSet;
      new_ptr->state = NEW_STATE;
      new_ptr->time_left = 0;
      new_ptr->time_start = (double)md_head_ptr->intArg2;
      new_ptr->quant_time = true;
      new_ptr->OCcurr = NULL;
      new_ptr->OClist = md_head_ptr;
      new_ptr->next_ptr = NULL;
      while (compareString(md_head_ptr->command, "app") ||
             compareString(md_head_ptr->strArg1, "end"))
      {
        if (compareString(md_head_ptr->command, "mem"))
        {
          int op_time = 0;
          if (compareString(md_head_ptr->command, "dev"))
          {
            op_time = md_head_ptr->intArg2 * config_dataptr->procCycleRate;
          }
          else
          {
            op_time = md_head_ptr->intArg2 * config_dataptr->ioCycleRate;
          }

          new_ptr->time_left = new_ptr->time_left + op_time;

          if (config_dataptr->cpuSchedCode &&
              config_dataptr->cpuSchedCode != CPU_SCHED_FCFS_N_CODE)
          {
            md_head_ptr->intArg3 = PREEMPTIVE_CODE;
          }
          else
          {
            md_head_ptr->intArg3 = NON_PREEMPTIVE_CODE;
          }
        }
        md_head_ptr->pid = pidSet;
        md_head_ptr = md_head_ptr->next_ptr;
      }
      head_ptr = PCBnode_add(head_ptr, new_ptr);
      ++pidSet;
    }
  }
  return head_ptr;
  free(new_ptr);
}

int PCBparse(ConfigDataType *config_dataptr, PCBdata *local_ptr)
{
  int PCBid = 0;
  int minTime = 0;
  int minId = NULL_PID;
  int loopCount = 0;
  int newBlockedCount = 0;

  if (config_dataptr->cpuSchedCode == CPU_SCHED_FCFS_P_CODE ||
      config_dataptr->cpuSchedCode == CPU_SCHED_FCFS_N_CODE)
  {
    while (local_ptr)
    {
      if (local_ptr->state == READY_STATE)
      {
        return local_ptr->pid;
      }
      if (local_ptr->state == BLOCKED_STATE || !local_ptr->state)
      {
        ++newBlockedCount;
      }
      local_ptr = local_ptr->next_ptr;
    }
  }
  else if (config_dataptr->cpuSchedCode == CPU_SCHED_RR_P_CODE)
  {
    local_ptr = PCBnode_pid(local_ptr, PCBid);
    if (local_ptr->state != BLOCKED_STATE && local_ptr->state != EXIT_STATE &&
        !local_ptr->quant_time)
    {
      local_ptr->quant_time = true;
      return local_ptr->pid;
    }
    local_ptr->quant_time = true;

    if (local_ptr->next_ptr)
      local_ptr = local_ptr->next_ptr;

    else
      local_ptr = local_ptr;

    PCBid = local_ptr->pid;

    while (loopCount < 2)
    {
      local_ptr = PCBnode_pid(local_ptr, PCBid);

      if (local_ptr->state == READY_STATE)
      {
        return local_ptr->pid;
      }
      if (local_ptr->state == BLOCKED_STATE || !local_ptr->state)
        ++newBlockedCount;

      if (local_ptr->next_ptr)
      {
        local_ptr = local_ptr->next_ptr;
      }
      else
      {
        ++loopCount;
      }
      PCBid = local_ptr->pid;
    }
  }
  else
  {
    while (local_ptr && local_ptr->state != READY_STATE)
    {
      if (!local_ptr->state || local_ptr->state == BLOCKED_STATE)
      {
        ++newBlockedCount;
      }

      local_ptr = local_ptr->next_ptr;
    }

    if (local_ptr)
    {
      minId = local_ptr->pid;
      minTime = local_ptr->time_left;
      local_ptr = local_ptr->next_ptr;
    }

    while (local_ptr)
    {
      if (local_ptr->state == READY_STATE && local_ptr->time_left < minTime)
      {
        minId = local_ptr->pid;
        minTime = local_ptr->time_left;
      }
      else if (local_ptr->state == BLOCKED_STATE || !local_ptr->state)
      {
        ++newBlockedCount;
      }
      local_ptr = local_ptr->next_ptr;
    }
  }

  if (minId < 0)
  {
    if (newBlockedCount < 1)
    {
      minId = EXIT;
    }
    else
    {
      minId = WAIT;
    }
  }

  return minId;
}

void PCBstate(ConfigDataType *config_dataptr, PCBdata *local_ptr)
{
  char timeString[MAX_STR_LEN];
  char reportString[MAX_STR_LEN];
  double sim_time = 0.0;
  PCBdata *PCB_ptr;

  for (PCB_ptr = local_ptr; PCB_ptr != NULL; PCB_ptr = PCB_ptr->next_ptr)
  {
    if (PCB_ptr->state == NEW_STATE)
    {
      sim_time = accessTimer(LAP_TIMER, timeString);
      if (PCB_ptr->time_start <= sim_time)
      {
        PCB_ptr->state = READY_STATE;
        sprintf(reportString,
                "OS: Process %d set to READY state from NEW state",
                PCB_ptr->pid);
        LOGdump(ADD_LOG, config_dataptr, reportString);
      }
    }
  }
}

void PCBdisplay(PCBdata *head_ptr)
{
  PCBdata *wkg_ptr;

  if (head_ptr)
  {
    while (wkg_ptr)
    {
      printf("PCB pid: %d, state: %d, time remaining: %d,\n", wkg_ptr->pid,
             wkg_ptr->state, wkg_ptr->time_left);

      printf("\tcurrent command: %s, ", wkg_ptr->OClist->command);

      printf("\tcurrent op code: %s, \n", wkg_ptr->OClist->strArg1);

      printf("\tfirst int arg: %d, second int arg: %d\n\n",
             wkg_ptr->OClist->intArg2, wkg_ptr->OClist->intArg3);

      wkg_ptr = wkg_ptr->next_ptr;
    }
  }
  else
  {
    printf("\n[-] INVALID PCB LIST\n");
  }
}

void PROCthread(ConfigDataType *CNF_ptr, OpCodeType *OPC_ptr, PCBdata *PCB_ptr)
{
  char reportString[MAX_STR_LEN];
  PCBdata *PCB_wkg_ptr;
  int oneCycle, cyclesToRun, quantumCount;
  _Bool isPreemptive, cont;
  _Bool interrupt = false;

  oneCycle = CNF_ptr->procCycleRate;
  quantumCount = CNF_ptr->quantumCycles;
  cyclesToRun = OPC_ptr->intArg2;
  cont = true;
  isPreemptive = (OPC_ptr->intArg3 == PREEMPTIVE_CODE);
  PCB_wkg_ptr = PCBnode_pid(PCB_ptr, OPC_ptr->pid);

  while (cont)
  {
    runTimer(oneCycle);
    PCB_wkg_ptr->time_left -= oneCycle;
    cyclesToRun--;
    quantumCount--;
    interrupt = interruptMNGR(INTERRUPT_CHECK, OPC_ptr, PCB_ptr, CNF_ptr);
    if (!cyclesToRun || isPreemptive)
    {
      cont = false;
    }
  }

  if (cyclesToRun > 0 && isPreemptive && !interrupt)
  {
    PCB_wkg_ptr->quant_time = true;
    sprintf(reportString,
            "OS: Process %d quantum time out, cpu process operation end",
            OPC_ptr->pid);
    LOGdump(ADD_LOG, CNF_ptr, reportString);
  }
  else
  {
    sprintf(reportString, "Process: %d, %s %s operation end", OPC_ptr->pid,
            OPC_ptr->command, OPC_ptr->strArg1);
    LOGdump(ADD_LOG, CNF_ptr, reportString);
  }

  OPC_ptr->intArg2 = cyclesToRun;
}

void *PROCthread_wrapper(void *arg)
{
  void **args = (void **)arg;
  ConfigDataType *config_dataptr = (ConfigDataType *)args[0];
  OpCodeType *OPC_ptr = (OpCodeType *)args[1];
  PCBdata *PCB_ptr = (PCBdata *)args[2];

  PROCthread(config_dataptr, OPC_ptr, PCB_ptr);

  pthread_exit(NULL);
}

void IOthread(ConfigDataType *config_dataptr, OpCodeType *OPC_ptr,
              PCBdata *PCB_ptr)
{
  char reportString[MAX_STR_LEN];
  PCBdata *local_ptr;

  if (OPC_ptr->intArg3 == NON_PREEMPTIVE_CODE)
  {
    runTimer(OPC_ptr->intArg2);
    sprintf(reportString, "Process: %d, %s %sput operation end", OPC_ptr->pid,
            OPC_ptr->strArg1, OPC_ptr->inOutArg);
    LOGdump(ADD_LOG, config_dataptr, reportString);
  }
  else
  {
    sprintf(reportString, "OS: Process %d blocked for %sput operation",
            OPC_ptr->pid, OPC_ptr->inOutArg);
    LOGdump(ADD_LOG, config_dataptr, reportString);

    local_ptr = PCBnode_pid(PCB_ptr, OPC_ptr->pid);
    local_ptr->state = BLOCKED_STATE;

    sprintf(reportString, "OS: Process %d set from RUNNING to BLOCKED",
            OPC_ptr->pid);
    LOGdump(ADD_LOG, config_dataptr, reportString);
    interruptMNGR(SET_IO_START, OPC_ptr, PCB_ptr, config_dataptr);
  }
}

void *IOthread_wrapper(void *arg)
{
  void **args = (void **)arg;
  ConfigDataType *config_dataptr = (ConfigDataType *)args[0];
  OpCodeType *OPC_ptr = (OpCodeType *)args[1];
  PCBdata *PCB_ptr = (PCBdata *)args[2];

  IOthread(config_dataptr, OPC_ptr, PCB_ptr);

  pthread_exit(NULL);
}

void OPCcopy(OpCodeType *destination, OpCodeType *source)
{
  destination->pid = source->pid;
  copyString(destination->command, source->command);
  copyString(destination->inOutArg, source->inOutArg);
  copyString(destination->strArg1, source->strArg1);
  destination->intArg2 = source->intArg2;
  destination->intArg3 = source->intArg3;
  destination->opEndTime = source->opEndTime;
  destination->next_ptr = source->next_ptr;
  return;
}

OpCodeType *addInterrupt(OpCodeType *local_ptr, OpCodeType *new_ptr)
{
  OpCodeType *addedNode;

  if (local_ptr)
  {
    local_ptr->next_ptr = addInterrupt(local_ptr->next_ptr, new_ptr);
    return local_ptr;
  }
  else
  {
    addedNode = (OpCodeType *)malloc(sizeof(OpCodeType));
    OPCcopy(addedNode, new_ptr);
    addedNode->next_ptr = NULL;
    return addedNode;
  }
}

OpCodeType *removeOpCodeNode(OpCodeType *headPtr, OpCodeType *removedPtr)
{
  OpCodeType *wkgPtr;

  wkgPtr = headPtr;
  if (removedPtr == headPtr)
  {
    headPtr = headPtr->next_ptr;
  }
  else
  {
    for (; wkgPtr->next_ptr != removedPtr; wkgPtr = wkgPtr->next_ptr)
    {
    }
    wkgPtr->next_ptr = wkgPtr->next_ptr->next_ptr;
    free(removedPtr);
  }
  return headPtr;
}

_Bool interruptMNGR(Interrupts CTRL_ptr, OpCodeType *OPC_ptr, PCBdata *PCB_ptr,
                    ConfigDataType *config_dataptr)
{
  char reportString[MAX_STR_LEN]; // Initialize array to zero
  double currentTime = 0.0;
  PCBdata *local_ptr = NULL; // Initialize pointer to NULL
  bool returnVal = false;
  OpCodeType *delOPC = NULL;
  OpCodeType *wkgOPC_ptr = NULL;

  delOPC = NULL; // Use NULL instead of 0LL
  returnVal = false;

  if (CTRL_ptr)
  {
    switch (CTRL_ptr)
    {
    case INIT_MNGR:
      wkgOPC_ptr = NULL;
      returnVal = true;

    case INTERRUPT_CHECK:
      wkgOPC_ptr = OPC_ptr; // Initialize wkgOPC_ptr
      while (wkgOPC_ptr)
      {
        local_ptr = PCBnode_pid(PCB_ptr, wkgOPC_ptr->pid);
        currentTime = accessTimer(1, reportString);
        if (currentTime > wkgOPC_ptr->opEndTime)
        {
          if (local_ptr->state != 4)
            returnVal = true; // Use boolean value instead of true
          delOPC = wkgOPC_ptr;
        }
        if (delOPC)
        {
          wkgOPC_ptr = removeOpCodeNode(wkgOPC_ptr, delOPC);
          delOPC = NULL; // Use NULL instead of 0LL
        }
        else
        {
          wkgOPC_ptr = wkgOPC_ptr->next_ptr;
        }
      }
      break;

    case SET_IO_START:
      currentTime = accessTimer(1, reportString);
      OPC_ptr->opEndTime = (double)OPC_ptr->intArg2 / 1000.0 + currentTime;
      wkgOPC_ptr = addInterrupt(wkgOPC_ptr, OPC_ptr);
      break;

    case RESOLVE_INTERRUPTS:
      wkgOPC_ptr = OPC_ptr; // Initialize wkgOPC_ptr
      while (wkgOPC_ptr)
      {
        local_ptr = PCBnode_pid(PCB_ptr, wkgOPC_ptr->pid);
        currentTime = accessTimer(1, reportString);
        if (currentTime > wkgOPC_ptr->opEndTime)
        {
          if (local_ptr->state != 4)
          {
            sprintf(reportString,
                    "OS: Interrupted by process %d, %s %sput operation",
                    wkgOPC_ptr->pid, wkgOPC_ptr->strArg1, wkgOPC_ptr->inOutArg);
            LOGdump(ADD_LOG, config_dataptr,
                    reportString); // Use integer 0 instead of 0LL
            local_ptr->state = 1;
            sprintf(reportString, "OS: Process %d set from BLOCKED to READY",
                    wkgOPC_ptr->pid);
            LOGdump(ADD_LOG, config_dataptr,
                    reportString); // Use integer 0 instead of 0LL
          }
          delOPC = wkgOPC_ptr;
        }
        if (delOPC)
        {
          wkgOPC_ptr = removeOpCodeNode(wkgOPC_ptr, delOPC);
          delOPC = NULL; // Use NULL instead of 0LL
        }
        else
        {
          wkgOPC_ptr = wkgOPC_ptr->next_ptr;
        }
      }
      returnVal = true;
      break;
    }
  }

  else
  {
    wkgOPC_ptr = NULL; // Use NULL instead
    return true;
  }

  return returnVal;
}

// mem node add
MEMnode *MEMnode_add(int physStart, int physEnd, int memState, int procNum,
                     int logStart, int logStop)
{
  MEMnode *result = (MEMnode *)malloc(sizeof(MEMnode));
  result->physicalStart = physStart;
  result->physicalStop = physEnd;
  result->memBlockState = memState;
  result->processNumber = procNum;
  result->logicalStart = logStart;
  result->logicalStop = logStop;
  result->next_ptr = NULL;
  return result;
}

void MEMnode_recycle(MEMnode **tempNode, int memState, int procNum,
                     int phyStart, int phyStop, int logStart, int logStop)
{
  (*tempNode)->memBlockState = memState;
  (*tempNode)->processNumber = procNum;
  (*tempNode)->physicalStart = phyStart;
  (*tempNode)->physicalStop = phyStop;
  (*tempNode)->logicalStart = logStart;
  (*tempNode)->logicalStop = logStop;
}

void MEMrepair(MEMnode **MEM_ptr)
{
  MEMnode *removePtr; // [rsp+10h] [rbp-10h]

  while (MEM_ptr)
  {
    if ((*MEM_ptr)->memBlockState == 1 && (*MEM_ptr)->next_ptr &&
        (*MEM_ptr)->next_ptr->memBlockState == 1)
    {
      MEMnode_recycle(MEM_ptr, 1, -1, (*MEM_ptr)->physicalStart,
                      (*MEM_ptr)->next_ptr->physicalStop, 0, 0);
      removePtr = (*MEM_ptr)->next_ptr;
      (*MEM_ptr)->next_ptr = removePtr->next_ptr;
      free(removePtr);
    }
    else
    {
      (*MEM_ptr) = (*MEM_ptr)->next_ptr;
    }
  }
}

// mem display
void MEMdisplay(MEMnode *MEM_ptr, char *output_str, _Bool output_flag)
{
  // TODO: LOOK THRU ALL MIN/MAX STR LENS.. POSSIBLY ADJUST?
  char output_string[MAX_STR_LEN];
  MEMnode *wkgMemPtr;

  if (output_flag != false)
  {
    puts("\n--------------------------------------------------");
    puts(output_str);
    wkgMemPtr = MEM_ptr;
    if (MEM_ptr == NULL)
    {
      puts("No memory configured");
    }
    for (; wkgMemPtr != NULL; wkgMemPtr = wkgMemPtr->next_ptr)
    {
      if (wkgMemPtr->memBlockState == 1)
      {
        copyString(output_string, "Open");
      }
      else
      {
        copyString(output_string, "Used");
      }
      if (wkgMemPtr->processNumber == -1)
      {
        printf("%d [ %s, P#: x, ", wkgMemPtr->physicalStart, output_string);
      }
      else
      {
        printf("%d [ %s, P#: %d, ", wkgMemPtr->physicalStart, output_string,
               wkgMemPtr->processNumber);
      }
      printf("%d-%d ] %d\n", wkgMemPtr->logicalStart, wkgMemPtr->logicalStop,
             wkgMemPtr->physicalStop);
    }
    puts("--------------------------------------------------");
  }
}

_Bool MMU(MEMnode **MEM_head, ConfigDataType *config_dataptr,
          OpCodeType *OPC_ptr)
{
  char displayStr[MAX_STR_LEN];
  MEMnode *tempNodePtr;
  MEMnode *head_ptr = (*MEM_head);
  int highMemLoc;
  int lowMemLoc;
  int processId;
  int logicalHigh;
  int requestedMemory;
  _Bool displayFlag = config_dataptr->memDisplay;
  int highestMemLoc = config_dataptr->memAvailable - 1;
  int lowestMemLoc = 0;
  MEMnode *wkgMemPtr;
  MEMnode *trlgPtr;
  int logicalOffset;
  int logicalLow;

  if (head_ptr == NULL)
  {
    // FIXME: remember to free this pointer
    head_ptr = MEMnode_add(lowestMemLoc, highestMemLoc, MEM_OPEN, NULL_PID,
                           MEM_INIT, MEM_INIT);
    copyString(displayStr, "After memory initialization");
    MEMdisplay(head_ptr, displayStr, displayFlag);
    // return true;
    displayFlag = true;
  }

  else
  {
    printf("<---CHECK MEMORY--->");
    if (compareString(OPC_ptr->strArg1, "clearAll") ||
        compareString(OPC_ptr->strArg1, "clearOne"))
    {
      logicalLow = 1;
      logicalOffset = 1;
    }
    else
    {
      logicalLow = OPC_ptr->intArg2;
      logicalOffset = OPC_ptr->intArg3;
    }

    requestedMemory = logicalOffset;
    logicalHigh = logicalOffset + logicalLow - 1;
    processId = OPC_ptr->pid;

    if ((!compareString(OPC_ptr->strArg1, "allocate") ||
         !compareString(OPC_ptr->strArg1, "access")) &&
        (logicalLow < 0 || logicalOffset < 1 ||
         config_dataptr->memAvailable <= logicalLow ||
         config_dataptr->memAvailable <= logicalHigh))
    {
      copyString(displayStr, "After limits out of range");
      MEMdisplay(head_ptr, displayStr, displayFlag);
      displayFlag = false;
    }
    else
    {
      if (compareString(OPC_ptr->strArg1, "allocate"))
      {
        // if (!compareString(OPC_ptr->strArg1, "access"))
        //{
        for (wkgMemPtr = head_ptr; wkgMemPtr != NULL;
             wkgMemPtr = wkgMemPtr->next_ptr)
        {
          if (wkgMemPtr->processNumber == processId &&
              wkgMemPtr->logicalStart <= logicalLow &&
              wkgMemPtr->logicalStop >= logicalLow &&
              wkgMemPtr->logicalStart <= logicalHigh &&
              wkgMemPtr->logicalStop >= logicalHigh)
          {
            // copyString(displayStr, "After access success");
            copyString(displayStr, "After allocate overlap failure");
            MEMdisplay(head_ptr, displayStr, displayFlag);
            // displayFlag = true;
            return false;
          }
        }
      }
    }
  }
  return displayFlag;
}
/*
copyString(displayStr, "After access failure");
MEMdisplay(head_ptr, displayStr, displayFlag);
displayFlag = false;
return false;
}
if (compareString(OPC_ptr->strArg1, "clearOne"))
{
wkgMemPtr = head_ptr;
while (wkgMemPtr)
{
  head_ptr = wkgMemPtr;
  wkgMemPtr = wkgMemPtr->next_ptr;
  free(head_ptr);
}
head_ptr = NULL;
copyString(displayStr, "After clear all process success");
MEMdisplay(head_ptr, displayStr, displayFlag);
return true;
}
else
{
for (wkgMemPtr = head_ptr; wkgMemPtr; wkgMemPtr = wkgMemPtr->next_ptr)
{
  if (wkgMemPtr->processNumber == processId)
    MEMnode_recycle(wkgMemPtr, 1, -1, wkgMemPtr->physicalStart,
                    wkgMemPtr->physicalStop, 0, 0);
}
MEMrepair(head_ptr);
sprintf(displayStr, "After clear process %d success", processId);
MEMdisplay(head_ptr, displayStr, displayFlag);
return true;
}
}
else
{
for (wkgMemPtr = head_ptr; wkgMemPtr != NULL;
   wkgMemPtr = wkgMemPtr->next_ptr)
{
if (wkgMemPtr->processNumber == processId &&
    ((wkgMemPtr->logicalStart <= logicalLow &&
      wkgMemPtr->logicalStop >= logicalLow) ||
     (wkgMemPtr->logicalStart <= logicalHigh &&
      wkgMemPtr->logicalStop >= logicalHigh)))
{
  copyString(displayStr, "After allocate overlap failure");
  MEMdisplay(head_ptr, displayStr, displayFlag);
  return false;
}
}
wkgMemPtr = head_ptr;
trlgPtr = head_ptr;
while (wkgMemPtr &&
     (wkgMemPtr->memBlockState == 2 ||
      wkgMemPtr->physicalStop - wkgMemPtr->physicalStart + 1 <
          requestedMemory))
{
trlgPtr = wkgMemPtr;
wkgMemPtr = wkgMemPtr->next_ptr;
}
}
if (wkgMemPtr != NULL)
{
if (wkgMemPtr->physicalStop - wkgMemPtr->physicalStart + 1 ==
  requestedMemory)
{
MEMnode_recycle(wkgMemPtr, MEM_USED, processId,
                wkgMemPtr->physicalStart, wkgMemPtr->physicalStop,
                logicalLow, logicalHigh);

copyString(displayStr, "After allocate failure");
MEMdisplay(head_ptr, displayStr, displayFlag);
return false;
}
}

lowMemLoc = wkgMemPtr->physicalStart;
highMemLoc = lowMemLoc + requestedMemory - 1;
tempNodePtr = MEMnode_add(lowMemLoc, highMemLoc, MEM_USED, processId,
                      logicalLow, logicalHigh);
if (wkgMemPtr == head_ptr)
{
head_ptr = tempNodePtr;
}
else
{
trlgPtr->next_ptr = tempNodePtr;
}
wkgMemPtr->physicalStart = highMemLoc + 1;
tempNodePtr->next_ptr = wkgMemPtr;
copyString(displayStr, "After allocate success");
MEMdisplay(head_ptr, displayStr, displayFlag);
}

// printf("MEMORY??");
return displayFlag;
}*/

void CPUidle(ConfigDataType *config_dataptr, PCBdata *PCB_ptr)
{
  char reportString[MAX_STR_LEN];
  OpCodeType *temp_ptr = NULL;
  int oneCycle = config_dataptr->procCycleRate;
  _Bool interruptFound = false;

  copyString(reportString, "OS: CPU idle, all active processes blocked");
  LOGdump(ADD_LOG, config_dataptr, reportString);
  while (!interruptFound)
  {
    runTimer(oneCycle);
    interruptFound =
        interruptMNGR(INTERRUPT_CHECK, temp_ptr, PCB_ptr, config_dataptr);
  }
  copyString(reportString, "OS: CPU interrupt, end idle");
  LOGdump(ADD_LOG, config_dataptr, reportString);
}

void runSim(ConfigDataType *config_dataptr, OpCodeType *meta_data_ptr)
{
  char reportString[MAX_STR_LEN];
  char timeString[MAX_STR_LEN];
  PCBdata *PCB_ptr;
  PCBdata *PCB_wkg;
  PCBdata *ID_ptr;
  OpCodeType *OPC_ptr = NULL;
  MEMnode *MEM_head = NULL;

  int currentPID = NULL_PID;
  bool isPreemptive;
  int lastPid = NULL_PID;
  _Bool runFlag = true;
  // IO thread arguments
  void *IO_args[1];
  // IO thread
  pthread_t IO;
  // IO pthread functions return code for create and join
  int io_init = 0;

  printf("Simulator Run");
  printf("\n-------------\n");
  accessTimer(ZERO_TIMER, timeString);

  LOGdump(INIT_LOG, config_dataptr, "OS: Simulator start");
  PCB_ptr = PCBcreate(config_dataptr, meta_data_ptr);

  isPreemptive = meta_data_ptr->next_ptr->intArg3 == PREEMPTIVE_CODE;
  // process interrupt requests
  interruptMNGR(INIT_MNGR, OPC_ptr, PCB_ptr, config_dataptr);
  // change state of PCB
  PCBstate(config_dataptr, PCB_ptr);

  // call Memory Mgmt Unit for processing requests
  MMU(&MEM_head, config_dataptr, meta_data_ptr);

  // enter this loop while runFlag is = to true, this is set to true since
  // we entered this function the needed flag was already called (-rs)
  do
  {
    currentPID = PCBparse(config_dataptr, PCB_ptr);

    if (currentPID == EXIT)
    {
      LOGdump(ADD_LOG, config_dataptr, "OS: System stop");
      runFlag = false;
    }

    else if (currentPID == WAIT)
    {
      CPUidle(config_dataptr, PCB_ptr);
    }

    else
    {
      PCBstate(config_dataptr, PCB_ptr);

      ID_ptr = PCBnode_pid(PCB_ptr, currentPID);

      // get the next opcode
      if (ID_ptr->OCcurr != NULL)
      {
        if (ID_ptr->OCcurr->intArg2 == 0)
        {
          OPC_ptr = ID_ptr->OCcurr->next_ptr;
        }

        else
        {
          OPC_ptr = ID_ptr->OCcurr;
        }
      }

      else
      {
        OPC_ptr = ID_ptr->OClist;
      }

      ID_ptr->OCcurr = OPC_ptr;

      if ((compareString(OPC_ptr->command, "app") ||
           compareString(OPC_ptr->strArg1, "start")) &&
          isPreemptive && currentPID != lastPid)
      {
        PCB_wkg = PCBnode_pid(PCB_ptr, currentPID);

        sprintf(reportString, "OS: Process %d selected with %d ms remaining",
                currentPID, PCB_wkg->time_left);

        LOGdump(ADD_LOG, config_dataptr, reportString);

        sprintf(reportString, "OS: Process %d set from READY to RUNNING\n",
                currentPID);

        LOGdump(ADD_LOG, config_dataptr, reportString);
      }

      if (compareString(OPC_ptr->command, "app") ||
          compareString(OPC_ptr->strArg1, "start"))
      {
        if (compareString(OPC_ptr->command, "app") ||
            compareString(OPC_ptr->strArg1, "end"))
        {
          if (compareString(OPC_ptr->command, "mem"))
          {
            if (compareString(OPC_ptr->command, "dev"))
            {
              if (!compareString(OPC_ptr->command, "cpu"))
              {
                sprintf(reportString, "Process: %d, %s %s operation start",
                        OPC_ptr->pid, OPC_ptr->command, OPC_ptr->strArg1);

                LOGdump(ADD_LOG, config_dataptr, reportString);

                PROCthread(config_dataptr, OPC_ptr, PCB_ptr);
              }
            }

            else
            {
              sprintf(reportString, "Process: %d, %s %sput operation start",
                      OPC_ptr->pid, OPC_ptr->strArg1, OPC_ptr->inOutArg);

              LOGdump(ADD_LOG, config_dataptr, reportString);
              OPC_ptr->intArg2 *= config_dataptr->ioCycleRate;

              IO_args[0] = (void *)config_dataptr;
              IO_args[1] = (void *)OPC_ptr;
              IO_args[2] = (void *)PCB_ptr;

              io_init = pthread_create(&IO, NULL, IOthread_wrapper, IO_args);

              if (io_init != 0)
              {
                fprintf(stderr, "Error: Failed to create IO thread\n");
              }
              io_init = pthread_join(IO, NULL);

              if (io_init != 0)
              {
                fprintf(stderr, "Error: Failed to join IO thread\n");
              }

              PCB_wkg = PCBnode_pid(PCB_ptr, currentPID);
              PCB_wkg->time_left -= OPC_ptr->intArg2;
              OPC_ptr->intArg2 = 0;
            }
          }
          else
          {
            sprintf(reportString, "Process: %d, mem %s request (%d, %d)",
                    OPC_ptr->pid, OPC_ptr->strArg1, OPC_ptr->intArg2,
                    OPC_ptr->intArg3);

            LOGdump(ADD_LOG, config_dataptr, reportString);

            if (MMU(&MEM_head, config_dataptr, OPC_ptr))
            {
              sprintf(reportString, "Process: %d, successful mem %s request",
                      OPC_ptr->pid, OPC_ptr->strArg1);

              LOGdump(ADD_LOG, config_dataptr, reportString);

              OPC_ptr->intArg2 = 0;
            }
            else
            {
              sprintf(reportString, "Process: %d, failed mem %s request",
                      OPC_ptr->pid, OPC_ptr->strArg1);

              LOGdump(ADD_LOG, config_dataptr, reportString);

              sprintf(reportString, "OS: Segmentation fault, Process % d ended",
                      OPC_ptr->pid);

              LOGdump(ADD_LOG, config_dataptr, reportString);

              copyString(OPC_ptr->strArg1, "clearOne");

              MMU(&MEM_head, config_dataptr, OPC_ptr);

              PCB_wkg->state = EXIT_STATE;

              sprintf(reportString, "OS: Process %d set to EXIT", currentPID);

              LOGdump(ADD_LOG, config_dataptr, reportString);
            }
          }
        }
        else
        {
          sprintf(reportString, "OS: Process %d ended\n", currentPID);

          LOGdump(ADD_LOG, config_dataptr, reportString);

          OPC_ptr->pid = currentPID;

          copyString(reportString, "clearOne");

          copyString(OPC_ptr->strArg1, reportString);

          MMU(&MEM_head, config_dataptr, OPC_ptr);

          PCB_wkg = PCBnode_pid(PCB_ptr, currentPID);

          PCB_wkg->state = EXIT_STATE;

          sprintf(reportString, "OS: Process %d set to EXIT", currentPID);

          LOGdump(ADD_LOG, config_dataptr, reportString);
        }
      }
      else
      {
        PCB_wkg = PCBnode_pid(PCB_ptr, currentPID);

        sprintf(reportString, "OS: Process %d selected with %d ms remaining",
                currentPID, PCB_wkg->time_left);

        LOGdump(ADD_LOG, config_dataptr, reportString);

        sprintf(reportString, "OS: Process %d set from READY to RUNNING\n",
                currentPID);

        LOGdump(ADD_LOG, config_dataptr, reportString);

        OPC_ptr->intArg2 = 0;
      }
    }
    // interruptMNGR(RESOLVE_INTERRUPTS, OPC_ptr, PCB_ptr, config_dataptr);
    lastPid = currentPID;
  }

  while (runFlag); // dirty trick for a do while loop

  PCB_ptr = PCBnode_del(PCB_ptr);

  copyString(OPC_ptr->strArg1, "clearAll");

  MMU(&MEM_head, config_dataptr, OPC_ptr);

  LOGdump(ADD_LOG, config_dataptr, "OS: Simulation end");

  LOGdump(DUMP_LOG, config_dataptr, reportString);

  accessTimer(STOP_TIMER, reportString);
}
