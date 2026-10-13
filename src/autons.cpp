/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autons.cpp                                                */
/*    Description:  Dispatches the auton selected in autons.h.                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// The list of routines and the function names other files call.
#include "autons.h"

// Each route lives in its own file. Include the header to call it.
#include "auton_skills.h"
#include "auton_match_left.h"
#include "auton_match_right.h"
// Brain is declared here, and we print the chosen routine on its screen.
#include "robot-config.h"

// So we can write Brain without the vex:: prefix.
using namespace vex;

// The routine that runs when the match enters autonomous.
// This is the one real copy of selectedAuton. The header only announces it.
// MatchLeft is the default until a picker chooses skills or the other side.
Auton selectedAuton = Auton::MatchLeft;

// Look up the screen label for a routine.
// A switch picks one return based on which Auton value was passed in.
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
  // If a new enum value is added and this switch is not updated, show this
  // instead of crashing. It is a hint that the list and this function disagree.
  return "Unknown";
}

// Step to the next routine. The order matches the enum in autons.h.
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
    // Wrap around so a later button can cycle forever.
    selectedAuton = Auton::None;
    break;
  }
}

// Clear the screen, show the name, then run that routine.
// Called from autonomous() in main.cpp when the match starts.
void runSelectedAuton() {
  Brain.Screen.clearScreen();
  // (1, 1) is the top-left of the brain screen.
  Brain.Screen.setCursor(1, 1);
  // %s means "insert the text from the next argument here."
  Brain.Screen.print("Auton: %s", autonName(selectedAuton));

  switch (selectedAuton) {
  case Auton::None:
    // Empty on purpose. The robot stays still for the whole autonomous period.
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
