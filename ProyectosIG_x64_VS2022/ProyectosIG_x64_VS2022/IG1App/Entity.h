#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0),mColor(1) {}; // 4x4 identity matrix
	virtual ~Abs_Entity() = default;

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0; // abstract method

	virtual void update() {};

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };


	glm::dvec4 getColor() { return mColor; }

	void setColor(glm::dvec4 c) { mColor = c; }

	void setTexture(Texture* tex) { mTexture = tex; }

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix

	glm::dvec4 mColor;

	Texture* mTexture;


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

	glm::dvec3 vectorTranslate;

	GLdouble angleX = 0;
	GLdouble rotVelX;
public:
	explicit TriangleRGB(GLdouble r,glm::dvec3 v,GLdouble retVelX);
	~TriangleRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

};

class Rectangle_cls :public Abs_Entity {
public:
	explicit Rectangle_cls(GLdouble w,GLdouble h);
	~Rectangle_cls();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Rectangle_RGB :public Abs_Entity {
public:
	explicit Rectangle_RGB(GLdouble w, GLdouble h);
	~Rectangle_RGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

class Cube : public Abs_Entity {
	glm::dvec3 vectorTranslate;

	int state = 0;
	
	std::vector<GLdouble> _angles;
	GLdouble rotVel;
public:
	explicit Cube(GLdouble w,bool center,GLdouble rotVel);
	~Cube();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;
};

class Ground : public Abs_Entity {


public:

	explicit Ground(GLdouble w, GLdouble h);

	~Ground();

	virtual void render(glm::dmat4 const& modelViewMat) const;

};

class BoxOutline : public Abs_Entity {


public:

	explicit BoxOutline(GLdouble lenght);

	~BoxOutline();

	virtual void render(glm::dmat4 const& modelViewMat) const;

protected:

	Texture* mTexture2;

};

class Star3D : public Abs_Entity {


public:

	explicit Star3D(GLdouble re, GLuint np, GLdouble h);

	~Star3D();

	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

private:

	GLdouble angleY = 0.0;

	GLdouble angleZ = 0.0;

};

class Box : public Abs_Entity {


public:

	explicit Box(GLdouble lenght);

	~Box();

	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

protected:

	Texture* mTexture2;

	Mesh* mMeshTapa = nullptr;

	Mesh* mMeshFondo = nullptr;

	GLdouble lenghtCube = 0.0;

	GLdouble angle = 0.0;

	bool opening = true;

};

#endif //_H_Entities_H_
