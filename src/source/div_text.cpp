#include "div_text.h"

DivText::DivText()
{
}

void DivText::set_align(std::string halign, std::string valign) {
	txt.set_align(halign, valign);
}

void DivText::create(std::string font) {
	txt = CBitmapFont();
	txt.compile();
	txt.apply_projection_matrix(GLB::PROJECTION);
	txt.create(font);
	
}

void DivText::render(glm::vec4 color) {
	txt.render(position.x, position.y, text, color);
}

void DivText::set_position(glm::vec2 pos) {
	position = glm::vec3(pos, 0.0f);
}

void DivText::set_text(std::string txt) {
	text = txt;
}

DivText::~DivText()
{
}
