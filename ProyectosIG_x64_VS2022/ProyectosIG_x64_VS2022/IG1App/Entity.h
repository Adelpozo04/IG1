#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0),mColor(1) {}; // 4x4 identity matrix
	virtual ~Abs_Entity() = default;

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0; // abstract method

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };


	glm::dvec4 getColor() { return mColor; }

	void setColor(glm::dvec4 c) { mColor = c; }

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

class RegularPolygon : public Abs_Entity
{
public:
	explicit RegularPolygon(GLuint v, GLdouble r);
	~RegularPolygon();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class TriangleRGB : public Abs_Entity {
public:
	explicit TriangleRGB(GLdouble r);
	~TriangleRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};


#endif //_H_Entities_H_
