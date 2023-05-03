// Header Files 
#include "simulator.h"

// Function Implementation

StrLinkedListNode *addStrNode( char *strToAdd, StrLinkedListNode *localPtr)
{
   // initialize function/variables 

   // if local pointer is null
   if (localPtr == NULL)
   {
      // make a new node 
         // function: malloc
      localPtr = (StrLinkedListNode *) malloc(sizeof(StrLinkedListNode));

      // set next node to null
      localPtr -> nextNode = NULL;

      // add the string into the node 
         // function: copyString
      copyString(localPtr -> lineStr, strToAdd);

      // return local pointer 
      return localPtr;

   }

   // otherwise, more of list 

   // recurse further into list 
   localPtr -> nextNode = addStrNode(strToAdd, localPtr->nextNode);

   // return local pointer 
   return localPtr;

}

MemLinkedListNode *clearMemLinkedList( MemLinkedListNode *wkgPtr)
{
   // if head pointer is not null 
   if (wkgPtr != NULL)
   {
      // recurse into function
         // function: clearStrLinkedList
      clearMemLinkedList(wkgPtr->nextNode); 

      // free the current pointer 
         // function: free
      free(wkgPtr);
   }

   // return NULL
   return NULL; 


}

void clearNode( MemLinkedListNode *nodeToClear)
{
   // initiaalize variables 

   // set the lower logical bound to 0 
   nodeToClear -> logicalStart = 0;

   // set the upper logical bound to 0 
   nodeToClear -> logicalEnd = 0;

   // set the pid to x 
   nodeToClear -> pid = NO_PROCESS;

   // set the node to be open
   nodeToClear -> openOrUsed = OPEN;

}

StrLinkedListNode *clearStrLinkedList( StrLinkedListNode *headPtr)
{
   // if head pointer is not null 
   if (headPtr != NULL)
   {
      // recurse into function
         // function: clearStrLinkedList
      clearStrLinkedList(headPtr->nextNode); 

      // free the current pointer 
         // function: free
      free(headPtr);
   }

   // return NULL
   return NULL; 
}

MemLinkedListNode *compressionCheck( MemLinkedListNode *headPtr)
{
   // initialize variables 
   MemLinkedListNode *wkgPtr = headPtr;
   MemLinkedListNode *tempPtr;

   // while not at end of list
   while (wkgPtr != NULL && wkgPtr -> nextNode != NULL)
   {
      // if the current node and the next node are both open 
      if (wkgPtr -> openOrUsed == OPEN && 
           wkgPtr -> nextNode -> openOrUsed == OPEN) 
      {
         // make the upper bound of the current node the upper bound of the next node 
         wkgPtr -> physicalEnd = wkgPtr -> nextNode -> physicalEnd; 

         // set temp pointer to next node 
         tempPtr = wkgPtr -> nextNode;

         // set next node from working pointer to be 2 nodes down
         wkgPtr -> nextNode = wkgPtr -> nextNode -> nextNode;  
 
         // free temp pointer 
         free( tempPtr);
      }
      
      // otherwise, go down list to keep checking 
      else
      {
         // update pointer 
         wkgPtr = wkgPtr -> nextNode;
      }
   }

   // return head pointer
   return headPtr;  

}

MemLinkedListNode *createMemNode( int lowerPhysical, int upperPhysical, 
                                   int lowerLogical, int upperLogical, 
                                    char pid, bool openOrUsed)
{
   // initialize variables 
   MemLinkedListNode *newNode;

   // malloc a new node 
      // function: malloc 
   newNode = (MemLinkedListNode *)malloc(sizeof(MemLinkedListNode));

   // set lower physical bound 
   newNode -> physicalStart = lowerPhysical; 

   // set upper physical bound 
   newNode -> physicalEnd = upperPhysical;

   // set lower logical bound 
   newNode -> logicalStart = lowerLogical; 

   // set upper logical bound 
   newNode -> logicalEnd = upperLogical; 

   // set pid 
   newNode -> pid = pid;

   // set if open or used 
   newNode -> openOrUsed = openOrUsed;

   // set next node to null 
   newNode -> nextNode = NULL;

   // return the pointer to the new node
   return newNode; 
}


PCBBlock *getProcesses( OpCodeType *metaDataHeadPtr, ConfigDataType *configPtr )
{
   // initialize function/variables
   OpCodeType *wkgPtr = metaDataHeadPtr;
   PCBBlock *processes;
   PCBBlock tempProcess;
   int pidCount = 0, processArrayIndex = 0;
   int timeToAdd = 0;

   // make an array for the processes
   processes = (PCBBlock *) malloc(sizeof(PCBBlock) * MAX_NUM_PROCESSES);

   // while not at end of metadata ops 
   while (wkgPtr != NULL && wkgPtr -> nextNode != NULL)
   {
      // move the pointer forward 
      wkgPtr = wkgPtr->nextNode;

      // if it is an app start 
         // function: compareString
      if (compareString(wkgPtr->strArg1, "start") == STR_EQ)
      {
         // reset temp process 
         tempProcess.pid = pidCount;
         tempProcess.estTime = 0.0;
         tempProcess.state = NEW_STATE;
         tempProcess.appStartPtr = wkgPtr;
         tempProcess.estFinishTime = 0;
         tempProcess.currentOpCode = NULL;

         // increment pid for next process
         pidCount++;
      }

      // if it is an app end and not the sys end
      if (compareString(wkgPtr->strArg1, "end") == STR_EQ && 
          wkgPtr -> nextNode != NULL)
      {         
         // store process in return array
         processes[processArrayIndex] = tempProcess; 
         
         // increment storing index
         processArrayIndex++; 
      }

      // otherwise, in middle of process
      else
      {
         // if process is not memory 
         if (compareString(wkgPtr->command, "mem") != STR_EQ)
         {
            // if process is io
            if (compareString(wkgPtr->inOutArg, "in") == STR_EQ || 
                  compareString(wkgPtr->inOutArg, "out") == STR_EQ)
            {
               // calc time 
               timeToAdd = configPtr->ioCycleRate * wkgPtr->intArg2;
            }
         
            // otherwise, process is processor based
            else 
            {
               // calc time  
               timeToAdd = configPtr->procCycleRate * wkgPtr->intArg2;
            }


         // add to total time
         tempProcess.estTime += timeToAdd;
    
         }

         // otherwise, memory, do not calculate time 
   
      }
   }

   // set pid of end process to -1 to see end of process array
   tempProcess.pid = -1;

   // insert end process into array
   processes[processArrayIndex] = tempProcess; 

   // return array of processes
   return processes;

}

