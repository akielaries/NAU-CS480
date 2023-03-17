/**
 * Driver code for running the simulator
 */
#include "simulator.h"

/* LOG node */
LOGnode LOGnode_add(LOGnode local_ptr, char *txt_input)
{
  if (local_ptr.next_ptr == NULL)
  {
    LOGnode new_ptr = {0};
    copyString(new_ptr.LOG_out, txt_input);
    local_ptr.next_ptr = &new_ptr;
  }
  else
  {
    LOGnode_add(*(local_ptr.next_ptr), txt_input);
  }
  return local_ptr;
}

LOGnode LOGnode_del(LOGnode *local_ptr)
{
  if (local_ptr != NULL)
  {
    LOGnode_del(local_ptr->next_ptr);
  }

  free(local_ptr);
  // 0LL? long long expected?
}

void LOGdump(int trigger, ConfigDataType *config_dataptr, char *txt_input)
{
  char outputString[MAX_STR_LEN];
  char timeString[MIN_STR_LEN];
  char WRITE_FLAG[2];
  FILE *outFilePtr;
  int status_cmp = 0;
  ConfigDataType *config;
  LOGnode local_ptr;
  LOGnode *wkg_ptr;

  copyString(WRITE_FLAG, "w");
  getSubString(outputString, txt_input, 0, 2);

  _Bool OS_STATUS = true;

  if (OS_STATUS != false)
  {
    status_cmp = compareString(outputString, "OS:");
    if (status_cmp != 0)
    {
      copyString(outputString, "\n ");
      OS_STATUS = false;
    }
  }
  else
  {
    status_cmp = compareString(outputString, "OS:");
    if (status_cmp == 0)
    {
      copyString(outputString, "\n ");
      OS_STATUS = true;
    }
  }

  /*
    if (OS_Toggle_3467 && compareString(outputString, "OS:"))
    {
        copyString(outputString, "\n ");
        OS_Toggle_3467 = 0;
    }
    else if (OS_Toggle_3467 || compareString(outputString, "OS:"))
    {
        copyString(outputString, " ");
    }
    else
    {
        copyString(outputString, "\n ");
        OS_Toggle_3467 = 1;
    }*/

  if (trigger)
  {
    accessTimer(LAP_TIMER, timeString);
  }
  else
  {
    local_ptr = (LOGnode){0};
    // TODO: CHECK IF MALLOC IS CORRECT
    config = (ConfigDataType *)malloc(sizeof(ConfigDataType));
    // replace with actual function code?
    // copyConfigData(config, config_dataptr);
    config->version = config_dataptr->version;
    copyString(config->metaDataFileName, config_dataptr->metaDataFileName);
    config->cpuSchedCode = config_dataptr->cpuSchedCode;
    config->quantumCycles = config_dataptr->quantumCycles;
    config->memDisplay = config_dataptr->memDisplay;
    config->memAvailable = config_dataptr->memAvailable;
    config->procCycleRate = config_dataptr->procCycleRate;
    config->ioCycleRate = config_dataptr->ioCycleRate;
    config->logToCode = config_dataptr->logToCode;
    copyString(config->logToFileName, config_dataptr->logToFileName);

    accessTimer(LAP_TIMER, timeString);
    trigger = 1;

    if (config->logToCode == LOGTO_FILE_CODE)
    {
      printf("Simulator running with output to file\n");
    }
  }
  if (trigger == 1)
  {
    printf("OUTPUT: %s", outputString);
    concatenateString(outputString, timeString);
    concatenateString(outputString, ", ");
    concatenateString(outputString, txt_input);
    if (config->logToCode == LOGTO_BOTH_CODE ||
        config->logToCode == LOGTO_FILE_CODE)
    {
      local_ptr = LOGnode_add(local_ptr, outputString);
    }
    if (config->logToCode == 7 || config->logToCode == 5)
    {
      printf(outputString);
    }
  }
  else
  {
    wkg_ptr = local_ptr;
    outFilePtr = fopen(config->logToFileName, WRITE_FLAG);
    fwrite("\n==================================================\n", 1uLL,
           0x34uLL, outFilePtr);

    fwrite("Simulator Log File Header\n\n", 1uLL, 0x1BuLL, outFilePtr);

    fprintf(outFilePtr, "File Name                       : %s\n",
            config->metaDataFileName);

    // configCodeToString(config->cpuSchedCode, outputString);

    fprintf(outFilePtr, "CPU Scheduling                  : %s\n", outputString);

    fprintf(outFilePtr, "Quantum Cycles                  : %d\n",
            (unsigned int)config->quantumCycles);

    fprintf(outFilePtr, "Memory Available (KB)           : %d\n",
            (unsigned int)config->memAvailable);

    fprintf(outFilePtr, "Processor Cycle Rate (ms/cycle) : %d\n",
            (unsigned int)config->procCycleRate);

    fprintf(outFilePtr, "I/O Cycle Rate (ms/cycle)       : %d\n\n",
            (unsigned int)config->ioCycleRate);

    fwrite("================\n", 1uLL, 0x11uLL, outFilePtr);

    fwrite("Begin Simulation\n\n", 1uLL, 0x12uLL, outFilePtr);
    while (wkg_ptr)
    {
      fprintf(outFilePtr, "%s\n", wkg_ptr->LOG_out);
      wkg_ptr = wkg_ptr->next_ptr;
    }
    fwrite("\nEnd Simulation - Complete\n", 1, 0x1BuLL, outFilePtr);
    fwrite("=========================\n\n", 1, 0x1BuLL, outFilePtr);
    fclose(outFilePtr);
    local_ptr = LOGnode_del(local_ptr);
    free(config);
  }
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
  // OpCodeType *md_head_ptr;
  PCBdata *new_ptr;
  PCBdata *head_ptr = NULL;

  int pidSet = 0;
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
      new_ptr->state = 0;
      new_ptr->time_left = 0;
      new_ptr->time_start = (double)md_head_ptr->intArg2;
      new_ptr->quant_time = false; // TODO: FALSE?
      new_ptr->OCcurr = 0;
      new_ptr->OClist = md_head_ptr;
      // TODO: new_ptr->memList = 0;
      new_ptr->next_ptr = 0;
      while (compareString(md_head_ptr->command, "app") ||
             compareString(md_head_ptr->strArg1, "end"))
      {
        if (compareString(md_head_ptr->command, "mem"))
        {
          // time_left = new_ptr->time_left;
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

          if (config_dataptr->cpuSchedCode && config_dataptr->cpuSchedCode != 4)
          {
            md_head_ptr->intArg3 = 9;
          }
          else
          {
            md_head_ptr->intArg3 = 8;
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
}

int PCBparse(ConfigDataType *config_dataptr, PCBdata *local_ptr)
{
  int PCBid = 0;
  int minTime = 0;
  int minId = -1;
  int loopCount = 0;
  int newBlockedCount = 0;

  if (config_dataptr->cpuSchedCode == 2 || config_dataptr->cpuSchedCode == 4)
  {
    while (local_ptr)
    {
      if (local_ptr->state == 1)
      {
        return (unsigned int)local_ptr->pid;
      }
      if (local_ptr->state == 3 || !local_ptr->state)
      {
        ++newBlockedCount;
      }
      local_ptr = local_ptr->next_ptr;
    }
  }
  else if (config_dataptr->cpuSchedCode == 3)
  {
    local_ptr = PCBnode_pid(local_ptr, PCBid);
    if (local_ptr->state != 3 && local_ptr->state != 4 &&
        !local_ptr->quant_time)
    {
      local_ptr->quant_time = 0;
      return (unsigned int)local_ptr->pid;
    }
    local_ptr->quant_time = 0;

    if (local_ptr->next_ptr)
      local_ptr = local_ptr->next_ptr;

    else
      local_ptr = local_ptr;

    PCBid = local_ptr->pid;

    while (loopCount < 2)
    {
      local_ptr = PCBnode_pid(local_ptr, PCBid);

      if (local_ptr->state == 1)
      {
        return (unsigned int)local_ptr->pid;
      }
      if (local_ptr->state == 3 || !local_ptr->state)
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
    while (local_ptr && local_ptr->state != 1)
    {
      if (!local_ptr->state || local_ptr->state == 3)
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
      if (local_ptr->state == 1 && local_ptr->time_left < minTime)
      {
        minId = local_ptr->pid;
        minTime = local_ptr->time_left;
      }
      else if (local_ptr->state == 3 || !local_ptr->state)
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
      minId = -606;
    }
    else
    {
      minId = -505;
    }
  }

  return minId;
}

void PCBstate(ConfigDataType *config_dataptr, PCBdata *local_ptr)
{
  char timeString[MIN_STR_LEN];
  char reportString[MAX_STR_LEN];
  double sim_time = 0.0;
  PCBdata *PCB_ptr;

  for (PCB_ptr = local_ptr; PCB_ptr != NULL; PCB_ptr = PCB_ptr->next_ptr)
  {
    if (PCB_ptr->state == 0)
    {
      sim_time = accessTimer(LAP_TIMER, timeString);
      if (PCB_ptr->time_start <= sim_time)
      {
        PCB_ptr->state = 1;
        sprintf(reportString,
                "OS: Process %d set to READY state from NEW state",
                PCB_ptr->pid);
        LOGdump(1, config_dataptr, reportString);
      }
    }
  }

  /*
    while (local_ptr)
    {
      if (!local_ptr->state)
      {
        sim_time = accessTimer(LAP_TIMER, timeString);
        if (sim_time >= local_ptr->time_start)
        {
          local_ptr->state = 1;
          sprintf(reportString,
                  "OS: Process %d set to READY state from NEW state",
                  (unsigned int)local_ptr->pid);

          LOGdump(1, config_dataptr, reportString);
        }
      }
      local_ptr = local_ptr->next_ptr;
    }*/
}

void PCBdisplay(PCBdata *head_ptr)
{
  PCBdata *wkg_ptr;

  if (head_ptr)
  {
    while (wkg_ptr)
    {
      printf("PCB pid: %d, state: %d, time remaining: %d,\n",
             (unsigned int)wkg_ptr->pid, (unsigned int)wkg_ptr->state,
             (unsigned int)wkg_ptr->time_left);

      printf("\tcurrent command: %s, ", wkg_ptr->OClist->command);

      printf("\tcurrent op code: %s, \n", wkg_ptr->OClist->strArg1);

      printf("\tfirst int arg: %d, second int arg: %d\n\n",
             (unsigned int)wkg_ptr->OClist->intArg2,
             (unsigned int)wkg_ptr->OClist->intArg3);

      wkg_ptr = wkg_ptr->next_ptr;
    }
  }
  else
  {
    printf("\n[-] INVALID PCB LIST\n");
  }
}

/* TODO: this probably IS NOT NEEDED
void *IOthread(void *time_elapsed)
{
    int cycles = (int *)time_elapsed;
    runTimer(*cycles);
    return ((void *) 0);
}
*/

void runSim(ConfigDataType *config_dataptr, OpCodeType *meta_data_ptr)
{
  char timeString[MIN_STR_LEN];
  char reportString[MAX_STR_LEN];
  double sim_time = 0.0;
  PCBdata *PCB_ptr;
  PCBdata *PCB_wkg;
  PCBdata *ID_ptr;
  OpCodeType *OPC_ptr;
  int currentPid;
  bool isPreemptive;
  int lastPid;
  bool runFlag;

  OPC_ptr = 0LL;
  runFlag = 1;
  currentPid = -1;
  lastPid = -1;

  printf("Simulator Run");
  printf("\n-------------\n");

  // TODO: this could be replaced with the actual PCB create
  PCB_ptr = PCBcreate(config_dataptr, meta_data_ptr);
  isPreemptive = meta_data_ptr->next_ptr->intArg3 == 9;
  // TODO: test commenting this out as well
  // SIM04 will have some sort of interrupt manager/controller function used
  // here
  // processIntRequest(INITIALIZE_INTERRUPT_MGR, 0LL, PCB_ptr);
  PCBstate(config_dataptr, PCB_ptr);

  // get next process

  // TODO: test commenting these out
  // processMemRequest(config_dataptr, metaDataMstrPtr);
  LOGdump(0, config_dataptr, "OS: Simulator start");
  do
  {
    currentPid = PCBparse(config_dataptr, PCB_ptr);
    if (currentPid == -606)
    {
      LOGdump(1, config_dataptr, "OS: System stop");
      runFlag = 0;
    }
    // else if (currentPid == -505)
    //{
    // TODO: replace this with the runCPUidle function
    // runCpuIdle(config_dataptr, PCB_ptr);
    //}
    else
    {
      PCBstate(config_dataptr, PCB_ptr);
      // TODO: this could be replaced by the getNextOpCode
      // function as well

      ID_ptr = PCBnode_pid(PCB_ptr, currentPid);

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

      // OPC_ptr = getNextOpCode(PCB_ptr, currentPid);

      if ((compareString(OPC_ptr->command, "app") ||
           compareString(OPC_ptr->strArg1, "start")) &&
          isPreemptive && currentPid != lastPid)
      {
        PCB_wkg = PCBnode_pid(PCB_ptr, currentPid);
        sprintf(reportString, "OS: Process %d selected with %d ms remaining",
                (unsigned int)currentPid, (unsigned int)PCB_wkg->time_left);
        LOGdump(1, config_dataptr, reportString);
        sprintf(reportString, "OS: Process %d set from READY to RUNNING",
                (unsigned int)currentPid);
        LOGdump(1, config_dataptr, reportString);
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
                        (unsigned int)OPC_ptr->pid, OPC_ptr->command,
                        OPC_ptr->strArg1);
                LOGdump(1, config_dataptr, reportString);
                // TODO: replace this with the code
                // from processRunOp function
                // processRunOp(config_dataptr, OPC_ptr, PCB_ptr);
                // ********************* COMMENT BACK
              }
            }
            else
            {
              sprintf(reportString, "Process: %d, %s %sput operation start",
                      (unsigned int)OPC_ptr->pid, OPC_ptr->strArg1,
                      OPC_ptr->inOutArg);

              LOGdump(1, config_dataptr, reportString);
              OPC_ptr->intArg2 *= config_dataptr->ioCycleRate;

              // TODO: replace with a code from function?
              // FIXME: THIS IS WHERE pthread MAGIG SHOULD HAPPEN
              // processIoOp(OPC_ptr, PCB_ptr);
              // ********************** TODO COMMENT BACK
              PCB_wkg = PCBnode_pid(PCB_ptr, currentPid);
              PCB_wkg->time_left -= OPC_ptr->intArg2;
              OPC_ptr->intArg2 = 0;
            }
          }
          else
          {
            sprintf(reportString, "Process: %d, mem %s request (%d, %d)",
                    (unsigned int)OPC_ptr->pid, OPC_ptr->strArg1,
                    (unsigned int)OPC_ptr->intArg2,
                    (unsigned int)OPC_ptr->intArg3);
            LOGdump(1, config_dataptr, reportString);

            // if (processMemRequest(config_dataptr, OPC_ptr))
            //{
            sprintf(reportString, "Process: %d, successful mem %s request",
                    (unsigned int)OPC_ptr->pid, OPC_ptr->strArg1);

            LOGdump(1, config_dataptr, reportString);
            OPC_ptr->intArg2 = 0;
            //}
            // else
            //{
            sprintf(reportString, "Process: %d, failed mem %s request",
                    (unsigned int)OPC_ptr->pid, OPC_ptr->strArg1);

            LOGdump(1, config_dataptr, reportString);

            sprintf(reportString, "OS: Segmentation fault, Process % d ended",
                    (unsigned int)OPC_ptr->pid);

            LOGdump(1, config_dataptr, reportString);
            copyString(OPC_ptr->strArg1, "clearOne");
            // processMemRequest(config_dataptr, OPC_ptr);
            PCB_wkg->state = 4;

            sprintf(reportString, "OS: Process %d set to EXIT",
                    (unsigned int)currentPid);

            LOGdump(1, config_dataptr, reportString);
            //}
          }
        }
        else
        {
          sprintf(reportString, "OS: Process %d ended",
                  (unsigned int)currentPid);
          LOGdump(1, config_dataptr, reportString);
          OPC_ptr->pid = currentPid;
          copyString(reportString, "clearOne");
          copyString(OPC_ptr->strArg1, reportString);
          // processMemRequest(config_dataptr, OPC_ptr);
          PCB_wkg = PCBnode_pid(PCB_ptr, currentPid);
          PCB_wkg->state = 4;
          sprintf(reportString, "OS: Process %d set to EXIT",
                  (unsigned int)currentPid);
          LOGdump(1, config_dataptr, reportString);
        }
      }
      else
      {
        PCB_wkg = PCBnode_pid(PCB_ptr, currentPid);
        sprintf(reportString, "OS: Process %d selected with %d ms remaining",
                (unsigned int)currentPid, (unsigned int)PCB_wkg->time_left);
        LOGdump(1, config_dataptr, reportString);
        sprintf(reportString, "OS: Process %d set from READY to RUNNING",
                (unsigned int)currentPid);
        LOGdump(1, config_dataptr, reportString);
        OPC_ptr->intArg2 = 0;
      }
    }
    // processIntRequest(RESOLVE_ALL_INTERRUPTS, OPC_ptr, PCB_ptr);
    lastPid = currentPid;
  } while (runFlag);
  PCB_ptr = PCBnode_del(PCB_ptr);
  copyString(OPC_ptr->strArg1, "clearAll");
  // processMemRequest(config_dataptr, OPC_ptr);
  LOGdump(1, config_dataptr, "OS: Simulation end");
  LOGdump(2, config_dataptr, reportString);

  accessTimer(STOP_TIMER, reportString);
}