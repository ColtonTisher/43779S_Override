/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_skills.cpp                                          */
/*    Description:  Skills autonomous. Uses the whole field for 60 seconds.   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Announces runSkills() so this file and autons.cpp agree on the name.
#include "auton_skills.h"

// Shared drive, turn, intake, and score moves.
#include "auton_controls.h"

// Skills starts next to the red alliance station and may use the whole field.
// This is a placeholder until the real route is planned.
void runSkills() {
  // 1. Drive off the starting tile.
  // 2. Score the preload.
  // 3. Collect and score along the route.
  // 4. End in the Midfield so center yellow Pin Halves count.

  // Slower than a match start because skills often begins near obstacles.
  autonDrive(12, 40);
  // Stop the drive and any mechanisms before the routine returns.
  autonStop();
}
