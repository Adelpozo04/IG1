#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <vector>

class Light { // Abstract class
protected:

	static GLuint cont; // Atributo para poder generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // Primer id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1 , 0.1 , 0.1 , 1 };
	glm::fvec4 diffuse = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 specular = { 0.5 , 0.5 , 0.5 , 1 };
	glm::fvec4 posDir = { 0 , 0 , 1 , 0 };
	// Añade setters para cambiar el valor de los atributos lumínicos
public:
	Light();
	Light(GLuint id);
	virtual ~Light() { disable(); }
	void uploadL() const;
	// Método abstracto
	virtual void upload(glm::dmat4 const& modelViewMat) const = 0;

	void disable() {
		if (id < GL_LIGHT0 + GL_MAX_LIGHTS) {

			glDisable(id);

		}
	};
	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };
	void setAmb(glm::fvec4 amb) {
		ambient = amb; 
		uploadL();
	};

	virtual void setDiff(glm::fvec4 diff) {
		diffuse = diff;
		uploadL();
	};
	virtual void setSpec(glm::fvec4 spec) {
		specular = spec;
		uploadL();
	};

	
};

class DirLight : public Light {
public:
	DirLight() : Light() {};
	DirLight(GLuint id_) : Light(id_) {};
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
};

class PosLight : public Light {
protected:
	// Factores de atenuación
	GLfloat kc = 1, kl = 0, kq = 0;
public:
	PosLight() : Light() {};
	PosLight(GLuint id_) : Light(id_) {};
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kcAux, GLfloat klAux, GLfloat kqAux);
};

class SpotLight : public PosLight {
protected:
	// Atributos del foco
	glm::fvec4 direction = { 0 , 0 , -1 , 0 };
	GLfloat cutoff = 180;
	GLfloat exp = 0;
public:
	SpotLight(glm::fvec3 pos = { 0 , 0 , 0 }) : PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	SpotLight(GLuint id_, glm::fvec3 pos = { 0 , 0 , 0 }) : PosLight(id_) {
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
};