PCBBlock getNextProcess( PCBBlock *processes, int *currentProcessIndex, ConfigDataType *configPtr)
{
   // initialize variables
   char algorithm[STD_STR_LEN];
   int processSearchIndex = 0;
   PCBBlock returnProcess, shortestProcess, tempProcess;
   static PCBBlock *lastProcess = NULL; 
   bool notFoundProcess = true;
   bool notEndFound = true;

   // get the proper string for the scheduling algorithm
      // function: configCodeToString
   configCodeToString(configPtr->cpuSchedCode, algorithm);

   // if the scheduling algorithm is FCFS-N or FCFS-P
      // function: compareString
   if (compareString( algorithm, "FCFS-N") == STR_EQ
        || compareString(algorithm, "FCFS-P") == STR_EQ)
   {
      // while not at end of processes
      while (processes[processSearchIndex].pid >= 0)
      {
         // if process is not in block and not in exited 
         if (processes[processSearchIndex].state != BLOCKED_STATE 
              && processes[processSearchIndex].state != EXIT_STATE
                && notFoundProcess)
         {
            // set boolean for found process 
            notFoundProcess = false; 

            // put value into return 
            returnProcess = processes[processSearchIndex];

         }
         
         // update search index 
         processSearchIndex++;
      }

      // if no process found 
      if (notFoundProcess)
      {
         // if none found, create copy of 0th process 
         returnProcess = processes[0];

         // set state of return to EXIT to signal failure 
         returnProcess.state = EXIT_STATE;
      }
   } 

   // otherwise, if the scheduling algorithm is SJF or SRTF
   else if (compareString( algorithm, "SJF-N") == STR_EQ
             || compareString(algorithm, "SRTF-P") == STR_EQ)
   {
      // assume first process is the shortest 
      shortestProcess = processes[0];

      // set shortest to exit in case of no bind 
      shortestProcess.state = EXIT_STATE;

      // set process search index to the second item 
      processSearchIndex = 1;

      // while not at end of processes
      while (processes[processSearchIndex].pid >= 0)
      {
         // bind temporary process
         tempProcess = processes[processSearchIndex];

         // if the time remaining is less than the shortest process and greater than 0
         // or the shortest process is completed
         if ((((tempProcess.estTime < shortestProcess.estTime && 
				tempProcess.estTime > 0)
				  || shortestProcess.state == EXIT_STATE)
                                     && tempProcess.state != EXIT_STATE)
                                     && tempProcess.state != BLOCKED_STATE)
         {
            // select new shortest process 
            shortestProcess = tempProcess;
         }

         // increment index 
         processSearchIndex++;

      }

      // put proper process into return 
      returnProcess = shortestProcess;

   }

   // if the scheduler is RR
   else if (compareString(algorithm, "RR-P") == STR_EQ)
   {
      tempProcess = processes[processSearchIndex];

      // if there was a last done process
      if (lastProcess != NULL)       
      {
         // start at the process after the last done process
         processSearchIndex = processes[lastProcess -> pid + 1].pid;

         // check if process is last process 
         if (processes[processSearchIndex].pid == -1)
         {
            // rebind index 
            processSearchIndex = 0;
         }

         // bind temp process to last process 
         tempProcess = *lastProcess;
      }

      // otherwise, first iteration 
      else
      {
         // set index to 1
         processSearchIndex = 0;

         // bind process to second process 
         tempProcess = processes[1];
      }

      // while not at last done process
      while (notEndFound && notFoundProcess)
      {

         // if the process to be looked at is not blocked or exited
         if (processes[processSearchIndex].state != BLOCKED_STATE 
               && processes[processSearchIndex].state != EXIT_STATE
                 && notFoundProcess)
         {
            // set found process 
            notFoundProcess = false; 
 
            // return it
            returnProcess = processes[processSearchIndex]; 

            // set last process 
            lastProcess = &processes[*currentProcessIndex];
         }
         
         // if the pid of the temp process and the search process are equal 
         if (tempProcess.pid == processes[processSearchIndex].pid)
         {
            // stop looping
            notEndFound = false; 
         }

         // update index 
         processSearchIndex++;

         // if the pid is -1 
         if (processes[processSearchIndex].pid == -1)
         {
            // set loop back to 0 
            processSearchIndex = 0;
         }

      }

      // if fall out of loop, no return 
      if (notFoundProcess)
      {
         // set return process to be temp process 
         returnProcess = processes[0];

         // set return process state to exit
         returnProcess.state = EXIT_STATE;
      }
   }

   // reset process index
   processSearchIndex = 0;

   // for each process 
   while (processes[processSearchIndex].pid >= 0)
   {
      // if the return process and the process in the array have equal pids 
      if (returnProcess.pid == processes[processSearchIndex].pid) 
      {
         // set process index to the loop index
         *currentProcessIndex = processSearchIndex;
      }

      // increment index 
      processSearchIndex++;
   }


   // if i have no processes left with time (i.e. return time is 0)
   if (returnProcess.state == EXIT_STATE)
   {
      // reset process search index
      processSearchIndex = 0;

      // assume all processes are in exit with pid -1 
      returnProcess.pid = ALL_EXIT;

      // for each process 
      while (processes[processSearchIndex].pid >= 0)
      {
         // if any are blocked 
         if (processes[processSearchIndex].state == BLOCKED_STATE)  
         {
            // set return to -2 to signal all blocked 
            returnProcess.pid = CPU_IDLE;
         }

         // increment process index 
         processSearchIndex++;
      }

   }

   // return the proper process 
   return returnProcess;

}

OpCodeType *getOpCode( PCBBlock currentProcess)
{
   // if there is no pointer for the used pointer slot 
   if (currentProcess.currentOpCode == NULL)
   {
      // return pointer to next pointer from app start pointer
      return currentProcess.appStartPtr -> nextNode;
   }

   // otherwise, see if current node has stuff left to do 
   else if (currentProcess.currentOpCode -> intArg2 > 0)
   {
      // return current pointer to complete
      return currentProcess.currentOpCode;

   }

   // otherwise, current pointer done 
   else
   {
      // return next pointer 
      return currentProcess.currentOpCode -> nextNode;
   }

}

bool interruptMgr(char *keyword, PCBBlock **ptrToProcessesArray)
{
   // initialize variables
   static PCBBlock *interrupts[MAX_NUM_PROCESSES]; 
   static int numInterrupts = 0;
   char runningTime[STD_STR_LEN]; 
   bool insertFlag = true; 
   int processIndex = 0;
   float valTime = 0;
   int interruptIndex = 0;
   PCBBlock *processes; 

   // store processes array 
   processes = *ptrToProcessesArray;

   // get the current time 
      // function: accessTimer
   accessTimer(LAP_TIMER, runningTime);

   // convert the current time to an int
      // function: timeStrToInt
   valTime = timeStrToFloat(runningTime);

   // for every process I have 
   while (processes[processIndex].pid >= 0)
   {
      // if the estimated finish time is less than the current time 
      if (processes[processIndex].estFinishTime < valTime 
           && processes[processIndex].state == BLOCKED_STATE)
      {
         // for every item in the interrupts queue  
         for (interruptIndex = 0; interruptIndex < numInterrupts; interruptIndex++)
         {
            // if the current item is in the queue 
            if (interrupts[interruptIndex] -> pid == processes[processIndex].pid)
            {
               // set flag to not insert 
               insertFlag = false;
            }

         }

         // if inserting 
         if (insertFlag)
         {

            // put that process into the interrupt queue 
            interrupts[numInterrupts] = &(processes[processIndex]);

            // increment counter 
            numInterrupts++;
         }

         // reset flag 
         insertFlag = true;
      }

      // increment process index 
      processIndex++;   
    
   }

   // if I am processing interrupts 
   if (compareString(keyword, "process") == STR_EQ)
   {
      // for each interrupt in the queue 
      for (interruptIndex = 0; interruptIndex < numInterrupts; interruptIndex++)
      {
         // set the process to ready 
         interrupts[interruptIndex] -> state = READY_STATE;   
      }

      // reset number of interrupts 
      numInterrupts = 0;

      // return true for successes
      return true;

   }

   // if I am reading interrupts 
   if (compareString(keyword, "read") == STR_EQ)
   {
      // return if numInterrupts > 0
      return numInterrupts == 0;
   }

   // otherwise, no valid keyword provided, return false
   return false; 
}
                  
