#include "source/global.hpp"

#include "source/grid.h"
#include "source/rectangle.h"
#include "source/div_text.h"

#include "pathfinding/a_star.h"

#include <LUA/lua.hpp>
#include <LuaBridge/LuaBridge.h>


namespace GLB {
	bool WINDOW_CLOSE = false;
	bool MOUSE_RIGHT = false, MOUSE_LEFT = false, MOUSE_RELEASE = false;
	int MOUSE_LEFT_X, MOUSE_LEFT_Y;
	int MOUSE_RIGHT_X, MOUSE_RIGHT_Y;
	bool ENTER = false, SPACE = false;
	bool CTRL = false, ALT = false, KEY_N = false;
	glm::mat4 PROJECTION;
}

namespace PATH {
	int GRID_MATRIX[sizeY / cellSize][sizeX / cellSize] = { 0 };
	int CLOSED_NODES[sizeY / cellSize][sizeX / cellSize] = { 0 };
	int OPEN_NODES[sizeY / cellSize][sizeX / cellSize] = { 0 };
	int DIR_MAP[sizeY / cellSize][sizeX / cellSize] = { 0 };
	int START_X = -1, START_Y = -1, FINAL_X = -1, FINAL_Y = -1;
}


void printMessage(const std::string& s) {
	std::cout << s << std::endl;
}

using namespace luabridge;

void readAndExecuteScript() {
	lua_State* L = luaL_newstate();
	/*Calling C++ from Lua*/
	luaL_openlibs(L);
	getGlobalNamespace(L).addFunction("Print", printMessage);
	luaL_loadfile(L, "hello.lua");

	int result = lua_pcall(L, 0, 0, 0);

	//Pop the function call
	//lua_pop(L, 1);

	/*Calling Lua from C++*/
	luaL_dofile(L, "move.lua");

	/*2 arguments sent to function moveTo*/
	lua_getglobal(L, "moveTo");
	lua_pushnumber(L, 5);
	lua_pushnumber(L, 6);

	/*Checking errors*/
	if (lua_pcall(L, 2, 2, 0) != 0) {
		std::cout << "ERROR ON CALLING FUNCTION: " << lua_tostring(L, -1) << std::endl;
		return;
	}

	if (!lua_isnumber(L, -1)) {
		std::cout << "ERROR ON X RETURNING TYPE" << std::endl;
		return;
	}

	if (!lua_isnumber(L, -2)) {
		std::cout << "ERROR ON Y RETURNING TYPE" << std::endl;
		return;
	}

	//Get the returned values
	int x = lua_tonumber(L, -1);
	int y = lua_tonumber(L, -2);

	//Pop the values (get the stack clean)
	lua_pop(L, 2);

	std::cout << "Moved to (" << x << ", " << y << ")" << std::endl;

	return;
}


using namespace GLB;
using namespace PATH;

myWindow window; 
Grid grid;
FRectangle rectangle;
DivText text;

aStar Path;
std::vector<glm::ivec2> path;
std::vector<glm::ivec2> collisionPoints;
std::string time_str;

void setPositions();
void setCollisions();
void clear();
void calculatePath();
void ui_render();

/* ----------------------------------------- */
/*                                           */
/*                  M A I N                  */
/*                                           */
/* ----------------------------------------- */


