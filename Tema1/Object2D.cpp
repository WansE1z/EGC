#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(10*length, 0, 0), color),
		VertexFormat(corner + glm::vec3(10*length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;

}

Mesh* Object2D::CreateOutRectangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(10 * length * 1.2f, 0, 0), color),
		VertexFormat(corner + glm::vec3(10 * length * 1.2f, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;

}

Mesh* Object2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner , color),
		VertexFormat(corner + glm::vec3(length, 0, 0) , color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 
											2, 1, 3};

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Object2D::CreateBow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill){
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	GLfloat arc;
	GLfloat twoPI = 2 * M_PI;

	vertices.emplace_back(corner + glm::vec3(0, 0, 0), color);
	for (GLushort i = 0; i <= 101; i++)
	{
		arc = M_PI * i / 100;
		vertices.emplace_back(corner + glm::vec3(sin(arc) * length, cos(arc) *length, 0), color);
		indices.push_back(i);
	}

	Mesh* bow = new Mesh(name);
	bow->InitFromData(vertices, indices);
	if (!fill) {
		bow->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		bow->SetDrawMode(GL_TRIANGLE_FAN);
	}
	return bow;
}

Mesh* Object2D::CreateArrow(std::string name, glm::vec3 leftBottomCorner, glm::vec3 leftBottomCorner2, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;
	glm::vec3 corner2 = leftBottomCorner2;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(40 * length / 6, 0, 0), color),
		VertexFormat(corner + glm::vec3(40 * length / 6, 4 * length / 6, 0), color),
		VertexFormat(corner + glm::vec3(0, 4 * length / 6, 0), color),
		VertexFormat(corner2 , color),
		VertexFormat(corner2 + glm::vec3(length, 0, 0) , color),
		VertexFormat(corner2 + glm::vec3(0, length, 0), color),
		VertexFormat(corner2 + glm::vec3(0, -length, 0), color),
	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices =
	{ 
		4, 5, 6,
		6, 5, 7,
		1, 2, 3,
		1, 3, 0
		
	};


	arrow->InitFromData(vertices, indices);
	return arrow;
}

Mesh* Object2D::CreateBalloon(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	GLfloat arc;
	GLfloat twoPI = 2 * M_PI;

	vertices.emplace_back(corner + glm::vec3(0, 0, 0), color);
	for (GLushort i = 0; i <= 101; i++)
	{
		arc = twoPI * i / 100;
		vertices.emplace_back(corner + glm::vec3(sin(arc) * length/2, cos(arc) * length, 0), color);
		indices.push_back(i);
	}

	Mesh* balon = new Mesh(name);
	balon->InitFromData(vertices, indices);
	if (!fill) {
		balon->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		balon->SetDrawMode(GL_TRIANGLE_FAN);
	}
	return balon;

}

Mesh* Object2D::CreatePolyLine(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-length * 0.9f, -length, 0), color),
		VertexFormat(corner + glm::vec3(length * 0.9f, -2 * length, 0), color),
		VertexFormat(corner + glm::vec3(-length * 0.9f, -3 * length, 0), color),
		VertexFormat(corner + glm::vec3(length, -4 * length, 0), color),
	};

	Mesh* poly = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		0, 1,
		1, 2,
		2, 3,
		3, 4,
	};
	poly->SetDrawMode(GL_LINES);
	poly->InitFromData(vertices, indices);
	return poly;

}

Mesh* Object2D::CreateShuriken(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(0, length, 0), color),
		VertexFormat(corner + glm::vec3(-length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, -length, 0), color),
		VertexFormat(corner + glm::vec3(length, -length, 0), color),
		VertexFormat(corner + glm::vec3(-length, 0, 0), color),
		VertexFormat(corner + glm::vec3(-length, -length, 0), color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 3, 4,
		0, 5, 6,
		0, 7, 8,

	};
	shuriken->SetDrawMode(GL_TRIANGLES);
	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

Mesh* Object2D::CreateStopSign(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;
	GLfloat arc;
	GLfloat twoPI = 2 * M_PI;

	vertices.emplace_back(corner + glm::vec3(0, 0, 0), color);
	for (GLushort i = 1; i <= 6; i++)
	{
		arc = twoPI * i / 6;
		vertices.emplace_back(corner + glm::vec3(sin(arc) * length, cos(arc) * length, 0), color);
	}

	std::vector<unsigned short> indices =
	{
		1, 2,
		2, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 1,
		1, 4,
		5, 2,

	};

	Mesh* stopSign = new Mesh(name);
	stopSign->InitFromData(vertices, indices);
	if (!fill) {
		stopSign->SetDrawMode(GL_LINES);
	}
	else {
		stopSign->SetDrawMode(GL_TRIANGLE_FAN);
	}
	return stopSign;
}

Mesh* Object2D::CreateHP(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;
	GLfloat arc;
	GLfloat twoPI = 2 * M_PI;

	vertices.emplace_back(corner + glm::vec3(0, 0, 0), color);
	for (GLushort i = 1; i <= 12; i++)
	{
		arc = twoPI * i / 12;
		vertices.emplace_back(corner + glm::vec3(sin(arc) * length, cos(arc) * length, 0), color);
	}

	std::vector<unsigned short> indices =
	{
		1, 2,
		2, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 7,
		7, 8,
		8, 9,
		9, 10,
		10, 11,
		11, 12,
		12, 1,
		1, 5,
		7, 11,
		3, 9,
	};

	Mesh* stopSign = new Mesh(name);
	stopSign->InitFromData(vertices, indices);
	if (!fill) {
		stopSign->SetDrawMode(GL_LINES);
	}
	else {
		stopSign->SetDrawMode(GL_TRIANGLE_FAN);
	}
	return stopSign;
}



