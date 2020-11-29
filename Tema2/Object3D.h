#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <include/gl.h>
using namespace std;

namespace Object3D
{
	Mesh* CreatePlatform(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateGasRect(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateGasRect2(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill, float percent);
}
