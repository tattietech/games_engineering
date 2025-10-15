# Games Engineering

This repository contains a collection of practice projects I completed for my Games Engineering module at university. Each practical demonstrates different game development concepts and techniques using C++ and SFML.

## Projects

### Practical 1 - Pong
A classic Pong game implementation featuring two paddles and ball physics.

### Practical 2 - Space Invaders
Recreation of the iconic Space Invaders arcade game with player controls, enemy movement patterns, and shooting mechanics.

### Practical 3 - Tile Engine
A tile-based game engine with level loading capabilities. Features a custom level system that reads map data from files and renders tile-based environments.

### Practical 4 - Pacman
Implementation of Pacman with player movement, ghost AI, and maze navigation using the Entity Component Model (ECM) architecture.

## Technologies Used

- **C++14**: Primary programming language
- **SFML**: Simple and Fast Multimedia Library for graphics, input, and windowing
- **CMake**: Build system configuration

## Custom Libraries

The project includes several custom-built libraries:

- **lib_tile_level_loader**: Level loading system for tile-based maps
- **lib_maths**: Mathematics utilities for game development
- **lib_ecm**: Entity Component Model system for game object management

## Building the Project

### Prerequisites
- CMake 3.9 or higher
- C++14 compatible compiler
- SFML library (included as submodule)

### Build Instructions

1. Clone the repository with submodules:
   ```bash
   git clone --recursive https://github.com/tattietech/games_engineering.git
   cd games_engineering
   ```

2. Create a build directory and run CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. Build the project:
   ```bash
   cmake --build .
   ```

4. Run the executables:
   - `PRACTICAL_1` - Pong
   - `PRACTICAL_2` - Space Invaders
   - `PRACTICAL_3` - Tile Engine
   - `PRACTICAL_4` - Pacman

## Project Structure

```
games_engineering/
├── practical_1/          # Pong game
├── practical_2/          # Space Invaders
├── practical_3/          # Tile Engine
├── practical_4/          # Pacman
├── lib_tile_level_loader/  # Tile level loading library
├── lib_maths/            # Math utilities
├── lib_ecm/              # Entity Component Model
├── res/                  # Resources (fonts, images, levels)
└── CMakeLists.txt        # Build configuration
```

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.