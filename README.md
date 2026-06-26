# Quadruped Robot – Autonomous Navigation

A 4-legged walking robot built in C++ (Arduino), capable of stable multi-terrain locomotion using a custom crawl gait sequence with independent per-leg servo control.

## Demo
🎥 [Watch the robot walk — LinkedIn Demo](https://www.linkedin.com/posts/ipshita-maheshwari-56426230a_robotics-quadrupedrobot-embeddedsystems-ugcPost-7459198789539667968-T06U/)

---

## Tech Stack
| Layer | Technology |
|---|---|
| Language | C++ (Arduino) |
| Hardware | Adafruit PWM Servo Driver (PCA9685) |
| Communication | I2C protocol |
| Actuators | 8 servo motors (coxa + femur per leg) |
| IDE | Arduino IDE |

---

## How It Works

### Gait Sequence
The robot uses a **crawl gait** — one leg moves at a time while the other three remain grounded for stability. Each leg follows a 5-phase motion cycle:

1. **Lift** — femur servo raises the leg off the ground
2. **Forward** — coxa servo swings the leg forward
3. **Down** — femur servo lowers the leg to the ground
4. **Push** — coxa servo pushes backward to propel the body
5. **Neutral** — leg returns to base position

### Servo Control
- Custom `angleToPulse()` function maps servo angles (0°–180°) to PWM pulse widths (150–600)
- All 8 servos controlled via I2C using the Adafruit PCA9685 PWM driver
- Per-leg directional inversion parameters handle mirrored servo mounting geometry

### Parameter Tuning
8 independent parameters tuned per leg through iterative physical testing:
- **Base angles** (coxa + femur) — neutral standing position per leg
- **Lift height** — how high each leg raises during swing phase
- **Step size** — forward stride length per gait cycle
- **Direction** — sign inversion for mirrored servo orientations

---

## Project Structure
```
quadruped-robot/
├── quadruped.ino       # Main gait control code
└── README.md
```

---

## Current Development
Actively integrating a **custom PCB** and **camera module** for real-time visual navigation and obstacle avoidance — expected completion July 2026.

> Note: This is the base gait implementation. Current hardware version includes additional tuning parameters not reflected here.

## Built By
Ipshita Maheshwari — [LinkedIn](https://www.linkedin.com/in/ipshita-maheshwari-56426230a)
