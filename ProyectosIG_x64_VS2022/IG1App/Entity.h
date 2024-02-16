#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0), mColor(1.0){}; // 4x4 identity matrix
	virtual ~Abs_Entity() = default;

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0; // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	glm::dvec4 getColor() {
		return mColor;
	}

	void setColor(glm::dvec4 color) {
		mColor = color;
	}

	void setColor(double r, double g, double b, double a) {

		mColor = { r, g, b, a };

	}

	virtual void update();

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix

	glm::dvec4 mColor;

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;
};

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class PoligonoRegular : public Abs_Entity
{
public:
	explicit PoligonoRegular(GLuint num, GLdouble r);
	~PoligonoRegular();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RBGTriangle : public Abs_Entity
{
public:
	explicit RBGTriangle(GLdouble r, GLdouble x, GLdouble y);
	~RBGTriangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;

private:
	GLdouble myX;
	GLdouble myY;
};

class RGBRectangle : public Abs_Entity
{
public:
	explicit RGBRectangle(GLuint w, GLuint h);
	~RGBRectangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Cube : public Abs_Entity
{
public:
	explicit Cube(GLdouble length);
	~Cube();
	virtual void render(glm::dmat4 const& modelViewMat) const;

private:

	GLdouble length;

};

#endif //_H_Entities_H_