MemLinkedListNode *insertMemNode( MemLinkedListNode *newNode, 
                                     MemLinkedListNode *headPtr)
{
   // initialize variables 
   MemLinkedListNode *wkgPtr = headPtr;

   // if head pointer null 
   if (headPtr == NULL)
   {
      // append to head pointer 
      headPtr = newNode; 
   }

   // otherwise, list 
   else
   {
      // while not at the end of the list
      while( wkgPtr -> nextNode != NULL) 
      {
         // move pointer forward 
         wkgPtr = wkgPtr -> nextNode;
      }

      // append new node to end of list 
      wkgPtr -> nextNode = newNode;
   }

   // return head pointer 
   return headPtr;

}   
                                 
PCBBlock prepareNextProcess( PCBBlock *processes, int *processIndexPtr, char *outputType,
                              StrLinkedListNode *headPtr, PCBBlock currentProcess, 
                              ConfigDataType *configPtr, bool segFaultFlag, 
                              MemLinkedListNode *memHeadPtr, bool interruptFlag)
{
      // initialize variables 
      PCBBlock tempProcess;
      int processIndex = *processIndexPtr;

      // if the output is to screen or both and no segfault for spacing reasons
      if ((compareString(outputType, "Monitor") == STR_EQ || 
            compareString(outputType, "Both") == STR_EQ) 
             && !segFaultFlag)
      {
         // print an endline 
            // function: printf
         printf("\n");
      }

      // if the output is to file or both and I did not segfault
      if ((compareString(outputType, "File") == STR_EQ || 
            compareString(outputType, "Both") == STR_EQ)
              && !segFaultFlag)
      {
         // add an endline to string linked list 
            // function: addStrNode
         addStrNode("\n", headPtr);
      }

      // if I did not interrupt 
      if (interruptFlag)
      {
         // if I did not segfault and did not interrupt  
         if (!segFaultFlag)
         {
            // end current process
               // function: printSimLine
            printSimLine("OS", "processEnded", outputType, NEW_STATE, NEW_STATE, 
                     &currentProcess, headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                       "NEITHER", "NOTMEM");

            // clear memory of current process 
               // function: processMemoryOperation  
            processMemoryRequest( NULL, &memHeadPtr, "processClear", 
                                      configPtr, currentProcess);

         }
    
         // set process to exit 
         processes[processIndex].state = EXIT_STATE;


         // print move to exit 
         printSimLine("OS", "stateSwitch", outputType, RUNNING_STATE, EXIT_STATE, 
                     &currentProcess, headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                       "NEITHER", "NOTMEM");
      }

      // select next process 
         // function: getNextProcess
      tempProcess = getNextProcess(processes, processIndexPtr, configPtr);

      // if the return from getNextProcess was CPU_IDLE
      if (tempProcess.pid == CPU_IDLE)
      {
         // print cpu idle 
            // function: printSimLine
         printSimLine("OS", "cpuIdle", outputType, NEW_STATE, NEW_STATE, 
                     NULL, headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                       "NEITHER", "NOTMEM");

         // all process blocked, loop while the interrupt manager has no 
         // interrupts
            // function: interruptMgr 
         while (interruptMgr("read", &processes))
         {
            // no operations, simply loop until an interrupt occurs 
         }

         // after loop, process interrupts 
            // function: interruptMgr
         interruptMgr("process", &processes);

         // after loop, get next process, some process is done 
            // function: getNextProcess
         tempProcess = getNextProcess(processes, processIndexPtr, configPtr);

         // if the current pointer is not null for the process 
         if (tempProcess.currentOpCode != NULL)
         {
            // move it to next
         //   tempProcess.currentOpCode = tempProcess.currentOpCode -> nextNode;
         }

         // otherwise, first operation 
         else
         {
            // set current pointer  
            tempProcess.currentOpCode = tempProcess.appStartPtr -> nextNode;
          
         }

         // print idle end 
            // function: printSimLine
         printSimLine("OS", "cpuIdleEnd", outputType, NEW_STATE, NEW_STATE, 
                     &tempProcess, headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                       "NEITHER", "NOTMEM");

         // print interrupt 
            // function: printSimLine
         printSimLine("OS", "interrupt", outputType, NEW_STATE, NEW_STATE, 
                     &tempProcess, headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                       "NEITHER", "NOTMEM");

         // print movement from blocked to ready 
            // function: printSimLine
         printSimLine("OS", "stateSwitch", outputType, BLOCKED_STATE, READY_STATE, 
                     &tempProcess, headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                       "NEITHER", "NOTMEM");


      }

      // if the process is not the end process
      if (tempProcess.pid >= 0)
      {
         // print selection 
            // function: printSimLine
         printSimLine("OS", "processSelect", outputType,
                       NEW_STATE, NEW_STATE, &tempProcess, 
                        headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                         "NEITHER", "NOTMEM");

         // print movement
            // function: printSimLine
         printSimLine("OS", "stateSwitch", outputType, READY_STATE, 
                         RUNNING_STATE, &tempProcess, 
                          headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, 
                           "NEITHER", "NOTMEM");
             
         // if the output is to screen or both
         if (compareString(outputType, "Monitor") == STR_EQ || 
               compareString(outputType, "Both") == STR_EQ)
         {
            // print an endline 
               // function: printf
            printf("\n");
         }

         // if the output is to file or both
         if (compareString(outputType, "File") == STR_EQ || 
               compareString(outputType, "Both") == STR_EQ)
         {
            // add an endline to string linked list 
               // function: addStrNode
            addStrNode("\n", headPtr);
         }
      
      }

      // return the process 
      return tempProcess;



}


void printMemLine(OpCodeType *memPtr, MemLinkedListNode *headPtr, 
                    char *operation)
{
   // initialize variables 
   MemLinkedListNode *wkgPtr = headPtr;

   // print a line of dashes 
   printf("--------------------------------------------------\n");

   // print the statement describing operation 
   printf("After %s\n", operation);

   // if the list is not empty 
   if (headPtr != NULL)
   {
      // while not at end of linked list 
      while (wkgPtr != NULL)
      {
         // if open 
         if (wkgPtr -> openOrUsed == OPEN)
         {
            // print open line
            printf("%d [ Open, P#: %c, %d-%d ] %d\n", 
                                      wkgPtr -> physicalStart, wkgPtr -> pid, 
                                       wkgPtr -> logicalStart, wkgPtr -> logicalEnd, 
                                         wkgPtr -> physicalEnd); 

         }

         // otherwise, used 
         else
         {
            // print used line
            printf("%d [ Used, P#: %c, %d-%d ] %d\n", 
                                      wkgPtr -> physicalStart, wkgPtr -> pid, 
                                       wkgPtr -> logicalStart, wkgPtr -> logicalEnd, 
                                         wkgPtr -> physicalEnd); 

         }

         // move working pointer 
         wkgPtr = wkgPtr -> nextNode;
      } 
   }

   // otherwise, empty list 
   else
   {
      // report no memory allocated 
      printf("No memory configured\n");
   }

   // print end dashes 
   printf("--------------------------------------------------\n");


}

