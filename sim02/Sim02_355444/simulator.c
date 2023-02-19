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

            printf("\tcurrent command: %s, ",
                   wkg_ptr->opCodeList->command);

            printf("\tcurrent op code: %s, \n",
                   wkg_ptr->opCodeList->strArg1);

            printf("\tfirst int arg: %d, second int arg: %d\n\n",
                   (unsigned int)wkg_ptr->opCodeList->intArg2,
                   (unsigned int)wkg_ptr->opCodeList->intArg3);

            wkg_ptr = wkg_ptr->next_ptr;
        }
    }
    else
    {
        puts("\nEmpty PCB List");
    }
}

void runSim(ConfigDataType *config_dataptr, OpCodeType *meta_data_ptr)
{
    printf("runSim called here.\n");
}
