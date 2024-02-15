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

RBGTriangle::RBGTriangle(GLdouble r)
	: Abs_Entity()
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
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
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
		glPolygonMode(GL_BACK, GL_FILL);

		glPolygonMode(GL_FRONT, GL_LINE);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

Cube::Cube(GLdouble length)
	: Abs_Entity()
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
		glPolygonMode(GL_BACK, GL_LINE);

		glPolygonMode(GL_FRONT, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);


		mMesh->render();

		
		glLineWidth(1);
	}
}
