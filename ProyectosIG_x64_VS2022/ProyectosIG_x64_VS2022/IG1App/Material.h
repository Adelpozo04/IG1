#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <vector>

class Material {

public:

	Material(GLuint cara, GLuint luz, glm::fvec4 coeficientes);

	void render();


private:
	
	GLuint mCara;

	GLuint mComponenteLuz;

	glm::fvec4 a;

};
