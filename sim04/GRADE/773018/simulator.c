#include "simulator.h"

/* NOTE THIS WILL ONLY COMPILE ON A LINUX MACHINE
So if you try to compile it on a windows or mac 
machine errors will occur due to the header file 
known as <pthread.h> which is only present on linux. 
This program should and does function when present on a linux machine.
Another Note: This function currently only does FCFS-N and SJF-N */


/* Another NOTE: If you have any questions about functions
check the simulator.h for quick descriptions!*/


/* THE RUNSIM MASTER LOOP */

void runSim(opcode *metadata, config *configData)
    {

    //VARIABLES AND PCB SET UP   
        controlblock *processBlocks;
        memblock *memoryBlock = (memblock *)malloc(sizeof(memblock)); 
        int processCount;
        int simDisplay, memDisp, memArg;
        int PCBIndex;
        int currentProcess;
        int prehemFlag[2];
        int currentOpcode;
        int processIndex;
        char currentTime[TIME_LENGTH]; // Number Pulled Directly from Timer
        float currentTimeF;
        bool memFlag = true;
        bool interrupt = false; 
        char tempStr[ARRAY_CAP];
        bool endFlag;

        LogData *logstrings = NULL;

        //malloc out data
        processBlocks = (controlblock *) malloc(ARRAY_CAP * sizeof(controlblock));

        //SET UP THE PCBS
        processCount = setUpPCB(metadata, configData, processBlocks);

        //CHECK CONFIG FOR WHAT OPERATION
        simDisplay = configFlag(configData);

        // SET UP INTERRUPTS
	
	    interruptcollection interruptList[5];

        //Set Mem Display
	    memoryBlock->maxMem = configData->memAval;
        memoryBlock->remainingMem = configData->memAval;
	    memoryBlock->physicalMem = NULL;
	    memoryBlock->logicalMem = NULL;
        if (compareStr(configData->memoryDisp, "On") == ZERO)
        {
            memDisp = MONITOR_P;
        }

    // SIM BEGINS
        //ZERO OUT TIMER
        accessTimer(ZERO_TIMER, currentTime);
       
        //Print out Opening Statement
        manageOutput(&logstrings,"\n=========================\n", simDisplay);
        manageOutput(&logstrings,"Begin Simulation\n\n", simDisplay);
        sprintf(tempStr,"%s, OS: Simulator Start\n", currentTime);
        manageOutput(&logstrings, tempStr, simDisplay);

    // Set Up Original Process, set the states
        for (PCBIndex = 0; PCBIndex < processCount; PCBIndex++)
            {
                // Sets the state
                accessTimer(LAP_TIMER, currentTime);
                sprintf(tempStr, "%s, OS: Process %d set to READY state from NEW state\n",
                        currentTime, processBlocks[PCBIndex].processID);
                processBlocks[PCBIndex].state = READY;
                manageOutput(&logstrings, tempStr, simDisplay);
            }
    // Intialize Memory Block
        runMemOp(processBlocks[ZERO].processList[ZERO], memoryBlock,
		logstrings, DUMMY_VAL, MEM_INTIAL, simDisplay, memDisp);

    // While EndFlag is false
        while (!endFlag)
            {
                // Get Next Process 
		        interrupt = false;
                currentProcess =  getNextProcess(configData, processBlocks, processCount, logstrings,
		        simDisplay, prehemFlag);

                // If all statements blocked, call Idle Manager
                if (currentProcess == DUMMY_VAL && endFlag != true)
                {
                    currentTimeF = accessTimer(LAP_TIMER, currentTime);
                    currentProcess = idleManage(currentTimeF, interruptList, processCount, 
                    &currentProcess, configData->cycleRateIO, logstrings, simDisplay);
                    accessTimer(LAP_TIMER, currentTime);
                    sprintf(tempStr,"\n%s, OS: Interrupted by Process %d\n",
                    currentTime, processBlocks[currentProcess].processID);
                    manageOutput(&logstrings, tempStr, simDisplay);

                    accessTimer(LAP_TIMER, currentTime);
                    sprintf(tempStr,"%s, OS: Process %d set from BLOCKED to READY\n\n",
                        currentTime, processBlocks[currentProcess].processID);
                    manageOutput(&logstrings, tempStr, simDisplay);
                    processBlocks[currentProcess].state = READY;
                }

                // Opening Statement
                accessTimer(LAP_TIMER, currentTime);
                sprintf(tempStr,"%s, OS: Process %d selected with %d ms remaining\n",
                    currentTime, processBlocks[currentProcess].processID, 
                        processBlocks[currentProcess].timeRemaining);
                manageOutput(&logstrings, tempStr, simDisplay);
		
                //Changes state
                accessTimer(LAP_TIMER, currentTime);
                sprintf(tempStr,"%s, OS: Process %d set from READY to RUNNING\n\n",
                        currentTime, processBlocks[currentProcess].processID);
                manageOutput(&logstrings, tempStr, simDisplay);
                processBlocks[currentProcess].state = RUNNING;


                // Loop thru Process Codes
                for(processIndex = 0; processIndex < 
                        processBlocks[currentProcess].processSize &&
                        memFlag == true && interrupt == false; processIndex++)
                {
                    // GET NEXT OP CODE
                    currentOpcode = getNextOpcode(processBlocks[currentProcess].processList, processBlocks[currentProcess].processSize);
                    switch(processBlocks[currentProcess].processList[currentOpcode].processFlag)
                    {
                        case IO: // IO Process
                            interrupt = runIOop(processBlocks[currentProcess].processList[currentOpcode],
                                    logstrings, interruptList, currentProcess, simDisplay, prehemFlag[ZERO]);

                            // Update the Time Remaining
			                updateTimeRem(processBlocks, currentProcess, currentOpcode);
                            break;

                        case PROCESS: // CPU process
                            runCPUop(processBlocks[currentProcess].processList[currentOpcode],
                                    logstrings, currentProcess, simDisplay, prehemFlag[ZERO], configData->cycleRateP, 
                                    configData->quanTime);

                            // Update the Time Remaining
			                updateTimeRem(processBlocks, currentProcess, currentOpcode);
                            break;

                        case MEM: // Memory Process
                            memArg = checkMemArg(processBlocks[currentProcess].processList[currentOpcode]);
                            memFlag = runMemOp(processBlocks[currentProcess].processList[currentOpcode],
                                    memoryBlock, logstrings, currentProcess, 
                                    memArg, simDisplay, memDisp);
			                updateTimeRem(processBlocks, currentProcess, currentOpcode);
                            break;
                    }

                    // INTERRUPT
                    
                }

                // Set State After Process Ends
                //PRINT ENDLINES
                accessTimer(LAP_TIMER, currentTime);
                if (interrupt) 
                {
                    accessTimer(LAP_TIMER, currentTime);
                    sprintf(tempStr, "%s, OS: Process %d set to BLOCKED\n",
                        currentTime, processBlocks[currentProcess].processID); 
                    manageOutput(&logstrings, tempStr, simDisplay);
                    processBlocks[currentProcess].state = BLOCKED;
                }
                else 
                {
                    if (memFlag)
                    {
                        sprintf(tempStr, "\n\n%s, OS: Process %d ended\n",
                            currentTime, processBlocks[currentProcess].processID);
                    }
                    else // IF A SEGFAULT OCCURED 
                    {
                        sprintf(tempStr, "\n\n%s, OS: Segmentation fault, Process %d ended\n",
                            currentTime, processBlocks[currentProcess].processID);                    
                        memFlag = true; // RESET MEM FLAG
                        // RESOLVE INTERRUPTS UNDER CURRENT PROCESS

                    }
                    //Sets proper string
                    manageOutput(&logstrings, tempStr, simDisplay);

                    // CLEAR MEMORY
                    runMemOp(processBlocks[currentProcess].processList[processIndex],
                    memoryBlock, logstrings, currentProcess, CLEAR, simDisplay, memDisp);
                    
                    // FINAL PRINT
                    accessTimer(LAP_TIMER, currentTime);
                    sprintf(tempStr, "%s, OS: Process %d set to EXIT\n",
                            currentTime, processBlocks[currentProcess].processID); 
                    manageOutput(&logstrings, tempStr, simDisplay);
                    processBlocks[currentProcess].state = EXIT;
                if (interruptManage(interruptList, currentTimeF, processCount, &currentProcess, CHECK))
                    {
                        accessTimer(LAP_TIMER, currentTime);
                        sprintf(tempStr,"\n%s, OS: Interrupted by Process %d\n",
                        currentTime, processBlocks[currentProcess].processID);
                        manageOutput(&logstrings, tempStr, simDisplay);

                        accessTimer(LAP_TIMER, currentTime);
                        sprintf(tempStr,"%s, OS: Process %d set from BLOCKED to READY\n\n",
                            currentTime, processBlocks[currentProcess].processID);
                        manageOutput(&logstrings, tempStr, simDisplay);
                        processBlocks[currentProcess].state = READY;   
                    }
		// CHECK FOR END
                endFlag = checkforEnd(processBlocks, processCount);

                }

            }

    // RESOLVE ALL INTERUPTS

    // After Loop. End sim   
            accessTimer(LAP_TIMER, currentTime);
            sprintf(tempStr, "%s, OS: System stop\n", currentTime);
            manageOutput(&logstrings, tempStr, simDisplay);


            accessTimer(LAP_TIMER, currentTime);
            sprintf(tempStr, "%s, OS: Simulation end\n\n", currentTime);
            manageOutput(&logstrings, tempStr, simDisplay);

            accessTimer(STOP_TIMER, currentTime);
            manageOutput(&logstrings,"End Simulation - Complete\n", simDisplay);
            manageOutput(&logstrings,"=========================\n", simDisplay);
    // After Sim is over, check to write to logFile
        if (simDisplay == FILE_P || simDisplay == BOTH_P)
        {
            //Get file Path and create file
            FILE *logFile = fopen(configData->logFile, "w");
            writeToLogFile(logFile, logstrings, configData);
        }
    }


