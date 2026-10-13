# 43779S Override

VEX V5 competition code for team 43779S, written for the 2026-2027 high school game OVERRIDE.

The program is a competition template. The field starts autonomous, then driver control. Until the field is connected, the brain runs setup and then waits.

This file is the hardware list and the working summary of the OVERRIDE rules. Fill in the Robot section, then ask to update the code from this file. The game notes are for writing robot code. They are not a copy of the manual and they are not a strategy guide. If they disagree with the current official manual or an official Q&A, the official source wins.

## Files

| File | What it is |
|---|---|
| `src/main.cpp` | Match setup, autonomous call, and driver control |
| `include/robot-config.h` | Ports, gearing, and device names |
| `src/robot-config.cpp` | Creates the motors and sets brake modes |
| `include/autons.h` | List of autonomous routines, and which one runs |
| `src/autons.cpp` | Runs the selected routine and prints its name |
| `include/auton_controls.h` | Shared drive, turn, intake, and score moves |
| `src/auton_skills.cpp` | 60-second skills route |
| `src/auton_match_left.cpp` | 15-second route from the left corner |
| `src/auton_match_right.cpp` | 15-second route from the right corner |

`include/` holds the names other files are allowed to use. `src/` holds the code that runs. The `vex/` folder is the VEXcode build system. Leave it alone.

Code that should follow the Robot and Autonomous sections:

- `include/robot-config.h` and `src/robot-config.cpp` for ports, gearing, and devices
- `src/main.cpp` for driver controls
- `include/autons.h`, `src/auton_*.cpp`, and `include/auton_controls.h` when routines are added or removed

## Robot

Leave a cell as `unused` when that device is not on the robot yet. `unused` maps to `PORT21`, which must stay empty.

### Drivetrain

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

### Mechanisms

One row per motor that is not part of the drive. `Role` is a short name used in code (`Intake`, `Scorer`). `Buttons` are the controller buttons that run it during driver control, written as `forward / reverse`.

| Role | Port | Cartridge | Reversed | Hold | Buttons |
|---|---|---|---|---|---|
| Intake | unused | green | no | coast | R1 / R2 |
| Scorer | unused | red | no | hold | L1 / L2 |

`Hold` is `coast`, `brake`, or `hold`.

### Sensors

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

Tank drive. The left stick (Axis3) runs the left wheels. The right stick (Axis2) runs the right wheels.

| Buttons | Mechanism | Speed |
|---|---|---|
| R1 / R2 | Intake forward / reverse | 100% |
| L1 / L2 | Scorer forward / reverse | 50% |

The intake and scorer are skipped until their ports are set in the Robot section. Releasing the buttons stops that mechanism.

## Autonomous

The routine in `Selected` is the one `autonomous()` runs. In code that value is `selectedAuton` in `src/autons.cpp`.

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

Write a path by calling the shared moves. A negative distance drives backward. A negative turn goes left. A negative mechanism speed runs in reverse.

```cpp
void runMatchLeft() {
  autonDrive(24, 50);          // 24 inches forward at half speed
  autonTurn(90, 40);           // 90 degrees right at 40%
  autonIntake(100, 500);       // intake for half a second
  autonScore(50, 800);         // scorer for 0.8 seconds
  autonStop();
}
```

To add a routine, add a name in `include/autons.h`, give it a label in `autonName()`, and call it from `runSelectedAuton()`. Then add a row to the routine table above.

## Changing the robot

Edit the Robot section first, then update the matching code:

- Ports, cartridges, and wheel size go in `include/robot-config.h` and `src/robot-config.cpp`.
- Controller buttons go in `src/main.cpp`.
- A device set to `unused` uses port 21. Leave that brain port empty.

A 6-motor drive of 11 W motors is over the 55 W drive limit. Check motor wattage before inspection. Details are in the Game section.

## Build

Open this folder in VS Code with the VEX extension and download the program to the brain. The makefile builds every `.cpp` file in `src/`.

## Game

Working summary for team 43779S, a VEX V5 high school robot. Taken from the VEX V5 Robotics Competition Override Game Manual, version 2.1 (October 8, 2026). Effective October 15, 2026.

Official manual: https://link.vex.com/docs/26-27/v5rc/game-manual

Next scheduled manual update: version 2.2 on December 3, 2026, effective December 10, 2026. Re-read the scoring and specific game rules when a new version comes out.

### Match clock

A head-to-head match is 2:00.

- Autonomous Period: 0:15. No controller input. The robot runs only the program registered with `Competition.autonomous`.
- Driver Controlled Period: 1:45. The last 10 seconds are the Endgame.
- Scores are checked after the match, up to 5 seconds after 0:00, once everything has stopped. Do not write code that keeps moving after the match to sneak in a score. That is a penalty, and the extra motion does not count.

Skills matches are 1:00. Driving Skills is all driver control. Autonomous Coding Skills is all autonomous. The robot must start in a legal spot next to the red alliance station. Skills uses a different object layout, and the GPS code strip is required for Autonomous Coding Skills.

### What scores

Score by stacking Pins and Cups on Goals, setting Toggles, and finishing in the Midfield.

| Action | Points |
|---|---|
| Each scored alliance-colored Pin Half | 5 |
| Each scored yellow Pin Half | 10 |
| Each robot ending at least partly in the Midfield | 8 |
| Autonomous Bonus (higher autonomous score) | 12, or 6 each if tied |

A Pin has two Pin Halves. A Pin Half scores only if that half is visible. A half hidden inside a Goal, or inside the opaque half of a Cup, does not score.

Yellow Pin Halves score only if the alliance Owns them:

