/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.cpp                                          */
/*    Description:  Creates the devices named in robot-config.h.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "robot-config.h"

using namespace vex;

brain Brain;
controller Controller1;

// Port, cartridge, and whether to flip the spin direction.
motor LeftFront(PORT_LEFT_FRONT, DRIVE_GEAR, LEFT_FRONT_REVERSED);
motor LeftMiddle(PORT_LEFT_MIDDLE, DRIVE_GEAR, LEFT_MIDDLE_REVERSED);
motor LeftBack(PORT_LEFT_BACK, DRIVE_GEAR, LEFT_BACK_REVERSED);
motor RightFront(PORT_RIGHT_FRONT, DRIVE_GEAR, RIGHT_FRONT_REVERSED);
motor RightMiddle(PORT_RIGHT_MIDDLE, DRIVE_GEAR, RIGHT_MIDDLE_REVERSED);
motor RightBack(PORT_RIGHT_BACK, DRIVE_GEAR, RIGHT_BACK_REVERSED);

motor_group LeftDrive(LeftFront, LeftMiddle, LeftBack);
motor_group RightDrive(RightFront, RightMiddle, RightBack);

// Wheel measurements let driveFor() and turnFor() use inches and degrees.
drivetrain Drivetrain(LeftDrive, RightDrive, WHEEL_TRAVEL_MM, TRACK_WIDTH_MM,
                      WHEEL_BASE_MM, DRIVE_UNITS, DRIVE_EXTERNAL_GEAR_RATIO);

// Green is 200 rpm. Red is 100 rpm. These stay on PORT_UNUSED until installed.
motor Intake(PORT_INTAKE, ratio18_1, INTAKE_REVERSED);
motor Scorer(PORT_SCORER, ratio36_1, SCORER_REVERSED);
inertial Inertial(PORT_INERTIAL);

// A device is installed when its port is not the unused placeholder.
bool hasIntake() { return PORT_INTAKE != PORT_UNUSED; }
bool hasScorer() { return PORT_SCORER != PORT_UNUSED; }
bool hasInertial() { return PORT_INERTIAL != PORT_UNUSED; }

// Run once before the match. A long wait here can make autonomous start late.
void initRobot() {
  // Brake resists rolling after a drive command stops.
  LeftDrive.setStopping(brake);
  RightDrive.setStopping(brake);
  LeftDrive.setVelocity(100, percent);
  RightDrive.setVelocity(100, percent);

  if (hasIntake()) {
    // Coast lets the rollers spin down when the button is released.
    Intake.setStopping(coast);
    Intake.setVelocity(100, percent);
  }

  if (hasScorer()) {
    // Hold keeps an arm from dropping when the button is released.
    Scorer.setStopping(hold);
    Scorer.setVelocity(50, percent);
  }

  if (hasInertial()) {
    // The sensor must sit still while it calibrates.
    Inertial.calibrate();
    while (Inertial.isCalibrating()) {
      wait(20, msec);
    }
  }

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Robot ready");
}