void printSimLine( char *callingEntity, char *inputType, char *outputType,  
                    ProcessState start, ProcessState end, 
                    PCBBlock *process, StrLinkedListNode *headPtr,
                    int memStart, int memEnd, int startOrEnd, char *inOutArg,
                    char *memOpType)
{
   // initialize function/variables 
   
      // make empty string for printing purposes
      char printingString[MAX_STR_LEN];

      // declare other variables
      char *runningTime;
      char ioType[STD_STR_LEN];

   // if it is input 
   if (compareString(inOutArg, "in") == STR_EQ)
   {
      // set io type to input 
         // function: copyString 
      copyString(ioType, "input");
   }

   // if it is output 
   if (compareString(inOutArg, "out") == STR_EQ)
   {
      // set io type to output 
         // function: copyString 
      copyString(ioType, "output");
   }

   // malloc a string for the running time 
      // function: malloc
   runningTime = (char *)malloc(sizeof(char) * STD_STR_LEN);

   // get the running time
      // thread: runningTime
   accessTimer(LAP_TIMER, runningTime);

   // if the input type is start 
   if (compareString(inputType, "start") == STR_EQ)
   {
      // print sim start 
         // function: sprintf
      sprintf(printingString, "%s, %s, Simulator Start\n", 
                                    runningTime, callingEntity);
   }

   // otherwise, if selecting a process 
   else if (compareString(inputType, "processSelect") == STR_EQ)
   {
      // print process selected line 
         // function: sprintf
      sprintf(printingString, 
                      "%s, %s, Process %d selected with %d ms remaining\n", 
                                    runningTime, callingEntity, process->pid, 
                                    process->estTime);
      
   }

   // otherwise, if input type is state switch 
   else if (compareString(inputType, "stateSwitch") == STR_EQ)
   {
      // if going from new to ready
      if (start == NEW_STATE && end == READY_STATE)
      {
         // print statement 
            // function: sprintf
         sprintf(printingString, 
                      "%s, %s, Process %d set to READY state from NEW state\n", 
                                    runningTime, callingEntity, process->pid);

      }

      // if going from ready to running 
      else if (start == READY_STATE && end == RUNNING_STATE)
      {
         // print statement 
            // function: sprintf
         sprintf(printingString, 
                      "%s, %s, Process %d set from READY state to RUNNING\n", 
                                    runningTime, callingEntity, process->pid);

      }

      // if exiting 
      else if (start == RUNNING_STATE && end == EXIT_STATE)
      {
         // print statement 
            // function: sprintf
         sprintf(printingString, 
                      "%s, %s, Process %d set to EXIT\n", 
                                    runningTime, callingEntity, process->pid);

      }

      // if blocking 
      else if (start == BLOCKED_STATE && end == READY_STATE)
      {
         // print block statement
            // function: sprintf
         sprintf(printingString, 
                      "%s, %s, Process %d set from BLOCKED to READY\n", 
                                    runningTime, callingEntity, process->pid);

      } 

      // if moving from running to blocked 
      else if (start == RUNNING_STATE && end == BLOCKED_STATE)
      {
         // print block statement
            // function: sprintf
         sprintf(printingString, 
                      "%s, %s, Process %d set from RUNNING to BLOCKED\n", 
                                    runningTime, callingEntity, process->pid);

      } 

   }
  
   // otherwise, if a process is ended
   else if (compareString(inputType, "processEnded") == STR_EQ)
   {
      // print statement 
         // function: sprintf
      sprintf(printingString, 
                   "%s, %s, Process %d ended\n", 
                                 runningTime, callingEntity, process->pid);

   }

   // otherwise, if system stop 
   else if (compareString(inputType, "sysStop") == STR_EQ)
   {
      // print statement 
         // function: sprintf
      sprintf(printingString, 
                   "%s, %s, System stop\n", 
                                 runningTime, callingEntity);

   }

   // otherwise, if simulation end 
   else if (compareString(inputType, "simStop") == STR_EQ)
   {
      // print statement 
         // function: sprintf
      sprintf(printingString, 
                   "%s, %s, Simulation End\n", 
                                 runningTime, callingEntity);

   }

   // otherwise, if segfault 
   else if (compareString(inputType, "segfault") == STR_EQ)
   {
      // print segfault 
      sprintf(printingString, 
               "\n%s, OS: Segmentation fault, Process %d ended\n", 
                  runningTime, process->pid);
   }

   // otherwise, check for idle 
   else if (compareString(inputType, "cpuIdle") == 0)
   {
      // print idle statement 
         // function: sprintf
      sprintf(printingString, 
                   "%s, %s, CPU idle, all active processes blocked\n", 
                                 runningTime, callingEntity);

   }

   // otherwise, check for idle end 
   else if (compareString(inputType, "cpuIdleEnd") == 0)
   {
      // print idle end statement
         // function: sprintf
      sprintf(printingString, 
                   "%s, %s, CPU interrupt, end idle\n", 
                                 runningTime, callingEntity);

   }

   // otherwise, check for interrupt 
   else if (compareString(inputType, "interrupt") == 0)
   {
      // print interrupt statement 
         // function: sprintf
      sprintf(printingString, 
                   "%s, %s, Interrupted by process %d, %s operation\n", 
                                 runningTime, callingEntity,
                                 process -> pid, 
                                 process -> currentOpCode -> strArg1);

   }

   // otherwise, check for block for input 
   else if (compareString(inputType, "blockForIO") == 0)
   {
      
      // print interrupt statement 
         // function: sprintf
      sprintf(printingString, 
                   "%s, %s, Process %d blocked for %s operation\n", 
                                 runningTime, callingEntity,
                                 process -> pid, ioType);

   }
   
   // otherwise, if the input type is not memory allocation
   else if (compareString(inputType, "mem") != STR_EQ) 
   {
      // if the device is starting
      if (startOrEnd == START) 
      {
         // if the process is "process"
         if (compareString(inputType, "process") == STR_EQ)
         {
            // print with cpu in front 
            sprintf(printingString, 
                  "%s, Process: %d, cpu %s operation start\n", 
                      runningTime, process->pid, inputType); 
         }

         // otherwise, anything else
	 else
         {            
            // print proper string
               // function: sprintf 
            sprintf(printingString, 
                  "%s, Process: %d, %s %s operation start\n", 
                      runningTime, process->pid, inputType, ioType); 
            
         }
      }

      // otherwise, is ending 
      else 
      {
         // if the process is "process"
         if (compareString(inputType, "process") == STR_EQ)
         {
            // print with cpu in front 
            sprintf(printingString, 
                  "%s, Process: %d, cpu %s operation end\n", 
                      runningTime, process->pid, inputType); 
         }
      
         // otherwise, anything else
         else
         {            
            // print proper string
               // function: sprintf 
            sprintf(printingString, 
                  "%s, Process: %d, %s output operation end\n", 
                      runningTime, process->pid, inputType); 

            

         }

      }
   }

   // otherwise, memory
   else 
   {
      // if the memory is in (i.e. requesting)
      if (compareString(inOutArg, "in") == STR_EQ)
      {
         // print string 
            // function: sprintf
         sprintf(printingString, 
                   "%s, Process: %d, %s %s request (%d, %d)\n", 
                       runningTime, process->pid, inputType, memOpType, 
                         memStart, memEnd);
      }

      // if the memory is out (i.e. output from request) 
      else
      {
         // if the operation succeded (i.e. start or end is start as it is not ending)
         if (startOrEnd == START)
         {
            // print success
            sprintf(printingString, 
                      "%s, Process: %d, successful mem %s request\n", 
                        runningTime, process->pid, memOpType);
         }

         // otherwise, failure 
         else
         {
            // print failure
            sprintf(printingString, 
                      "%s, Process: %d, failed mem %s request\n", 
                        runningTime, process->pid, memOpType);
            
         } 
      }
   }

   // if the output is to screen or both
      // functions: compareString)
   if (compareString(outputType, "Monitor") == STR_EQ || 
         compareString(outputType, "Both") == STR_EQ)
   {
      // print to screen 
         // function: printf
      printf("%s", printingString);
   }

   // if the output is to file or both
   if (compareString(outputType, "File") == STR_EQ || 
         compareString(outputType, "Both") == STR_EQ)
   {
      // add to linked list 
         // function: addStrLinkedListNode
      headPtr = addStrNode(printingString, headPtr);
   }

   // free time string 
      // function: free
   free(runningTime);

}

