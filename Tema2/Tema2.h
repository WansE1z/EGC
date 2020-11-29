#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include "LabCamera.h"
#include "Plank.h"
#include "Sphere.h"
#include "Gas.h"
#include "Transform3D.h"
#include <algorithm>
using namespace std;

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();
		void Init() override;
		Plank plank[24];
		Plank plank2[24];
		Plank invizPlank[24];
		Sphere sphere;
		Gas gas;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 &color);

	protected:
		bool firstPerson, jump = false, jumping = false, outsideOfMap = false, fallen = false, speedy = false, gasMod = false;
		float angJump = 0, speed = 1.f;
		int random, nrPlanks = 0, seconds = 1, random2, random3, secondsSpeed = 1, secondsGas = 1;
		glm::ivec2 res = window->GetResolution();
		glm::mat4 modelPlank[24], modelPlank2[24], modelSphere, projectionMatrix, modelGas, modelInnerGas;
		glm::vec3 lastPosCamera;
		MyCamera* camera;


};
