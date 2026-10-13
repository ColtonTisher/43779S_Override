// Standard headers the VEX libraries expect.
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// VEX V5 hardware and competition helpers (motors, controller, drivetrain).
#include "v5.h"
#include "v5_vcs.h"

// Pause and recheck until condition is true. The short wait keeps the brain
// from spinning as fast as it can.
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

// Run the next block iterations times. iterator counts 0, 1, 2, ...
#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
