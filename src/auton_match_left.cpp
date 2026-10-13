/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_match_left.cpp                                      */
/*    Description:  Match autonomous for the left starting corner.            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Announces runMatchLeft() so this file and autons.cpp agree on the name.
#include "auton_match_left.h"

// Shared drive, turn, intake, and score moves.
#include "auton_controls.h"

// Left means the left corner on your alliance side, as the driver faces
// the field. Stay on your half of the Autonomous Line for all 15 seconds.
void runMatchLeft() {
  // 1. Drive off the starting tile.
  // 2. Score the preload on a Goal on your half.
  // 3. Leave the field wall before autonomous ends.

  autonDrive(24, 50);
  autonStop();
}