bool processMemoryRequest(OpCodeType *memPtr, MemLinkedListNode **headPtr, 
				char *operation, ConfigDataType *configPtr,
                                PCBBlock currentProcess)
{
   // initialize variables 
   bool memDisplay, returnSuccess, badOperation, notInserted;
   MemLinkedListNode *wkgHeadPtr, *newNode, *wkgPtr; 
   int upperBound, oldPhysicalEnd, finalAccessVal; 
   char displayString[STD_STR_LEN];

   // set variable for memory display on or off 
   memDisplay = configPtr -> memDisplay;

   // set working head pointer 
   wkgHeadPtr = *headPtr; 

   // if the operation given is to initialize 
      // function: compareString
   if (compareString(operation, "initialize") == STR_EQ)
   {
      // create a node for the list 
         // function: createMemNode
      newNode = createMemNode(0, configPtr->memAvailable - 1, 0, 0, NO_PROCESS, OPEN);

      // bind the head pointer to the new node 
      *headPtr = newNode;

      // set return to true for successful initialization
      returnSuccess = true; 

      // if the memory display is on 
      if (memDisplay)
      {
         // print memory display 
            // function: printMemDisplay 
         printMemLine(memPtr, *headPtr, "memory initialization");
      }
   }

   // otherwise, if the operation is an allocate 
      // function: compareString
   else if (compareString(operation, "allocate") == STR_EQ)
   {
      // set flag to assume good operation
      badOperation = false; 

      // set working pointer 
      wkgPtr = wkgHeadPtr; 

      // find the upperBound of memory needed for the process 
      upperBound = memPtr -> intArg3 + memPtr -> intArg2;

      // for every node in the list
      while (wkgPtr != NULL) 
      {
         // if the operation is in the same process and 
         // has logical bounds inside itself and has good bounds
         if ((wkgPtr -> pid == currentProcess.pid + '0' && 
              ((memPtr -> intArg2 > wkgPtr -> logicalStart && 
               memPtr -> intArg2 < wkgPtr -> logicalEnd) ||
              (upperBound > wkgPtr -> logicalStart && 
               upperBound < wkgPtr -> logicalEnd))))
         {
            // set flag to bad allocate
            badOperation = true;
         }

         // update pointer 
         wkgPtr = wkgPtr -> nextNode;
      }

      // if not a bad allocate
      if (!badOperation)
      {
         // set working pointer 
         wkgPtr = wkgHeadPtr;

         // set insertion flag 
         notInserted = true; 

         // while not at end of memory list 
         while (wkgPtr != NULL && notInserted )
         {
            // if the range could fit into a node 
            if (memPtr -> intArg3 < 
                 (wkgPtr -> physicalEnd - wkgPtr -> physicalStart) 
                   && wkgPtr -> openOrUsed == OPEN)
            {
               // insert the memory requested into an open slot 

                  // store old upper bound 
                  oldPhysicalEnd = wkgPtr -> physicalEnd; 
               
                  // change the lower logical bound 
                  wkgPtr -> logicalStart = memPtr -> intArg2;
 
                  // change the upper logical bound 
                  wkgPtr -> logicalEnd = upperBound - 1; 

                  // make the upper physical bound lower bound + range - 1
                  wkgPtr -> physicalEnd = wkgPtr -> physicalStart + memPtr -> intArg3 - 1;

                  // set the node to used 
                  wkgPtr -> openOrUsed = USED;

                  // insert the proper pid 
                  wkgPtr -> pid = currentProcess.pid + '0';

                  // set flag to false
                  notInserted = false; 

               // if there is memory left 
               if (oldPhysicalEnd - (wkgPtr -> physicalEnd + 1) > 0)
               {
                  // create a new node for the leftover memory 
                     // function: createMemNode
                  newNode = createMemNode(wkgPtr -> physicalEnd + 1, oldPhysicalEnd, 
                                                 0, 0, NO_PROCESS, OPEN);
               }

               // insert the new node 
               
                  // set new node next pointer to wkg pointer next pointer 
                  newNode -> nextNode = wkgPtr -> nextNode;

                  // set working pointer next pointer to node 
                  wkgPtr -> nextNode = newNode;

               // check for compression of open space 
                  // function: compressionCheck
               *headPtr = compressionCheck(wkgHeadPtr);

               // set return to true for successful insert
               returnSuccess = true;  

               // if the memory display is on
               if (memDisplay) 
               {
                  // print memory display 
                     // function: printMemDisplay
                  printMemLine(memPtr, *headPtr, "allocate success");
               } 
            }
            
            // update pointer 
            wkgPtr = wkgPtr -> nextNode;
         }
       
         // if I was not able to insert the node 
         if (!returnSuccess)
         {
            // set return to failure 
            returnSuccess = false; 

            // if the memory display is on 
            if (memDisplay)
            {
               // print memory display 
                  // function: printMemDisplay 
               printMemLine(memPtr, *headPtr, "allocate lack of space failure"); 
            }
         }
      } 

      // otherwise, process trying to logical overlap itself 
      else
      {
         // set return to failure for segmentation fault 
         returnSuccess = false; 

         // if the memory display is on 
         if (memDisplay)
         {
            // print memory display 
               // function: printMemDisplay 
            printMemLine(memPtr, *headPtr, "allocate logical overlap failure");
         }
      }
   }

   // otherwise, check if an access request 
      // function: compareString
   else if (compareString(operation, "access") == STR_EQ)
   {
      // assume allocate will fail
      returnSuccess = false;

      // calculate the final access value (base + offset)
      finalAccessVal = memPtr -> intArg2 + memPtr -> intArg3; 

      // set working pointer 
      wkgPtr = wkgHeadPtr;

      // while not at the end of memory linked list 
      while (wkgPtr -> nextNode != NULL)
      {
         // if the process is the correct process and the final value is in the range 
         if (wkgPtr -> pid == currentProcess.pid + '0' && 
              finalAccessVal >= wkgPtr -> logicalStart && 
               finalAccessVal < wkgPtr -> logicalEnd)
         {
            // set allocate flag successful 
            returnSuccess = true; 
         }
         
         // update pointer 
         wkgPtr = wkgPtr -> nextNode;
        
      }

       // if allocate successful 
       if (returnSuccess && memDisplay)
       {
         // print memory display 
            // function: printMemDisplay
         printMemLine(memPtr, *headPtr, "access success"); 
       }

       // otherwise. unsuccessful allocate, print if mem display on 
       else if (memDisplay)
       {
         // print memory display 
            // function: printMemDisplay
         printMemLine(memPtr, *headPtr, "access failure");   
         
       }
   }

   // otherwise, check if clear request for process 
      // function: compareString
   else if (compareString(operation, "processClear") == STR_EQ)
   {
      // set working pointer 
      wkgPtr = wkgHeadPtr; 

      // assume operation will fail 
      returnSuccess = false; 

      // while not at end of linked list 
      while (wkgPtr -> nextNode != NULL)
      {
         // if the node is of the process being cleared 
         if (wkgPtr -> pid == currentProcess.pid + '0')
         {
            // clear the node 
               // function: clearNode
            clearNode(wkgPtr);

            // set success to true 
            returnSuccess = true; 
         }
  
         // update pointer 
         wkgPtr = wkgPtr -> nextNode;
      }  

      // compress open space 
         // function: compressionCheck
      *headPtr = compressionCheck( *headPtr); 

      // if the memory display is on 
      if (memDisplay)
      {

         // if successful 
         if (returnSuccess)
         {
            // make string to put to display 
               // function: sprintf 
            sprintf(displayString, "process %d clear successful", 
                                             currentProcess.pid);
         }

         // otherwise, failed 
         else
         {
            // make failure string 
               // function: sprintf 
            sprintf(displayString, "process %d clear failed", 
                                             currentProcess.pid);

         }

         // print memory display 
            // function: printMemDisplay 
         printMemLine(memPtr, *headPtr, displayString);
      }

      // set success flag 
      returnSuccess = true; 
   }

   // otherwise, if the request is to clear all memory 
      // function: compareString
   else if (compareString(operation, "clearAllMem") == STR_EQ)
   {
      // clear linked list 
         // function: clearMemLinkedList
      *headPtr = clearMemLinkedList(*headPtr);

      // if the memory display is on 
      if (memDisplay)
      {
         // print memory display 
            // function: printMemDisplay 
         printMemLine(memPtr, *headPtr, "clear all process success");
      }

      // set success flag 
      returnSuccess = true;
   }

   // return result from operation
   return returnSuccess;
}

