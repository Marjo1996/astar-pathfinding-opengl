#pragma once

#include "global.hpp"
#include "shader.h"

class Grid : public Shader
{
public:
	Grid();
	void create();
	void render();
	~Grid();
};
