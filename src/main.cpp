/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       colto                                                     */
/*    Created:      10/8/2026, 9:10:30 PM                                     */
/*    Description:  Competition entry point for VEX V5 2026-2027 OVERRIDE.    */
/*                  Devices live in robot-config. Autonomous routines live   */
/*                  in src/auton-*.cpp. Game rules are summarized in GAME.md. */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// The auton list and runSelectedAuton().
#include "autons.h"
// Motors, controller, brain, and initRobot().
#include "robot-config.h"
// VEX helpers, including the competition object and wait().
#include "vex.h"

// So we can write competition, percent, and forward without the vex:: prefix.
using namespace vex;

// Talks to the field control system. It decides when autonomous and driver
// control are allowed to run during a match.
competition Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  Runs once after the brain powers on. Return from this function or        */
/*  autonomous and driver control will not start.                            */
/*---------------------------------------------------------------------------*/

// Setup that must finish before the match. Keep this short. A long wait here
// can make the robot miss the start of autonomous.
void pre_auton(void) {
  // Set brake modes and calibrate the inertial sensor if it is installed.
  initRobot();

  // Show which routine will run, on the line under "Robot ready".
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Auton: %s", autonName(selectedAuton));
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/

// The field calls this when the autonomous period starts.
// It runs once, then returns. Do not put a forever loop in here.
void autonomous(void) { runSelectedAuton(); }

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

// The field calls this when the driver-control period starts.
// The loop never ends on its own. The field stops the program when the
// match ends.
void usercontrol(void) {
  // "while (true)" means "repeat forever."
  while (true) {
    // Tank drive: the left stick runs the left wheels, the right stick runs
    // the right wheels. Axis values are about -100 to 100.
    // Swap to arcade later if the driver prefers one stick for forward
    // and the other stick for turning.
    const int leftSpeed = Controller1.Axis3.position();
    const int rightSpeed = Controller1.Axis2.position();
    // spin keeps turning at this percent until the next command replaces it.
    LeftDrive.spin(forward, leftSpeed, percent);
    RightDrive.spin(forward, rightSpeed, percent);

    // Intake on the right shoulder buttons. Skipped until PORT_INTAKE is set.
    if (hasIntake()) {
      // R1 sucks in (or scores, depending on how the rollers are geared).
      if (Controller1.ButtonR1.pressing()) {
        Intake.spin(forward, 100, percent);
      // R2 runs the rollers the other way, to spit a game piece back out.
      } else if (Controller1.ButtonR2.pressing()) {
        Intake.spin(reverse, 100, percent);
      } else {
        // Neither button is held, so let the intake coast to a stop.
        Intake.stop();
      }
    }

    // Scorer on the left shoulder buttons. Skipped until PORT_SCORER is set.
    if (hasScorer()) {
      // L1 runs the scorer forward at half speed.
      if (Controller1.ButtonL1.pressing()) {
        Scorer.spin(forward, 50, percent);
      // L2 runs it backward, for example to lower an arm.
      } else if (Controller1.ButtonL2.pressing()) {
        Scorer.spin(reverse, 50, percent);
      } else {
        // Neither button is held. stop() uses the hold mode from initRobot,
        // so an arm stays where the driver left it.
        Scorer.stop();
      }
    }

    // Pause 20 thousandths of a second before reading the controller again.
    // That is 50 updates per second, fast for a driver and easy on the brain.
    wait(20, msec);
  }
}

// Every C++ program starts in main. The VEX competition template uses it to
// register the two match functions, run setup, then sit idle.
int main() {
  // Tell the field which functions to call for each match period.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Set up devices now, before the match clock starts.
  pre_auton();

  // Stay alive so the field can still call autonomous() and usercontrol().
  // If main returned, the program would exit and the robot would not drive.
  while (true) {
    wait(100, msec);
  }
}
