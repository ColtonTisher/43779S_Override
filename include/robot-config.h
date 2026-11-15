/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.h                                            */
/*    Description:  Ports, gearing, and the devices the rest of the code uses.*/
/*                  Change hardware in ROBOT.md, then update this file.       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Read this file only once, even if several other files include it.
#pragma once

#include "vex.h"

// Lets the rest of the project write motor instead of vex::motor.
using namespace vex;

// The brain and the driver's controller. Created in robot-config.cpp.
extern brain Brain;
extern controller Controller1;

// Port 21 means "not installed." Leave that port empty on the brain.
// Smart ports are plain numbers. PORT1 is 0, so a brain port is the number minus 1.
static const int32_t PORT_UNUSED = 20;

// Drive motors. Reversed is true when a motor is mounted backward, so a
// "forward" command still rolls that wheel forward.
static const int32_t PORT_LEFT_FRONT = 13;
static const bool LEFT_FRONT_REVERSED = true;
static const int32_t PORT_LEFT_BACK = 12;
static const bool LEFT_BACK_REVERSED = true;

static const int32_t PORT_RIGHT_FRONT = 17;
static const bool RIGHT_FRONT_REVERSED = false;
static const int32_t PORT_RIGHT_BACK = 18;
static const bool RIGHT_BACK_REVERSED = false;

// Mechanisms. PORT_UNUSED until the motor is plugged in.
static const int32_t PORT_SCORER = PORT_UNUSED;
static const bool SCORER_REVERSED = false;

// String lift, brain ports 8 and 9. Code ports are the brain number minus 1.
// The two motors share one shaft, facing each other. Port 9 must be commanded
// backward or the motors fight.
static const int32_t PORT_LIFT_A = 7;
static const bool LIFT_A_REVERSED = false;
static const int32_t PORT_LIFT_B = 8;
static const bool LIFT_B_REVERSED = true;

// Arm motor, brain port 7. Forward spins toward the front.
static const int32_t PORT_ARM = 6;
static const bool ARM_REVERSED = false;

// Ratcheting claw, brain port 15. Forward intakes. A short reverse cracks it open.
static const int32_t PORT_CLAW = 14;
static const bool CLAW_REVERSED = false;
// Motor degrees of reverse after B is held for 2 seconds. Then the motor holds.
static const double CLAW_OPEN_DEGREES = 30;
static const int CLAW_OPEN_SPEED = 30;
// How long B must be held before the claw opens instead of just stopping.
static const int CLAW_OPEN_HOLD_MSEC = 2000;

// Wrist that tilts the claw, brain port 11. Up and Down spin it. Release holds.
static const int32_t PORT_WRIST = 10;
static const bool WRIST_REVERSED = false;

// Odometry. The forward wheel faces the front of the robot. The sideways
// wheel is perpendicular to it. Both are 2 inch omni wheels, one turn of the
// sensor per wheel turn. Offsets are from the robot center, in inches.
// Positive sideways offset is to the right. Positive forward offset is ahead.
static const int32_t PORT_FORWARD_ROTATION = 9;
static const bool FORWARD_ROTATION_REVERSED = false;
static const int32_t PORT_SIDEWAYS_ROTATION = 15;
static const bool SIDEWAYS_ROTATION_REVERSED = false;
static const int32_t PORT_INERTIAL = 0;
static const double ODOM_WHEEL_DIAMETER_IN = 2.0;
// 6 inches from the right side and 5.75 inches from the left side.
static const double ODOM_FORWARD_OFFSET_IN = -0.125;
// 5.5 inches from the front and 2 inches from the back.
static const double ODOM_SIDEWAYS_OFFSET_IN = 1.75;

// Distance sensors, one on each side. They look out from that side.
static const int32_t PORT_DISTANCE_FRONT = 2;
static const int32_t PORT_DISTANCE_LEFT = 1;
static const int32_t PORT_DISTANCE_RIGHT = 4;
static const int32_t PORT_DISTANCE_BACK = 11;

// Green cartridge (200 rpm). 0.6 motor turns per wheel turn is about 333 rpm
// at the wheel. Wheel travel is one rotation of a 3.25 inch wheel. Track
// width is 11.5 inches between the left and right wheels. Wheelbase is 11
// inches between the front and back axles.
static const gearSetting DRIVE_GEAR = ratio18_1;
static const double WHEEL_TRAVEL_MM = 259.34;
static const double TRACK_WIDTH_MM = 292.1;
static const double WHEEL_BASE_MM = 279.4;
static const distanceUnits DRIVE_UNITS = mm;
static const double DRIVE_EXTERNAL_GEAR_RATIO = 0.6;

// Created in robot-config.cpp. extern means "the real object is in another file."
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;

// One command spins every motor on that side.
extern motor_group LeftDrive;
extern motor_group RightDrive;

// Distance and turn commands for autonomous.
extern drivetrain Drivetrain;

// Check hasScorer(), hasLift(), hasArm(), hasClaw(), hasWrist(), or hasInertial()
// before using these.
extern motor Scorer;
extern inertial Inertial;

// Tracking wheels. Read these for position. Do not use them as drive motors.
extern rotation ForwardRotation;
extern rotation SidewaysRotation;

// Wall distance on each side of the robot.
extern distance DistanceFront;
extern distance DistanceLeft;
extern distance DistanceRight;
extern distance DistanceBack;

// Both lift motors. Spin Lift, not the single motors, so they stay together.
extern motor LiftA;
extern motor LiftB;
extern motor_group Lift;

// Arm motor. The driver holds a button to move it.
extern motor Arm;

// Ratcheting claw. X intakes. A short B stops it. A long B cracks it open.
extern motor Claw;

// Tilts the claw. Hold an arrow to move it, release to hold.
extern motor Wrist;

// 3-wire pneumatic on brain port A. true opens the solenoid.
extern digital_out Pneumatic;

// Set brake modes, and calibrate the inertial sensor if it is installed.
void initRobot();

// True only when that device has a real port.
bool hasScorer();
bool hasLift();
bool hasArm();
bool hasClaw();
bool hasWrist();
bool hasInertial();
