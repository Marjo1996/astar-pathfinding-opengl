# 2d Grid A* Pathfinding in OpenGL framework

This repository contains a complete VS2017 solution (with precompiled libraries and headers); I aim to implement an A* algorithm based on a static 2d grid - an int 2d array - useful for 2d rts games.

You can interact with the application using the keyboard and the mouse, selecting the start point and the end point and adding/removing collision points. 

## How does the application work?

Here some screenshots:

![i1](/imgs/image0.png)
![i2](/imgs/image1.png)
![i3](/imgs/image2.png)
![i4](/imgs/image3.png)

## How to easily edit the application?

In `source/global.hpp`:

```cpp
static const int sizeX = 600;
static const int sizeY = 600;
static const int cellSize = 15;
```

In `pathfinding/` there is the core of the aStar algorithm[1].

## Credits 

[1] https://www.bogotobogo.com/Algorithms/path_finding_algorithm.php