int main() {

	readAndExecuteScript();




	PROJECTION = glm::ortho(0.0f, (float)sizeX, 0.0f, (float)sizeY, -100.0f, 100.0f);

	window = myWindow();
	window.init();

	grid = Grid();
	grid.compile();
	grid.create();
	
	rectangle = FRectangle();
	rectangle.compile();
	rectangle.create(cellSize, cellSize, "bottom-left");

	Path = aStar();

	text = DivText();
	text.create("tahoma_6");

	while (!WINDOW_CLOSE) {

		glfwPollEvents();
		window.clear_buffers();

		if (!SPACE) {
			ui_render();
			

		}

		else {
			clear();
			setCollisions();
			setPositions();
		
			grid.render();

			if (START_X >= 0 && START_Y >= 0) {
				rectangle.set_color(glm::vec4(255.0f, 0.f, 0.f, 255.f));
				rectangle.render(START_X * cellSize, START_Y * cellSize);
			}
			if (FINAL_X >= 0 && FINAL_Y >= 0) {
				rectangle.set_color(glm::vec4(0.0f, 255.f, 0.f, 255.f));
				rectangle.render(FINAL_X * cellSize, FINAL_Y * cellSize);
			}
			if ((START_X >= 0 && START_Y >= 0) && (FINAL_X >= 0 && FINAL_Y >= 0)) {
				if (ENTER) {
					ENTER = false;
					calculatePath();
				}
			}
			if (collisionPoints.size() > 0) {
				collisionPoints.erase(unique(collisionPoints.begin(), collisionPoints.end()), collisionPoints.end());
				for (int i = 0; i < collisionPoints.size(); ++i) {
					rectangle.set_color(glm::vec4(0.0f, 0.0f, 0.0f, 255.f));
					rectangle.render(collisionPoints[i].x * cellSize, collisionPoints[i].y * cellSize);
				}
			}
			if (path.size() > 0) {
				for (int i = 0; i < path.size() - 1; ++i) {
					rectangle.set_color(glm::vec4(255.0f, 255.f, 255.f, 255.f));
					rectangle.render(path[i].x * cellSize, path[i].y * cellSize);
				}
				text.set_text(time_str);

				text.set_position(glm::vec2(sizeX - 99, sizeY - 31));				
				text.render(glm::vec4(0.f, 0.f, 0.f, 255.f));
				text.set_position(glm::vec2(sizeX - 100, sizeY - 30));
				text.render(glm::vec4(255.f, 242.f, 0.f, 255.f));
			}
		}

		window.swap_buffers();
	}
	glfwTerminate();
	return 0;
}


/* ----------------------------------------- */
/*                                           */
/*            F U N C T I O N S              */
/*                                           */
/* ----------------------------------------- */



void clear() {
	if (CTRL && KEY_N) {

		CTRL = false;
		KEY_N = false;

		std::cout << "yes\n";

		path = { };
		START_X = -1;
		START_Y = -1;
		FINAL_X = -1;
		FINAL_Y = -1;
		collisionPoints = { };

		for (int i = 0; i < sizeY / cellSize; i++) {
			for (int j = 0; j < sizeX / cellSize; j++) {
				PATH::GRID_MATRIX[i][j] = 0;
			}
		}
	}
}



void setPositions() {
	if (MOUSE_LEFT && !CTRL && !ALT) {
		MOUSE_LEFT = false;
		START_X = window.get_mouse_x() / cellSize;
		START_Y = window.get_mouse_y() / cellSize;
		path = { };
	}
	if (MOUSE_RIGHT && !CTRL && !ALT) {
		MOUSE_RIGHT = false;
		FINAL_X = window.get_mouse_x() / cellSize;
		FINAL_Y = window.get_mouse_y() / cellSize;
		path = { };
	}
}



void setCollisions() {
	if (MOUSE_LEFT && CTRL) {
		int x = window.get_mouse_x() / cellSize;
		int y = window.get_mouse_y() / cellSize;
		PATH::GRID_MATRIX[y][x] = 1;
		collisionPoints.push_back(glm::ivec2(x, y));
	}
	if (MOUSE_LEFT && ALT) {
		int x = window.get_mouse_x() / cellSize;
		int y = window.get_mouse_y() / cellSize;
		PATH::GRID_MATRIX[y][x] = 0;
		collisionPoints.erase(std::remove(collisionPoints.begin(), collisionPoints.end(), glm::ivec2(x, y)), collisionPoints.end());
	}
}



void calculatePath() {
	clock_t start = clock();
	path = Path.pathFind(Location(START_Y, START_X), Location(FINAL_Y, FINAL_X));
	clock_t end = clock();
	double time = double(end - start);
	time_str = "Time (ms): " + std::to_string((int)time);
}


void ui_render() {
	int vspace = 20;
	int startY = sizeY - 200;

	std::vector<std::string> strings = {
		"PRESS SPACE TO ENABLE/DISABLE UI",
		" ",
		"LEFT-CLICK = Start position;",
		"RIGHT-CLICK = End position;",
		"CTRL + LEFT-CLICK = Set collision point;",
		"ALT + LEFT-CLICK = Remove collision point;",
		"ENTER = Calculate best path;",
		"CTRL + N = Clear grid."
	};

	for (int i = 0; i < strings.size(); ++i) {
		text.set_position(glm::vec2(sizeX / 2 - 200, startY));
		text.set_text(strings[i]);
		text.render();
		startY -= vspace;
	}
	
}