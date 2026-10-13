/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autons.cpp                                                */
/*    Description:  Dispatches the auton selected in autons.h.                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// The list of routines and the function names other files call.
#include "autons.h"

// Each routine lives in its own file. Include the header to call it.
#include "auton-drive-forward.h"
#include "auton-skills.h"
// Brain is declared here, and we print the chosen routine on its screen.
#include "robot-config.h"

// So we can write Brain and similar names without the vex:: prefix.
using namespace vex;

// The routine that runs when the match enters autonomous.
// This is the one real copy of selectedAuton. The header only announces it.
// DriveForward is the default so a new program does something testable.
Auton selectedAuton = Auton::DriveForward;

// Look up the screen label for a routine.
// A switch picks one return based on which Auton value was passed in.
const char *autonName(Auton auton) {
  switch (auton) {
  case Auton::None:
    return "None";
  case Auton::DriveForward:
    return "Drive Forward";
  case Auton::Skills:
    return "Skills";
  }
  // If a new enum value is added and this switch is not updated, show this
  // instead of crashing. It is a hint that the list and this function disagree.
  return "Unknown";
}

// Step to the next routine. The order matches the enum in autons.h.
void selectNextAuton() {
  switch (selectedAuton) {
  case Auton::None:
    selectedAuton = Auton::DriveForward;
    break;
  case Auton::DriveForward:
    selectedAuton = Auton::Skills;
    break;
  case Auton::Skills:
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
  case Auton::DriveForward:
    runDriveForward();
    break;
  case Auton::Skills:
    runSkills();
    break;
  }
}
