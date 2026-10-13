/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.cpp                                          */
/*    Description:  Constructs the devices declared in robot-config.h.        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// The header holds the names. This file creates the real objects.
#include "robot-config.h"

// So we can write motor, brain, and brake without the vex:: prefix.
using namespace vex;

// Create the brain object. There is one brain on the robot.
brain Brain;
// Create the primary controller object. It reads the joysticks and buttons.
controller Controller1;

// Build each drive motor: which port, which cartridge, and whether to flip
// its spin direction. These run as soon as the program starts.
motor LeftFront(PORT_LEFT_FRONT, DRIVE_GEAR, LEFT_FRONT_REVERSED);
motor LeftMiddle(PORT_LEFT_MIDDLE, DRIVE_GEAR, LEFT_MIDDLE_REVERSED);
motor LeftBack(PORT_LEFT_BACK, DRIVE_GEAR, LEFT_BACK_REVERSED);
motor RightFront(PORT_RIGHT_FRONT, DRIVE_GEAR, RIGHT_FRONT_REVERSED);
motor RightMiddle(PORT_RIGHT_MIDDLE, DRIVE_GEAR, RIGHT_MIDDLE_REVERSED);
motor RightBack(PORT_RIGHT_BACK, DRIVE_GEAR, RIGHT_BACK_REVERSED);

// Bundle each side so driver control can set one speed for three motors.
motor_group LeftDrive(LeftFront, LeftMiddle, LeftBack);
motor_group RightDrive(RightFront, RightMiddle, RightBack);

// Build the drivetrain from both sides plus the wheel measurements.
// Autonomous uses this for driveFor, which moves a set distance and stops.
drivetrain Drivetrain(LeftDrive, RightDrive, WHEEL_TRAVEL_MM, TRACK_WIDTH_MM,
                      WHEEL_BASE_MM, DRIVE_UNITS, DRIVE_EXTERNAL_GEAR_RATIO);

// Optional devices share PORT_UNUSED until you assign a real port. Call the
// matching has*() check before using Intake, Scorer, or Inertial.
// Green cartridge (200 rpm) is a common intake speed: fast, with some torque.
motor Intake(PORT_INTAKE, ratio18_1, INTAKE_REVERSED);
// Red cartridge (100 rpm) is slower and stronger, which suits a lift or arm.
motor Scorer(PORT_SCORER, ratio36_1, SCORER_REVERSED);
// The inertial sensor object. It does nothing useful until it is calibrated.
inertial Inertial(PORT_INERTIAL);

// True when the intake has a real port. "!=" means "is not equal to".
bool hasIntake() { return PORT_INTAKE != PORT_UNUSED; }

// True when the scorer has a real port.
bool hasScorer() { return PORT_SCORER != PORT_UNUSED; }

// True when the inertial sensor has a real port.
bool hasInertial() { return PORT_INERTIAL != PORT_UNUSED; }

// Prepare motors and sensors once, before autonomous or driver control.
void initRobot() {
  // Brake mode: when a drive command stops, the motors resist rolling.
  // That keeps the robot from coasting past the target in autonomous.
  LeftDrive.setStopping(brake);
  RightDrive.setStopping(brake);
  // Default drive speed is full. Driver control overwrites this every loop
  // with the joystick value. Autonomous sets its own speed before moving.
  LeftDrive.setVelocity(100, percent);
  RightDrive.setVelocity(100, percent);

  // Only touch the intake if it is actually installed.
  if (hasIntake()) {
    // Coast lets the rollers spin down freely when the button is released.
    Intake.setStopping(coast);
    Intake.setVelocity(100, percent);
  }
  // Only touch the scorer if it is actually installed.
  if (hasScorer()) {
    // Hold uses the motor to stay at the last position, so an arm does not drop.
    Scorer.setStopping(hold);
    // Half speed is gentler for a lift until you tune it on the robot.
    Scorer.setVelocity(50, percent);
  }
  // The inertial sensor needs a few seconds sitting still before turns are accurate.
  if (hasInertial()) {
    Inertial.calibrate();
    // Stay here until calibration finishes. 20 ms pauses keep the CPU calm.
    while (Inertial.isCalibrating()) {
      wait(20, msec);
    }
  }

  // Wipe the brain screen and print a ready message on the first line.
  Brain.Screen.clearScreen();
  // Rows and columns start at 1. (1, 1) is the top-left corner.
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Robot ready");
}