/* BASE SUPPORT FUNCTIONS FOR THE MASTER LOOP */

bool checkforEnd(controlblock *processBlocks, int processCount)
    {
        int index;
        for (index = 0; index < processCount; index++)
            {
                if( processBlocks[index].state != EXIT )
                {
                    return false;
                }
            }
        return true;
    }

void manageOutput(LogData **logStrings, char *currentStr, int displayFlag)
    {
        //If Monitor or Both, print string
        if (displayFlag == MONITOR_P || displayFlag == BOTH_P)
        {
            printf("%s", currentStr);
        }

        //If File or Both, Store String
        if (displayFlag == FILE_P || displayFlag == BOTH_P)
        {
            *logStrings = addLine(*logStrings, currentStr);
        }

    }
// Run Mem 
bool runMemOp(processblock currentOp, memblock *memoryBlock, LogData *logStrings, int processID, int memCode, int displayFlag, int memDisp)
    {
        char currentTime[TIME_LENGTH]; // Number Pulled Directly from Timer
        char tempStr[ARRAY_CAP];
        //Check If INTIAL 
        if (memCode == MEM_INTIAL)
        {
            //Intialize Memory
            addMemBlock(memoryBlock, ZERO, memoryBlock->maxMem);
	        printMem(memoryBlock, processID, MEM_INTIAL, true, memDisp);
            //Return True
            return true;        
        }

        // SWITCH CASE FOR ALL MEM CODES

        switch( memCode )
        {
            case ALLOCATE: // Allocates Memory
                //Start String
                accessTimer(LAP_TIMER, currentTime);    
                sprintf(tempStr,"%s, Process: %d, mem allocate request (%d, %d)\n", 
                currentTime, processID, currentOp.memBlock[START],
                currentOp.memBlock[END] + 1);   
                manageOutput(&logStrings, tempStr, displayFlag); 

                //get next time
                accessTimer(LAP_TIMER, currentTime);    
                // Check if Allocation Works
                if (allocateMem(memoryBlock, currentOp.memBlock[START], currentOp.memBlock[END]))
                {
                    //PRINTING
                    printMem(memoryBlock, processID, ALLOCATE, true, memDisp);
                    sprintf(tempStr,"%s, Process: %d, successful mem allocate request\n", 
                    currentTime, processID);
                    manageOutput(&logStrings, tempStr, displayFlag); 
                    return true;
                }
                else
                {
                    // PRINTING
                    printMem(memoryBlock, processID, ALLOCATE, false, memDisp);
                    sprintf(tempStr,"%s, Process: %d, failed mem allocate request\n", 
                    currentTime, processID);
                    manageOutput(&logStrings, tempStr, displayFlag);                    
                    return false;
                }
                break;

            case ACCESS: // Checks for Access
                //Start String
                accessTimer(LAP_TIMER, currentTime);    
                sprintf(tempStr,"%s, Process: %d, mem access request (%d, %d)\n", 
                currentTime, processID, currentOp.memBlock[START],
                currentOp.memBlock[END] + 1);   
                manageOutput(&logStrings, tempStr, displayFlag); 

                // GET END TIME
                accessTimer(LAP_TIMER, currentTime);    

                if (accessMem(memoryBlock, currentOp.memBlock[START], currentOp.memBlock[END]))
                {
                    // PRINTING
                    printMem(memoryBlock, processID, ACCESS, true, memDisp);
                    sprintf(tempStr,"%s, Process: %d, successful mem access request\n", 
                    currentTime, processID);
                    manageOutput(&logStrings, tempStr, displayFlag); 
                    return true;
                }
                else
                {
                    // PRINTING
                    printMem(memoryBlock, processID, ACCESS, false, memDisp);
                    sprintf(tempStr,"%s, Process: %d, failed mem access request\n", 
                    currentTime, processID);
                    manageOutput(&logStrings, tempStr, displayFlag); 
                    return false;
                }
                break;

            case CLEAR: // Clears list
                clearMem(memoryBlock);
		        printMem(memoryBlock, processID, CLEAR, true, memDisp);
                return true;
                break;
        }

        return false;
    }

