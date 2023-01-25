/**
 * Custom data types needed for sim01
 */
#ifndef TYPES_H
#define TYPES_H


typedef struct ConfigDataType 
    {
        double version;
        
        // TODO : change this paramater to string length?
        char metaDataFileName[96];
        char logToFileName[96];

        // TODO : define specific bit types? int8_t?
        int cpuSchedCode;
        int quantumCycles;
        _Bool memDisplay;
        int memAvailable;
        int procCycleRate;
        int ioCycleRate;
        int logToCode;
    } ConfigDataType;


#endif

