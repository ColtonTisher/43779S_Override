# Robot spec

This file is the source of truth for hardware. Fill it in, then ask to update the code from `ROBOT.md`.

Code that should follow this file:

- `include/robot-config.h` and `src/robot-config.cpp` for ports, gearing, and devices
- `src/main.cpp` for driver controls
- `include/autons.h`, `src/auton_*.cpp`, and `include/auton_controls.h` when routines are added or removed

Leave a cell as `unused` when that device is not on the robot yet. `unused` maps to `PORT21`, which must stay empty.

## Drivetrain

| Setting | Value |
|---|---|
| Type | tank |
| Motors per side | 2 |
| Cartridge | green |
| Wheel diameter (in) | 3.25 |
| Track width (mm) | 292.1 |
| Wheelbase (mm) | 279.4 |
| External gear ratio | 0.6 |

`Type` is `tank` or `arcade`.

`Cartridge` is `red` (100 rpm), `green` (200 rpm), or `blue` (600 rpm).

`External gear ratio` is motor turns per wheel turn. Use `1.0` for a direct drive. Use `0.6` for a 36-tooth driven gear on a 60-tooth wheel gear.

| Motor | Port | Reversed |
|---|---|---|
| Left front | 14 | yes |
| Left middle | unused | no |
| Left back | 13 | yes |
| Right front | 18 | no |
| Right middle | unused | yes |
| Right back | 19 | no |

For a 4-motor drive, set `Motors per side` to `2` and set `Left middle` and `Right middle` to `unused`.

## Mechanisms

One row per motor that is not part of the drive. `Role` is a short name used in code (`Scorer`). `Buttons` are the controller buttons that run it during driver control, written as `forward / reverse`.

| Role | Port | Cartridge | Reversed | Hold | Buttons |
|---|---|---|---|---|---|
| Scorer | unused | red | no | hold | unused |
| Lift A | 8 | green | no | hold | L1 / L2 |
| Lift B | 9 | green | yes | hold | L1 / L2 |
| Arm | 7 | red | no | hold | R1 / R2 |
| Claw | 15 | green | no | hold | X / B |
| Wrist | 11 | green | no | hold | Up / Down |

Lift A and Lift B share one shaft and face each other. Port 9 is commanded the opposite way from port 8 so they turn the shaft the same way. L1 winds the string up. L2 lets it down. Releasing both buttons holds the string.

The arm has no sensor. Hold R1 to move it toward the front. Hold R2 to move it toward the back. Releasing both holds it where it is.

The motor shaft has a 24-tooth gear driving a 72-tooth gear on the arm, so the output is 3 times slower than the motor.

The claw is a ratchet on port 15. Hold X and it spins to intake. A short press of B stops it. Hold B for more than 2 seconds and it turns 30 motor degrees the other way, then holds it open.

The wrist tilts the claw. Hold Up to tilt one way. Hold Down to tilt the other way. Releasing both holds it. It uses brain port 11, which used to be the left middle drive motor. Port 20 is empty.

`Hold` is `coast`, `brake`, or `hold`.

## Pneumatics

A 3-wire solenoid. `Port` is a letter `A` through `H` on the brain's 3-wire bank. `Button` is the controller button that turns it on while held. Releasing the button turns it off.

| Role | Port | Button |
|---|---|---|
| Pneumatic | A | Left |

## Sensors

| Sensor | Port | Notes |
|---|---|---|
| Inertial | 1 | Calibrated in pre_auton. Sits still for about 2 seconds. |
| Forward rotation | 10 | 2 inch omni, facing the front. 0.125 inches left of center. |
| Sideways rotation | 16 | 2 inch omni, perpendicular. 1.75 inches in front of center. |
| Distance front | 3 | Looks forward. |
| Distance left | 2 | Looks left. |
| Distance right | 5 | Looks right. |
| Distance back | 12 | Looks backward. |

Smart sensor ports are `1`–`20`, or `unused`. 3-wire ports are `A`–`H`. The arm has no sensor.

Autonomous drive and turn commands use the tracking wheels and the inertial sensor. `autonDriveToWall` stops at a measured wall distance. For left or right it turns to face that wall, drives, then turns back. Driver control still uses the joysticks.

## Driver control

| Setting | Value |
|---|---|
| Drive | tank |
| Left stick | Axis3 |
| Right stick | Axis2 |

For arcade, set `Drive` to `arcade` and name the forward and turn axes, for example `Axis3` and `Axis1`.

## Autonomous

The routine in `Selected` is the one `autonomous()` runs.

| Setting | Value |
|---|---|
| Selected | Match Left |

| Routine | File | Description |
|---|---|---|
| None | src/autons.cpp | Does nothing |
| Skills | src/auton_skills.cpp | Stub route, 12 inches at 40% |
| Match Left | src/auton_match_left.cpp | Drive 24 inches at 50% |
| Match Right | src/auton_match_right.cpp | Drive 24 inches at 50% |

Shared moves used by every routine live in `include/auton_controls.h` and `src/auton_controls.cpp`.

Add a row here when you want a new routine file.
