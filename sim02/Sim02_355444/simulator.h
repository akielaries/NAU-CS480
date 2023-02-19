#ifndef SIMULATOR_H
#define SIMULATOR_H

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
} ProcessState;

// PCB data
typedef struct PCBdata
{
    int pid;
    int state;
    int time_left;
    double time_start;
    _Bool quant_time_out;

    struct OpCodeTypeStruct *OCcurr;
    struct OpCodeTypeStruct *OClist;
    struct PCBdata *next_ptr;
    // TODO: struct manipulation?
} PCBdata;

// logging
typedef struct LOGnode
{
    char LOG_out[128];
    struct LOGnode *next_ptr;
} LOGnode;


/* add lines to log buffer */
LOGnode *LOGnode_add(LOGnode *local_ptr, char *txt_input);

/* delete lines in log buffer */
LOGnode *LOGnode_del(LOGnode *local_ptr);

/* inserts PCB data into the list */
PCBdata *PCBnode_add(PCBdata *local_ptr, PCBdata *new_ptr);

/* clears PCB data */
PCBdata *PCBnode_del(PCBdata *local_ptr);

/* display PCB data */
void PCB_display(PCBdata *head_ptr);

/* runs the simulator log report */
void sim_log(int counter, ConfigDataType *config_dataptr, char *txt_input);

/* simulator driver */
void runSim(ConfigDataType *config_dataptr, OpCodeType *meta_data_ptr);

#endif
