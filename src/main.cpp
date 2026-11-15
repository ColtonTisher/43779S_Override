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
const int LIFT_SPEED = 100;
const int ARM_SPEED = 50;
const int WRIST_SPEED = 50;

// One button spins forward, the other spins backward. Releasing both holds.
static void runMotor(motor &device, bool forwardButton, bool reverseButton, int speed) {
  if (forwardButton) {
    device.spin(forward, speed, percent);
  } else if (reverseButton) {
    device.spin(reverse, speed, percent);
  } else {
    device.stop();
  }
}

// X keeps the claw intaking. A short B press stops it. Holding B for 2 seconds
// turns it 30 degrees open, then holds. Opening starts when the hold time is up.
static void runClaw(bool intakeButton, bool actionButton) {
  static bool actionWasPressed = false;
  static bool opening = false;
  static timer actionHold;

  bool actionJustPressed = actionButton && !actionWasPressed;
  bool actionJustReleased = !actionButton && actionWasPressed;
  actionWasPressed = actionButton;

  if (intakeButton) {
    opening = false;
    Claw.spin(forward, 100, percent);
    return;
  }

  if (actionJustPressed) {
    actionHold.reset();
  }

  if (actionButton && actionHold.time(msec) >= CLAW_OPEN_HOLD_MSEC && !opening) {
    Claw.setPosition(0, degrees);
    Claw.spin(reverse, CLAW_OPEN_SPEED, percent);
    opening = true;
  }

  if (actionJustReleased && !opening) {
    Claw.stop();
  }

  if (opening) {
    double turned = Claw.position(degrees);
    if (turned < 0) {
      turned = -turned;
    }
    if (turned >= CLAW_OPEN_DEGREES) {
      Claw.stop();
      opening = false;
    }
  }
}

// Same button logic for two motors that must spin together.
static void runMotorGroup(motor_group &devices, bool forwardButton, bool reverseButton, int speed) {
  if (forwardButton) {
    devices.spin(forward, speed, percent);
  } else if (reverseButton) {
    devices.spin(reverse, speed, percent);
  } else {
    devices.stop();
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

    // R1 moves the arm toward the front. R2 moves it toward the back.
    // L1 winds the lift up. L2 lets it down.
    // X intakes with the claw. A short B stops it. Hold B for 2 seconds to open it.
    // Up tilts the wrist one way. Down tilts it the other way.
    if (hasLift()) {
      // Port 9 is already reversed in its setup, so both get the same command.
      if (Controller1.ButtonL1.pressing()) {
        LiftA.spin(forward, LIFT_SPEED, percent);
        LiftB.spin(forward, LIFT_SPEED, percent);
      } else if (Controller1.ButtonL2.pressing()) {
        LiftA.spin(reverse, LIFT_SPEED, percent);
        LiftB.spin(reverse, LIFT_SPEED, percent);
      } else {
        LiftA.stop();
        LiftB.stop();
      }
    }
    if (hasArm()) {
      runMotor(Arm, Controller1.ButtonR1.pressing(), Controller1.ButtonR2.pressing(), ARM_SPEED);
    }
    if (hasClaw()) {
      runClaw(Controller1.ButtonX.pressing(), Controller1.ButtonB.pressing());
    }
    if (hasWrist()) {
      runMotor(Wrist, Controller1.ButtonUp.pressing(), Controller1.ButtonDown.pressing(), WRIST_SPEED);
    }

    // Left arrow turns the port A pneumatic on. Releasing it turns the solenoid off.
    Pneumatic.set(Controller1.ButtonLeft.pressing());

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
