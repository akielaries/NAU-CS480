#include "simtimer.h" // include header file with function declarations
#include <stdio.h>

int main()
{
  char timeStr[10];

  printf("Starting timer...\n");
  accessTimer(ZERO_TIMER, timeStr);

  printf("Timer running...\n");
  runTimer(5000); // wait for 5 seconds

  printf("Lap time: %s seconds\n", timeStr);
  accessTimer(LAP_TIMER, timeStr);

  printf("Timer running...\n");
  runTimer(3000); // wait for another 3 seconds

  printf("Lap time: %s seconds\n", timeStr);
  accessTimer(LAP_TIMER, timeStr);

  printf("Stopping timer...\n");
  accessTimer(STOP_TIMER, timeStr);

  printf("Total time: %s seconds\n", timeStr);

  return 0;
}
