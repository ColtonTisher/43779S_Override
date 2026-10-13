/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_controls.h                                          */
/*    Description:  Shared moves used by every autonomous routine.            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once

// Drive straight. Negative inches drives backward. speedPercent is 1 to 100.
void autonDrive(double inches, double speedPercent);

// Turn in place. Positive degrees turns right, negative turns left.
void autonTurn(double degrees, double speedPercent);

// Spin the intake, then stop. Negative speed runs it in reverse.
// 1000 milliseconds is one second. Does nothing if the intake is not installed.
void autonIntake(double speedPercent, int milliseconds);

// Spin the scorer, then stop. Negative speed runs it in reverse.
// Does nothing if the scorer is not installed.
void autonScore(double speedPercent, int milliseconds);

// Stop the drive, intake, and scorer.
void autonStop();
