#include "simulator.h"
/**
 * Driver code for running the simulator
 */

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
        new_ptr = (LOGnode *)malloc(sizeof(LOGnode) + 1);
        copyString(new_ptr->LOG_out, txt_input);
        new_ptr->next_ptr = 0LL;
        return new_ptr;
    }
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
    // 0LL? long long expected?
    return 0;
}

PCBdata *PCBnode_add(PCBdata *local_ptr, PCBdata *new_ptr)
{
    PCBdata *wkg_ptr;      // [rsp+18h] [rbp-8h]

    if (local_ptr &&
        new_ptr->OClist->intArg2 >= local_ptr->OClist->intArg2)
    {
        for (wkg_ptr = local_ptr;
                wkg_ptr->next_ptr && 
                new_ptr->OClist->intArg2 >=
                wkg_ptr->next_ptr->OClist->intArg2;
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

void PCB_display(PCBdata *head_ptr)
{
    PCBdata *wkg_ptr;

    if (head_ptr)
    {
        while (wkg_ptr)
        {
            printf("PCB pid: %d, state: %d, time remaining: %d,\n",
                   (unsigned int)wkg_ptr->pid,
                   (unsigned int)wkg_ptr->state,
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
        puts("\nEmpty PCB List\n");
    }
}

void runSim(ConfigDataType *config_dataptr, OpCodeType *meta_data_ptr)
{
  char reportString[128]; // [rsp+10h] [rbp-B0h] BYREF
  PcbNodeType_0 *pcbListPtr; // [rsp+98h] [rbp-28h]
  int currentPid; // [rsp+A0h] [rbp-20h]
  bool isPreemptive; // [rsp+A7h] [rbp-19h]
  int lastPid; // [rsp+A8h] [rbp-18h]
  bool runFlag; // [rsp+AFh] [rbp-11h]
  OpCodeType_0 *wkgOpCode; // [rsp+B0h] [rbp-10h]
  PcbNodeType_0 *pcbWkgPtr; // [rsp+B8h] [rbp-8h]

  wkgOpCode = 0LL;
  runFlag = 1;
  currentPid = -1;
  lastPid = -1;
  showSimStart(configPtr);
  pcbListPtr = setAllPCB(configPtr, metaDataMstrPtr);
  isPreemptive = metaDataMstrPtr->nextNode->intArg3 == 9;
  processIntRequest(INITIALIZE_INTERRUPT_MGR, 0LL, pcbListPtr);
  setNewToReady(configPtr, pcbListPtr);
  processMemRequest(configPtr, metaDataMstrPtr);
  do
  {
    currentPid = getNextProcess(configPtr, pcbListPtr);
    if ( currentPid == -606 )
    {
      runSimReport(1, configPtr, "OS: System stop");
      runFlag = 0;
    }
    else if ( currentPid == -505 )
    {
      runCpuIdle(configPtr, pcbListPtr);
    }
    else
    {
      setNewToReady(configPtr, pcbListPtr);
      wkgOpCode = getNextOpCode(pcbListPtr, currentPid);
      if ( (compareString(wkgOpCode->command, "app") || compareString(wkgOpCode->strArg1, "start"))
        && isPreemptive
        && currentPid != lastPid )
      {
        pcbWkgPtr = getPcbById(pcbListPtr, currentPid);
        sprintf(
          reportString,
          "OS: Process %d selected with %d ms remaining",
          (unsigned int)currentPid,
          (unsigned int)pcbWkgPtr->timeRemaining);
        runSimReport(1, configPtr, reportString);
        sprintf(reportString, "OS: Process %d set from READY to RUNNING", (unsigned int)currentPid);
        runSimReport(1, configPtr, reportString);
      }
      if ( compareString(wkgOpCode->command, "app") || compareString(wkgOpCode->strArg1, "start") )
      {
        if ( compareString(wkgOpCode->command, "app") || compareString(wkgOpCode->strArg1, "end") )
        {
          if ( compareString(wkgOpCode->command, "mem") )
          {
            if ( compareString(wkgOpCode->command, "dev") )
            {
              if ( !compareString(wkgOpCode->command, "cpu") )
              {
                sprintf(
                  reportString,
                  "Process: %d, %s %s operation start",
                  (unsigned int)wkgOpCode->pid,
                  wkgOpCode->command,
                  wkgOpCode->strArg1);
                runSimReport(1, configPtr, reportString);
                processRunOp(configPtr, wkgOpCode, pcbListPtr);
              }
            }
            else
            {
              sprintf(
                reportString,
                "Process: %d, %s %sput operation start",
                (unsigned int)wkgOpCode->pid,
                wkgOpCode->strArg1,
                wkgOpCode->inOutArg);
              runSimReport(1, configPtr, reportString);
              wkgOpCode->intArg2 *= configPtr->ioCycleRate;
              processIoOp(wkgOpCode, pcbListPtr);
              pcbWkgPtr = getPcbById(pcbListPtr, currentPid);
              pcbWkgPtr->timeRemaining -= wkgOpCode->intArg2;
              wkgOpCode->intArg2 = 0;
            }
          }
          else
          {
            sprintf(
              reportString,
              "Process: %d, mem %s request (%d, %d)",
              (unsigned int)wkgOpCode->pid,
              wkgOpCode->strArg1,
              (unsigned int)wkgOpCode->intArg2,
              (unsigned int)wkgOpCode->intArg3);
            runSimReport(1, configPtr, reportString);
            if ( processMemRequest(configPtr, wkgOpCode) )
            {
              sprintf(
                reportString,
                "Process: %d, successful mem %s request",
                (unsigned int)wkgOpCode->pid,
                wkgOpCode->strArg1);
              runSimReport(1, configPtr, reportString);
              wkgOpCode->intArg2 = 0;
            }
            else
            {
              sprintf(
                reportString,
                "Process: %d, failed mem %s request",
                (unsigned int)wkgOpCode->pid,
                wkgOpCode->strArg1);
              runSimReport(1, configPtr, reportString);
              sprintf(reportString, "OS: Segmentation fault, Process %d ended", (unsigned int)wkgOpCode->pid);
              runSimReport(1, configPtr, reportString);
              copyString(wkgOpCode->strArg1, "clearOne");
              processMemRequest(configPtr, wkgOpCode);
              pcbWkgPtr->state = 4;
              sprintf(reportString, "OS: Process %d set to EXIT", (unsigned int)currentPid);
              runSimReport(1, configPtr, reportString);
            }
          }
        }
        else
        {
          sprintf(reportString, "OS: Process %d ended", (unsigned int)currentPid);
          runSimReport(1, configPtr, reportString);
          wkgOpCode->pid = currentPid;
          copyString(reportString, "clearOne");
          copyString(wkgOpCode->strArg1, reportString);
          processMemRequest(configPtr, wkgOpCode);
          pcbWkgPtr = getPcbById(pcbListPtr, currentPid);
          pcbWkgPtr->state = 4;
          sprintf(reportString, "OS: Process %d set to EXIT", (unsigned int)currentPid);
          runSimReport(1, configPtr, reportString);
        }
      }
      else
      {
        pcbWkgPtr = getPcbById(pcbListPtr, currentPid);
        sprintf(
          reportString,
          "OS: Process %d selected with %d ms remaining",
          (unsigned int)currentPid,
          (unsigned int)pcbWkgPtr->timeRemaining);
        runSimReport(1, configPtr, reportString);
        sprintf(reportString, "OS: Process %d set from READY to RUNNING", (unsigned int)currentPid);
        runSimReport(1, configPtr, reportString);
        wkgOpCode->intArg2 = 0;
      }
    }
    processIntRequest(RESOLVE_ALL_INTERRUPTS, wkgOpCode, pcbListPtr);
    lastPid = currentPid;
  }
  while ( runFlag );
  pcbListPtr = clearAllPcbNodes(pcbListPtr);
  copyString(wkgOpCode->strArg1, "clearAll");
  processMemRequest(configPtr, wkgOpCode);
  runSimReport(1, configPtr, "OS: Simulation end");
  runSimReport(2, configPtr, reportString);
  accessTimer(2, reportString);

}








