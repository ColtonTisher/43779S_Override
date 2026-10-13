/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       colto                                                     */
/*    Created:      10/8/2026, 9:10:30 PM                                     */
/*    Description:  Match entry point. Setup, autonomous, then driver control.*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "autons.h"
#include "robot-config.h"
#include "vex.h"

using namespace vex;

// Talks to the field. The field decides when each match period may run.
competition Competition;

// Percent power for the mechanisms. Drive speed comes from the joysticks.
const int INTAKE_SPEED = 100;
const int SCORER_SPEED = 50;

// One button spins forward, the other spins backward. Neither button stops.
static void runMotor(motor &device, bool forwardButton, bool reverseButton, int speed) {
  if (forwardButton) {
    device.spin(forward, speed, percent);
  } else if (reverseButton) {
    device.spin(reverse, speed, percent);
  } else {
    device.stop();
  }
}

// Runs once when the brain turns on. Keep it short so autonomous is not late.
void pre_auton(void) {
  initRobot();

  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Auton: %s", autonName(selectedAuton));
}

// The field calls this once at the start of autonomous.
void autonomous(void) {
  runSelectedAuton();
}

// The field calls this when driver control starts. It runs until the match ends.
void usercontrol(void) {
  while (true) {
    // Tank drive. Left stick drives the left wheels, right stick the right wheels.
    LeftDrive.spin(forward, Controller1.Axis3.position(), percent);
    RightDrive.spin(forward, Controller1.Axis2.position(), percent);

    // R1 / R2 run the intake. L1 / L2 run the scorer. Skipped if not installed.
    if (hasIntake()) {
      runMotor(Intake, Controller1.ButtonR1.pressing(), Controller1.ButtonR2.pressing(), INTAKE_SPEED);
    }
    if (hasScorer()) {
      runMotor(Scorer, Controller1.ButtonL1.pressing(), Controller1.ButtonL2.pressing(), SCORER_SPEED);
    }

    // Read the controller 50 times per second.
    wait(20, msec);
  }
}

// Register the match functions, set up the robot, then wait for the field.
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  // Leaving main would end the program, so the robot would not drive.
  while (true) {
    wait(100, msec);
  }
}
