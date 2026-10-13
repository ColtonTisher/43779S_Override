/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autons.h                                                  */
/*    Description:  Autonomous routine list and the selector used by main.    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Read this header only once, even if several files include it.
#pragma once

// A list of every autonomous routine the robot knows.
// "enum class" is a set of named choices, safer than plain numbers because
// you cannot accidentally mix them with unrelated integers.
// To add a routine: add a name here, write a run function, include its header
// from autons.cpp, and add a case in runSelectedAuton().
enum class Auton {
  // Do nothing. Useful if you need the robot to sit still for autonomous.
  None,
  // Short straight drive, used to check ports and wheel size.
  DriveForward,
  // The skills-challenge route. Still a short stub until the route is planned.
  Skills,
};

// Which routine autonomous() will run. "extern" means the real variable
// lives in autons.cpp, so every file shares one copy.
// Change that value, or call selectNextAuton() once a button picker exists.
extern Auton selectedAuton;

// Turn an Auton choice into words for the brain screen.
// "const char *" is a piece of text that this function does not modify.
const char *autonName(Auton auton);

// Move to the next routine in the list, wrapping from Skills back to None.
// Handy for a controller or brain button later.
void selectNextAuton();

// Run whichever routine selectedAuton currently names.
void runSelectedAuton();
