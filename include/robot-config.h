/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.h                                            */
/*    Description:  Device ports, gearing, and subsystem objects.             */
/*                  Hardware values come from ROBOT.md. Game rules that      */
/*                  the code must follow are summarized in GAME.md.          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// "pragma once" tells the compiler to read this file only one time, even if
// several other files include it. Without this, names would be defined twice.
#pragma once

// Bring in the VEX library and the waitUntil / repeat helpers.
#include "vex.h"

// Let us write "motor" instead of "vex::motor" everywhere in this project.
using namespace vex;

// The brain is the robot's computer. Declared here so every file can use it.
// The real object is created in robot-config.cpp.
extern brain Brain;
// The driver's joystick. Controller1 is the primary controller.
extern controller Controller1;

// ---------------------------------------------------------------------------
// Ports
//
// Match these to the brain ports the devices are plugged into.
// Motors: PORT1-PORT20. PORT21 is reserved as PORT_UNUSED.
// Three-wire devices use brain.ThreeWirePort.A-H.
// Flip *_REVERSED to true when a motor spins the wrong way in the field.
// ---------------------------------------------------------------------------

// A fake port number for devices that are not installed yet.
// "static" here means "private to this file's includers, one copy each."
// "const" means the value cannot be changed while the program runs.
// Do not plug a motor into port 21 while code still uses it as "unused".
static const vex::port PORT_UNUSED = PORT21;

// Drivetrain. Tank drive, three motors per side. 6-motor drive is the
// usual V5 starting layout; drop to two per side by editing robot-config.cpp.

// Left side of the drive, looking from behind the robot.
// Each motor needs a brain port and a true/false "reversed" flag.
// Reversed is true when that motor is mounted facing the other way,
// so the wheel still rolls forward when we command "forward".
static const vex::port PORT_LEFT_FRONT = PORT1;
static const bool LEFT_FRONT_REVERSED = false;
static const vex::port PORT_LEFT_MIDDLE = PORT2;
static const bool LEFT_MIDDLE_REVERSED = false;
static const vex::port PORT_LEFT_BACK = PORT3;
static const bool LEFT_BACK_REVERSED = false;

// Right side of the drive. These are reversed because the motors face
// the opposite direction from the left side on a typical tank build.
static const vex::port PORT_RIGHT_FRONT = PORT11;
static const bool RIGHT_FRONT_REVERSED = true;
static const vex::port PORT_RIGHT_MIDDLE = PORT12;
static const bool RIGHT_MIDDLE_REVERSED = true;
static const vex::port PORT_RIGHT_BACK = PORT13;
static const bool RIGHT_BACK_REVERSED = true;

// Intake motor. PORT_UNUSED means "not installed", so driver code skips it.
static const vex::port PORT_INTAKE = PORT_UNUSED;
static const bool INTAKE_REVERSED = false;

// Scoring mechanism (arm, lift, or catapult). PORT_UNUSED until installed.
static const vex::port PORT_SCORER = PORT_UNUSED;
static const bool SCORER_REVERSED = false;

// Inertial sensor measures which way the robot is facing.
// Autonomous turns need this. PORT_UNUSED until it is plugged in.
static const vex::port PORT_INERTIAL = PORT_UNUSED;

// ---------------------------------------------------------------------------
// Gearing and wheel geometry
//
// gearSetting: ratio36_1 (red, 100 rpm), ratio18_1 (green, 200 rpm),
//              ratio6_1 (blue, 600 rpm).
// Wheel travel is the circumference in mm. A 4 inch omni is about 319.19 mm
// (4 * 25.4 * pi). Track width is the distance between the left and right
// wheel contact patches, in mm. Measure it on the robot before tuning auton.
// ---------------------------------------------------------------------------

// Blue cartridge: fast wheel speed, less torque. Matches ROBOT.md.
static const gearSetting DRIVE_GEAR = ratio6_1;
// How far one wheel rotation travels, in millimeters. Used so driveFor(inches)
// knows how many motor turns equal one inch.
static const double WHEEL_TRAVEL_MM = 319.19;
// Distance between the left and right wheels. Used so turnFor(degrees)
// knows how far each side must drive to spin the robot.
static const double TRACK_WIDTH_MM = 320.0;
// Distance from the front axle to the back axle. The drivetrain uses this
// with track width to estimate turns.
static const double WHEEL_BASE_MM = 260.0;
// Tell the drivetrain that the three numbers above are in millimeters.
static const distanceUnits DRIVE_UNITS = mm;
// Motor turns divided by wheel turns. 1.0 means the motor shaft is the wheel.
static const double DRIVE_EXTERNAL_GEAR_RATIO = 1.0;

// ---------------------------------------------------------------------------
// Devices
//
// "extern" means "this object lives in another file." The constructors that
// actually create the motors are in src/robot-config.cpp.
// ---------------------------------------------------------------------------

// The six drive motors, one object per physical motor.
extern motor LeftFront;
extern motor LeftMiddle;
extern motor LeftBack;
extern motor RightFront;
extern motor RightMiddle;
extern motor RightBack;

// Groups let us spin a whole side with one command during driver control.
extern motor_group LeftDrive;
extern motor_group RightDrive;
// Drivetrain adds distance and turn commands for autonomous.
extern drivetrain Drivetrain;

// Optional mechanisms. Safe to mention in code only after the matching has*()
// function returns true, because their ports may still be PORT_UNUSED.
extern motor Intake;
extern motor Scorer;
extern inertial Inertial;

// Set motor brake modes and wait for the inertial sensor to finish calibrating.
// Call this once from pre_auton, before the match starts.
void initRobot();

// These return true only when that device has a real brain port.
// Driver control uses them so missing hardware does not get commanded.
bool hasIntake();
bool hasScorer();
bool hasInertial();
