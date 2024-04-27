#include "Ilumination.h"

#include <glm/gtc/type_ptr.hpp>

#pragma region Material

void Material::upload()
{		
	//glColorMaterial(face, GL_AMBIENT);
	//glColorMaterial(face, GL_DIFFUSE);
	glColorMaterial(face, GL_SPECULAR);
	glColorMaterial(face, GL_SHININESS);

	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
	
	//glLightModeli ( GL_LIGHT_MODEL_TWO_SIDE , GL_FALSE ); // Defecto
}

void Material::setCopper()
{
	ambient = { 0.19125 , 0.0735 , 0.0225 , 1 };
	diffuse = { 0.7038 , 0.27048 , 0.0828 , 1 };
	specular = { 0.256777 , 0.137622 , 0.086014 , 1 };
	expF = 12.8;
}

void Material::setGold()
{
	ambient = { 0.24725 , 0.1995 , 0.0745 , 1.0 };
	diffuse = { 0.75164 , 0.60648 , 0.22648 , 1.0 };
	specular = { 0.628281 , 0.555802 , 0.366065 , 1.0 };
	

	expF = 51.4;
}

#pragma endregion

#pragma region Lights

#pragma region Light Abstract

GLuint Light::cont = 0;

Light::Light()
{
	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		glEnable(id);
	}

}

void Light::uploadL() const {
	// Transfiere las características de la luz a la GPU
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}

#pragma endregion

#pragma region DirLights


void DirLight::upload(glm::dmat4 const& modelViewMat) const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	uploadL();
}

// Ojo al 0.0 que determina que la luz sea remota
void DirLight::setPosDir(glm::fvec3 dir) {
	posDir = glm::fvec4(dir, 0.0);
}

#pragma endregion

#pragma region PosLight

void PosLight::upload(glm::dmat4 const& modelViewMat) const {
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	glLightf(id, GL_CONSTANT_ATTENUATION, kc);
	glLightf(id, GL_LINEAR_ATTENUATION, kl);
	glLightf(id, GL_QUADRATIC_ATTENUATION, kq);
	uploadL();
}

// Ojo al 1.0 que determina que la luz sea local
void PosLight::setPosDir(glm::fvec3 dir) {
	posDir = glm::fvec4(dir, 1.0);
}


#pragma endregion



#pragma endregion
