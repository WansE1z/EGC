#include "Tema1.h"
#include "Limits.hpp"
#include "PrintConsole.hpp"
#include "MatrixUpdate.hpp"
#include "ArrowFunctions.hpp"
#include "Collision.hpp"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"

using namespace std;


Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)res.x, 0, (float)res.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 1));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	xBal[0] = rand() % 200 + 400; // 400-600 ox
	xBal[1] = rand() % 200 + 650; // 650-850 ox
	xBal[2] = rand() % 200 + 900; // 900-1100 ox

	ySh[0] = rand() % 200 + 100; // 100-300 oy
	ySh[1] = rand() % 200 + 500; // 500-700 oy

	xStop = rand() % 600 + 300; // 100-700 ox
	yStop = 100;

	yHp = 620;
	xHp = rand() % 600 + 500; // 500-1100 ox

	colorPicker1 = colorPicker2 = rand() % 3;

	glm::vec3 corner = glm::vec3(70, 0, 0);
	glm::vec3 corner2 = glm::vec3(110, 2, 0);
	glm::vec3 corner3 = glm::vec3(110, 110, 0);
	glm::vec3 cornerBow = glm::vec3(30, 0, 0);
	glm::vec3 cornerBalloon = glm::vec3(0, 0, 0);
	glm::vec3 cornerPolyLine = glm::vec3(0, -20, 0);
	glm::vec3 cornerShuriken = glm::vec3(0, 0, 0);
	glm::vec3 cornerPowerBar = glm::vec3(600, -100, 0);
	glm::vec3 cornerPowerUp = glm::vec3(600, 100, 0);
	glm::vec3 cornerSquare = glm::vec3(0, 0, 0);
	glm::vec3 cornerStopSign = glm::vec3(0, 0, 0);
	glm::vec3 cornerHP = glm::vec3(0, 0, 0);

	Mesh* bow = Object2D::CreateBow("bow", cornerBow, bowSize, glm::vec3(1, 1, 1), false);
	Mesh* arrow = Object2D::CreateArrow("arrow", corner, corner2, arrowSize, glm::vec3(1, 1, 1), true);
	Mesh* balloonRed = Object2D::CreateBalloon("balloon", cornerBalloon, balloonSize, glm::vec3(0.8f, 0, 0), true);
	Mesh* balloonYellow = Object2D::CreateBalloon("balloonYellow", cornerBalloon, balloonSize, glm::vec3(0.9f, 0.9f, 0), true);
	Mesh* polyline = Object2D::CreatePolyLine("poly", cornerPolyLine, polyLineSize, glm::vec3(1, 1, 1), true);
	Mesh* shuriken = Object2D::CreateShuriken("shuriken", cornerShuriken, shurikenSize, glm::vec3(1, 1, 1), true);
	Mesh* powerbarDown = Object2D::CreateRectangle("powerbarDown", cornerPowerBar, powerBarSize, glm::vec3(1, 1, 1), true);
	Mesh* powerbarUp = Object2D::CreateRectangle("powerbarUp", cornerPowerUp, powerBarSize, glm::vec3(1, 1, 1), true);
	Mesh* square = Object2D::CreateSquare("square", cornerSquare, squareSize, glm::vec3(0.8f, 0, 0), true);
	Mesh* stopSign = Object2D::CreateStopSign("stop", cornerStopSign, stopSize, glm::vec3(0.8f, 0, 0), false);
	Mesh* outRectUp = Object2D::CreateOutRectangle("rectoutUp", cornerPowerUp, powerBarSize, glm::vec3(1, 1, 1), false);
	Mesh* outRectDown = Object2D::CreateOutRectangle("rectoutDown", cornerPowerBar, powerBarSize, glm::vec3(1, 1, 1), false);
	Mesh* hpInc = Object2D::CreateHP("hp", cornerHP, hpSize, glm::vec3(0, 0.9f, 0.1f), false);

	AddMeshToList(arrow);
	AddMeshToList(bow);
	AddMeshToList(balloonRed);
	AddMeshToList(balloonYellow);
	AddMeshToList(polyline);
	AddMeshToList(shuriken);
	AddMeshToList(powerbarDown);
	AddMeshToList(powerbarUp);
	AddMeshToList(square);
	AddMeshToList(stopSign);
	AddMeshToList(outRectUp);
	AddMeshToList(outRectDown);
	AddMeshToList(hpInc);

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
;
	// sets the screen area where to draw
	glViewport(0, 0, res.x, res.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	mouseX = window->GetCursorPosition().x;
	mouseY = window->GetCursorPosition().y;
	mouseYFinal = -mouseY - yBow + res.y / 2;
	angularBow = glm::atan((float)mouseYFinal / (float)mouseX);

	updateAngleArrow(arrowShot, lastArrowAngle, angularBow); 

	// STOP SIGN
	{
		matrixStop = glm::mat3(1);
		matrixStopSignUpdate(moveStopSign, deltaTimeSeconds, res, yStop, matrixStop, xStop);

		RenderMesh2D(meshes["stop"], shaders["VertexColor"], matrixStop);
	}

	// HP SIGN
	{
		matrixHp = glm::mat3(1);
		matrixHpUpdate(moveHp, yHp, deltaTimeSeconds, res, matrixHp, xHp, dissHp);
		if (dissHp != true) {
			RenderMesh2D(meshes["hp"], shaders["VertexColor"], matrixHp);
		}
		else {
			secondsHpInc(secondsHp, dissHp);
		}
	}

	// BALONUL
	{
		for (int i = 0; i < 3; i++) {
			matrixBalloon[i] = glm::mat3(1);
			matrixBalloon[i] *= Transform2D::Translate(xBal[i], -10);
			// pozitia initiala pe ecran

			yBal[i] += 0.2f * deltaTimeSeconds * res.y;
			matrixBalloon[i] *= Transform2D::Translate(0, yBal[i]);
			// miscarea "in sus" a balonului

			// daca exista coliziune, dispare balonul
			if (collisionBal[i] == 1) {
				matrixBalloon[i] *= Transform2D::Scale(0, 0);
				collisionBal[i] = 0;
				dissapearedBal[i] = true;
			}

			// readucerea in pozitie cand iese de pe axa oy a scenei
			// daca balonul a fost lovit, cand revine pe ecran sa reapara
			if (yBal[i] >= (res.y * 1.2f)) {
				if (dissapearedBal[i] == true) {
					dissapearedBal[i] = false;
				}
				yBal[i] = -10;
			}

			// daca nu e lovit, render it
			if (dissapearedBal[i] == false) {
				RenderMesh2D(meshes["poly"], shaders["VertexColor"], matrixBalloon[i]);

				if (i == colorPicker1 || i == colorPicker2) {
					RenderMesh2D(meshes["balloonYellow"], shaders["VertexColor"], matrixBalloon[i]);
					balloonColor[i] = "yellow";
				}
				else {
					RenderMesh2D(meshes["balloon"], shaders["VertexColor"], matrixBalloon[i]);
					balloonColor[i] = "red";
				}
			}
		}
	}

	// SHURIKENUL
	{
		angularStep += deltaTimeSeconds;

		for (int i = 0; i < 2; i++) {
			matrixSh[i] = glm::mat3(1);
			matrixSh[i] *= Transform2D::Translate(res.x, ySh[i]);

			// valoare de se scade mereu din x, ca sa mearga pe orizontala invers
			xSh[i] -= 0.2f * deltaTimeSeconds * res.x;
			matrixSh[i] *= Transform2D::Translate(xSh[i], 0);

			// daca exista coliziune intre sageata-shuriken sau arc-shuriken, acesta dispare
			if (collisionSh[i] == 1 || collisionBow[i] == 1) {
				matrixSh[i] *= Transform2D::Scale(0, 0);
				collisionSh[i] = 0;
				collisionBow[i] = 0;
				dissapearedSh[i] = true;
			}

			// daca iese din ecran, sa revina
			if (xSh[i] < -res.x * 1.1f) {
				if (dissapearedSh[i] == true) {
					dissapearedSh[i] = false;
				}
				xSh[i] = res.x * 0.1f;
			}

			// sa se invarta in timp ce se misca pe orizontala
			matrixSh[i] *= Transform2D::Rotate(angularStep);

			// daca nu a disparut, il randez, altfel, nu
			if (dissapearedSh[i] == false) {
				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], matrixSh[i]);
			}
		}
	}

	// ARCUL
	{
		matrixBow = matrixArrow = matrixPowerBar = glm::mat3(1);
		matrixArrow = matrixBow *= Transform2D::Translate(0, res.y / 2);

		BowMoveUpDown(moveBow, yBow, bowSize, border, res);

		matrixBow *= Transform2D::Translate(0, yBow);
		matrixBow *= Transform2D::Rotate(angularBow);
		
		// coliziune bow - shuriken
		for (int i = 0; i < 2; i++) {
			distXBow[i] = res.x - xBow + xSh[i] - bowSize/2;
			distYBow[i] = yBow + res.y/2 - ySh[i];
			distBow[i] = sqrt((distXBow[i] * distXBow[i]) + (distYBow[i] * distYBow[i]));
			if (distBow[i] <= shurikenSize + bowSize) {
				collisionBow[i] = 1;
				xSh[i] = -res.x * 1.1f;
				// x-ul shuriken-ului il fac -res.x * 1.1f, ca sa apara disparut, sa reapara pe ecran

				lifes--;
				// daca este coliziune , scad o viata
			}

		}

		// powerbar foloseste aceeasi matrice ca bow-ul, doar ca nu se roteste, ramane orizontal
		matrixPowerBar = matrixBow;

		if (leftClick == true) {
			// daca am apasat click

			arrowShotDirection(arrowShot, xArrow, yArrow, powerArrow, deltaTimeSeconds, lastArrowAngle,
				radToGrade, arrowTipInitX, arrowTipInitY, matrixArrow);

			// coliziune balon - sageata
			for (int i = 0; i < 3; i++) {
				distxBal[i] = arrowTipInitX - xBal[i];
				distyBal[i] = arrowTipInitY - yBal[i] + res.y / 2 + balloonSize + 4;
				distBal[i] = sqrt((distxBal[i] * distxBal[i]) + (distyBal[i] * distyBal[i]));
				if (distBal[i] <= balloonSize) {
					collisionBal[i] = 1;
					yBal[i] = 1.2f * res.y;
					// formula punct-cerc, a avut loc coliziune

					// adun scor de la baloane (balon ROSU -> 100 / GALBEN -> -50)
					addScoreBalloons(balloonColor, score, i);
				}
			}

			// coliziune shuriken - sageata
			for (int i = 0; i < 2; i++) {
				distxSh[i] = arrowTipInitX - res.x - xSh[i];
				distyShuriken[i] = arrowTipInitY - ySh[i] + res.y / 2;
				distSh[i] = sqrt((distxSh[i] * distxSh[i]) + (distyShuriken[i] * distyShuriken[i]));

				if (distSh[i] <= shurikenSize) {
					collisionSh[i] = 1;
					xSh[i] = -res.x * 1.1f;
					// formula punct-cerc, a avut loc coliziune

					score += 200;
				}
			}

			collisionStopCalc(distXStop, distYStop, xStop, yStop, arrowTipInitX,
				arrowTipInitY, distStop, res, stopSize, collisionStop, lifes);

			collisionHpCalc(distXHp, distYHp, xHp, yHp, arrowTipInitX,
				arrowTipInitY, distHp, res, hpSize, collisionHp, lifes, dissHp);

			setLimitsArrow(xArrow, yArrow, res, leftClick, arrowShot, powerArrow, scaleXPowerBar);
		}
		else {
			arrowNotShot(matrixArrow, yBow, angularBow, yArrow, arrowTipInitY, arrowTipInitX);
		}

		scaleThePowerBar(matrixPowerBar, matrixPowerBarOut, angularBow, scaleXPowerBar);

		// verificare atunci cand arcul este in pozitia maxima de jos, powerbar-ul sa nu dispara de pe ecran
		// acesta sa apara deasupra ecranului, sa fie vazut in continuare
		if (yBow + (res.y / 2) < powerBarMargin) {
			RenderMesh2D(meshes["powerbarUp"], shaders["VertexColor"], matrixPowerBar);
			RenderMesh2D(meshes["rectoutUp"], shaders["VertexColor"], matrixPowerBarOut);
		}
		else {
			RenderMesh2D(meshes["powerbarDown"], shaders["VertexColor"], matrixPowerBar);
			RenderMesh2D(meshes["rectoutDown"], shaders["VertexColor"], matrixPowerBarOut);
		}

		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], matrixArrow);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], matrixBow);
	}

	 /* 
		 patrate sus, cand pierzi o viata, sa nu se mai randeze un patrat,
		 reflectand pierderea unei vieti
	 */
	{
		for (int i = 0; i < lifes; i++) {
			matrixHealth[i] = glm::mat3(1);
			matrixHealth[i] *= Transform2D::Translate(xHealth[i], res.y - 40);
			RenderMesh2D(meshes["square"], shaders["VertexColor"], matrixHealth[i]);
		}
	}
	PrintScore(seconds, score);
	PrintFinish(lifes, score);
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		moveBow = 0;
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		moveBow = 1;
	} else if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		setLimitsPower(arrowShot, powerArrow, scaleXPowerBar);
	}
}

void Tema1::OnKeyPress(int key, int mods)
{

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (arrowShot == false) {
		// daca nu e trasa sageata, se poate trage
		if (button == 1) {
			leftClick = false;
		}
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (arrowShot == false) {
		// daca nu e trasa sageata, si s-a adunat power, se trage
		if (button == 1) {
			leftClick = true;
		}
	}
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
