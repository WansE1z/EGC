#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Object3D.h"
#include "LabCamera.h"
#include "Detection.h"
#include "GameMechanics.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	nrPlanks = 24;
	camera = new MyCamera();
	camera->Set(glm::vec3(0, 1, 10), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	PlankFunc::initPlanks(plank, plank2, invizPlank, nrPlanks, random, random2, random3);
	sphere.poz = plank[0].poz + glm::vec3(1.5, 0.6, 0);
	gas.poz = glm::vec3(4, 3, 0);
	gas.fuel = 30.0f;

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* plat = Object3D::CreatePlatform("platWhite", plank[0].poz, 3, glm::vec3(0, 0, 1), false);
		AddMeshToList(plat);

		Mesh* plat2 = Object3D::CreatePlatform("platPurple", plank[0].poz, 3, glm::vec3(0.2, 0, 0.4), false);
		AddMeshToList(plat2);

		Mesh* plat3 = Object3D::CreatePlatform("platGreen", plank[0].poz, 3, glm::vec3(0, 0.9, 0.3), false);
		AddMeshToList(plat3);

		Mesh* plat4 = Object3D::CreatePlatform("platRed", plank[0].poz, 3, glm::vec3(0.9, 0, 0), false);
		AddMeshToList(plat4);

		Mesh* plat5 = Object3D::CreatePlatform("platOrange", plank[0].poz, 3, glm::vec3(0.8, 0.6, 0.3), false);
		AddMeshToList(plat5);

		Mesh* plat6 = Object3D::CreatePlatform("platYellow", plank[0].poz, 3, glm::vec3(0.9, 1, 0), false);
		AddMeshToList(plat6);
	}

	{
		Mesh* rect = Object3D::CreateGasRect("rect", gas.poz , 2, glm::vec3(1, 1, 1), false);
		AddMeshToList(rect);

		Mesh* rect100 = Object3D::CreateGasRect2("rect100", gas.poz, 1.99, glm::vec3(0,0.5,0.2), false, 1);
		Mesh* rect90 = Object3D::CreateGasRect2("rect90", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.9);
		Mesh* rect80 = Object3D::CreateGasRect2("rect80", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.8);
		Mesh* rect70 = Object3D::CreateGasRect2("rect70", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.7);
		Mesh* rect60 = Object3D::CreateGasRect2("rect60", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.6);
		Mesh* rect50 = Object3D::CreateGasRect2("rect50", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.5);
		Mesh* rect40 = Object3D::CreateGasRect2("rect40", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.4);
		Mesh* rect30 = Object3D::CreateGasRect2("rect30", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.3);
		Mesh* rect20 = Object3D::CreateGasRect2("rect20", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.2);
		Mesh* rect10 = Object3D::CreateGasRect2("rect10", gas.poz, 1.99, glm::vec3(0, 0.5, 0.2), false, 0.1);
		AddMeshToList(rect100);
		AddMeshToList(rect90);
		AddMeshToList(rect80);
		AddMeshToList(rect70);
		AddMeshToList(rect60);
		AddMeshToList(rect50);
		AddMeshToList(rect40);
		AddMeshToList(rect30);
		AddMeshToList(rect20);
		AddMeshToList(rect10);
	}

	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}


}  
	


