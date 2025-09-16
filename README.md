# README.md

# C++ Cloth Simulation

A simple interactive cloth simulation built in **C++** using **SFML**.
Click on the lines to tear the cloth, and watch the particles respond to gravity in real time!

---

## Features

* Verlet integration for realistic particle motion
* Constraints between particles to simulate cloth
* Interactive tearing with mouse clicks
* Pinned particles to hold the cloth in place
* Customizable grid size, spacing, and gravity

---

## Requirements

* C++17 compatible compiler (Clang, GCC, or MSVC)
* [SFML](https://www.sfml-dev.org/) 2.5 or newer

---

## Installation / Build

### On Mac:

1. Make sure SFML is installed (via Homebrew):

   ```bash
   brew install sfml
   ```

2. Compile the project:

   ```bash
   clang++ -std=c++17 main.cpp -Iinclude -o cloth-simulation -lsfml-graphics -lsfml-window -lsfml-system
   ```

3. Run the simulation:

   ```bash
   ./cloth-simulation
   ```

---

## Project Structure

```
cloth-simulation/
├── include/
│   ├── particle.h
│   ├── constraint.h
│   └── input_handler.h
├── main.cpp
├── README.md
└── .gitignore
```

---

## Usage

* **Left-click** on a line to tear the cloth.
* The top row of particles is pinned and holds the cloth in place.
* Modify `ROWS`, `COLS`, `SPACING`, and `GRAVITY` in `main.cpp` to change cloth behavior.

---

## License

This project is open source and free to use under the MIT License.

