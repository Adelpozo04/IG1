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

#pragma region EjesRGB


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

#pragma endregion

#pragma region RegularPolygon


RegularPolygon::RegularPolygon(GLuint v, GLdouble r)
	: Abs_Entity()
{
	mMesh = Mesh::generateRegularPolygon(v,r);
}

RegularPolygon::~RegularPolygon()
{
	delete mMesh;
	mMesh = nullptr;
};

void
RegularPolygon::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		
		//set config
		glLineWidth(2);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		mMesh->render();

		//reset config
		glColor4d(0.0,0.0,0.0 ,1.0);
		glLineWidth(1);
	}
}

#pragma endregion

#pragma region TriangleRGB

TriangleRGB::TriangleRGB( GLdouble r)
	: Abs_Entity()
{
	mMesh = Mesh::generateTriangleRGB(r);
}

TriangleRGB::~TriangleRGB()
{
	delete mMesh;
	mMesh = nullptr;
};

void
TriangleRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);

		glCullFace(GL_BACK);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		mMesh->changePrimitive(GL_TRIANGLES);

		//set config
		glLineWidth(2);

		mMesh->render();
		//reset config
		glLineWidth(1);


		glCullFace(GL_FRONT);

		mMesh->changePrimitive(GL_LINE_LOOP);

		//set config
		glLineWidth(2);

		mMesh->render();
		//reset config
		glLineWidth(1);

		glDisable(GL_CULL_FACE);

	}
}



#pragma endregion