// Run IO
bool runIOop(processblock currentOp, LogData *logStrings, interruptcollection *interruptList, int processID, int displayFlag, int prehemFlag)
    {
        //Variables
        pthread_t ioThread;
        char currentTime[TIME_LENGTH]; // Number Pulled Directly from Timer
        char tempStr[ARRAY_CAP];
        char IOstr[ARRAY_CAP];
        float timeFloat; 

        //Check either Input or Ouput
        if (currentOp.IOFlag == IN)
            {
                copyStr(IOstr, "input");
            }
        else
            {
                copyStr(IOstr, "output");
            }
        
        //Get Start Time
        timeFloat = accessTimer(LAP_TIMER, currentTime);    
        sprintf(tempStr,"%s, Process: %d,%s %s operation start\n", 
                currentTime, processID, currentOp.processName, IOstr);   
        manageOutput(&logStrings, tempStr, displayFlag);
        // Threads

        int time = currentOp.time;
        if ( prehemFlag == NON ) // IF NON - PRE
        {

        //Run Timer and Start Thread
        pthread_create(&ioThread, NULL, runTimer, (void *) &time);

	    //Join Thread
	    pthread_join(ioThread, NULL);  

        //Get End Time
        accessTimer(LAP_TIMER, currentTime);    
        sprintf(tempStr,"%s, Process: %d,%s %s operation end\n", 
                currentTime, processID, currentOp.processName, IOstr);   
        manageOutput(&logStrings, tempStr, displayFlag);  
        }

        else // IF PRE
        {
            timeFloat = timeFloat + (time / 100);

            // SET THE INTERRUPT
            interruptList[processID].endTime = timeFloat;
            interruptList[processID].processID = processID;
            interruptList[processID].currentOp = currentOp;

            accessTimer(LAP_TIMER, currentTime);    
            sprintf(tempStr,"%s, Process: %d blocked for %s operation\n", 
                currentTime, processID, currentOp.processName);   
            manageOutput(&logStrings, tempStr, displayFlag); 
            return true;
        }

        return false;
    }

