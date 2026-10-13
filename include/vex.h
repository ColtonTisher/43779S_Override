// Pull in the C math helpers (sin, pi, and friends) in case a routine needs them.
#include <math.h>
// Pull in printf-style printing. The brain screen uses this style of text.
#include <stdio.h>
// Pull in general C helpers such as memory allocation. The VEX libraries expect it.
#include <stdlib.h>
// Pull in text helpers such as copying and comparing words.
#include <string.h>

// The VEX V5 brain hardware library.
#include "v5.h"
// The VEX competition helpers: motors, controller, drivetrain, and so on.
#include "v5_vcs.h"

// Keep checking a condition until it becomes true.
// wait(5, msec) pauses 5 thousandths of a second so the brain is not stuck
// spinning as fast as it can. The "!" means "not", so the loop continues
// while the condition is still false.
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

// Run the next block of code a fixed number of times.
// "iterator" counts from 0 up to (but not including) iterations.
#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
