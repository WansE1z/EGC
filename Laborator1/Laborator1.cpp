#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

#define SPEED (.02f)

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

auto keyPressed = false;
vector<string> meshName = { "box", "teapot", "sphere" };
int meshOrder = 0;
glm::vec3 pos = glm::vec3(-3, 0.5f, 0);
GLfloat grade;
GLfloat x, y, z;
glm::vec3 pos2 = glm::vec3(2,0.5f,2);

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Mesh* mesh2 = new Mesh("teapot");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh2->GetMeshID()] = mesh2;

		Mesh* mesh3 = new Mesh("sphere");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;

		Mesh* mesh4 = new Mesh("sphere");
		mesh4->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh4->GetMeshID()] = mesh4;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer

	grade += SPEED;
	if (grade > 360.f) {
		grade = 0.f;
	}

	float x2 = 2.0f;
	float y2 = 2.0f;

	pos2.x = 3.0f;
	pos2.y = 3.0f;

	pos2.x -= x2;
	pos2.y -= y2;

	pos2.x = pos2.x * cos(grade) - pos2.y * sin(grade) + x2;
	pos2.y = pos2.y * sin(grade) + pos2.x * cos(grade) + y2;

	if (keyPressed) {
		glClearColor(255, 255, 0, 1);
	}
	else {
		glClearColor(0, 0, 0, 1);
	}

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	RenderMesh(meshes[meshName[meshOrder % 3]], pos, glm::vec3(1));

	RenderMesh(meshes["sphere"], pos2,glm::vec3(0.5f));

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		keyPressed = !keyPressed;
	} else if (key == GLFW_KEY_R) {
		meshOrder++;
	} else if (key == GLFW_KEY_W) {
		pos.z += 0.2f;
	} else if (key == GLFW_KEY_S) {
		pos.z -= 0.2f;
	} else if (key == GLFW_KEY_A) {
		pos.x -= 0.2f;
	} else if (key == GLFW_KEY_D) {
		pos.x += 0.2f;
	} else if (key == GLFW_KEY_E) {
		pos.y += 0.2f;
	} else if (key == GLFW_KEY_Q) {
		pos.y -= 0.2f;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
