#include "metaUtil.h"

enum OP_CODES { IO, PROCESS, MEM };

enum IO_CODES { IN, OUT, NA };

enum STATE_CODES { NEW, READY, RUNNING, EXIT, BLOCKED };

enum SCHEDULE_CODES { FCFS_N, SJF_N, SRTF_P, FCFS_P, RR_P };

enum DISPLAY_CODES { MONITOR_P, FILE_P, BOTH_P };

enum MEM_DISPLAY_CODES { MEM_INTIAL, ALLOCATE, ACCESS, CLEAR };

enum START_END { START, END };

enum INTERRUPT_CODES { INITIALIZE, CHECK, RESOLVE };

enum PREHEMPTIVE_FLAG { NON, PRE };

struct ProcessBlock
    {
        int processFlag;
        int time;
        char processName[ARRAY_CAP];
        int IOFlag;
        int memBlock[2];
        int memFlag;
	bool finishFlag;
    };
    typedef struct ProcessBlock processblock;

struct ControlBlock
    {
        int processID;
        int startVal;
        int endVal;
        int timeRemaining;
        int state;
        int processSize;
        processblock *processList;        
    };
    typedef struct ControlBlock controlblock;

struct InterruptCollection
    {
        int processID;
        processblock currentOp;
        float endTime; 
    };
    typedef struct InterruptCollection interruptcollection;


typedef struct MemData
    {
        int start;
        int end;
        struct MemData *nextPtr;
    } MemData;


struct MemBlock
    {
        struct MemData *logicalMem;
        struct MemData *physicalMem;
        int remainingMem;
        int maxMem;
    };
    typedef struct MemBlock memblock;

typedef struct LogData
    {
        char *string;
        struct LogData *nextPtr;
    } LogData;




// THE MASTER LOOP FUNCTION
void runSim(opcode *metadata, config *configData);


bool checkforEnd(controlblock *processBlocks, int processCount);

//Determines whether to printf and/or store the string in the logstrings
void manageOutput(LogData **logStrings, char *currentStr, int displayFlag);

// Runs the appropriate mem op, if fails it will return false and segfault the process
bool runMemOp(processblock currentOp, memblock *memoryBlock, LogData *logStrings, int processID, int memCode, int displayFlag, int memDisp);

// Runs a Thread with the IO op code
bool runIOop(processblock currentOp, LogData *logStrings, interruptcollection *interruptList, int processID, int displayFlag, int prehemFlag);

// Runs a CPU Op Code
void runCPUop(processblock currentOp, LogData *logStrings, int processID, int displayFlag, int prehemFlag, int cycle, int quantime);

// Gets the next process based off of the schedule
int getNextProcess(config *configData, controlblock *processBlocks, int processCount, LogData *logStrings, int simDisplay, int *prehemFlag);

//Gets next Opcode
int getNextOpcode(processblock *currentProcessList, int listSize);

// Adds Line for the linked list of strings
LogData *addLine(LogData *logStrings, char *currentStr);

//Dumps Data to the Log File
void writeToLogFile(FILE *logFile, LogData *logStrings, config *configData);

//Updating time remaining
void updateTimeRem(controlblock *processblocks, int processID, int currentOpCode);

bool interruptManage(interruptcollection *interruptList, float currentTime, int processCount, int *currentProcess, int interCode);

int idleManage(float currentTime, interruptcollection *interruptList, int processCount, int *currentProcess, int cycle, LogData *logStrings, int simDisplay);


// Loops through and determines whether it can be allocates and calls addMemBlock if it can
bool allocateMem(memblock *memoryBlock, int start, int end);

// Loops through and determines whether the input can be accessed
bool accessMem(memblock *memoryBlock, int start, int end);

// Clears Old Memory Blocks and resets to default
bool clearMem(memblock *memoryBlock);

// Adds new Nodes for the next Memory Block
void addMemBlock(memblock *memoryBlock, int start, int end);

//Prints the right Memory Line
void printMem(memblock *memoryBlock, int processID, int memCode, bool memFlag, int memDisp);





//This sets up the outside PCB's and calls the Process set up
int setUpPCB(opcode *metadata, config *configData, controlblock *processBlocks);

//This counts how many processes are in a block, sets time, a flag to whether its Process, Mem or IO and stores it's argv1
int setUpProcess(opcode *metadata, config *configData, controlblock *processBlocks, int count);

//This Checks the Opcode and returns 0-2 that correspond to IO, MEM and PROCESS
int checkOp(command opcode);

//This checks whether it is the app start or app end
bool checkForApp(command opcode);

//This returns a check for what IO value it has 0-2 correspond to IN, OUT, NA
int checkIO(command opcode);

//Simply calculates the time required
int calculateTime(int cycles, int time);

//Checks for Monitor, Both or File
int configFlag(config *configData);

int checkMemArg(processblock currentOp);