// Run CPU
void runCPUop(processblock currentOp, LogData *logStrings, int processID, int displayFlag, int prehemFlag, int cycle, int quantime)
    {
        //Variables
        char currentTime[TIME_LENGTH]; // Number Pulled Directly from Timer
        char tempStr[ARRAY_CAP];
        int time = currentOp.time;

        //Get Start Time
        accessTimer(LAP_TIMER, currentTime);    
        sprintf(tempStr,"%s, Process: %d, cpu process operation start\n", 
                currentTime, processID);   
        manageOutput(&logStrings, tempStr, displayFlag);

        if (prehemFlag == NON)
        {

        //Run Timer
        runTimer((void *) &time);
        }

        else 
        {

            while ( quantime > ZERO && currentOp.time > ZERO)
            {
                //Run Timer
                runTimer((void *) &cycle);
                currentOp.time -= cycle;
                quantime--;
            }
            // Check whether its finished or not
            if ( currentOp.time > ZERO)
            {
                accessTimer(LAP_TIMER, currentTime);    
                sprintf(tempStr,"%s, OS: Process %d quantum time out, cpu process operation end\n", 
                currentTime, processID);   
                manageOutput(&logStrings, tempStr, displayFlag);  
            }

        }
        //Get End Time
        accessTimer(LAP_TIMER, currentTime);    
        sprintf(tempStr,"%s, Process: %d, cpu process operation end\n", 
                currentTime, processID);   
        manageOutput(&logStrings, tempStr, displayFlag);
    }

