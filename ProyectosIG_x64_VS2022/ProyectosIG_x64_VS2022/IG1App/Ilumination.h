#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Material {
protected:
	// Coeficientes de reflexión
	glm::fvec4 ambient = { 0.2 , 0.2 , 0.2 , 1.0 };
	glm::fvec4 diffuse = { 0.8 , 0.8 , 0.8 , 1.0 };
	glm::fvec4 specular = { 0.0 , 0.0 , 0.0 , 1.0 };

	GLfloat expF = 51.2; // Exponente para la reflexión especular
	GLuint face = GL_FRONT_AND_BACK;
	GLuint sh = GL_SMOOTH; // Tipo de matizado

public:
	Material() {};
	virtual ~Material() {};
	virtual void upload();


	void setCopper();
	void setGold();

};


class Light { // Abstract class
protected:
	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1 , 0.1 , 0.1 , 1 };
	glm::fvec4 diffuse = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 specular = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 posDir = { 0 , 0 , 1 , 0 };
public:
	Light();
	virtual ~Light() { disable(); }
	void uploadL()const ;


	// Método abstracto
	virtual void upload(glm::dmat4 const& modelViewMat) const = 0;
	

	void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };
	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };

	// setters para cambiar el valor de los atributos lumínicos
	void setAmb(glm::fvec4 amb) {
		ambient = amb; uploadL();
	};

	void setDiff(glm::fvec4 diff) {
		diffuse = diff; uploadL();
	};

	void setSpec(glm::fvec4 spec) {
		specular = spec; uploadL();
	};

	//set dir
	void setPosDir(glm::fvec4 pDir) {
		posDir = pDir; uploadL();
	};
};

class DirLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
};
