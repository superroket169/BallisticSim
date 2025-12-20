# BallisticSim

BallisticSim is a simple physics simulation written in C++ using SFML.
It simulates the vertical motion of an object under gravity and shows the motion visually.

## Overview
The project simulates an object affected by gravity.
The object moves, collides with the ground, and reacts based on basic physics rules.
The simulation is visual and runs in a window using SFML.

## Features
- Gravity-based motion simulation
- Ground collision handling
- Real-time rendering with SFML
- Basic UI elements (buttons and text)
- Height and motion calculated using physics formulas

## Tech Stack
- C++
- SFML (Graphics)
- Basic physics math

## How It Works
- Gravity constantly affects the object
- Velocity and position are updated every frame
- When the object hits the ground, the simulation reacts accordingly
- The simulation runs in real time inside a window

## Status
Beta — core simulation works, UI and controls are still improving.

## Planned Features
- Start / reset button
- Main menu
- Live height display
- Result and statistics panel
- Improved user interface

## Build & Run
Make sure SFML is installed.

Example (Linux):
```bash
g++ main.cpp -o BallisticSim -lsfml-graphics -lsfml-window -lsfml-system
./BallisticSim
