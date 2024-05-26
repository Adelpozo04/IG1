#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"

#include "Ilumination.h"

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

	void setBackTexture(Texture* texture) { mBackTexture = texture; }

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

	void setBackTexture(Texture* texture) { mBackTexture = texture; }


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


#pragma region Entidades cuadricas

class QuadricEntity : public Abs_Entity {
public:
	QuadricEntity() {
		q = gluNewQuadric();
		red = green = blue = 0;
	};
	~QuadricEntity() { gluDeleteQuadric(q); };

	void setColor(GLdouble _red, GLdouble _green, GLdouble _blue) {
		red = _red;
		green = _green;
		blue = _blue;
	}

protected:
	GLUquadricObj* q;

	
	GLdouble red;
	GLdouble green;
	GLdouble blue;
};

class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;

	
protected:
	GLdouble r;

	
};

class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble baseR, GLdouble topR,GLdouble height); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble baseRadio;
	GLdouble topRadio;
	GLdouble height;
};

class Disk : public QuadricEntity {
public:

	Disk(GLdouble innerRadio, GLdouble outerRadio); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadio;
	GLdouble outerRadio;
};

class PartialDisk : public QuadricEntity {
public:

	PartialDisk(GLdouble innerRadio, GLdouble outerRadio,
				GLdouble startAngle,GLdouble sweepAngle); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble innerRadio;
	GLdouble outerRadio;
	GLdouble startAngle;
	GLdouble sweepAngle;

};
	
#pragma endregion


#pragma region Entidades compuestas

class CompoundEntity : public Abs_Entity {
	
protected:
	std::vector<Abs_Entity*> gObjects;

public:

	explicit CompoundEntity();
	~CompoundEntity();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

	void addEntity(Abs_Entity* ae);


};

class Advanced_TIE_X1 : public CompoundEntity {
public:
	explicit Advanced_TIE_X1();
	~Advanced_TIE_X1();
};

class Advanced_TIE_X1_Morro : public CompoundEntity {
public:
	explicit Advanced_TIE_X1_Morro();
	~Advanced_TIE_X1_Morro();
};

class WingAdvancedTIE : public Abs_Entity {
public:
	explicit WingAdvancedTIE();
	~WingAdvancedTIE();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

#pragma endregion


#pragma region Cubo con normales

class Cubo 
	: public Abs_Entity {

public:

	explicit Cubo(GLdouble w);
	~Cubo();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update() override;

private:



};

#pragma endregion


class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};


#pragma region Objetos con mallas de revolucion

class Sphere_mbr : public EntityWithMaterial {

public:
	Sphere_mbr(GLdouble radius,GLint pPunto, GLint meridianos); // r es el radio de la esfera
	//~Sphere_mbr();
	
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

class Toroid : public Abs_Entity {

public:
	Toroid(GLdouble grosor,GLdouble radius, GLint m, GLint p); // r es el radio de la esfera
	//~Toroid();

	virtual void render(glm::dmat4 const& modelViewMat) const;


};

#pragma endregion



class Piramid : public Abs_Entity {
public:


	explicit Piramid();
	//~Piramid();
	virtual void render(glm::dmat4 const& modelViewMat) const;

};



class PiramidText : public EntityWithMaterial {
public:


	explicit PiramidText(GLdouble width ,GLdouble height);
	virtual void render(glm::dmat4 const& modelViewMat) const;

};

class TriagonalPrismText : public Abs_Entity {
public:


	explicit TriagonalPrismText(GLdouble width, GLdouble height,GLdouble depth);
	virtual void render(glm::dmat4 const& modelViewMat) const;

};


class PiramidTextComplex : public CompoundEntity {
public:

	explicit PiramidTextComplex(GLdouble width, GLdouble height, std::vector<Texture*> textures);

};



#endif //_H_Entities_H_
