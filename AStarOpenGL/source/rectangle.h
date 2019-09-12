#pragma once

#include "global.hpp"
#include "shader.h"

class FRectangle : public Shader
{
public:
	FRectangle();
	void set_color(glm::vec4 col);
	void create(float width, float height, std::string origin);
	void render(int xPos, int yPos);
	~FRectangle();

private:
	float w, h;
	float x0, y0, x1, y1, x2, y2, x3, y3;
	glm::mat4 modelMat;
	glm::vec4 color;

};

