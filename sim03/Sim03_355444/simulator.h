#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "StringUtils.h"
#include "constants.h"
#include "simtimer.h"
#include "types.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// process state struct
typedef enum ProcessState
{
  NEW_STATE = 0,
  READY_STATE = 1,
  RUNNING_STATE = 2,
  BLOCKED_STATE = 3,
  EXIT_STATE = 4
} ProcessState;

// memory state struct
typedef enum MemState
{
  MEM_INIT = 0,
  MEM_OPEN = 1,
  MEM_USED = 2
} MemState;

// INTERUPT MANAGEMENT
typedef enum Interrupts
{
  INIT_MNGR = 0,
  INTERRUPT_CHECK = 1,
  SET_IO_START = 2,
  RESOLVE_INTERRUPTS = 3
} Interrupts;

// PCB data
typedef struct PCBdata
{
  int pid;
  int state;
  int time_left;
  double time_start;
  _Bool quant_time;

  struct OpCodeTypeStruct *OCcurr;
  struct OpCodeTypeStruct *OClist;
  struct MEMnode *MEMlist;
  struct PCBdata *next_ptr;
} PCBdata;

// Memory data
typedef struct MEMnode
{
  int physicalStart;
  int physicalStop;
  int memBlockState;
  int processNumber;
  int logicalStart;
  int logicalStop;
  struct MEMnode *next_ptr;
} MEMnode;

// logging
typedef struct LOGnode
{
  char LOG_out[MAX_STR_LEN];
  struct LOGnode *next_ptr;
} LOGnode;

// different triggers for the LOGdump function
typedef enum LOGtrig
{
  INIT_LOG = 0,
  ADD_LOG = 1,
  DUMP_LOG = 2
} LOGtrig;

/* add lines to log buffer */
LOGnode *LOGnode_add(LOGnode *local_ptr, char *txt_input);

/* delete lines in log buffer */
LOGnode *LOGnode_del(LOGnode *local_ptr);

/* runs the simulator log report */
void LOGdump(int trigger, ConfigDataType *config_dataptr, char *txt_input);

/* inserts PCB data into the list */
PCBdata *PCBnode_add(PCBdata *local_ptr, PCBdata *new_ptr);

/* clears PCB data */
PCBdata *PCBnode_del(PCBdata *local_ptr);

/* retrieves PCB PID */
PCBdata *PCBnode_pid(PCBdata *local_ptr, int PCB_PID);

/* FUNCTION TO EXECUTE CREATION OF PROCESS CONTROL BLOCK (PCB) */
PCBdata *PCBcreate(ConfigDataType *config_dataptr, OpCodeType *md_head_ptr);

/* acts as a parser functions for finding next operations stored */
int PCBparse(ConfigDataType *config_dataptr, PCBdata *local_ptr);

/* change state of PCB */
void PCBstate(ConfigDataType *config_dataptr, PCBdata *local_ptr);

/* display PCB data */
void PCBdisplay(PCBdata *head_ptr);

/* function that creates a seperate thread of IN/OUT operations */
void IOthread(OpCodeType *OPC_ptr, PCBdata *PCB_ptr);

/* IOthread pthread function wrapper. acts as driver for IOthreading*/
void *IOthread_wrapper(void *arg);

/* function that creates a seperate thread for processes */
void PROCthread(ConfigDataType *CNF_ptr, OpCodeType *OPC_ptr, PCBdata *PCB_ptr);

/* PROCthread wrapper function */
void *PROCthread_wrapper(void *arg);

void *TIMERthread(void *arg, int type);

/* add node to InterruptMNGR */
OpCodeType *addInterrupt(OpCodeType *local_ptr, OpCodeType *new_ptr);

/*remove OP code from list */
OpCodeType *removeOpCodeNode(OpCodeType *headPtr, OpCodeType *removedPtr);

/* copy OpCode information function */
void OPCcopy(OpCodeType *destination, OpCodeType *source);

/* function to process interrupts */
_Bool interruptMNGR(Interrupts CTRL_ptr, OpCodeType *OPC_ptr, PCBdata *PCB_ptr,
                    ConfigDataType *config_dataptr);

/* add/append nodes to MEMnode data struct */
MEMnode *MEMnode_add(int physStart, int physEnd, int memState, int procNum,
                     int logStart, int logStop);

/* function to recycle memory nodes */
void MEMnode_recycle(MEMnode *tempNode, int memState, int procNum, int phyStart,
                     int phyStop, int logStart, int logStop);

/* memory fix function to reuse memory over skipped blocks */
void MEMrepair(MEMnode *MEM_ptr);

/* displays memory related logging data */
void MEMdisplay(MEMnode *MEM_ptr, char *output_str, _Bool output_flag);

/* driver function for Memory Management Unit handling memory requests */
_Bool MMU(MEMnode *MEM_head, ConfigDataType *config_dataptr,
          OpCodeType *OPC_ptr);

/* function that checks for interrupts and deams CPU idle based on condition */
void CPUidle(ConfigDataType *config_dataptr, PCBdata *PCB_ptr);

/* simulator driver */
void runSim(ConfigDataType *config_dataptr, OpCodeType *meta_data_ptr);

#endif
