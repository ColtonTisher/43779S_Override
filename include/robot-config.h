/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.h                                            */
/*    Description:  Ports, gearing, and the devices the rest of the code uses.*/
/*                  Change hardware in README.md, then update this file.      */
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
static const vex::port PORT_UNUSED = PORT21;

// Drive motors. Reversed is true when a motor is mounted backward, so a
// "forward" command still rolls that wheel forward.
static const vex::port PORT_LEFT_FRONT = PORT1;
static const bool LEFT_FRONT_REVERSED = false;
static const vex::port PORT_LEFT_MIDDLE = PORT2;
static const bool LEFT_MIDDLE_REVERSED = false;
static const vex::port PORT_LEFT_BACK = PORT3;
static const bool LEFT_BACK_REVERSED = false;

static const vex::port PORT_RIGHT_FRONT = PORT11;
static const bool RIGHT_FRONT_REVERSED = true;
static const vex::port PORT_RIGHT_MIDDLE = PORT12;
static const bool RIGHT_MIDDLE_REVERSED = true;
static const vex::port PORT_RIGHT_BACK = PORT13;
static const bool RIGHT_BACK_REVERSED = true;

// Mechanisms. PORT_UNUSED until the motor is plugged in.
static const vex::port PORT_INTAKE = PORT_UNUSED;
static const bool INTAKE_REVERSED = false;
static const vex::port PORT_SCORER = PORT_UNUSED;
static const bool SCORER_REVERSED = false;

// Needed for accurate autonomous turns. PORT_UNUSED until it is plugged in.
static const vex::port PORT_INERTIAL = PORT_UNUSED;

// Blue cartridge (600 rpm). Wheel travel is the distance one wheel rotation
// covers. Track width is the gap between the left and right wheels. Wheelbase
// is the gap between the front and back axles. Measure these on the robot
// before tuning autonomous distance and turns.
static const gearSetting DRIVE_GEAR = ratio6_1;
static const double WHEEL_TRAVEL_MM = 319.19;
static const double TRACK_WIDTH_MM = 320.0;
static const double WHEEL_BASE_MM = 260.0;
static const distanceUnits DRIVE_UNITS = mm;
static const double DRIVE_EXTERNAL_GEAR_RATIO = 1.0;

// Created in robot-config.cpp. extern means "the real object is in another file."
extern motor LeftFront;
extern motor LeftMiddle;
extern motor LeftBack;
extern motor RightFront;
extern motor RightMiddle;
extern motor RightBack;

// One command spins every motor on that side.
extern motor_group LeftDrive;
extern motor_group RightDrive;

// Distance and turn commands for autonomous.
extern drivetrain Drivetrain;

// Check hasIntake(), hasScorer(), or hasInertial() before using these.
extern motor Intake;
extern motor Scorer;
extern inertial Inertial;

// Set brake modes, and calibrate the inertial sensor if it is installed.
void initRobot();

// True only when that device has a real port.
bool hasIntake();
bool hasScorer();
bool hasInertial();
