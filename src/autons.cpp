/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autons.cpp                                                */
/*    Description:  Chooses and runs one autonomous routine.                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "autons.h"

#include "auton_match_left.h"
#include "auton_match_right.h"
#include "auton_skills.h"
#include "robot-config.h"

using namespace vex;

// Change this to pick the routine that runs at the start of autonomous.
Auton selectedAuton = Auton::MatchLeft;

const char *autonName(Auton auton) {
  switch (auton) {
  case Auton::None:
    return "None";
  case Auton::Skills:
    return "Skills";
  case Auton::MatchLeft:
    return "Match Left";
  case Auton::MatchRight:
    return "Match Right";
  }
  return "Unknown";
}

void selectNextAuton() {
  switch (selectedAuton) {
  case Auton::None:
    selectedAuton = Auton::Skills;
    break;
  case Auton::Skills:
    selectedAuton = Auton::MatchLeft;
    break;
  case Auton::MatchLeft:
    selectedAuton = Auton::MatchRight;
    break;
  case Auton::MatchRight:
    selectedAuton = Auton::None;
    break;
  }
}

void runSelectedAuton() {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Auton: %s", autonName(selectedAuton));

  switch (selectedAuton) {
  case Auton::None:
    break;
  case Auton::Skills:
    runSkills();
    break;
  case Auton::MatchLeft:
    runMatchLeft();
    break;
  case Auton::MatchRight:
    runMatchRight();
    break;
  }
}
