/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_controls.cpp                                        */
/*    Description:  Shared autonomous moves. Change a move here and every     */
/*                  routine that calls it picks up the change.                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auton_controls.h"
#include "robot-config.h"

using namespace vex;

// VEX wants a direction and a positive speed, so a negative speed means reverse.
static void spinAt(motor &device, double speedPercent) {
  if (speedPercent >= 0) {
    device.spin(forward, speedPercent, percent);
  } else {
    device.spin(reverse, -speedPercent, percent);
  }
}

// Spin one mechanism for a set time. Skip it when that motor is not installed.
static void spinFor(motor &device, bool installed, double speedPercent, int milliseconds) {
  if (!installed) {
    return;
  }

  spinAt(device, speedPercent);
  if (milliseconds > 0) {
    wait(milliseconds, msec);
  }
  device.stop();
}

void autonDrive(double inches, double speedPercent) {
  Drivetrain.setDriveVelocity(speedPercent, percent);
  if (inches >= 0) {
    Drivetrain.driveFor(forward, inches, vex::inches);
  } else {
    Drivetrain.driveFor(reverse, -inches, vex::inches);
  }
}

void autonTurn(double degrees, double speedPercent) {
  Drivetrain.setTurnVelocity(speedPercent, percent);
  if (degrees >= 0) {
    Drivetrain.turnFor(right, degrees, vex::degrees);
  } else {
    Drivetrain.turnFor(left, -degrees, vex::degrees);
  }
}

void autonIntake(double speedPercent, int milliseconds) {
  spinFor(Intake, hasIntake(), speedPercent, milliseconds);
}

void autonScore(double speedPercent, int milliseconds) {
  spinFor(Scorer, hasScorer(), speedPercent, milliseconds);
}

void autonStop() {
  Drivetrain.stop();
  if (hasIntake()) {
    Intake.stop();
  }
  if (hasScorer()) {
    Scorer.stop();
  }
}
