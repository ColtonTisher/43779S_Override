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
motor LeftBack(PORT_LEFT_BACK, DRIVE_GEAR, LEFT_BACK_REVERSED);
motor RightFront(PORT_RIGHT_FRONT, DRIVE_GEAR, RIGHT_FRONT_REVERSED);
motor RightBack(PORT_RIGHT_BACK, DRIVE_GEAR, RIGHT_BACK_REVERSED);

motor_group LeftDrive(LeftFront, LeftBack);
motor_group RightDrive(RightFront, RightBack);

// Wheel measurements let driveFor() and turnFor() use inches and degrees.
drivetrain Drivetrain(LeftDrive, RightDrive, WHEEL_TRAVEL_MM, TRACK_WIDTH_MM,
                      WHEEL_BASE_MM, DRIVE_UNITS, DRIVE_EXTERNAL_GEAR_RATIO);

// Red is 100 rpm. Stays on PORT_UNUSED until installed.
motor Scorer(PORT_SCORER, ratio36_1, SCORER_REVERSED);
inertial Inertial(PORT_INERTIAL);
rotation ForwardRotation(PORT_FORWARD_ROTATION, FORWARD_ROTATION_REVERSED);
rotation SidewaysRotation(PORT_SIDEWAYS_ROTATION, SIDEWAYS_ROTATION_REVERSED);
distance DistanceFront(PORT_DISTANCE_FRONT);
distance DistanceLeft(PORT_DISTANCE_LEFT);
distance DistanceRight(PORT_DISTANCE_RIGHT);
distance DistanceBack(PORT_DISTANCE_BACK);

// Green cartridge. LiftB is reversed so the pair pulls one string together.
motor LiftA(PORT_LIFT_A, ratio18_1, LIFT_A_REVERSED);
motor LiftB(PORT_LIFT_B, ratio18_1, LIFT_B_REVERSED);
motor_group Lift(LiftA, LiftB);

// External gears are 24 driving 72, so the arm output is three times slower
// than the motor shaft. Forward moves the arm toward the front.
motor Arm(PORT_ARM, ratio36_1, ARM_REVERSED);

// Green cartridge. Forward intakes. A short reverse after a long B press opens the ratchet.
motor Claw(PORT_CLAW, ratio18_1, CLAW_REVERSED);

// Green cartridge. Tilts the claw. Up and Down move it. Release holds the angle.
motor Wrist(PORT_WRIST, ratio18_1, WRIST_REVERSED);

// 3-wire solenoid on the brain's ADI port A. Starts off.
digital_out Pneumatic(Brain.ThreeWirePort.A);

// A device is installed when its port is not the unused placeholder.
bool hasScorer() { return PORT_SCORER != PORT_UNUSED; }
bool hasLift() { return PORT_LIFT_A != PORT_UNUSED && PORT_LIFT_B != PORT_UNUSED; }
bool hasArm() { return PORT_ARM != PORT_UNUSED; }
bool hasClaw() { return PORT_CLAW != PORT_UNUSED; }
bool hasWrist() { return PORT_WRIST != PORT_UNUSED; }
bool hasInertial() { return PORT_INERTIAL != PORT_UNUSED; }

// Run once before the match. A long wait here can make autonomous start late.
void initRobot() {
  // Coast lets the robot roll after a drive command stops.
  LeftDrive.setStopping(coast);
  RightDrive.setStopping(coast);
  LeftDrive.setVelocity(100, percent);
  RightDrive.setVelocity(100, percent);

  if (hasScorer()) {
    // Hold keeps an arm from dropping when the button is released.
    Scorer.setStopping(hold);
    Scorer.setVelocity(50, percent);
  }

  if (hasLift()) {
    // Hold keeps the string from unwinding when the button is released.
    Lift.setStopping(hold);
    Lift.setVelocity(100, percent);
  }

  if (hasArm()) {
    // Hold keeps the arm from dropping when the button is released.
    Arm.setStopping(hold);
    Arm.setVelocity(15, percent);
  }

  if (hasClaw()) {
    // Hold keeps the ratchet open after the reverse spin finishes.
    Claw.setStopping(hold);
    Claw.setVelocity(100, percent);
  }

  if (hasWrist()) {
    // Hold keeps the claw from flopping when the arrow is released.
    Wrist.setStopping(hold);
    Wrist.setVelocity(50, percent);
  }

  if (hasInertial()) {
    // The sensor must sit still while it calibrates.
    Inertial.calibrate();
    while (Inertial.isCalibrating()) {
      wait(20, msec);
    }
    Inertial.setHeading(0, degrees);
  }

  // Tracking starts at the spot the robot is sitting when the program starts.
  ForwardRotation.resetPosition();
  SidewaysRotation.resetPosition();

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Robot ready");
}
