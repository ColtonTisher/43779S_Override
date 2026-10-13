/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autons.h                                                  */
/*    Description:  Autonomous routine list and the selector used by main.    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once

// Add a routine in three places: this list, autonName(), and runSelectedAuton().
enum class Auton {
  None,       // Sit still.
  Skills,     // 60-second skills route. Whole field.
  MatchLeft,  // 15-second match route from the left corner.
  MatchRight, // 15-second match route from the right corner.
};

// The routine autonomous() will run. The real value lives in autons.cpp.
extern Auton selectedAuton;

// Screen label for a routine.
const char *autonName(Auton auton);

// None -> Skills -> MatchLeft -> MatchRight -> None.
void selectNextAuton();

// Run the routine named by selectedAuton.
void runSelectedAuton();