void Tema2::FrameStart()
{

	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::Update(float deltaTimeSeconds)
{
	{ // PLATFORME
		PlankFunc::planksOutOfVision(nrPlanks, camera, plank, plank2, invizPlank);
		for (int i = 0; i < nrPlanks; i++) {
			PlankFunc::powerupsPlank(plank2, plank, gas, speedy, i, gasMod);

			// generarea primelor randuri
			// adica practic cate o coloana pe rand
			modelPlank[i] = glm::mat4(1);
			modelPlank[i] = Transform3D::Translate(plank[i].poz.x, plank[i].poz.y, plank[i].poz.z);
			if (plank[i].color == "purple") {
				RenderMesh(meshes["platPurple"], shaders["VertexColor"], modelPlank[i]);
			}
			else if (plank[i].color == "green") {
				RenderMesh(meshes["platGreen"], shaders["VertexColor"], modelPlank[i]);
			}
			else if (plank[i].color == "orange") {
				RenderMesh(meshes["platOrange"], shaders["VertexColor"], modelPlank[i]);
			}
			else {
				RenderMesh(meshes["platWhite"], shaders["VertexColor"], modelPlank[i]);
			}

			// sa se spawneze o singura platforma la start-ul jocului
			modelPlank2[i] = glm::mat4(1);
			modelPlank2[i] = Transform3D::Translate(plank2[i].poz.x, plank2[i].poz.y, plank2[i].poz.z);
			if (plank2[i].color == "purple") {
				RenderMesh(meshes["platPurple"], shaders["VertexColor"], modelPlank2[i]);
			}
			else if (plank2[i].color == "red"){
				RenderMesh(meshes["platRed"], shaders["VertexColor"], modelPlank2[i]);
			}
			else if (plank2[i].color == "yellow") {
				RenderMesh(meshes["platYellow"], shaders["VertexColor"], modelPlank2[i]);
			}
			else {
				RenderMesh(meshes["platWhite"], shaders["VertexColor"], modelPlank2[i]);
			}
		}
	}
	GameMechanics::timeForSpeedPowerup(speedy, secondsSpeed);
	GameMechanics::timeForGasPowerup(gasMod, secondsGas);

	{ // SFERA
		GameMechanics::movementCameraObjects(sphere, gas, deltaTimeSeconds, speed, camera);

		// saritura
		SphereFunc::jumpSphere(jump, seconds, jumping, firstPerson, camera, sphere, gas);

		Detection::changeColorWhenTouchedFirstCol(sphere, plank, outsideOfMap, nrPlanks);
		Detection::changeColorWhenTouched(sphere, plank2, outsideOfMap, nrPlanks);
		Detection::detectOutOfMap(sphere, invizPlank, outsideOfMap, nrPlanks);
		SphereFunc::fallingSphere(sphere, outsideOfMap, firstPerson, camera, fallen);

		modelSphere = glm::mat4(1);
		modelSphere = Transform3D::Translate(sphere.poz.x, sphere.poz.y, sphere.poz.z);
		if (!speedy && !gasMod) {
			RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelSphere);
		}
		if (speedy && !gasMod) {
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelSphere, glm::vec3(1, 1, 1));
		}
		if (!speedy && gasMod) {
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelSphere, glm::vec3(1, 1, 1));
		}
		if (speedy && gasMod) {
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], modelSphere, glm::vec3(1, 1, 1));
		}
		
	}

	{ // GAS
		
		modelInnerGas = modelGas = glm::mat4(1);
		modelGas *= Transform3D::Translate(gas.poz.x, gas.poz.y, gas.poz.z);
		modelInnerGas *= Transform3D::Translate(gas.poz.x, gas.poz.y, gas.poz.z);
		RenderMesh(meshes["rect"], shaders["VertexColor"], modelGas);

		// randarea pe segmente a combustibilului
		if (gas.fuel <= 30.f && gas.fuel >= 27.f) RenderMesh(meshes["rect100"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 27.f && gas.fuel >= 24.f) RenderMesh(meshes["rect90"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 24.f && gas.fuel >= 21.f) RenderMesh(meshes["rect80"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 21.f && gas.fuel >= 18.f) RenderMesh(meshes["rect70"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 18.f && gas.fuel >= 15.f) RenderMesh(meshes["rect60"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 15.f && gas.fuel >= 12.f) RenderMesh(meshes["rect50"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 12.f && gas.fuel >= 9.f)  RenderMesh(meshes["rect40"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 9.f && gas.fuel >= 6.f)   RenderMesh(meshes["rect30"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 6.f && gas.fuel >= 3.f)   RenderMesh(meshes["rect20"], shaders["VertexColor"], modelInnerGas);
		if (gas.fuel <= 3.f && gas.fuel >= 0.f)   RenderMesh(meshes["rect10"], shaders["VertexColor"], modelInnerGas);
	
		GasFunc::outOfFuel(gas);
	}
}

void Tema2::FrameEnd()
{
	
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	GameMechanics::changeSpeed(speedy, secondsSpeed, speed, window);
}

void Tema2::OnKeyPress(int key, int mods)
{
	GameMechanics::jumpAD(fallen, window, sphere, firstPerson, camera, gas, jump);
	GameMechanics::toggleFirstPersonOrThirdPerson(key, firstPerson, camera, sphere, gas);
}

void Tema2::OnKeyRelease(int key, int mods)
{

}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
	{
		return;
	}

	// Render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Get shader location for uniform mat4 "Model"
	GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");

	// Set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Get shader location for uniform mat4 "View"
	GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

	// Set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Get shader location for uniform mat4 "Projection"
	GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// Set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Get shader location for "Time"
	GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");

	GLint locObject = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(locObject, 1, glm::value_ptr(color));

	// Set shader uniform "Time" to elapsed time
	glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}
