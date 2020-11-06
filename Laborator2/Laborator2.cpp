#include "Laborator2.h"

#include <vector>
#include <iostream>
#include <math.h>

#include <Core/Engine.h>

using namespace std;

bool keyP = false;

Laborator2::Laborator2()
{
}

Laborator2::~Laborator2()
{

}

void Laborator2::Init()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 1), glm::vec3(.5f, 1.f, 0)),
			VertexFormat(glm::vec3(1, 0, 1), glm::vec3(.2f, .8f, 1.f)),
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(.4f, 0, .5f)),
			VertexFormat(glm::vec3(1, 1, 1), glm::vec3(.3f, 1.f, .25f)),
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1.f, .5f)),
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(.5f, 0, .375f)),
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(.25f, .75f, 1.f)),
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(.5f, 1.f, 0)),
			// TODO: Complete the information for the cube
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			1, 3, 2,	// indices for second triangle
			2, 3, 7,
			2, 7, 6,
			1, 7, 3,
			1, 5, 7,
			6, 7, 4,
			7, 5, 4,
			0, 4, 1,
			1, 4, 5,
			2, 6, 4,
			0, 2, 4
			// TODO: Complete indices data
		};

		meshes["cube1"] = new Mesh("generated cube 1");
		meshes["cube1"]->InitFromData(vertices, indices);

		// Create a new mesh from buffer data
		Mesh *cube = CreateMesh("cube3", vertices, indices);
	}

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(.25f, .75f, .5f)),
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(.75f, .25f, .5f)),
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1.f, .25f)),
			VertexFormat(glm::vec3(1, 0, 1), glm::vec3(1.f, .5f, .5f))
		};

		vector<unsigned short> indices =
		{
			0, 2, 1,
			0, 1, 3,
			1, 2, 3,
			0, 2, 3,
			// TODO: Complete indices data
		};

		Mesh* tetraedru = CreateMesh("tetraedru", vertices, indices);
	}

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(.25f, .75f, .5f)),
			VertexFormat(glm::vec3(0, 0, 1), glm::vec3(.75f, .25f, .5f)),
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1.f, .25f)),
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(1.f, .5f, .5f))
		};

		vector<unsigned short> indices =
		{
			0, 3, 2,
			0, 3, 1,
			// TODO: Complete indices data
		};

		CreateMesh("square", vertices, indices);

	}

	{
		vector<VertexFormat> vertices;
		vector<unsigned short> indices;
		GLfloat arc;

		vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(0.5f, 1.f, 0));
		for (GLushort i = 0; i <= 75; i++)
		{
			arc = 2 * M_PI * i / 75;
			vertices.emplace_back(glm::vec3(cos(arc), sin(arc), 0), glm::vec3(0.5f, 1.f, 0));
			indices.push_back(i);
		}
		indices.push_back(1);

		CreateMesh("circle", vertices, indices);
		meshes["circle"]->SetDrawMode(GL_TRIANGLE_FAN);
	}

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)), // negru
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, .9f, .1f)), //albastru
			VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1.f, 1.f)), //cyan
			VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0.4f, 0.1f, 0)), // rosu
			VertexFormat(glm::vec3(0, 2, 0), glm::vec3(0.9f, 0.5f, .1f)), // oranj
			VertexFormat(glm::vec3(1, 2, 0), glm::vec3(1.f, 1.f, 0)), // galben
			VertexFormat(glm::vec3(1, 2, 1), glm::vec3(1.f, .5f, 1.f)), // roz
			VertexFormat(glm::vec3(0, 2, 1), glm::vec3(1.f, .5f, .5f)), // pink faded
		};

		vector<unsigned short> indices
		{
			0, 3, 2,
			0, 2, 1,
			3, 7, 4,
			3, 4, 2,
			7, 4, 0,
			// ...
		};

		CreateMesh("paral", vertices, indices);
		meshes["paral"]->SetDrawMode(GL_TRIANGLE_FAN);
	}

	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1.f, 0.f, 0.f)), // 0
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.f, 0.f, 1.f)), // 1
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1.f, 1.f, 0.f)), // 2
			
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(1.f, 0.f, 0.f)), // 3
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0.f, 0.f, 1.f)), // 4
			VertexFormat(glm::vec3(0, 1, 1), glm::vec3(1.f, 1.f, 1.f)), // 5

			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0.f, 0.f, 1.f)), // 6
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1.f, 1.f, 0.f)), // 7
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1.f, 1.f, 1.f)), // 8

			VertexFormat(glm::vec3(1, 0, 1), glm::vec3(1.f, 0.f, 0.f)), // 9
			VertexFormat(glm::vec3(1, 0, 1), glm::vec3(1.f, 1.f, 0.f)), // 10
			VertexFormat(glm::vec3(1, 0, 1), glm::vec3(1.f, 1.f, 1.f)), // 11
		};

		vector<unsigned short> indices =
		{
			2, 7, 10,
			4, 6, 1,
			3, 0, 9,
			11, 8, 5,
			// TODO: Complete indices data
		};

		Mesh* tetraedru2 = CreateMesh("tetraedru2", vertices, indices);
	}
}

Mesh* Laborator2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO); // generate vertex array object names
	glBindVertexArray(VAO); // bind vao

	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO); // vbo is buffer, generate buffer object names

	// TODO: Send vertices data into the VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // allocate data for the buffer
	/* void glBufferData(	GLenum target,
	GLsizeiptr size,
		const void* data,
			GLenum usage);
	*/


	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO); // ibo is buffer, generate buffer object names
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); // bind the buffer

	// TODO: Send indices data into the IBO buffer

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
	/* void glBufferData(	GLenum target,
	GLsizeiptr size,
		const void* data,
			GLenum usage);
	*/

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Laborator2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Set face custom culling. Use the "cullFace" variable
	glCullFace(cullFace);

	// render an object using face normals for color
	//RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

	// render an object using colors from vertex
	RenderMesh(meshes["cube1"], shaders["VertexColor"], glm::vec3(-2.f, 0.5f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["cube3"], shaders["VertexColor"], glm::vec3(-1.f, 0.5f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["tetraedru"], shaders["VertexColor"], glm::vec3(0.f, 0.5f, 0), glm::vec3(0.75f));
	RenderMesh(meshes["square"], shaders["VertexColor"], glm::vec3(1.f, 0.5f, 0), glm::vec3(0.75f));
	RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(2.f, 0.5f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["paral"], shaders["VertexColor"], glm::vec3(3.f, 0.5f, 0), glm::vec3(0.5f));
	RenderMesh(meshes["tetraedru2"], shaders["VertexColor"], glm::vec3(4.f, 0.5f, 0), glm::vec3(0.75f));
	
	// Disable face culling
	glDisable(GL_CULL_FACE);
}

void Laborator2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator2::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator2::OnKeyPress(int key, int mods)
{
	// TODO: switch between GL_FRONT and GL_BACK culling
	// Save the state in "cullFace" variable and apply it in the Update() method not here

	if (key == GLFW_KEY_F2) {
		keyP = !keyP;
	}

	if (keyP) {
		cullFace = GL_FRONT;
	}
	else {
		cullFace = GL_BACK;
	}

	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Laborator2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator2::OnWindowResize(int width, int height)
{
}
