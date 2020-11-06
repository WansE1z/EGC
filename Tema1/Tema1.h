#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <cstdlib>
#include <Core/Engine.h>
#include <chrono> 

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

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

	protected:
		glm::mat3 matrixSh[2], matrixArrow, matrixPowerBar, matrixBalloon[3], matrixBow, matrixHealth[3];
		float xBow = 0.f, yBow = 0.f, xArrow = 0.f,
			xBal[3], yBal[3], xSh[2], ySh[2], yArrow = 0.f, xHealth[3] = { 150, 200, 250 },
			scaleXPowerBar = 0.2f, powerArrow = 0, arrowTipInitX = 116, arrowTipInitY = 8,
			distxBal[3], distyBal[3], distBal[3], distxSh[2], distyShuriken[2], distSh[2], distXBow[2], distYBow[2], distBow[2],
			angularStep, angularBow, lastArrowAngle, radToGrade = 180 / M_PI;
		int bowSize = 50, arrowSize = 6, balloonSize = 20, polyLineSize = 5, shurikenSize = 20, powerBarSize = 5, squareSize = 20,
			balMeter, colorPicker1, colorPicker2,
			moveBow = -1, border = 3, powerBarMargin = 100, mouseX, mouseY, mouseYFinal,
			collisionBal[3] = { 0 }, collisionSh[2] = { 0 }, collisionBow[2] = { 0 },
			score = 0, lifes = 3, scoreSh = 0, scoreBal = 0, seconds = 0;
		bool leftClick = false, arrowShot = false, dissapearedBal[3], dissapearedSh[2];
		std::string balloonColor[3];
		glm::ivec2 res = window->GetResolution();

};
