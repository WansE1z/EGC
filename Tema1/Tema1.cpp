#include "Tema1.h"
#include "Arrow.h"
#include "Bow.h"
#include "PowerBar.h"
#include "StopSign.h"
#include "HealthBoost.h"
#include "GameMechanics.h"
#include "Balloon.h"
#include "Shuriken.h"

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
	GameMechanics::setInitialPositions(xBal, ySh, res, xStop, yStop, xHp, yHp, colorPicker1, colorPicker2);

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

	GameMechanics::Intro();
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, res.x, res.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	angleBow = GameMechanics::calculateAngle(mouseX, mouseY, yBow, res, angleBow, mouseYFinal, window);

	Arrow::updateAngleArrow(arrowShot, lastArrowAngle, angleBow);
	GameMechanics::updateDifficutly(score, nrBal, nrSh);

	// STOP SIGN
	{
		StopSign::stopSignMovement(moveStopSign, deltaTimeSeconds, res, yStop, matrixStop, xStop);
		RenderMesh2D(meshes["stop"], shaders["VertexColor"], matrixStop);
	}
	
	// HP SIGN
	{
		HealthBoost::hpBoostMovement(moveHp, yHp, deltaTimeSeconds, res, matrixHp, xHp, dissHp);
		if (dissHp != true) {
			RenderMesh2D(meshes["hp"], shaders["VertexColor"], matrixHp);
		}
		else {
			GameMechanics::secondsHpInc(secondsHp, dissHp);
		}
	}

	// BALONUL
	{
		for (int i = 0; i < nrBal; i++) {
			Balloon::balloonMovementAndDissapear(i, matrixBalloon, xBal, yBal, deltaTimeSeconds, res,
				collisionBal, dissapearedBal);

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

		for (int i = 0; i < nrSh; i++) {
			Shuriken::shurikenMovementAndDissapear(i, matrixSh, res, xSh, ySh, deltaTimeSeconds, collisionSh, collisionBow,
				dissapearedSh, angularStep);

			// daca nu a disparut, il randez, altfel, nu
			if (dissapearedSh[i] == false) {
				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], matrixSh[i]);
			}
		}
	}

	// ARCUL
	{
		// initializare si miscarea arcului
		Bow::BowMoveUpDown(moveBow, yBow, bowSize, border, res, matrixBow, matrixArrow, matrixPowerBar, angleBow);
		
		// coliziune bow - shuriken
		Bow::CheckCollisionBow(nrSh, res, distXBow, distYBow, xBow, yBow, xSh, ySh, bowSize, distBow,
			shurikenSize, collisionBow, lifes);

		if (leftClick == true) {

			// daca am apasat click
			Arrow::arrowShotDirection(arrowShot, xArrow, yArrow, powerArrow, deltaTimeSeconds, lastArrowAngle,
				radToGrade, arrowTipInitX, arrowTipInitY, matrixArrow);

			// coliziune balon - sageata
			Balloon::checkCollisionBalloon(nrBal, distxBal, distyBal, distBal, arrowTipInitX, arrowTipInitY, xBal, yBal,
				res, balloonSize, collisionBal, balloonColor, score);

			// coliziune shuriken - sageata
			Shuriken::checkCollisionShuriken(nrSh, distxSh, distySh, distSh, arrowTipInitX, arrowTipInitY, res, xSh, ySh,
				shurikenSize, collisionSh, score);

			// coliziune stopsign - sageata
			StopSign::collisionStopCalc(distXStop, distYStop, xStop, yStop, arrowTipInitX,
				arrowTipInitY, distStop, res, stopSize, collisionStop, lifes);

			// coliziune healthboost - sageata
			HealthBoost::collisionHpCalc(distXHp, distYHp, xHp, yHp, arrowTipInitX,
				arrowTipInitY, distHp, res, hpSize, collisionHp, lifes, dissHp);

			// verific cand sageata iese din ecran, sa revina pe arc sau cand e viteza foarte mica, sa se respawneze
			Arrow::setLimitsArrow(xArrow, yArrow, res, leftClick, arrowShot, powerArrow, scaleXPowerBar);
		}
		else {
			// daca sageata nu este trasa
			Arrow::arrowNotShot(matrixArrow, yBow, angleBow, yArrow, arrowTipInitY, arrowTipInitX);
		}
		// scalez powerbar-ul sa se mareasca cand se tine apasat click
		PowerBar::scaleThePowerBar(matrixPowerBar, matrixPowerBarOut, angleBow, scaleXPowerBar);

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
			HealthBoost::renderHealth(i, lifes, matrixHealth, xHealth, res);
			RenderMesh2D(meshes["square"], shaders["VertexColor"], matrixHealth[i]);
		}
	}
	GameMechanics::PrintScore(seconds, score);
	GameMechanics::PrintFinish(lifes, score);
	// BONUS:
	// Am adaugat dificultate, cand se depaseste scorul de 2000, sunt 5 baloane si 3 shuriken-uri
	// Cand scor >= 4000, 7 baloane si 4 shuriken-uri
	// Health boost, iti da o viata (hexagon verde)
	// Stop sign, iti ia toate vietiile (te omoara)
	// Apar vietiile sus in stanga, ca reper
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// daca se tine apasat pe W, se poate tine apasat si click, de aceea maresc si powerArrow-ul
	GameMechanics::holdWSClick(window, arrowShot, powerArrow, scaleXPowerBar, moveBow);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// daca nu e trasa sageata, se poate trage
	GameMechanics::holdMouseUpdate(arrowShot, button, leftClick, false);
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// daca nu e trasa sageata, se poate trage si dau increase si la powerArrow
	GameMechanics::holdMouseUpdate(arrowShot, button, leftClick, true);
}
