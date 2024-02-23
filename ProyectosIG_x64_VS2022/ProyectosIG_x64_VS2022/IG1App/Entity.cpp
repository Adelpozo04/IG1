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

TriangleRGB::TriangleRGB( GLdouble r,dvec3 v,GLdouble rotVelX)
	: Abs_Entity(),vectorTranslate(v),rotVelX(rotVelX)
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
		//glEnable(GL_CULL_FACE);

		//glCullFace(GL_BACK);

		//alternativa a cull faces	
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		

		dmat4 aMat = modelViewMat * 
						rotate(dmat4(1), radians(-angleX), dvec3(0, 0, 1)) * 
						translate(mModelMat,vectorTranslate) * 
						rotate(dmat4(1), radians(angleX*3), dvec3(0, 0, 1)); // glm matrix multiplication
		upload(aMat);

		mMesh->changePrimitive(GL_TRIANGLES);

		//set config
		glLineWidth(2);

		mMesh->render();
		//reset config
		glLineWidth(1);



		//reset
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/*
		glCullFace(GL_FRONT);

		mMesh->changePrimitive(GL_LINE_LOOP);

		//set config
		glLineWidth(2);

		mMesh->render();
		//reset config
		glLineWidth(1);

		glDisable(GL_CULL_FACE);
		*/

	}
}

void TriangleRGB::update()
{
	angleX -= rotVelX;
}



#pragma endregion


#pragma region Rectangle

Rectangle_cls::Rectangle_cls(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRectangle(w, h);
}

Rectangle_cls::~Rectangle_cls()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Rectangle_cls::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		//set config
		glLineWidth(2);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		mMesh->render();

		//reset config
		glColor4d(0.0, 0.0, 0.0, 1.0);
		glLineWidth(1);
	}
}




#pragma endregion

#pragma region Rentangle RGB


Rectangle_RGB::Rectangle_RGB(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}

Rectangle_RGB::~Rectangle_RGB()
{
	delete mMesh;
	mMesh = nullptr;
};

void
Rectangle_RGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_FILL);
		//set config
		glLineWidth(2);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		mMesh->render();

		//reset config
		glColor4d(0.0, 0.0, 0.0, 1.0);
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}




#pragma endregion


#pragma region Cube



Cube::Cube(GLdouble w,bool center,GLdouble rotVel) : vectorTranslate(dvec3(0,0,0)) , rotVel(rotVel)
{
	mMesh = Mesh::generateCube(w);
	if (!center) {
		vectorTranslate = dvec3(w , w , -w );
	}
	
	_angles.push_back(GLdouble(0.0));
	_angles.push_back(GLdouble(0.0));
	_angles.push_back(GLdouble(0.0));
}

Cube::~Cube()
{
	delete mMesh;
	mMesh = nullptr;
}

void Cube::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat* 
					rotate(dmat4(1), radians(_angles[2]), dvec3(0, 1, 0)) * 
					rotate(dmat4(1), radians(_angles[1]), dvec3(0, 0, 1)) * 
					rotate(dmat4(1), radians(_angles[0]), dvec3(1, 0, 0)) * 
					translate(mModelMat, vectorTranslate); // glm matrix multiplication			
		
		upload(aMat);

		//set config
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);
		glLineWidth(2);

		mMesh->render();

		//reset config
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Cube::update() {

	_angles[state] += rotVel;
	if (_angles[state] >= 180) {
		state = (state+1)%3;
		if (state == 0) {
			_angles[0] = (int)(_angles[0] + 180) % 360;
			_angles[1] = (int)(_angles[1] + 180) % 360;
			_angles[2] = (int)(_angles[2] + 180) % 360;		
		}
	}	
}

#pragma endregion


#pragma region Ground


Ground::Ground(GLdouble w,GLdouble h)
{
	mModelMat = dmat4(1);
	mMesh = Mesh::generateRectangleTexCor(w, h);
	
	mTexture = new Texture();
	mTexture->load("Bmps/papelE.bmp");

}

Ground::~Ground()
{

}


void Ground::render(glm::dmat4 const& modelViewMat) const
{

	if(mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat * 
						rotate(dmat4(1), radians(90.0), glm::dvec3(1, 0, 0)); // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);


		mTexture->bind(GL_REPLACE);

		mMesh->render();

		mTexture->unbind();

		//reset config
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}





#pragma endregion