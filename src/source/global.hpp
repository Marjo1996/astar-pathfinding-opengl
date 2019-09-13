#ifndef GLOBAL_H
#define GLOBAL_H

#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "window.h"

static const int sizeX = 600;
static const int sizeY = 600;
static const int cellSize = 15;

namespace GLB {
	extern bool WINDOW_CLOSE;
	extern bool MOUSE_RIGHT, MOUSE_LEFT, MOUSE_RELEASE;
	extern int MOUSE_LEFT_X, MOUSE_LEFT_Y;
	extern int MOUSE_RIGHT_X, MOUSE_RIGHT_Y;
	extern bool ENTER;
	extern bool CTRL, ALT, SPACE;
	extern bool KEY_N;
	extern glm::mat4 PROJECTION;
}

namespace PATH {
	extern int GRID_MATRIX[sizeY / cellSize][sizeX / cellSize];
	extern int CLOSED_NODES[sizeY / cellSize][sizeX / cellSize];
	extern int OPEN_NODES[sizeY / cellSize][sizeX / cellSize];
	extern int DIR_MAP[sizeY / cellSize][sizeX / cellSize];
	extern int START_X, START_Y, FINAL_X, FINAL_Y;
}

static std::string ReadFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);
	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}
	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

#endif