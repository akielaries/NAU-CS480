#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "constants.h"
#include "simtimer.h"
#include "strutils.h"
#include "types.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// process state struct
typedef enum ProcessState
{
  NEW_STATE,
  READY_STATE,
  RUNNING_STATE,
  BLOCKED_STATE,
  EXIT_STATE
};

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
  struct PCBdata *next_ptr;
  // TODO: struct manipulation?
};

// logging
typedef struct LOGnode
{
  char LOG_out[1024];
  struct LOGnode *next_ptr;
};

/* add lines to log buffer */
LOGnode LOGnode_add(LOGnode local_ptr, char *txt_input);

/* delete lines in log buffer */
LOGnode LOGnode_del(LOGnode *local_ptr);

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

/* runs the simulator log report */
void LOGdump(int trigger, ConfigDataType *config_dataptr, char *txt_input);

/* function that creates a seperate thread of IN/OUT operations */
void IOthread(void *time_elapsed);

/* removes necessary code from opcode list */
//_Bool

/* simulator driver */
void runSim(ConfigDataType *config_dataptr, OpCodeType *meta_data_ptr);

#endif
