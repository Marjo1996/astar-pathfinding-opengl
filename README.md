# 2d Grid A* Pathfinding in OpenGL framework

This repository contains a complete VS2017 solution (with precompiled libraries and headers); I aim to implement an A* algorithm based on a static 2d grid - an int 2d array - useful for 2d rts games.

You can interact with the application using the keyboard and the mouse, selecting the start point and the end point and adding/removing collision points. 

## Download:

https://github.com/fabiomarigo7/astar-pathfinding-opengl/releases

## How does the application work?

Here some screenshots:

![i1](/img/image0.png)
![i2](/img/image1.png)
![i3](/img/image2.png)
![i4](/img/image3.png)

## How to easily edit the application?

In `src/source/global.hpp` you can modify the Window/Grid size and the cell size:

```cpp
static const int sizeX = 600;
static const int sizeY = 600;
static const int cellSize = 15;
```

In `src/pathfinding/` there is the core of the aStar algorithm[1]. I edited the heuristics (see `src/pathfinding/node.cpp`) as below, to obtain a good performance and result:
```cpp
// Euclidian Distance
d = 14 * (int)sqrt(rd*rd+cd*cd);
```
That is an Euclidean distance, multiplied by 14 (please note that 10 is the scale of penalization, as you can see below).
```cpp
GValue += ((i % 2 == 0 ? 10 : 14));
```
## Credits 

[1] https://www.bogotobogo.com/Algorithms/path_finding_algorithm.php