// Get Next Process
int getNextProcess(config *configData, controlblock *processBlocks, int processCount, LogData *logStrings, int simDisplay, int *prehemFlag)
    {
        int index = 0;
        int result = DUMMY_VAL;
        int currentSmallestTime;
        int currentID = DUMMY_VAL;
        char CPUcode[FIVE][ARRAY_CAP] = {"FCFS-N","SJF-N","SRTF-P", "FCFS-P", "RR-P"};

        //Check for  CPU code
        while (result != ZERO && index < FIVE)
        {
            result = compareStr(CPUcode[index], configData->CPUSS);
            index++;
        }
  
	    index--; // Reset the Index;

        // Switch Case for all Process
        switch(index)
            {
                case FCFS_N: // FCFS - Return Smallest ID that isn't EXIT
                    for (index = 0; index < processCount; index++)
                    {
                        if (processBlocks[index].state != EXIT)
                        {
                            prehemFlag[ZERO] = NON;
                            return processBlocks[index].processID;
                        }
                    }
                    break;
                case SJF_N: // SJF - Return Smallest Time Remaining that isn't EXIT 
                    currentSmallestTime = MAX_VAL;
                    for (index = 0; index < processCount; index++)
                    {                        
                        if (processBlocks[index].state != EXIT && processBlocks[index].timeRemaining < currentSmallestTime)
                        {
                            currentSmallestTime = processBlocks[index].timeRemaining;
                            currentID = processBlocks[index].processID;
                        }
                    }
                    prehemFlag[ZERO] = NON;
                    return currentID; 
                    break;
                case SRTF_P: // SRTF - RETURNS SHORTEST TIME REM That isn't blocked or exit
                    currentSmallestTime = MAX_VAL;
                    for (index = 0; index < processCount + 1; index++)
                    {                        
                        if (processBlocks[index].state != EXIT && processBlocks[index].state != BLOCKED
                         && processBlocks[index].timeRemaining < currentSmallestTime &&
			     processBlocks[index].timeRemaining > ZERO)
                        {
                            currentSmallestTime = processBlocks[index].timeRemaining;
                            currentID = processBlocks[index].processID;
                        }
                    }
                    prehemFlag[ZERO] = PRE;
                    return currentID; 
                    break;
                case FCFS_P: // FCFSP - Temp Return of just smallest ID that isn't EXIT
                    for (index = 0; index < processCount; index++)
                    {
                        if (processBlocks[index].state != EXIT && processBlocks[index].state != BLOCKED &&
			     processBlocks[index].timeRemaining > ZERO)
                        {
                            prehemFlag[ZERO] = PRE;
                            return processBlocks[index].processID;
                        }
                    }
                    break;
                case RR_P: // RR  - Temp return of just smallest ID that isn't EXIT          
                    for (index = 0; index < processCount; index++)
                    {
                        if (processBlocks[index].state != EXIT && processBlocks[index].state != BLOCKED &&
			     processBlocks[index].timeRemaining > ZERO)
                        {
                            prehemFlag[ZERO] = PRE;
                            return processBlocks[index].processID;
                        }
                    }
                    break;
            }
        // THIS Is to prevent any compile errors, This should never be reached   
        return DUMMY_VAL;

    }

int getNextOpcode(processblock *currentProcessList, int listSize)
{
    int index;

    for (index = 0; index < listSize; index++)
    {
        if (currentProcessList[index].finishFlag == false)
        {
            return index;
        }
    }

    return DUMMY_VAL;

}

LogData *addLine(LogData *logStrings, char *currentStr)
    {
	//Make new Node
	LogData *newString = (LogData *) malloc(sizeof(LogData));
	LogData *wkPtr = logStrings;
	newString->string = (char *) malloc(ARRAY_CAP);
    
    //Copy String
    copyStr(newString->string, currentStr);
	newString->nextPtr = NULL;

	// Checks for Data
	if (logStrings == NULL)
	{
	    logStrings = newString;
	}
	else
	{
	    while (wkPtr->nextPtr != NULL) 
   	    {
		wkPtr = wkPtr->nextPtr;
	    }
	    wkPtr->nextPtr = newString;
	}
	
	return logStrings;

    }

// Dump to Log File
void writeToLogFile(FILE *logFile, LogData *logStrings, config *configData)
    {
        // DISPLAY TO USER
        printf("\n\nDumping to LogFile ... \n\n");
        //Writing the LogFile header
        fprintf(logFile, "==================================================\n");
        fprintf(logFile, "Simulator Log File Header\n\n");

        //Inserting Config Data
        fprintf(logFile, "File Name                       : %s\n", configData->metaFile);
        fprintf(logFile, "CPU Scheduling                  : %s\n", configData->CPUSS);
        fprintf(logFile, "Quantum Cycles                  : %d\n", configData->quanTime);
        fprintf(logFile, "Memory Available (KB)           : %d\n", configData->memAval);
        fprintf(logFile, "Processor Cycle Rate (ms/cycle) : %d\n", configData->cycleRateP);
        fprintf(logFile, "I/O Cycle Rate (ms/cycle)       : %d\n", configData->cycleRateIO);
        //Loop through Strings

	    LogData *wkPtr = logStrings;
        while (wkPtr != NULL)
            {
                fprintf(logFile, "%s", wkPtr->string);
		wkPtr = wkPtr->nextPtr;
            }

    }

//Update Time Remaining
void updateTimeRem(controlblock *processblocks, int processID, int currentOpCode)
{
    processblocks[processID].timeRemaining -= processblocks[processID].processList[currentOpCode].time;
    
    if (processblocks[processID].processList[currentOpCode].time <= ZERO || 
	processblocks[processID].processList[currentOpCode].processFlag == IO)
    {
        processblocks[processID].processList[currentOpCode].finishFlag = true;
    }   
    processblocks[processID].processSize--; 
}

/* INTERRUPT OPERATIONS - ALL FUNCTIONS INVOLVING INTERRUPTS */

