// header
#include "configuration.h"
#include "metaData.h"
#include "simulator.h"
#include "simulatorUtility.h"

// constants

// program
int main(int argc, char **argv)
{
  configuration config;
  metaData *data;
  char *inputFile;
  int loopCount, index;
  bool dm = false, dc = false, rs = false;
  bool readConfig = false, readMeta = false;

  // print top display
  printf("Simulator Program\n=================\n\n");

  if (argc < 3 || argc > 5)
  {
    printf("Usage: Display Types, File\n");
  }
  else
  {
    inputFile = argv[argc - 1];
    loopCount = argc - 2;

    if (readConfiguration(&config, inputFile))
    {
      readConfig = true;
      if (readMetaData(&data, config.filePath))
      {
        readMeta = true;
      }
    }

    for (index = 1; index <= loopCount; index++)
    {
      if (compareStrings(argv[index], DISPLAY_CONFIG) == 0)
      {
        // display config is true
        dc = true;
      }
      else if (compareStrings(argv[index], DISPLAY_MD) == 0)
      {
        dm = true;
      }
      else if (compareStrings(argv[index], RUN_SIM) == 0)
      {
        rs = true;
      }
      else
      {
        print_error("Unknown display type");
      }
    }
  }

  if (dc)
  {
    // DISPLAY CONFIGURATION
    display_config(&config, readConfig);
  }

  if (dm)
  {
    // DISPLAY META-DATA
    display_MD(data, readMeta);
  }

  if (rs)
  {
    // RUN_SIM
    makeSim(&config, data);
  }

  clearData(data);
  printf("\n\nSimulator Program End.\n");

  return 0;
}
