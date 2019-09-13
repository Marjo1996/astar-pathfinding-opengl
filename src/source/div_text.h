#pragma once

#include "global.hpp"
#include "bitmap_font.h"

class DivText
{
public:
	DivText();
	void set_position(glm::vec2 pos);
	void set_text(std::string txt);
	void set_align(std::string halign = "left", std::string valign = "normal");
	void create(std::string font);
	void render(glm::vec4 color = glm::vec4(255.f));
	~DivText();
private:
	CBitmapFont txt;
	glm::vec3 position;
	std::string text;
};

