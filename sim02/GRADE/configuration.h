#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// headers
#include "simulatorUtility.h"

// struct
struct Config
{
  float version; // 0.0 < V < 10.0
  char filePath[MAX_STR_LEN];
  char cpuCode[MIN_STR_LEN];     // FCFS-N, SJF-N, SRTF-P, FCFS-P, RR-P
  int qTime;                     // 0 < qT < 100
  int memAvailable;              // 1024 < MA < 102400
  char memory[MIN_STR_LEN];      // on/off
  int processorCT;               // 0 < PCT < 100
  int ioCT;                      // 1 < ioCT < 1000
  char logTo[MIN_STR_LEN];       // Monitor, File, Both
  char logFilePath[MAX_STR_LEN]; // NOT NULL
};
typedef struct Config configuration;

// prototypes
bool checkConfig(configuration *config);
void display_config(configuration *config, bool displayFlag);
bool readConfiguration(configuration *config, char *fileName);

#endif