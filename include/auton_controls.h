/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_controls.h                                          */
/*    Description:  Shared moves used by every autonomous routine.            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once

// Drive straight using the tracking wheels. Negative inches drives backward.
// speedPercent is 1 to 100.
void autonDrive(double inches, double speedPercent);

// Turn in place using the inertial sensor. Positive degrees turns right,
// negative turns left.
void autonTurn(double degrees, double speedPercent);

// Drive until that side is the target distance from a wall, then stop.
// side is "front", "back", "left", or "right".
// Left and right turn to face the wall, drive, then turn back to the start heading.
void autonDriveToWall(const char *side, double inches, double speedPercent);

// Spin the scorer, then stop. Negative speed runs it in reverse.
// 1000 milliseconds is one second. Does nothing if the scorer is not installed.
void autonScore(double speedPercent, int milliseconds);

// Spin the claw to intake, then crack it open. Does nothing if the claw is not installed.
void autonClawIntake(int milliseconds);

// Stop the drive, scorer, lift, arm, and claw.
void autonStop();
