/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_match_right.cpp                                     */
/*    Description:  Match autonomous for the right starting corner.           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Announces runMatchRight() so this file and autons.cpp agree on the name.
#include "auton_match_right.h"

// Shared drive, turn, intake, and score moves.
#include "auton_controls.h"

// Right means the right corner on your alliance side, as the driver faces
// the field. Stay on your half of the Autonomous Line for all 15 seconds.
void runMatchRight() {
  // 1. Drive off the starting tile.
  // 2. Score the preload on a Goal on your half.
  // 3. Leave the field wall before autonomous ends.

  autonDrive(24, 50);
  autonStop();
}
