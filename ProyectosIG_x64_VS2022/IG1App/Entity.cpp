#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Abs_Entity::upload(dmat4 const& modelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat)); // transfers modelView matrix to the GPU
}

void 
Abs_Entity::update() {

}

EjesRGB::EjesRGB(GLdouble l)
  : Abs_Entity()
{
	mMesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB()
{
	delete mMesh;
	mMesh = nullptr;
};

void
EjesRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

PoligonoRegular::PoligonoRegular(GLuint num, GLdouble r)
	: Abs_Entity()
{
	mMesh = Mesh::generateRegularPolygon(num, r);
}

PoligonoRegular::~PoligonoRegular()
{
	delete mMesh;
	mMesh = nullptr;
};

void
PoligonoRegular::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		glClearColor(0.6, 0.7, 0.8, 1.0);
	}
}

RBGTriangle::RBGTriangle(GLdouble r, glm::dvec3 v, GLdouble otherRotVecX)
	: Abs_Entity(), myV(v), rotVelX(otherRotVecX)
{
	mMesh = Mesh::generateRegularPolygonMultiColor(3, r);
}

RBGTriangle::~RBGTriangle()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RBGTriangle::render(dmat4 const& modelViewMat) const
{

	glPolygonMode(GL_FRONT, GL_FILL);

	glPolygonMode(GL_BACK, GL_LINE);

	if (mMesh != nullptr) {

		dmat4 aMat =  modelViewMat * rotate(dmat4(1), radians(angleX), dvec3(0, 0, 1)) * translate(mModelMat, myV) * rotate(dmat4(1), radians(- angleX * 2), dvec3(0, 0, 1)); // glm matrix multiplication
		upload(aMat);

		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void
RBGTriangle::update() {

	angleX += rotVelX;

}

RGBRectangle::RGBRectangle(GLuint w, GLuint h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}

RGBRectangle::~RGBRectangle()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RGBRectangle::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT, GL_LINE);

		glPolygonMode(GL_BACK, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

Cube::Cube(GLdouble length, GLdouble rV)
	: Abs_Entity(), rotVelX(rV)
{
	mMesh = Mesh::generateCube(length);
}

Cube::~Cube()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Cube::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);


		mMesh->render();

		
		glLineWidth(1);
	}
}

void
Cube::update() {

	switch (rotState)
	{

		case 0:
			angleX += rotVelX;

			break;

		case 1:

			angleY += rotVelX;

			break;

		case 2:

			angleZ += rotVelX;

		default:
			break;
	}
	angleX += rotVelX;

}