// Interrupt manager
bool interruptManage(interruptcollection *interruptList, float currentTime, int processCount, int *currentProcess, int interCode)
{
    int index;
    // Switch Case
    switch(interCode)
        {
        // Initialize
        case INITIALIZE:
            // Make enough interrupts so there is one for each Process
            for (index = 0; index < processCount; index++)
            {
		interruptList[index].currentOp.processFlag = DUMMY_VAL;
                interruptList[index].endTime = DUMMY_VAL;
                interruptList[index].processID = index;
            }
            break;

        // Check
        case CHECK:
            // Check if Time has gotten past the smallest interrupt
            for (index = 0; index < processCount; index++)
            {
                if ( currentTime > interruptList[index].endTime 
                && interruptList[index].currentOp.processFlag != DUMMY_VAL)
                {
		interruptList[index].currentOp.processFlag = DUMMY_VAL;
                interruptList[index].endTime = DUMMY_VAL;
                interruptList[index].processID = index;

                    (*currentProcess) = index; 
                    return true;
                }
            } 
            break;

        // Resolve
        case RESOLVE:
            // Set Interrupts to -1
            break;
             
        }

        return false;
}

// Idle Manager ( is called in get next process )
int idleManage(float currentTime, interruptcollection *interruptList, int processCount, int *currentProcess, int cycle, LogData *logStrings, int simDisplay)
{
    char tempStr[ARRAY_CAP];
    
    // Check if all Process is blocked
    sprintf(tempStr ,"\n\n %f, OS: CPU idle, all active processes blocked\n", currentTime);   
    manageOutput(&logStrings, tempStr, simDisplay);

    // If blocked, run until Interrupt is true
    while ( !interruptManage(interruptList, currentTime, processCount, currentProcess, CHECK))
    {
        runTimer((void *) &cycle);
        currentTime = accessTimer(LAP_TIMER, tempStr);
    }

    sprintf(tempStr ," %f, CPU interrupt, end idle\n\n", currentTime);   
    manageOutput(&logStrings, tempStr, simDisplay);

    return (*currentProcess);

}
/* MEMORY OPERATIONS - SUPOORT FUNCTIONS FOR MEMORY OPERATIONS */


bool allocateMem(memblock *memoryBlock, int start, int end)
{
    int difference = end - start;
    MemData *wkPtrLog = memoryBlock->logicalMem;

    // CHECK IF THERE IS ENOUGH PHYSICAL MEMORY
    if (difference > memoryBlock->remainingMem)
    {
        return false;
    }

    // Loop through Logical Memory
    while (wkPtrLog != NULL)
    {
        // Check if there are any overlaps
        // Check if the start of the insert is less than the end
        // Check if the end of the insert is greater than the start
        if (start < wkPtrLog->end && end > wkPtrLog->start)
        {
            // return false if there is
            return false;
        }

        wkPtrLog = wkPtrLog->nextPtr;
        
    }

    addMemBlock(memoryBlock, start, end);
    return true;
}

bool accessMem(memblock *memoryBlock, int start, int end)
    {
        MemData *wkPtrLog = memoryBlock->logicalMem;
        // Loop through Logical Memory
	    int difference = start + end;
        while (wkPtrLog->nextPtr != NULL)
        {
            //Check to see if its inside of parameters 
                if (start < wkPtrLog->end && difference > wkPtrLog->start)
                {
                    // return true if there is
                    return true;
                }
                wkPtrLog = wkPtrLog->nextPtr;
        }
        
        return false;
    }

bool clearMem(memblock *memoryBlock)
    {
	    MemData *wkPtrLog = memoryBlock->logicalMem;
        MemData *wkPtrPhy = memoryBlock->physicalMem;

        //Clear Logical Data
        while (wkPtrLog != NULL) 
        {
            MemData *nextNode = wkPtrLog->nextPtr;
            free(wkPtrLog);
            wkPtrLog = nextNode;
        }
        //Set Data to NULL
        memoryBlock->logicalMem = NULL;

        // Clear Physical Data
        while (wkPtrPhy != NULL) 
        {
            MemData *nextNode = wkPtrPhy->nextPtr;
            free(wkPtrPhy);
            wkPtrPhy = nextNode;
        }

        // Set Data to NULL
        memoryBlock->physicalMem = NULL;
        memoryBlock->remainingMem = memoryBlock->maxMem;

        // RESET BLOCKS WITH JUST BASICS
	    addMemBlock(memoryBlock, ZERO, memoryBlock->maxMem);
	
	    return true;
    }

