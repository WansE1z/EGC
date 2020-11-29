#include "Object3D.h"

Mesh* Object3D::CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(length, 0, 0), color),
		VertexFormat(glm::vec3(length, 0.05 * length, 0), color),
		VertexFormat(glm::vec3(0, 0.05 * length, 0), color),
		VertexFormat(glm::vec3(0, 0, -5 * length), color),
		VertexFormat(glm::vec3(length, 0, -5 * length), color),
		VertexFormat(glm::vec3(length, 0.05 * length, -5 * length), color),
		VertexFormat(glm::vec3(0, 0.05 * length, -5 * length), color)
	};

	vector<unsigned short> indices =
	{
		0, 5, 1,	
		0, 4, 5,	
		0, 7, 4,	
		0, 3, 7,
		3, 6, 7,
		3, 2, 6,
		2, 5, 6,
		2, 1, 5,
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6
	};

	Mesh* cube = new Mesh(name);
	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* Object3D::CreateGasRect(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	vector<VertexFormat> vertices
	{
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, 0.1 * length, 0), color),
		VertexFormat(corner + glm::vec3(0, 0.1 * length, 0), color),
		VertexFormat(corner + glm::vec3(0, 0, 0.001 * length), color),
		VertexFormat(corner + glm::vec3(length, 0, 0.001 * length), color),
		VertexFormat(corner + glm::vec3(length, 0.1* length, 0.001 * length), color),
		VertexFormat(corner + glm::vec3(0, 0.1 * length, 0.001 * length), color)
	};

	vector<unsigned short> indices =
	{
		0, 5, 1,
		0, 4, 5,
		0, 7, 4,
		0, 3, 7,
		3, 6, 7,
		3, 2, 6,
		2, 5, 6,
		2, 1, 5,
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6
	};

	Mesh* cube = new Mesh(name);
	cube->SetDrawMode(GL_LINES);
	cube->InitFromData(vertices, indices);
	return cube;
}

Mesh* Object3D::CreateGasRect2(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill, float percent)
{
	glm::vec3 corner = leftBottomCorner;

	vector<VertexFormat> vertices
	{
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(percent * length, 0, 0), color),
		VertexFormat(corner + glm::vec3(percent * length, 0.1 * length, 0), color),
		VertexFormat(corner + glm::vec3(0, 0.1 * length, 0), color),
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(percent * length, 0, 0), color),
		VertexFormat(corner + glm::vec3(percent * length, 0.1 * length, 0), color),
		VertexFormat(corner + glm::vec3(0, 0.1 * length, 0), color)
	};

	vector<unsigned short> indices =
	{
		0, 5, 1,
		0, 4, 5,
		0, 7, 4,
		0, 3, 7,
		3, 6, 7,
		3, 2, 6,
		2, 5, 6,
		2, 1, 5,
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6
	};

	Mesh* cube = new Mesh(name);
	cube->InitFromData(vertices, indices);
	return cube;
}

