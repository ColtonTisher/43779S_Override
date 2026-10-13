# OVERRIDE game notes

Working summary for team 43779S, a VEX V5 high school robot. Taken from the VEX V5 Robotics Competition Override Game Manual, version 2.1 (October 8, 2026). Effective October 15, 2026.

This file is for writing robot code. It is not a copy of the manual and it is not a strategy guide. If this file and the current official manual or an official Q&A disagree, the official source wins.

Official manual: https://link.vex.com/docs/26-27/v5rc/game-manual

Next scheduled manual update: version 2.2 on December 3, 2026, effective December 10, 2026. Re-read the scoring and specific game rules when a new version comes out.

## Match clock

A head-to-head match is 2:00.

- Autonomous Period: 0:15. No controller input. The robot runs only the program registered with `Competition.autonomous`.
- Driver Controlled Period: 1:45. The last 10 seconds are the Endgame.
- Scores are checked after the match, up to 5 seconds after 0:00, once everything has stopped. Do not write code that keeps moving after the match to sneak in a score. That is a penalty, and the extra motion does not count.

Skills matches are 1:00. Driving Skills is all driver control. Autonomous Coding Skills is all autonomous. The robot must start in a legal spot next to the red alliance station. Skills uses a different object layout, and the GPS code strip is required for Autonomous Coding Skills.

## What scores

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

## Autonomous Win Point

At a normal event, an alliance earns the Autonomous Win Point if it finishes autonomous with all of these, and no penalties during autonomous:

1. At least 6 Pin Halves scored for that alliance, not counting halves scored on the opponent's side of the Autonomous Line.
2. At least 2 Goals that each hold at least 2 Pin Halves scored for that alliance. Same side limit.
3. Neither alliance robot is touching the field wall.

Events that qualify straight to Worlds use a harder bar: 7 Pin Halves, and 3 Goals with at least 2 scored halves each. The wall rule stays the same.

Any penalty in autonomous gives the Autonomous Bonus to the other alliance and blocks the Autonomous Win Point. If both alliances break a rule, nobody gets the bonus.

During autonomous the robot may not touch tiles, objects, or field pieces on the other side of the Autonomous Line. Objects that start on that line (28 of them) are neutral and either alliance may use them. The center is also open to both alliances. Do not code an autonomous that drives onto the opponent's half.

## Objects and possession

- A Pin is about 1.6 in (40 mm) across and 6.5 in (165 mm) tall. Colors are red/yellow, blue/yellow, red/blue, and yellow/yellow.
- A Cup is about 3.15 in (80 mm) across and 6.5 in (164.5 mm) tall. One half is clear, one half is gray and opaque.
- Each robot gets one preload Pin: red/yellow if playing red, blue/yellow if playing blue. It must touch that robot and nothing else that scores.
- A robot may possess at most 1 Pin and 1 Cup at the same time. Possession means the robot fully supports the object, or the object stays with the robot no matter which way it drives. Pushing objects with the front of the robot is not possession, even with a scooped front.
- If the robot is holding too many, it must drop the extra ones before it scores, touches a Goal or Toggle, or parks in the Midfield.
- Mechanisms must let scoring objects fall out with the power off.

## Field pieces the code should know

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

## Robot limits that affect this code

- Starting size is 18 x 18 x 18 in. Once the match starts, the footprint may grow to 24 x 24 in. Height may grow to 50 in. The robot must be still at the start: no motors moving.
- Start touching the alliance wall and the tiles, on the alliance side of the Autonomous Line, alone in a corner, not touching Goals, Loaders, Load Zones, or Toggles.
- One V5 brain. Program must be a competition template so the field can enable and disable it. This project already does that in `src/main.cpp`.
- Motors on the whole robot may total at most 88 W. The drive (subsystem 2) may total at most 55 W. An 11 W motor is the 276-4840. A 5.5 W motor is the 276-4842. Eight 11 W motors is the maximum if they are all 11 W. Six 11 W drive motors is 66 W, which is over the 55 W drive cap. A legal 6-motor drive needs a mix that stays at or under 55 W, such as four 11 W and two 5.5 W. The current `ROBOT.md` drive does not say motor wattage. Check it before inspection.
- VEXos 1.1.5 or newer. No beta firmware. VEXnet for head-to-head matches. Bluetooth is allowed in the pit and in skills.
- The brain team-number field must be the registered number and letter with no spaces, for Smart Field Control.
- License plates with the team number go on two opposite sides and must stay visible. They are not mounted on a moving intake.

## What the mechanisms are for

The game is stacking and setting Toggles, plus a Midfield park in the last 10 seconds.

- Intake: pick up one Pin or one Cup. Must be able to release without power.
- Scorer: place a Pin into a Goal (openings start at 3.25 in tall) and nest a Cup on a placed Pin. Highest Goal opening is about 8.77 in off the floor, before any stack height.
- A separate action can flip a Toggle on the wall. The Toggle must be left fully seated, and the robot must back off so it is not touching it.
- Driver control should make it easy to drop an extra object, because holding two Pins or two Cups is illegal.
- Autonomous should stay on its own half, score Pin Halves, use more than one Goal, and finish off the wall if an Autonomous Win Point is the goal.
- Skills should be able to score on every Goal, use the red loaders, and end in the Midfield so center yellow halves count.
