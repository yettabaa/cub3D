# **Cube3D - 3D Maze Renderer**

[![42 Badge](https://img.shields.io/badge/Score-125%2F100-brightgreen)](#)

![Project Preview](https://github.com/yettabaa/Cube3D/blob/master/assets/cube3D.gif)

**Cube3D** is a 42 School project that implements a 3D maze renderer using raycasting techniques. This project demonstrates real-time rendering of walls, ceilings, and floors, delivering an immersive gaming experience. Completed with all mandatory and bonus features, including a minimap system, animated sprites, and interactive doors.

---

## **Table of Contents**
1. [Overview](#overview)  
2. [Features](#features)  
3. [Technologies Used](#technologies-used)  
4. [Allowed Functions and Libraries](#allowed-functions-and-libraries)  
5. [Map Format](#map-format)  
6. [Raycasting: The Core Logic](#raycasting-the-core-logic)  
7. [Rendering Process](#rendering-process)  
8. [Bonus Features](#bonus-features)  
9. [Installation](#installation)  
10. [Contributing](#contributing)  
11. [License](#license)  

---

## **1. Overview**  
**Cube3D** brings the classic maze renderer concept to life by applying **raycasting**, a fundamental technique used in 3D games like **Wolfenstein 3D**. The project reads a 2D map and generates a fully interactive 3D world.

- **Validation Date**: June 22, 2023  
- **Score**: 125/100 (including bonus)  
- **Mandatory Features**:  
  1. Parsing a well-defined map file format.  
  2. Real-time 3D rendering using raycasting.  
  3. Texture mapping for walls.  
  4. Floor and ceiling color rendering.  
  5. Basic player navigation (movement and rotation).  
- **Bonus Features**:  
  1. Minimap system.  
  2. Interactive doors that open and close.  
  3. Animated sprites.  

---

## **2. Features**
- **Real-time rendering**: A dynamic environment rendered using raycasting.  
- **Map flexibility**: Load environments from configurable map files with walls, doors, and sprites.  
- **Interactive gameplay**: Doors and sprites react to player interactions and proximity.  
- **Minimap system**: A top-down view aids in navigation.  
- **Optimized performance**: Efficient memory and rendering techniques.  

---

## **3. Technologies Used**
- **Language**: C  
- **Graphics Library**: MiniLibX (custom library provided by 42).  
- **Build Tool**: Makefile  
- **Libft Integration**:  
  Cube3D incorporates functions from [Libft](https://github.com/yettabaa/Libft), a custom utility library created during a previous 42 project.  
- **Project Connection**:  
  Shares mathematical concepts and pixel rendering logic with the [FdF project](https://github.com/yettabaa/FdF).  


---
## **4. Allowed Functions and Libraries**  
This project adheres to the strict function usage rules set by 42 School. The only allowed libraries and functions are:  

- **Graphics and Rendering**: MiniLibX (`mlx_init`, `mlx_new_window`, `mlx_put_image_to_window`, etc.)  
- **File I/O**: `open`, `read`, `write`, `close`  
- **Memory Management**: `malloc`, `free`  
- **String and Utility Functions**:  
  Utilizes `libft` functions for parsing, string manipulation, and error handling.  

---

## **5. Map Format**
The map defines the environment of the game. Each number corresponds to a specific object:

| Number | Description                  |  
|--------|------------------------------|  
| `0`    | Floor                        |  
| `1`    | Wall                         |  
| `2`    | Door (automatically opens/closes) |  
| `3`    | Sprite (e.g., an animated object) |  

Additionally, the map specifies:  
- **Textures**:  
  Each wall (`1`), door (`2`), and sprite (`3`) uses a texture defined in the configuration file.  
- **Colors**:  
  Floor and ceiling colors are specified using RGB values.  

Example map configuration:  

```  
NO ./textures/north_wall.xpm  
SO ./textures/south_wall.xpm  
WE ./textures/west_wall.xpm  
EA ./textures/east_wall.xpm  
DO ./textures/door_texture.xpm  
SP ./textures/sprite_texture.xpm  
F 220,100,0  (Floor RGB Color)  
C 0,50,200  (Ceiling RGB Color)  

1111111  
1000001  
1020301  
1111111  
```  

This map:  
- Encloses a floor (`0`) with walls (`1`).  
- Includes a door (`2`) and animated sprite (`3`).  
- Specifies RGB colors for the floor and ceiling.  

---


## **6. Raycasting: The Core Logic**  
Raycasting transforms a 2D map into a 3D-rendered environment. Key steps include:  

1. **Ray Projection**:  
   - Cast rays from the player's position in the direction of the camera view.  

2. **Wall Detection**:  
   - Determine where each ray intersects a wall using trigonometric functions.  

3. **Distance Calculation**:  
   - Calculate the distance to the intersection point for texture scaling.  

4. **Texture Mapping**:  
   - Apply the appropriate texture to walls, doors, and sprites based on the intersection point.  

---

## **7. Rendering Process**  
Rendering occurs pixel by pixel for precision:  

1. **Walls**:  
   Textures are scaled and rendered based on the distance to each wall.  

2. **Ceilings and Floors**:  
   Pixels are filled with solid colors or optional textures.  

3. **Doors and Sprites**:  
   Doors automatically open/close when the player approaches, and sprites are animated.  

---

## **8. Bonus Features**  
- **Minimap**: Displays the player's position and the maze layout in real-time.  
- **Interactive Doors**: React to player proximity and animate open/close actions.  
- **Animated Sprites**: Objects such as enemies or collectibles move and animate dynamically.  

---


## **9. Installation**  
Clone the repository and compile the project:  

```bash  
git clone git@github.com:yettabaa/Cube3D.git  
cd Cube3D  
make  
```  

Run the program with a sample map (mandatory part only):  

```bash  
./cub3d maps/maze.cub  
```  

To compile the project with bonus features:  

```bash  
make bonus  
```  

Run the program with all features enabled:  

```bash  
./cub3d_bonus maps/bonus_maze.cub  
```  

---
## **10. Contributing**  
Contributions are welcome! If you have suggestions for improving this project, feel free to fork the repository and submit a pull request.  

1. **Fork the Repository**  
2. **Create a Feature Branch**:  
   ```bash  
   git checkout -b feature-branch-name  
   ```  
3. **Commit Changes**:  
   ```bash  
   git commit -m "Description of changes"  
   ```  
4. **Push Changes**:  
   ```bash  
   git push origin feature-branch-name  
   ```  
5. **Open a Pull Request**  

---

## **11. License**  
This project is licensed under the [MIT License](LICENSE).  

---
