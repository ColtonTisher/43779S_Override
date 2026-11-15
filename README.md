# 43779S Override

VEX V5 competition code for team 43779S, written for the 2026-2027 high school game OVERRIDE.

The program is a competition template. The field starts autonomous, then driver control. Until the field is connected, the brain runs setup and then waits.

## Files

| File | What it is |
|---|---|
| `src/main.cpp` | Match setup, autonomous call, and driver control |
| `include/robot-config.h` | Ports, gearing, and device names |
| `src/robot-config.cpp` | Creates the motors and sets brake modes |
| `include/autons.h` | List of autonomous routines, and which one runs |
| `src/autons.cpp` | Runs the selected routine and prints its name |
| `include/auton_controls.h` | Shared drive, turn, and score moves |
| `src/auton_skills.cpp` | 60-second skills route |
| `src/auton_match_left.cpp` | 15-second route from the left corner |
| `src/auton_match_right.cpp` | 15-second route from the right corner |
| `ROBOT.md` | Hardware list. Update the code from this file when the robot changes |
| `GAME.md` | Working summary of the OVERRIDE rules |

`include/` holds the names other files are allowed to use. `src/` holds the code that runs. The `vex/` folder is the VEXcode build system. Leave it alone.

## Driver control

Tank drive. The left stick (Axis3) runs the left wheels. The right stick (Axis2) runs the right wheels.

| Buttons | Mechanism | Speed |
|---|---|---|
| R1 / R2 | Arm toward the front / toward the back | 50% |
| L1 / L2 | Lift up / down | 100% |
| X | Claw intake | 100% |
| B, short press | Claw stop | hold |
| B, held 2 seconds | Claw open 30 degrees | 30% |
| Up / Down | Wrist tilt | 50% |
| Left | Pneumatic on port A | on while held |

Releasing the lift buttons holds the string so it does not unwind. The arm moves only while R1 or R2 is held, then holds where you let go. Hold X to intake with the claw. Tap B to stop it. Hold B for 2 seconds and it turns 30 degrees open, then holds. Up and Down tilt the wrist, and it holds when you let go. The scorer has no driver buttons yet.

## Autonomous

The routine that runs is `selectedAuton` in `src/autons.cpp`. It is currently Match Left.

| Routine | What it does now |
|---|---|
| None | Sits still |
| Skills | Drives 12 inches at 40% |
| Match Left | Drives 24 inches at 50% |
| Match Right | Drives 24 inches at 50% |

Write a path by calling the shared moves. A negative distance drives backward. A negative turn goes left. A negative mechanism speed runs in reverse.

```cpp
void runMatchLeft() {
  autonDrive(24, 50);          // 24 inches forward, measured by the tracking wheel
  autonTurn(90, 40);           // 90 degrees right, measured by the inertial
  autonDriveToWall("front", 8, 40); // stop 8 inches from the front wall
  autonDriveToWall("left", 6, 40);  // turn left, stop 6 inches from that wall, turn back
  autonScore(50, 800);         // scorer for 0.8 seconds
  autonStop();
}
```

To add a routine, add a name in `include/autons.h`, give it a label in `autonName()`, and call it from `runSelectedAuton()`. Then add a row to `ROBOT.md`.

## Changing the robot

Edit `ROBOT.md` first, then update the matching code:

- Ports, cartridges, and wheel size go in `include/robot-config.h` and `src/robot-config.cpp`.
- Controller buttons go in `src/main.cpp`.
- A device set to `unused` uses port 21. Leave that brain port empty.

A 6-motor drive of 11 W motors is over the 55 W drive limit. Check motor wattage before inspection. Details are in `GAME.md`.

## Build

Open this folder in VS Code with the VEX extension and download the program to the brain. The makefile builds every `.cpp` file in `src/`.
