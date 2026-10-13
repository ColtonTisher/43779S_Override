/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton-skills.cpp                                          */
/*    Description:  Skills autonomous. Each step is a comment until the       */
/*                  route and mechanisms exist.                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Announces runSkills() so this file and autons.cpp agree on the name.
#include "auton-skills.h"

// Brings in the Drivetrain object this routine commands.
#include "robot-config.h"

// So we can write forward, percent, and inches without the vex:: prefix.
using namespace vex;

// Skills lasts 60 seconds and uses the whole field. This is only a placeholder
// so the selector has something to run until the real route is written.
void runSkills() {
  // Planned route, not coded yet:
  // 1. Drive off the starting tile.
  // 2. Score preload.
  // 3. Collect and score along the route.
  // 4. End near the next scoring position.

  // Slower than the test auton because a skills start is usually near obstacles.
  Drivetrain.setDriveVelocity(40, percent);
  // One foot forward, then stop. Replace this once the route is planned.
  Drivetrain.driveFor(forward, 12, inches);
  // Apply the brake mode so the robot does not roll after the short move.
  Drivetrain.stop();
}
