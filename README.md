# cub3D

## 💡 Overview
**cub3D** is a 3D game engine project developed as part of the [42 Lisboa](https://www.42lisboa.com) curriculum.  
It is based on **raycasting techniques**, similar to early FPS games like *Wolfenstein 3D*, transforming a 2D map into a real-time 3D environment.

---

## Key Concepts
- Raycasting and 3D projection from a 2D map
- Real-time rendering with MiniLibX
- Player movement, rotation, and collision detection
- Texture mapping for walls and environment
- Game loop and event handling
- Modular architecture for easy expansion

---

## Custom Features
Unlike the default cub3D project, this version includes:

### Interactive Menu
At startup, the player can select different modes:
- **Evaluation Mode** – designed to simulate 42-style evaluation conditions  
- **Training Mode** – free exploration and practice  
- **Game Mode** – full gameplay experience
- **Game Keys** - game controls

### Game Logic
- Inspired by **The World’s Hardest Game**, reimagined in **3D**
- Focus on obstacle navigation, precision movement, and challenge progression
- Not just a renderer, but a **fully playable game with objectives**

### Additional Features
- Animated sprites and dynamic obstacles
- Enemies with advanced gameplay mechanics
- HUD displaying level, collectables and deaths
- Level progression system
- Checkpoints for player recovery and flow control

---

## Compilation / Installation
```bash
git clone https://github.com/martimsaunders/cub3D.git
cd cub3D
make mlx_download (to download the mlx library)
make
```
This will generate the executable:
```bash
./cub3D
```

## Usage
### Mandatory
```bash
./cub3D maps/example.cub (you can play the game without a map argument)
```

<p align="center">
  <img src="assets/make_cub3D.gif" alt="" width="1020">
</p>
<p align="center">
  <img src="assets/menu_cub3D.gif" alt="" width="1020">
</p>
<p align="center">
  <img src="assets/eval_cub3D.gif" alt="" width="1020">
</p>
<p align="center">
  <img src="assets/game_cub3D.gif" alt="" width="1020">
</p>
<p align="center">
  <img src="assets/train_cub3D.gif" alt="" width="1020">
</p>

---

## Controls(keyboard)
- `W` → Move Up
- `A` → Move Left
- `S` → Move Down
- `D` → Move Right
- `->` → Rotate Right
- `<-` → Rotate Left
- `ESC` → Exit the game
- You can also move the camera with your mouse

---

## Tech Stack
- C
- MiniLibX
- UNIX system calls (`read`, `open`, etc)
- Trigonometry and dda algorithm 
- Makefile

---

## Challenges / Lessons Learned
- Implementing raycasting and real-time rendering from scratch
- Handling precise movement, collisions, and camera rotation
- Parsing and validating .cub map configuration files
- Managing performance while rendering continuously
- Designing a clean and modular architecture for game logic
- Designing and implementing a real-time minimap synchronized with the 3D world
- Expanding a graphics engine into a real, playable game

---

Author

- Martim Prazeres Saunders