void runSim( ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr)
{
   // initialize function/variables
   char outputType[STD_STR_LEN]; 
   char schedulingMethod[STD_STR_LEN];
   char headerString[MAX_STR_LEN];
   char configStr[MAX_STR_LEN]; 
   char currentTime[STD_STR_LEN];
   StrLinkedListNode *headPtr = NULL;
   MemLinkedListNode *memHeadPtr = NULL;
   char tempStr[STD_STR_LEN];
   char endOfFileStr[MAX_STR_LEN];
   int processIndex = 0;
   float currentTimeFloat = 0;
   float timeToRunSeconds = 0;
   float estFinalTime = 0;
   int numCycles = 0;
   int timeRan = 0;
   uintptr_t timeToRun = 0;
   PCBBlock *processes;
   PCBBlock tempProcess;
   OpCodeType *wkgPtr = NULL;
   pthread_t runningTimeThread; 
   bool goodResult = false; 
   bool segFaultFlag = false; 
   bool notInterrupted = true;
   bool preemptiveStrategy = false; 

   // create a thread for time
   accessTimer(ZERO_TIMER, tempStr);


   // get output method 
      // function: configCodeToString
   configCodeToString(configPtr->logToCode, outputType);
   
   // get scheduling method 
      // function: configCodeToString
   configCodeToString(configPtr->cpuSchedCode, schedulingMethod);

   // make header string 
      // function: sprintf
   sprintf(headerString, 
           "================\n"
           "Begin Simulation\n\n");

   // determine if the scheduling algorithm is preemptive or not 
   preemptiveStrategy = (compareString(schedulingMethod, "FCFS-P") == STR_EQ
                         || compareString(schedulingMethod, "SRTF-P") == STR_EQ
                           || compareString(schedulingMethod, "RR-P") == STR_EQ);


   // if the output is to file or both 
   if (compareString(outputType, "File") == STR_EQ || 
         compareString(outputType, "Both") == STR_EQ)
   {  
      // add nodes to linked list for all config data lines 
         // function: sprintf
      sprintf(configStr, 
           "======================================================\n"
           "Simulator Log File Header\n\n");

      
      headPtr = addStrNode(configStr, headPtr);

      // add file name 
      sprintf(configStr, "File Name                       : %s\n",
                  configPtr->metaDataFileName);

      headPtr = addStrNode(configStr, headPtr);

      // add cpu scheduling method
      sprintf(configStr, "CPU Scheduling                  : %s\n", 
                  schedulingMethod);

      headPtr = addStrNode(configStr, headPtr);

      // add quantum cycles
      sprintf(configStr, "Quantum Cycles                  : %d\n", 
                  configPtr->quantumCycles);

      headPtr = addStrNode(configStr, headPtr);

      // add memory available 
      sprintf(configStr, "Memory Available (KB)           : %d\n", 
                  configPtr->memAvailable);

      headPtr = addStrNode(configStr, headPtr);

      // add processor cycle rate 
      sprintf(configStr, "Processor Cycle Rate (ms/cycle) : %d\n", 
                   configPtr->procCycleRate);

      headPtr = addStrNode(configStr, headPtr);

      // add io cycle rate 
      sprintf(configStr, "I/O Cycle Rate (ms/cycle)       : %d\n\n", 
                   configPtr->ioCycleRate);

      headPtr = addStrNode(configStr, headPtr);

      // add header 
         // function: addStrNode
      headPtr = addStrNode(headerString, headPtr);
   }

   // if the output is to screen or both
   if (compareString(outputType, "Monitor") == STR_EQ || 
         compareString(outputType, "Both") == STR_EQ)
   {
      // print header 
         // function: printf
      printf("Simulator Run\n");
      printf("-------------\n\n");
   }

   // if the output is just to file 
   if (compareString(outputType, "File") == STR_EQ)
   {
      // print statement 
      printf("Printing To File:\n");
   }

   // print simulator lead line
      // function: printSimLine
   printSimLine("OS", "start", outputType, NEW_STATE, NEW_STATE, NULL, headPtr, 
                   NOT_MEM, NOT_MEM, NOT_START_OR_END, "NEITHER", "NOTMEM");

   // get the processes from the metadata ops 
      // function: getProcesses 
   processes = getProcesses(metaDataMstrPtr, configPtr);

   // get the first process 
      // function: getNextProcess
   tempProcess = processes[processIndex];

   // for each process 
   while (tempProcess.pid >= 0)
   {
      // set the state to ready 
      processes[processIndex].state = READY_STATE;

      // print state update 
         // function: printSimLine
      printSimLine("OS", "stateSwitch", outputType, NEW_STATE, READY_STATE, &tempProcess, 
                     headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, "NEITHER", "NOTMEM");
      
      // update process index 
      processIndex++;

      // update process
      tempProcess = processes[processIndex];
   }    

   // initialize memory 
      // function: processMemoryRequest 
   processMemoryRequest(NULL, &memHeadPtr, "initialize", configPtr, tempProcess);

   // reset process index to 0
   processIndex = 0;
 
   // select the first process 
   tempProcess = getNextProcess(processes, &processIndex, configPtr);

   // move it to running 
   tempProcess.state = RUNNING_STATE;

   // print selection 
      // function: printSimLine
   printSimLine("OS", "processSelect", outputType, NEW_STATE, NEW_STATE, &tempProcess, 
                   headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, "NEITHER", "NOTMEM");

   // print movement
      // function: printSimLine
   printSimLine("OS", "stateSwitch", outputType, READY_STATE, RUNNING_STATE, &tempProcess, 
                  headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, "NEITHER", "NOTMEM");

   // if the output is to screen or both
   if (compareString(outputType, "Monitor") == STR_EQ || 
         compareString(outputType, "Both") == STR_EQ)
   {
      // print an endline 
         // function: printf
      printf("\n");
   }

   // if the output is to file or both
   if (compareString(outputType, "File") == STR_EQ || 
         compareString(outputType, "Both") == STR_EQ)
   {
      // add an endline to string linked list 
         // function: addStrNode
      addStrNode("\n", headPtr);
   }

   // while there are still processes to process
   while (tempProcess.pid >= 0) 
   {
      // assume process will not segfault 
      segFaultFlag = false;

      // set working pointer to start of process 
      wkgPtr = getOpCode(tempProcess);

      // reset flag for interupt 
      notInterrupted = true;

      // while not at app end or bad process
      while((wkgPtr != NULL && wkgPtr -> nextNode != NULL 
              && compareString(wkgPtr->nextNode->strArg1, "end") != STR_EQ)
              && notInterrupted)
      {
         // get next op code 
            // function: getOpCode
         wkgPtr = getOpCode(tempProcess);

         // reset interrupted flag 
         notInterrupted = true; 

         // if the operation is not memory 
         if (compareString(wkgPtr-> command, "mem") != STR_EQ)
         {
            // print the op code 
               // function: printSimLine
            printSimLine("Process", wkgPtr->strArg1, outputType, NEW_STATE, NEW_STATE, 
                           &tempProcess, headPtr, NOT_MEM, NOT_MEM, START, 
                              wkgPtr->inOutArg, "NOTMEM");

            // if process is io
            if (compareString(wkgPtr->inOutArg, "in") == STR_EQ || 
                  compareString(wkgPtr->inOutArg, "out") == STR_EQ)
            {
               // calc time 
               timeToRun = configPtr->ioCycleRate * wkgPtr->intArg2;

               // if the scheduler is preemptive 
               if (preemptiveStrategy)
               {    
                  // subtract time from the runtime 
                  processes[processIndex].estTime -= timeToRun;  
       
                  // convert time to run into seconds 
                  timeToRunSeconds = timeToRun / MS_TO_SECONDS; 

                  // get the current time 
                     // function: accessTimer
                  accessTimer(LAP_TIMER, currentTime); 

                  // convert current time to int 
                     // function: timeStrToFloat
                  currentTimeFloat = timeStrToFloat(currentTime);

                  // add time to run to current time 
                  estFinalTime = timeToRunSeconds + currentTimeFloat; 

                  // put into PCB
                  processes[processIndex].estFinishTime = estFinalTime;

                  // set PCB new working pointer to be current pointer 
                  processes[processIndex].currentOpCode = wkgPtr;

                  // set flag to false to switch to new process 
                  notInterrupted = false;   

                  // block the process until it is complete 
                  processes[processIndex].state = BLOCKED_STATE;

                  // set the number of cycles to 0
                  wkgPtr -> intArg2 = 0;

                  // print blocking of process
                     // function: printSimLine
                  printSimLine("OS", "blockForIO", outputType, NEW_STATE, NEW_STATE, 
                                 &tempProcess, headPtr, NOT_MEM, NOT_MEM, START, 
			            wkgPtr->inOutArg, "NOTMEM");

                  // print block state change 
                     // function: printSimLine
                  printSimLine("OS", "stateSwitch", outputType, RUNNING_STATE, 
                                BLOCKED_STATE, &tempProcess, headPtr, 
                                 NOT_MEM, NOT_MEM, START, 
			            wkgPtr->inOutArg, "NOTMEM");

                  // set working pointer to null to signal stop
                  wkgPtr = NULL;


               }

               // otherwise, non-preemptive 
               else
               {
                  // run timer as a thread 
                     // function: pthread_create
                  pthread_create(&runningTimeThread, NULL, runTimerThread, (void *)timeToRun); 
               
                  // join the thread
                     // function: pthread_join 
                  pthread_join(runningTimeThread, NULL); 
               }
               
            }
         
            // otherwise, process is processor based
            else 
            {
               // calc time  
               timeToRun = configPtr->procCycleRate * wkgPtr->intArg2;

               // if the scheduler is preemptive 
               if (preemptiveStrategy)
               {
                  // reset number of cycles 
                  numCycles = 0;

                  // reset time ran 
                  timeRan = 0;  

                  // while I still have cycles, I have not quantum timed out, and
                  // no interupts
                  while (numCycles < wkgPtr -> intArg2 
                          && numCycles < configPtr -> procCycleRate 
                           && interruptMgr("read", &processes))
                  {

                     // run timer as a function for 1 cycle
                        // function: runTimer
                     runTimer(configPtr -> procCycleRate);

                     // add time to running total
                     timeRan += configPtr -> procCycleRate;  

                     // up cycles ran 
                     numCycles++;
                  }

                  // if I was interrupted 
                  if (!(numCycles < wkgPtr -> intArg2 
                         || numCycles < configPtr -> procCycleRate))
                  {
                     // set flag
                     notInterrupted = false;                  
                  }

                  // subtract ran time from process total
                  processes[processIndex].estTime -= timeRan;

                  // subtract cycle time from total 
                  wkgPtr -> intArg2 -= numCycles;
               }

               // otherwise, non-preemptive
               else 
               {
                  // run timer 
                     // function: runTimer
                  runTimer(timeToRun);

                  // subtract time from total time 
                  processes[processIndex].estTime -= timeToRun;
               }   

            }

            // if I was not interrupted 
            if (notInterrupted)
            {
               // print end of op code       
               printSimLine("Process", wkgPtr->strArg1, outputType, NEW_STATE, 
                            NEW_STATE, &tempProcess, headPtr, NOT_MEM, 
                             NOT_MEM, END, wkgPtr->inOutArg, "NOTMEM");
            
            }


         }

         // otherwise, is memory 
         else
         {
            // print request line 
            printSimLine("Process", wkgPtr->command, outputType, NEW_STATE, NEW_STATE, 
                           &tempProcess, headPtr, wkgPtr->intArg2, wkgPtr->intArg3, 
                             NOT_START_OR_END, "in", wkgPtr->strArg1);

            // process memory request
               // function: processMemoryRequest
            goodResult = processMemoryRequest(wkgPtr, &memHeadPtr, 
                                               wkgPtr->strArg1, configPtr, 
                                                tempProcess); 

            // if bad memory request 
            if (!goodResult)
            {
               // print failed mem access request 
                  // function: printSimLine
               printSimLine("Process", wkgPtr->command, outputType, NEW_STATE, NEW_STATE, 
                           &tempProcess, headPtr, wkgPtr->intArg2, wkgPtr->intArg3, 
                             END, "NEITHER", wkgPtr->strArg1);


               // print segmentation fault 
                  // function: printSimLine
               printSimLine("OS", "segfault", outputType, NEW_STATE, NEW_STATE, 
                              &tempProcess, headPtr, NOT_MEM, NOT_MEM, 
                               NOT_START_OR_END, "NEITHER", "NOTMEM");

               // set segfault flag to true, failure 
               segFaultFlag = true; 

               // clear the process memory 
                  // function: processMemoryRequest
               processMemoryRequest(wkgPtr, &memHeadPtr, "processClear", 
                                               configPtr, tempProcess);

               // move current process to exit 
               processes[processIndex].state = EXIT_STATE;

               // process next process 
                  // function: prepareNextProcess
               tempProcess = prepareNextProcess(processes, &processIndex, outputType, 
                                                  headPtr, tempProcess, configPtr,
                                                   segFaultFlag, memHeadPtr, notInterrupted);

               // if the returned process exists                
               if (tempProcess.pid >= 0)
               {
                  // rebind working pointer 
                  wkgPtr = tempProcess.appStartPtr;
               }

               // otherwise, no process 
               else
               {
                  // set pointer to null
                  wkgPtr = NULL;
               }

               // assume next process does not segfault 
               segFaultFlag = false;

            }

            // otherwise, good memory request 
            else
            {
               // print good memory request 
                  // function: printSimLine
               printSimLine("Process", wkgPtr->command, outputType, NEW_STATE, NEW_STATE, 
                           &tempProcess, headPtr, wkgPtr->intArg2, wkgPtr->intArg3, 
                             START, "NEITHER", wkgPtr->strArg1);
            }

         }

         // if working pointer exists 
         if (wkgPtr != NULL)
         {
            // set the number of cycles remaining in the opcode to 0
            wkgPtr -> intArg2 = 0;
         }

         // set current pointer to working pointer 
         tempProcess.currentOpCode = wkgPtr;

      }

      // set seg fault flag to false, success of process
      segFaultFlag = false; 

      // if preemptive strategy 
      if (preemptiveStrategy)
      {
         // call interupt manager to see if any processes are done 
            // function: interruptMgr
         interruptMgr("process", &processes);
      }

      // if the last process existed 
      if (tempProcess.pid >= 0)
      {
         // process next process 
            // function: prepareNextProcess
         tempProcess = prepareNextProcess(processes, &processIndex, outputType, 
                                            headPtr, tempProcess, configPtr,
                                             segFaultFlag, memHeadPtr, notInterrupted);
      }

   }

   // print end of system 
      // function: printSimLine
   printSimLine("OS", "sysStop", outputType, NEW_STATE, NEW_STATE, NULL, 
                 headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, "NEITHER", "NOTMEM");

   // clear the memory
      // function: processMemoryRequest 
   processMemoryRequest(wkgPtr, &memHeadPtr, "clearAllMem", configPtr, 
                         tempProcess);

   // print end of simulation 
      // function: printSimLine
   printSimLine("OS", "simStop", outputType, NEW_STATE, NEW_STATE, NULL, 
                 headPtr, NOT_MEM, NOT_MEM, NOT_START_OR_END, "NEITHER", "NOTMEM");


   // end thread for time

   // if the log file is to be written 
   if (compareString(outputType, "File") == STR_EQ || 
         compareString(outputType, "Both") == STR_EQ)
   {
      // get end of file string 
         // function: sprintf
      sprintf(endOfFileStr, "\nEnd of Simulation - Complete\n"
                            "============================\n\n");

      // add the end of file stuff to the file 
         // function: addStrNode
      addStrNode(endOfFileStr, headPtr);

      // write the linked list to file
         // function: strLinkedListToFile
      strLinkedListToFile(headPtr, configPtr->logToFileName);
   }   

   // clear the linked list 
      // function: clearStrLinkedList
   headPtr = clearStrLinkedList(headPtr);

   // free the processes array
      // function: free
   free(processes);





}

