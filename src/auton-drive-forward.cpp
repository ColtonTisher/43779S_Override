/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton-drive-forward.cpp                                   */
/*    Description:  Drives forward a short distance, then stops.              */
/*                  Use this to confirm ports, direction, and wheel size.    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Announces runDriveForward() so this file and autons.cpp agree on the name.
#include "auton-drive-forward.h"

// Brings in the Drivetrain object this routine commands.
#include "robot-config.h"

// So we can write forward, percent, and inches without the vex:: prefix.
using namespace vex;

// A first autonomous test: leave the starting area in a straight line.
// If the robot drives backward, flip the reversed flags in robot-config.h.
// If the distance is wrong, measure the wheels and update WHEEL_TRAVEL_MM.
void runDriveForward() {
  // Half speed is slow enough to watch and stop if a port is wrong.
  Drivetrain.setDriveVelocity(50, percent);
  // driveFor blocks until the move finishes. 24 inches is two feet.
  Drivetrain.driveFor(forward, 24, inches);
  // Stop the motors even though driveFor already ends at rest. This makes
  // the "we are done" intent obvious and applies the brake mode from initRobot.
  Drivetrain.stop();
}