void addMemBlock(memblock *memoryBlock, int start, int end)
{
	//Make new Node
	MemData *newLogical = (MemData *) malloc(sizeof(MemData));
    MemData *newPhysical = (MemData *)malloc(sizeof(MemData));
	MemData *wkPtrLog = memoryBlock->logicalMem;
    MemData *wkPtrPhy = memoryBlock->physicalMem;
    int tempVal;
	

	// Checks for Data
	if (memoryBlock->physicalMem == NULL) // CASE IF NOTHING IS INTITLIZED
	{
	    memoryBlock->physicalMem = (MemData *) malloc(sizeof(MemData));
	    memoryBlock->physicalMem->start = ZERO;
        memoryBlock->physicalMem->end = memoryBlock->maxMem; 
        memoryBlock->physicalMem->nextPtr = NULL;
            
	    memoryBlock->logicalMem = (MemData *) malloc(sizeof(MemData));
        memoryBlock->logicalMem->start = ZERO;
        memoryBlock->logicalMem->end = ZERO;
        memoryBlock->logicalMem->nextPtr = NULL;
	}
	else
	{
        //PREP THE DATA
        newLogical->start = start;
        newLogical->end = start + end;
	    newLogical->nextPtr = NULL;
	    newPhysical->nextPtr = NULL;


        //Loop tp end of List
	    while (wkPtrLog->nextPtr != NULL) 
   	    {
		wkPtrLog = wkPtrLog->nextPtr;
	    }
        // Set New Logical Data
	    wkPtrLog->nextPtr = newLogical;

        while (wkPtrPhy->nextPtr != NULL)
        {
            wkPtrPhy = wkPtrPhy->nextPtr;
        }
	    
        // SET ALL NEW DATA
        tempVal = wkPtrPhy->end;
        wkPtrPhy->end = end + wkPtrPhy->start;
        newPhysical->start = wkPtrPhy->end + 1;
        newPhysical->end = tempVal;
	    newPhysical->nextPtr = NULL;

        wkPtrPhy->nextPtr = newPhysical;
	}
	
}

void printMem(memblock *memoryBlock, int processID, int memCode, bool memFlag, int memDisp)
    {
	    if (memDisp == MONITOR_P) // ONLY PRINTS IF MEM DISP IS ON
	    {
            MemData *wkPtrLog = memoryBlock->logicalMem;
            MemData *wkPtrPhy = memoryBlock->physicalMem;
            // CHECK FLAGS AND PRINT ACCORDINGLY
            printf("--------------------------------------------------\n");

            switch( memCode )
                {
                    case MEM_INTIAL:
                        printf("After memory initialization\n");
                        break;

                    case ALLOCATE:
                        if (memFlag) //Success
                        {
                            printf("After allocate success\n");
                        }
                        else //failure
                        {
                            printf("After allocate overlap failure\n");
                        }
                        break;

                    case ACCESS:
                        if (memFlag) //Success
                        {
                            printf("After access success\n");
                        }
                        else //failure
                        {
                            printf("After access failure\n");
                        }
                        break;

                    case CLEAR: 
                            printf("After clear process %d success\n", processID);
                        break;
                }
            // Print Data
            while ( wkPtrLog->nextPtr != NULL)
                {
                    printf("%d [ Used, P#: %d, %d-%d ] %d\n", wkPtrPhy->start,
                                    processID,
                                                                wkPtrLog->start, 
                                                                wkPtrLog->end,
                                                                wkPtrPhy->end);
                    wkPtrPhy = wkPtrPhy->nextPtr;
            wkPtrLog = wkPtrLog->nextPtr;
                }
            printf("%d [ Open, P#: x, %d-%d ] %d\n", wkPtrPhy->start,
                                                                wkPtrLog->start, 
                                                                wkPtrLog->end,
                                                                wkPtrPhy->end);
            printf("--------------------------------------------------\n"); 
	    }
    }



/* ALL OF THE FUNCTION BELOW ARE RESPONSIBLE FOR PCB SET UP
All of which will only be supports to the actual set up of the sim
for further descriptions please check simulator.h*/


// Set Up PCB and Process and String Array
int setUpPCB(opcode *metadata, config *configData, controlblock *processBlocks)
    {
        int index;
        int processCount = 0;
        bool startFlag = true;
        // runs through all of meta data, sets the start and end points
        for (index = 0; index < metadata->size; index++)
        {
            //CHECK FOR START OF A NEW BLOCK
            if (checkForApp(metadata->metaData[index]))
            {
                //Set process ID
                processBlocks[processCount].processID = processCount;

                //Set Start State
                processBlocks[processCount].state = NEW;
                // Check if its the start
                if(startFlag)
                {
                    //Change to end flag
                    startFlag = false;
                    processBlocks[processCount].startVal = index;
                }
                else
                //set End flag
                {
                processBlocks[processCount].endVal = index;
                startFlag = true;
                processCount++;

                }
            }

        }
        // Another Loop that sets all of the Proccesses

        for (index = 0; index < processCount; index++)
        {
            //sets up the processBlocks and gets the timeTotal
            processBlocks[index].timeRemaining = 
                    setUpProcess(metadata, configData, processBlocks, index);
        }

        return processCount;

    }

