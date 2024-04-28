#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

Material::Material(GLuint cara, GLuint luz, glm::fvec4 coeficientes) : mCara(cara), mComponenteLuz(luz), a(coeficientes)
{

	glMaterialfv(mCara, mComponenteLuz, glm::value_ptr(a));

}

void Material::render() {

	glColorMaterial(mCara, mComponenteLuz);

}