void strLinkedListToFile( StrLinkedListNode *headPtr, char *fileName)
{
   // declare functions/variables 
   StrLinkedListNode *wkgPtr = headPtr;
   FILE *outputFile; 

   // open file
      // function: fopen
   outputFile = fopen(fileName, "w");

   // while not at end of list 
   while (wkgPtr != NULL)
   {
      // print line to file 
         // function: fprintf
      fprintf(outputFile, "%s", wkgPtr->lineStr);

      // move pointer 
      wkgPtr = wkgPtr->nextNode;
   }

   // close file 
      // function: fclose
   fclose(outputFile);

}

float timeStrToFloat( char *timeStr)
{
   // initialize variables 
   int timeStrLen = 0;
   int exponentPower = 0;
   float multiplier = 1;
   int strIndex = 0;
   int timeStrVal = 0;
   float totalTimeVal = 0;

   // get the length of the time string 
      // function: getStringLength
   timeStrLen = getStringLength(timeStr);

   // take the length of the substring and subtract 7 for decimal and 6 decimal vals
   exponentPower = timeStrLen - LEN_DEC_AND_DEC_POINT;

   // while exponent power is positive
   while (exponentPower > 0)
   {
      // take multiplier and multiply by 10
      multiplier *= 10;

      // take exponent power and subtract 1
      exponentPower -= 1;
   }
   // for every value in the string 
   for (strIndex = 0; strIndex < timeStrLen; strIndex++)
   {
      // if it is a digit 
      if (timeStr[strIndex] >= '0' && timeStr[strIndex] <= '9')
      {
         // convert char number to int 
         timeStrVal = timeStr[strIndex] - '0';

         // multiply by multiplier and add to return 
         totalTimeVal += timeStrVal * multiplier;

      } 

      // divide multiplier by 10 to move to next item 
      multiplier /= 10;

   }

   // return time int 
   return totalTimeVal;
}