//  Run Set process
int setUpProcess(opcode *metadata, config *configData, controlblock *processBlocks, int count)
    {
        //set up data in process
        int index;
        int innerIndex = processBlocks[count].startVal + 1;
        processBlocks[count].processSize = (processBlocks[count].endVal - processBlocks[count].startVal) - 1;
        int timeTotal = 0;

        // Sets up Process list
        processBlocks[count].processList = 
                (processblock *) malloc(processBlocks[count].processSize * sizeof(processblock));
        
        //Runs through the process size and sets minimal data needed for process
        for (index = 0; index < processBlocks[count].processSize; index++, innerIndex++)
        {
            //Checks the State aka IO, MEM or PROCESS
            processBlocks[count].processList[index].processFlag = 
                        checkOp(metadata->metaData[innerIndex]);
	    processBlocks[count].processList[index].finishFlag = false;
            switch(processBlocks[count].processList[index].processFlag)
            {
                case 0: //IO OPERATION
                    //Calcuates time for each process by using the correct cycle rate and arg2
                    processBlocks[count].processList[index].time = 
                        calculateTime(metadata->metaData[innerIndex].arg2, configData->cycleRateIO);
                    //Copies Arg1, which will be used to print the respective string later
                    copyStr(processBlocks[count].processList[index].processName, metadata->metaData[innerIndex].arg1);
                    //Due to it being an IO operation, IO is checked whether its input or output
                    processBlocks[count].processList[index].IOFlag = checkIO(metadata->metaData[innerIndex]);
		            processBlocks[count].processList[index].processFlag = IO;
                    break;
                case 1: // PROCESS OPERATION
                    //Calcuates time for each process by using the correct cycle rate and arg2
                    processBlocks[count].processList[index].time = 
                        calculateTime(metadata->metaData[innerIndex].arg2, configData->cycleRateP);
                    //Copies Arg1, which will be used to print the respective string later
                    copyStr(processBlocks[count].processList[index].processName, metadata->metaData[innerIndex].arg1);
                    //IO flag set to NA because its not an IO operation
                    processBlocks[count].processList[index].IOFlag = NA;
		            processBlocks[count].processList[index].processFlag = PROCESS;
                    break;
                case 2: // MEM OPERATION
                    //Since its a Memory process, Time is set to 0
                    processBlocks[count].processList[index].time = ZERO;
                    //Copies Arg1, which will be used to print the respective string later
                    copyStr(processBlocks[count].processList[index].processName, metadata->metaData[innerIndex].arg1);
                    //IO flag set to NA because its not an IO operation
                    processBlocks[count].processList[index].IOFlag = NA;
                    //Set Memory Blocks
                    processBlocks[count].processList[index].memBlock[0] = metadata->metaData[innerIndex].arg2;
                    processBlocks[count].processList[index].memBlock[1] = metadata->metaData[innerIndex].arg3 - 1;
		            processBlocks[count].processList[index].processFlag = MEM;     
		    //Set Memory Flag
                    if (compareStr(metadata->metaData[innerIndex].arg1, " allocate") == ZERO)
                        {
                            processBlocks[count].processList[index].memFlag = ALLOCATE;
                        }
                    else
                        {
                            processBlocks[count].processList[index].memFlag = ACCESS;  
                        }
                    break;
                    
            }
            //Calculates time total which will return the time remaining for each PCB
            timeTotal += processBlocks[count].processList[index].time;
        }

        return timeTotal;
    }

int checkOp(command opcode)
    {
        int result;
        //Checks to see if IO operations
        result = compareStr(opcode.io, "NA");
        if (result == 0)
        {
            result = compareStr(opcode.cmd, "mem");
            if (result == 0)
            {
                return MEM;
            }
            return PROCESS;
        }
        return IO;
    }

bool checkForApp(command opcode)
    {
        //Checks for app which will represent start or end
        int result;
        result = compareStr(opcode.cmd, "app");
        if (result == 0)
        {
            return true;
        }
        return false;
    }

int checkIO(command opcode)
    {
        //Check for either In or Out
        int result;
        result = compareStr(opcode.io, " in");
        if(result == 0)
        {
            return IN;
        }

        return OUT;
    }

int calculateTime(int cycles, int time)
    {
        //Simple time Calculation
        return (cycles * time);
    }

int configFlag(config *configData)
    {
        int result;
        int index = 0;
        //Represents what the three options are;
        char logTo[FIVE][ARRAY_CAP] = {"Monitor", "File", "Both"};
        while (index < FIVE)
        {
            result = compareStr(logTo[index], configData->logTo);
            if (result == 0)
            {
                //Index in this case will represent the three
                //0 = Monitor
                //1 = File
                //2 = Both
                return index;
            }
            index++;
        }
        // This line is only present to prevent compile errors
        // Normally the Function will not run if the Config File doesn't have
        //The correct logTo operations set up
        return DUMMY_VAL;
    }

int checkMemArg(processblock currentOp)
    {
        if ( compareStr(currentOp.processName, " access") == ZERO)
        {
            return ACCESS;
        }
        return ALLOCATE;
    }
