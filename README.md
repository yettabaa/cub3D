# **Cube3D - 3D Maze Renderer**

[![42 Badge](https://img.shields.io/badge/Score-125%2F100-brightgreen)](#)

![Project Preview](https://github.com/yettabaa/cube3D/blob/master/assets/cube3D.gif)

**Cube3D** is a 42 School project that implements a 3D maze renderer using raycasting techniques. This project demonstrates real-time rendering of walls, ceilings, and floors, delivering an immersive gaming experience. Completed with all mandatory and bonus features, including a minimap system, animated sprites, and interactive doors.

---

## **Table of Contents**
1. [Overview](#overview)  
2. [Features](#features)  
3. [Technologies Used](#technologies-used)  
4. [Allowed Functions and Libraries](#allowed-functions-and-libraries)  
5. [Map Format](#map-format)  
6. [Raycasting: The Core Logic](#raycasting-the-core-logic)  
7. [Bonus Features](#bonus-features)  
8. [Installation](#installation)  
9. [Usage](#usage)
10. [Contributing](#contributing)  
11. [License](#license)  

---

## **1. Overview**  
**Cube3D** brings the classic maze renderer concept to life by applying **raycasting**, a fundamental technique used in 3D games like **Wolfenstein 3D**. The project reads a 2D map and generates a fully interactive 3D world.

- **Validation Date**: June 22, 2023  
- **Score**: 125/100 (including bonus)  
- **Mandatory Features**:  
  - Parsing a well-defined map file format.  
  - Real-time 3D rendering using raycasting.  
  - Texture mapping for walls.  
  - Floor and ceiling color rendering.  
  - Basic player navigation (movement and rotation).  
- **Bonus Features**:  
  - Minimap system.  
  - Interactive doors that open and close.  
  - Animated sprites.  

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
NO   ./Common/textures/text/image1.xpm
SO   ./Common/textures/text/image3.xpm
WE   ./Common/textures/text/image2.xpm
EA   ./Common/textures/text/image4.xpm

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

## **7. Bonus Features**

- **Minimap System**:  
  Displays the player's position and the maze layout in real-time, aiding navigation through the environment. Additionally, it can detect enemies (sprites) even if they are behind walls, by using raycasting to identify if the line of sight is blocked by obstacles. This ensures that the minimap provides an accurate representation of the player’s surroundings, including hidden or obstructed enemies.

- **Interactive Doors**:  
  Doors react to player proximity, animating open/close actions as the player approaches or interacts with them. The door textures are preloaded to represent different stages of the opening. As the player approaches, the door's texture index increases to simulate gradual opening, and decreases as the player moves away to close it. Raycasting is used to determine the player's proximity to the door, affecting which texture frame is displayed. Since raycasting can detect multiple doors in a single line of sight, objects are sorted by distance, and rendering occurs from the farthest to the closest.

- **Animated Sprites**:  
  Objects like enemies or collectibles are dynamically animated within the 3D environment. Similar to doors, sprites are rendered based on their distance from the player, with nearer objects appearing more prominently. Sprites are detected during map parsing using the player's viewpoint and field of vision. Their position is calculated using the arctangent of the difference between the player's and sprite's coordinates. Like doors, multiple sprites can be detected along the same ray, and all objects are sorted by distance, ensuring correct rendering order from farthest to closest.

- **Distance Sorting**:  
  Objects (walls, doors, sprites) are rendered in the correct order relative to the player's viewpoint by sorting them based on their distance from the player. This ensures that closer objects, such as doors or sprites, are rendered on top of farther ones to avoid visual overlap and maintain proper layering.

---


## **8. Installation**  
Clone the repository and compile the project:  

```bash  
git clone git@github.com:yettabaa/Cube3D.git  
cd Cube3D  
make  
```  

Run the program with a sample map (mandatory part only):  

```bash  
./cub3D maps/map1.cub 
```  

To compile the project with bonus features:  

```bash  
make bonus  
```  

Run the program with all features enabled:  

```bash  
./cub3D_bonus maps/map0.cub 
```  

---
## **9. Usage**  

**Cube3D** provides intuitive controls for navigating the 3D maze:  

- **Arrow Keys**:  
  - Left Arrow: Rotate the camera left.  
  - Right Arrow: Rotate the camera right.  

- **W/A/S/D**:  
  - W: Move forward.  
  - A: Move left.  
  - S: Move backward.  
  - D: Move right.  

- **Shift**:  
  - Hold Shift to increase movement speed.
**Key Combinations**:  
- You can combine any of the above keys for more complex movements, such as moving forward while rotating or moving sideways while increasing speed.
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
