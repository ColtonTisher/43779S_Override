# Robot spec

This file is the source of truth for hardware. Fill it in, then ask to update the code from `ROBOT.md`.

Code that should follow this file:

- `include/robot-config.h` and `src/robot-config.cpp` for ports, gearing, and devices
- `src/main.cpp` for driver controls
- `include/autons.h` and `src/auton-*.cpp` when routines are added or removed

Leave a cell as `unused` when that device is not on the robot yet. `unused` maps to `PORT21`, which must stay empty.

## Drivetrain

| Setting | Value |
|---|---|
| Type | tank |
| Motors per side | 3 |
| Cartridge | blue |
| Wheel diameter (in) | 4 |
| Track width (mm) | 320 |
| Wheelbase (mm) | 260 |
| External gear ratio | 1.0 |

`Type` is `tank` or `arcade`.

`Cartridge` is `red` (100 rpm), `green` (200 rpm), or `blue` (600 rpm).

`External gear ratio` is motor turns per wheel turn. Use `1.0` for a direct drive. Use `0.6` for a 36-tooth driven gear on a 60-tooth wheel gear.

| Motor | Port | Reversed |
|---|---|---|
| Left front | 1 | no |
| Left middle | 2 | no |
| Left back | 3 | no |
| Right front | 11 | yes |
| Right middle | 12 | yes |
| Right back | 13 | yes |

For a 4-motor drive, set `Motors per side` to `2` and set `Left middle` and `Right middle` to `unused`.

## Mechanisms

One row per motor that is not part of the drive. `Role` is a short name used in code (`Intake`, `Scorer`). `Buttons` are the controller buttons that run it during driver control, written as `forward / reverse`.

| Role | Port | Cartridge | Reversed | Hold | Buttons |
|---|---|---|---|---|---|
| Intake | unused | green | no | coast | R1 / R2 |
| Scorer | unused | red | no | hold | L1 / L2 |

`Hold` is `coast`, `brake`, or `hold`.

## Sensors

| Sensor | Port | Notes |
|---|---|---|
| Inertial | unused | Calibrated in pre_auton when the port is set |

Sensor ports are smart ports `1`–`20`, or `unused`.

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
| Selected | Drive Forward |

| Routine | File | Description |
|---|---|---|
| None | src/autons.cpp | Does nothing |
| Drive Forward | src/auton-drive-forward.cpp | Drive 24 inches at 50% |
| Skills | src/auton-skills.cpp | Stub route, 12 inches at 40% |

Add a row here when you want a new routine file.
