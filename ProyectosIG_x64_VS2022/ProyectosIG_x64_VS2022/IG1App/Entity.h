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

	void setTexture(Texture* newTexture) { mTexture = newTexture; }

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix

	glm::dvec4 mColor; //colors

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

class BoxOutLine : public Abs_Entity {

protected:
	Texture* mBackTexture;

public:
	explicit BoxOutLine(GLdouble w);
	~BoxOutLine();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

class Box  : public Abs_Entity {

protected:
	Texture* mBackTexture;

	Mesh* botomMesh;
	Mesh* topMesh;

	glm::dvec3 translationVecY;
	glm::dvec3 translationVecX;

	glm::dvec3 translationOffSet;

	GLdouble topVel;
	GLdouble topAngle;

	int state = 0;

public:
	explicit Box(GLdouble w,GLdouble topVel, glm::dvec3 OffSetVec);
	~Box();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

private:

	void renderMainMesh(glm::dmat4 const& modelViewMat) const;
	void renderBottomMesh(glm::dmat4 const& modelViewMat) const;
	void renderTopMesh(glm::dmat4 const& modelViewMat) const;

};

class Star3D : public Abs_Entity {
	GLdouble zAngle;
	GLdouble yAngle;
	GLdouble zRotVel;
	GLdouble YRotVel;

	glm::dvec3 traslationVec;

public:
	explicit Star3D(GLdouble re, GLuint np, GLdouble h,GLdouble yVel,GLdouble zVel, glm::dvec3 traslationVec = glm::dvec3(0,0,0));
	~Star3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;
};


class GlassParapet : public Abs_Entity {


public:

	explicit GlassParapet(GLdouble longitud);
	~GlassParapet();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};


class Grass : public Abs_Entity {

	glm::dvec3 traslationVec;
public:

	explicit Grass(GLdouble w,GLdouble h, glm::dvec3 traslationVec = glm::dvec3(0, 0, 0));
	~Grass();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

class Photo : public Abs_Entity {


public:

	explicit Photo(GLdouble w, GLdouble h);
	~Photo();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

};

class RectanglePhoto : public Abs_Entity {

	glm::dvec3 traslationVec;


public:

	explicit RectanglePhoto(GLdouble w, GLdouble h, glm::dvec3 traslationVec = glm::dvec3(0, 0, 0));
	~RectanglePhoto();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class QuadricEntity : public Abs_Entity {

	public:
		QuadricEntity() {

			q = gluNewQuadric();

		}

		~QuadricEntity() { gluDeleteQuadric(q); };
	protected:
		GLUquadricObj* q;

		glm::dvec3 colorVec_;

};


class Sphere : public QuadricEntity {
public:

	Sphere(GLdouble r, glm::dvec3 colorVec); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;

protected:

	GLdouble r;

};


class Cylinder : public QuadricEntity {
public:

	Cylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble height, glm::dvec3 colorVec); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;

protected:

	GLdouble baseRadius_;

	GLdouble topRadius_;

	GLdouble height_;

};

class Disk : public QuadricEntity {
public:

	Disk(GLdouble innerRadius, GLdouble outerRadius, glm::dvec3 colorVec); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;

protected:

	GLdouble innerRadius_;

	GLdouble outerRadius_;

};

class PartialDisk: public QuadricEntity {
public:

	PartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle, glm::dvec3 colorVec); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;

protected:

	GLdouble innerRadius_;

	GLdouble outerRadius_;

	GLdouble startAngle_;

	GLdouble sweepAngle_;


};



#endif //_H_Entities_H_
