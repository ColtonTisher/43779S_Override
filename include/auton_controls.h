/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_controls.h                                          */
/*    Description:  Shared moves that every autonomous routine can call.      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// Read this header only once, even if several routine files include it.
#pragma once

// Drive straight for a set distance.
// inches is how far to go. Use a negative number to drive backward.
// speedPercent is 1 to 100. Slower is easier to watch while testing.
void autonDrive(double inches, double speedPercent);

// Turn in place by a set angle.
// degrees is how far to spin. Positive turns right, negative turns left.
// This uses the drivetrain math, so wheel size and track width must be right.
void autonTurn(double degrees, double speedPercent);

// Run the intake for a set time, then stop.
// Use a positive speed to take a piece in, and a negative speed to spit it out.
// milliseconds is how long to spin. 1000 milliseconds is one second.
void autonIntake(double speedPercent, int milliseconds);

// Run the scorer for a set time, then stop.
// Use a positive speed to score or raise, and a negative speed to reverse.
void autonScore(double speedPercent, int milliseconds);

// Stop the drive, intake, and scorer.
// Call this at the end of a routine so nothing keeps spinning.
void autonStop();
