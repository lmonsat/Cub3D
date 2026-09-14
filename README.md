# cub3D

A 42 common-core project inspired by **Wolfenstein 3D**, the first widely known first-person shooter. The goal is to build a dynamic first-person view of a maze using **raycasting**, MiniLibX, and a scene description file (`.cub`).

This implementation renders a textured 3D view and a separate **minimap** window.

## Overview

The program reads a `.cub` scene, validates the map and textures, then opens two windows:

- **Cube3D** — first-person view (walls, floor, ceiling)
- **Minimap** — 2D representation of the maze and the player

Walls are textured according to the cardinal direction they face (North, South, East, West). Floor and ceiling colors come from RGB values in the scene file.

## Features

- Parsing and validation of a `.cub` scene file
- Closed-map check (flood fill)
- Raycasting with DDA, perpendicular distances (no fish-eye)
- Distinct wall textures for N / S / E / W
- Floor and ceiling RGB colors
- Player movement with collision against walls
- Minimap in a second window
- Clean exit with `ESC` or the window close button



## Requirements

- Linux
- `gcc` / `cc`
- MiniLibX dependencies: `libx11-dev`, `libxext-dev`, `libbsd-dev`, `zlib1g-dev`
- Math library (`-lm`)

Example install on Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev zlib1g-dev
```



## Build

```bash
make
```

Useful targets:


| Target        | Description                   |
| ------------- | ----------------------------- |
| `make`        | Build `cube3d`                |
| `make clean`  | Remove object files           |
| `make fclean` | Remove objects and the binary |
| `make re`     | Rebuild from scratch          |




## Usage

```bash
./cube3d assets/maps/map2.cub
```

The program takes **exactly one** argument: a scene file with the `.cub` extension.

Example maps:

- `assets/maps/map.cub`
- `assets/maps/map2.cub`



## Controls


| Key              | Action        |
| ---------------- | ------------- |
| `W` / Up arrow   | Move forward  |
| `S` / Down arrow | Move backward |
| `A`              | Strafe left   |
| `D`              | Strafe right  |
| Left arrow       | Rotate left   |
| Right arrow      | Rotate right  |
| `ESC`            | Quit          |
| Window close     | Quit          |


## Scene file (`.cub`)

The file contains texture paths and colors first, then the map. Identifiers (except the map) may appear in any order and may be separated by empty lines. The **map must be last**.

### Identifiers

```
NO ./textures/wood.xpm
SO ./textures/greystone.xpm
WE ./textures/redbrick.xpm
EA ./textures/colorstone.xpm

F 220,100,0
C 225,30,0
```


| Identifier | Meaning                       |
| ---------- | ----------------------------- |
| `NO`       | North wall texture (XPM path) |
| `SO`       | South wall texture            |
| `WE`       | West wall texture             |
| `EA`       | East wall texture             |
| `F`        | Floor color `R,G,B` (0–255)   |
| `C`        | Ceiling color `R,G,B` (0–255) |




### Map characters


| Character       | Meaning                                     |
| --------------- | ------------------------------------------- |
| `0`             | Empty space / floor                         |
| `1`             | Wall                                        |
| `N` `S` `E` `W` | Player spawn and facing direction           |
| space           | Valid padding (void); must stay unreachable |


Rules from the subject:

- Only those characters are allowed
- Exactly **one** player spawn
- The map must be **closed** by walls
- Spaces are part of the map and must be handled
- Invalid input must print `Error` followed by a message, then exit

Minimal example:

```
NO ./textures/wood.xpm
SO ./textures/greystone.xpm
WE ./textures/redbrick.xpm
EA ./textures/colorstone.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```



## Project structure

```
Cube3D/
├── Makefile
├── include/
│   ├── cube3d.h
│   ├── get_next_line.h
│   ├── Libft_plus/          # libft
│   └── mlx_linux/           # MiniLibX (Linux)
├── src/                     # parsing, raycasting, rendering, movement
├── assets/maps/             # example .cub scenes
└── textures/                # XPM wall textures
```

Main modules:

- **Parsing** — `.cub` identifiers, RGB colors, map extraction, flood fill
- **Raycasting** — DDA rays, wall distance, texture mapping
- **Gameplay** — movement, rotation, collision
- **Rendering** — 3D frame, floor/ceiling, minimap



## Subject notes (mandatory)

The official cub3D subject requires:

- A first-person view of a maze using raycasting
- MiniLibX for windows, images, and events
- Different textures for North / South / East / West walls
- Floor and ceiling colors
- `W` `A` `S` `D` (or equivalent) to move and arrows to look
- Window close on `ESC` and on the red cross
- No global variables, Norm-compliant C, a proper Makefile
- Allowed C library functions: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`, plus math and MiniLibX

Bonuses in this project: **wall collisions** and a **minimap**.

## Authors

42 project by **drenquin** and **lmonsat**.