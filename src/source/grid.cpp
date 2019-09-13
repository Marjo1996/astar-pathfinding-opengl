#include "grid.h"

Grid::Grid()
{
	vPath = "shaders/grid/vertex.glsl";
	fPath = "shaders/grid/fragment.glsl";
}

void Grid::create() {

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	float vertices[] = {
		// X,Y,Z										// uv coords		
		0.f, 0.f, 0.f,									0.f, 1.f,  // in basso a sx
		sizeX, 0.f, 0.f,					1.f, 1.f,  // in basso a dx
		sizeX, sizeY, 0.f,		1.f, 0.f,  // in alto a dx
		0.f, sizeY, 0.f,					0.f, 0.f   // in alto a sx
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* This texture comes from the real grid of 0/1 */

	int grid_sizeX = sizeX / cellSize;
	int grid_sizeY = sizeY / cellSize;
	unsigned char* gridData = new unsigned char[grid_sizeX * grid_sizeY * 4];
	for (int y = 0; y < grid_sizeY; ++y) {
		for (int x = 0; x < grid_sizeX; ++x) {

			if ((x+y)%2==0) {
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 0] = 120;
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 1] = 120;
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 2] = 120;
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 3] = 255;
			}
			else {
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 0] = 140;
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 1] = 140;
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 2] = 140;
				gridData[(grid_sizeX * (grid_sizeY - 1 - y) + x) * 4 + 3] = 255;
			}
		}
	}

	textureIdList.push_back(0);

	glGenTextures(1, &textureIdList[0]);
	glBindTexture(GL_TEXTURE_2D, textureIdList[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, grid_sizeX, grid_sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)gridData);
}

void Grid::render() {

	glUseProgram(shaderId);
	glUniformMatrix4fv(glGetUniformLocation(shaderId, "projection"), 1, GL_FALSE, glm::value_ptr(GLB::PROJECTION));

	/* Draw */

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glUniform1i(glGetUniformLocation(shaderId, "grid_color"), 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureIdList[0]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

Grid::~Grid()
{
}
