#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

void Material::upload()
{

	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
	glLightModeli ( GL_LIGHT_MODEL_TWO_SIDE , GL_FALSE ); // Defecto

}

void Material::setSpecular(glm::fvec4 specularAux)
{

	specular = specularAux;

}

void Material::setDiffuse(glm::fvec4 diffuseAux)
{
	diffuse = diffuseAux;

}

void Material::setAmbient(glm::fvec4 ambientAux)
{

	ambient = ambientAux;

}

void Material::setExponent(GLfloat exp)
{

	expF = exp;

}
