/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_skills.cpp                                          */
/*    Description:  Skills route. Starts by the red station. Whole field.     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "auton_skills.h"
#include "auton_controls.h"

// Placeholder until the route is planned. End in the Midfield so the center
// yellow Pin Halves count.
void runSkills() {
  autonDrive(12, 40);
  autonStop();
}