- In a corner Goal, the Toggle in that corner must be fully seated on the alliance color, and no robot may be touching that Toggle.
- In the center Goal, the alliance must finish with more robots in the Midfield. A tie means those yellow halves score for nobody.

The Midfield is the square in the middle of the field, bounded by the inner edges of the white tape. Any part of the robot inside that volume counts. Midfield points and center-Goal yellow ownership are end-of-match only. They are not part of the autonomous score.

### Autonomous Win Point

At a normal event, an alliance earns the Autonomous Win Point if it finishes autonomous with all of these, and no penalties during autonomous:

1. At least 6 Pin Halves scored for that alliance, not counting halves scored on the opponent's side of the Autonomous Line.
2. At least 2 Goals that each hold at least 2 Pin Halves scored for that alliance. Same side limit.
3. Neither alliance robot is touching the field wall.

Events that qualify straight to Worlds use a harder bar: 7 Pin Halves, and 3 Goals with at least 2 scored halves each. The wall rule stays the same.

Any penalty in autonomous gives the Autonomous Bonus to the other alliance and blocks the Autonomous Win Point. If both alliances break a rule, nobody gets the bonus.

During autonomous the robot may not touch tiles, objects, or field pieces on the other side of the Autonomous Line. Objects that start on that line (28 of them) are neutral and either alliance may use them. The center is also open to both alliances. Do not code an autonomous that drives onto the opponent's half.

### Objects and possession

- A Pin is about 1.6 in (40 mm) across and 6.5 in (165 mm) tall. Colors are red/yellow, blue/yellow, red/blue, and yellow/yellow.
- A Cup is about 3.15 in (80 mm) across and 6.5 in (164.5 mm) tall. One half is clear, one half is gray and opaque.
- Each robot gets one preload Pin: red/yellow if playing red, blue/yellow if playing blue. It must touch that robot and nothing else that scores.
- A robot may possess at most 1 Pin and 1 Cup at the same time. Possession means the robot fully supports the object, or the object stays with the robot no matter which way it drives. Pushing objects with the front of the robot is not possession, even with a scooped front.
- If the robot is holding too many, it must drop the extra ones before it scores, touches a Goal or Toggle, or parks in the Midfield.
- Mechanisms must let scoring objects fall out with the power off.

### Field pieces the code should know

12 ft x 12 ft field, 6 tiles by 6 tiles. Outer size on the field drawing is about 140.41 in (3566.4 mm).

Nine Goals. Opening is about 2.37 in (60.1 mm) across, so a Pin nests in it. A Cup nests on a Pin.

| Goal | Height | Where |
|---|---|---|
| Alliance (red or blue) | 3.25 in (82.5 mm) | One in each of the four corners |
| Neutral short | 5.77 in (146.5 mm) | One more in each corner |
| Neutral tall (center) | 8.77 in (222.7 mm) | Middle of the field |

Four Toggles, one on the wall of each corner. Each is a long triangle, about 26 in (660 mm) long, with red, blue, and yellow faces. It must sit fully against its mounts to count as set. Robot contact makes it neutral.

Four Loaders, two beside each alliance station. Drivers drop match loads in from the top or the back during driver control only. The robot takes them out of the bottom. The bottom opening is about 4.02 in (102 mm) wide. Do not code the robot to take objects from the other alliance's loaders.

Alliance Goals are protected: do not touch the other alliance's colored Goals or the stacks on them. Do not knock placed objects out of neutral Goals. During the Endgame, do not place objects on the center Goal.

### Robot limits that affect this code

- Starting size is 18 x 18 x 18 in. Once the match starts, the footprint may grow to 24 x 24 in. Height may grow to 50 in. The robot must be still at the start: no motors moving.
- Start touching the alliance wall and the tiles, on the alliance side of the Autonomous Line, alone in a corner, not touching Goals, Loaders, Load Zones, or Toggles.
- One V5 brain. Program must be a competition template so the field can enable and disable it. This project already does that in `src/main.cpp`.
- Motors on the whole robot may total at most 88 W. The drive (subsystem 2) may total at most 55 W. An 11 W motor is the 276-4840. A 5.5 W motor is the 276-4842. Eight 11 W motors is the maximum if they are all 11 W. Six 11 W drive motors is 66 W, which is over the 55 W drive cap. A legal 6-motor drive needs a mix that stays at or under 55 W, such as four 11 W and two 5.5 W. The drive in the Robot section does not say motor wattage. Check it before inspection.
- VEXos 1.1.5 or newer. No beta firmware. VEXnet for head-to-head matches. Bluetooth is allowed in the pit and in skills.
- The brain team-number field must be the registered number and letter with no spaces, for Smart Field Control.
- License plates with the team number go on two opposite sides and must stay visible. They are not mounted on a moving intake.

### What the mechanisms are for

The game is stacking and setting Toggles, plus a Midfield park in the last 10 seconds.

- Intake: pick up one Pin or one Cup. Must be able to release without power.
- Scorer: place a Pin into a Goal (openings start at 3.25 in tall) and nest a Cup on a placed Pin. Highest Goal opening is about 8.77 in off the floor, before any stack height.
- A separate action can flip a Toggle on the wall. The Toggle must be left fully seated, and the robot must back off so it is not touching it.
- Driver control should make it easy to drop an extra object, because holding two Pins or two Cups is illegal.
- Autonomous should stay on its own half, score Pin Halves, use more than one Goal, and finish off the wall if an Autonomous Win Point is the goal.
- Skills should be able to score on every Goal, use the red loaders, and end in the Midfield so center yellow halves count.
