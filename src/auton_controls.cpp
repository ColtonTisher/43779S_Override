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

// Inches one tracking wheel has rolled since its position was last cleared.
static double wheelInches(rotation &sensor) {
  return sensor.position(turns) * ODOM_WHEEL_DIAMETER_IN * 3.1415926535;
}

// Heading in degrees. Right is positive. Falls back to 0 without the inertial.
static double headingError(double targetDegrees) {
  if (!hasInertial()) {
    return 0;
  }
  double error = targetDegrees - Inertial.heading(degrees);
  while (error > 180) {
    error = error - 360;
  }
  while (error < -180) {
    error = error + 360;
  }
  return error;
}

void autonDrive(double inches, double speedPercent) {
  ForwardRotation.resetPosition();
  double startHeading = 0;
  if (hasInertial()) {
    startHeading = Inertial.heading(degrees);
  }

  int guard = 0;
  while (guard < 250) {
    double traveled = wheelInches(ForwardRotation);
    // A forward wheel off center also rolls during a turn. Take that out.
    if (hasInertial()) {
      double turned = headingError(startHeading);
      traveled = traveled + (turned * 3.1415926535 / 180.0) * ODOM_FORWARD_OFFSET_IN;
    }
    double remaining = inches - traveled;
    double magnitude = remaining;
    if (magnitude < 0) {
      magnitude = -magnitude;
    }
    if (magnitude <= 0.5) {
      break;
    }

    double power = speedPercent;
    if (magnitude < 6) {
      power = speedPercent * (magnitude / 6.0);
    }
    if (power < 15) {
      power = 15;
    }
    if (remaining < 0) {
      power = -power;
    }

    // A small heading correction keeps the drive straight.
    double turn = headingError(startHeading) * 0.4;
    LeftDrive.spin(forward, power + turn, percent);
    RightDrive.spin(forward, power - turn, percent);
    wait(20, msec);
    guard = guard + 1;
  }

  LeftDrive.stop();
  RightDrive.stop();
}

// Inches from the named side to the nearest object. 0 if that side is unknown.
static double wallInches(const char *side) {
  distance *sensor = nullptr;
  if (side[0] == 'f') {
    sensor = &DistanceFront;
  } else if (side[0] == 'b') {
    sensor = &DistanceBack;
  } else if (side[0] == 'l') {
    sensor = &DistanceLeft;
  } else if (side[0] == 'r') {
    sensor = &DistanceRight;
  }
  if (sensor == nullptr) {
    return 0;
  }
  return sensor->objectDistance(inches);
}

// Drive forward or backward until the front or back sensor hits the target.
static void driveUntil(const char *side, double inches, double speedPercent, bool toward) {
  int guard = 0;
  while (guard < 250) {
    double reading = wallInches(side);
    double remaining = reading - inches;
    if (!toward) {
      remaining = -remaining;
    }
    if (remaining <= 0.5) {
      break;
    }

    double power = speedPercent;
    if (remaining < 6) {
      power = speedPercent * (remaining / 6.0);
    }
    if (power < 15) {
      power = 15;
    }
    if (!toward) {
      power = -power;
    }

    LeftDrive.spin(forward, power, percent);
    RightDrive.spin(forward, power, percent);
    wait(20, msec);
    guard = guard + 1;
  }

  LeftDrive.stop();
  RightDrive.stop();
}

void autonDriveToWall(const char *side, double inches, double speedPercent) {
  // Left and right have no strafe. Turn that side to the front, drive, turn back.
  if (side[0] == 'l' || side[0] == 'r') {
    double turn = 90;
    if (side[0] == 'r') {
      turn = -90;
    }
    autonTurn(turn, speedPercent);
    bool toward = wallInches("front") > inches;
    driveUntil("front", inches, speedPercent, toward);
    autonTurn(-turn, speedPercent);
    return;
  }

  bool toward = wallInches(side) > inches;
  driveUntil(side, inches, speedPercent, toward);
}

void autonTurn(double turnDegrees, double speedPercent) {
  double startHeading = 0;
  if (hasInertial()) {
    startHeading = Inertial.heading(degrees);
  }
  double target = startHeading + turnDegrees;

  int guard = 0;
  while (guard < 250) {
    double error = headingError(target);
    double magnitude = error;
    if (magnitude < 0) {
      magnitude = -magnitude;
    }
    if (magnitude <= 1.5) {
      break;
    }

    double power = speedPercent;
    if (magnitude < 25) {
      power = speedPercent * (magnitude / 25.0);
    }
    if (power < 12) {
      power = 12;
    }
    if (error < 0) {
      power = -power;
    }

    LeftDrive.spin(forward, power, percent);
    RightDrive.spin(forward, -power, percent);
    wait(20, msec);
    guard = guard + 1;
  }

  LeftDrive.stop();
  RightDrive.stop();
}

void autonScore(double speedPercent, int milliseconds) {
  spinFor(Scorer, hasScorer(), speedPercent, milliseconds);
}

void autonClawIntake(int milliseconds) {
  if (!hasClaw()) {
    return;
  }

  spinFor(Claw, true, 100, milliseconds);
  // Spin a set number of degrees open, then hold.
  Claw.setPosition(0, degrees);
  Claw.spin(reverse, CLAW_OPEN_SPEED, percent);
  while (true) {
    double turned = Claw.position(degrees);
    if (turned < 0) {
      turned = -turned;
    }
    if (turned >= CLAW_OPEN_DEGREES) {
      break;
    }
    wait(10, msec);
  }
  Claw.stop();
}

void autonStop() {
  Drivetrain.stop();
  if (hasScorer()) {
    Scorer.stop();
  }
  if (hasLift()) {
    Lift.stop();
  }
  if (hasArm()) {
    Arm.stop();
  }
  if (hasClaw()) {
    Claw.stop();
  }
}
