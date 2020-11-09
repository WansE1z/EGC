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
		glm::mat3 matrixSh[4], matrixArrow, matrixPowerBar, matrixBalloon[7], matrixBow, matrixHealth[10], matrixStop, matrixPowerBarOut, matrixHp;
		float xBow = 0.f, yBow = 0.f, xArrow = 0.f,
			xBal[7], yBal[7], xSh[4], ySh[4], yArrow = 0.f, xHealth[10] = { 150, 200, 250, 300, 350, 400, 450, 500, 550, 600 },
			xStop, yStop, distXStop, distYStop, distStop,
			xHp, yHp, distXHp, distYHp, distHp,
			scaleXPowerBar = 0.2f, powerArrow = 0, arrowTipInitX = 116, arrowTipInitY = 8,
			distxBal[7], distyBal[7], distBal[7], distxSh[4], distySh[4], distSh[4], distXBow[4], distYBow[4], distBow[4],
			angularStep, angularBow, lastArrowAngle, radToGrade = 180 / M_PI;
		int bowSize = 50, arrowSize = 6, balloonSize = 20, polyLineSize = 5, shurikenSize = 20, powerBarSize = 10, squareSize = 20, stopSize = 30, hpSize = 10,
			balMeter, colorPicker1, colorPicker2,
			moveBow = -1, border = 3, powerBarMargin = 100, mouseX, mouseY, mouseYFinal,
			collisionBal[7] = { 0 }, collisionSh[4] = { 0 }, collisionBow[4] = { 0 }, collisionStop, collisionHp,
			score = 0, lifes = 3, scoreSh = 0, scoreBal = 0, seconds = 0, secondsHp = 1002,
			nrBal = 3, nrSh = 2;
		bool leftClick = false, arrowShot = false, dissapearedBal[7], dissapearedSh[4], dissHp, moveStopSign = true, moveHp = true;
		std::string balloonColor[7];
		glm::ivec2 res = window->GetResolution();

};
