/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_controls.cpp                                        */
/*    Description:  Shared autonomous moves. Routines call these instead of   */
/*                  talking to motors directly, so a fix applies everywhere.  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// The names of the shared moves.
#include "auton_controls.h"

// Motors, the drivetrain, and the hasIntake / hasScorer checks.
#include "robot-config.h"

// So we can write forward, percent, inches, and degrees without vex::.
using namespace vex;

// Pause for a number of thousandths of a second.
// "msec" is the VEX name for milliseconds.
static void autonWait(int milliseconds) {
  // A negative wait does not make sense, so treat it as "do not wait."
  if (milliseconds > 0) {
    wait(milliseconds, msec);
  }
}

// Flip a negative command into a positive speed plus a reverse direction.
// VEX spin() wants the direction and the speed as two separate arguments.
static void autonSpin(motor &device, double speedPercent) {
  if (speedPercent >= 0) {
    device.spin(forward, speedPercent, percent);
  } else {
    // The minus sign turns -40 into 40, because speed itself is not negative.
    device.spin(reverse, -speedPercent, percent);
  }
}

// Drive straight. A negative distance drives backward for that many inches.
void autonDrive(double inches, double speedPercent) {
  Drivetrain.setDriveVelocity(speedPercent, percent);
  if (inches >= 0) {
    Drivetrain.driveFor(forward, inches, vex::inches);
  } else {
    Drivetrain.driveFor(reverse, -inches, vex::inches);
  }
}

// Turn in place. Positive degrees turn right. Negative degrees turn left.
void autonTurn(double degrees, double speedPercent) {
  Drivetrain.setTurnVelocity(speedPercent, percent);
  if (degrees >= 0) {
    Drivetrain.turnFor(right, degrees, vex::degrees);
  } else {
    Drivetrain.turnFor(left, -degrees, vex::degrees);
  }
}

// Spin the intake only if that motor is installed.
void autonIntake(double speedPercent, int milliseconds) {
  // PORT_UNUSED means the intake is not on the robot yet, so skip it.
  if (!hasIntake()) {
    return;
  }
  autonSpin(Intake, speedPercent);
  autonWait(milliseconds);
  // Stop so the rollers do not keep running into the next drive move.
  Intake.stop();
}

// Spin the scorer only if that motor is installed.
void autonScore(double speedPercent, int milliseconds) {
  if (!hasScorer()) {
    return;
  }
  autonSpin(Scorer, speedPercent);
  autonWait(milliseconds);
  // stop() uses the hold mode from initRobot, so an arm stays put.
  Scorer.stop();
}

// Make sure every autonomous subsystem is stopped.
void autonStop() {
  Drivetrain.stop();
  if (hasIntake()) {
    Intake.stop();
  }
  if (hasScorer()) {
    Scorer.stop();
  }
}
