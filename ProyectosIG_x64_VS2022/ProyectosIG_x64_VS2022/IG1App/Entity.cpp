#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


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
	//mMesh = Mesh::generateRectangleTexCor(w, h);
	mMesh = Mesh::generaRectangleTexCor(w, h, 4, 4);
	mTexture = new Texture();
	mTexture->load("Bmps/baldosaC.bmp");

}

Ground::~Ground()
{
	delete mMesh;
	mMesh = nullptr;
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


		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_REPLACE);
	

		mMesh->render();

		mTexture->unbind();

		//reset config
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}





#pragma endregion

#pragma region BoxOutLine


BoxOutLine::BoxOutLine(GLdouble w)
{
	mModelMat = dmat4(1);
	mMesh = Mesh::generateBoxOutlineTexCor(w);

	mTexture = new Texture();

	//IMPORTANTE, BORRAR MEMORIA DE LAS TEXTURE

	//mTexture actua como frontTexture
	mTexture = new Texture();
	mTexture->load("Bmps/container.bmp");

	mBackTexture = new Texture();
	mBackTexture->load("Bmps/papelE.bmp");

}



BoxOutLine::~BoxOutLine()
{
	delete mMesh;
	mMesh = nullptr;
}

void BoxOutLine::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {
		//modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);
		//enable face culling 
		glEnable(GL_CULL_FACE);

		//cull back face
		glCullFace(GL_BACK);


		//bind front texture
		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_MODULATE);


		//matriz del modelo principal
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		//render main mesh(front)
		mMesh->render();

		//unbind front texture
		mTexture->unbind();
		//bind backTexture
		mBackTexture->bind(GL_MODULATE);
		//culling front face
		glCullFace(GL_FRONT);

		mMesh->render();


		//unbing back texture
		mBackTexture->unbind();


		//disableFaceCulling
		glDisable(GL_CULL_FACE);
		//reset config
		glLineWidth(1);
		//reset modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
}


#pragma endregion

#pragma region Box


Box::Box(GLdouble w,GLdouble topVel, glm::dvec3 OffSetVec):topVel(topVel)
{

	mModelMat = dmat4(1);
	mMesh = Mesh::generateBoxOutlineTexCor(w);
	topMesh = Mesh::generateRectangleTexCor(w*2, w*2);
	botomMesh = Mesh::generateRectangleTexCor(w*2, w*2);

	//IMPORTANTE, BORRAR MEMORIA DE LAS TEXTURE

	//mTexture actua como frontTexture
	mTexture = new Texture();
	mTexture->load("Bmps/container.bmp");

	mBackTexture = new Texture();
	mBackTexture->load("Bmps/papelE.bmp");

	translationVecY = dvec3(0, w, 0);
	translationVecX = dvec3(w, 0, 0);

	translationOffSet = OffSetVec;

	topAngle = 0;
}

Box::~Box()
{
	delete mMesh;
	delete topMesh;
	delete botomMesh;
	mMesh = nullptr;
	topMesh = nullptr;
	botomMesh = nullptr;
}

void Box::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		//modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);
		//enable face culling 
		glEnable(GL_CULL_FACE);

		//cull back face
		glCullFace(GL_BACK);


		//bind front texture
		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_REPLACE);

		renderBottomMesh(modelViewMat);
		renderMainMesh(modelViewMat);
		renderTopMesh(modelViewMat);

		//unbind front texture
		mTexture->unbind();
		//bind backTexture
		mBackTexture->bind(GL_REPLACE);
		//culling front face
		glCullFace(GL_FRONT);


		renderBottomMesh(modelViewMat);
		renderMainMesh(modelViewMat);
		renderTopMesh(modelViewMat);


		//unbing back texture
		mBackTexture->unbind();


		//disableFaceCulling
		glDisable(GL_CULL_FACE);
		//reset config
		glLineWidth(1);
		//reset modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


void Box::renderMainMesh(glm::dmat4 const& modelViewMat)const {
	//matriz del modelo principal
	dmat4 aMat = modelViewMat *translate(mModelMat,translationOffSet) * mModelMat; // glm matrix multiplication
	upload(aMat);
	//render main mesh(front)
	mMesh->render();
}
void Box::renderBottomMesh(glm::dmat4 const& modelViewMat)const {
	//upload de la matriz del botomMesh
	dmat4 aMat = modelViewMat * translate(mModelMat, translationOffSet) * translate(mModelMat, -translationVecY) * rotate(dmat4(1), radians(90.0), dvec3(1, 0, 0)); // glm matrix multiplication
	upload(aMat);
	//render del botom mesh
	botomMesh->render();
}
void Box::renderTopMesh(glm::dmat4 const& modelViewMat)const {
	//upload matriz del top mesh
	dmat4 aMat = modelViewMat * translate(mModelMat, translationOffSet) * translate(mModelMat, translationVecY) *
		translate(mModelMat, translationVecX)*
		rotate(mModelMat,radians(-topAngle),dvec3(0,0,1))*
		translate(mModelMat, -translationVecX)*
		rotate(mModelMat, radians(-90.0), dvec3(1, 0, 0)); // glm matrix multiplication

	upload(aMat);
	//render del top mesh
	topMesh->render();

}

void Box::update() {
	if (state == 0) {
		topAngle += topVel;
		if (topAngle >= 180) state = 1;
	}
	else if (state == 1) {
		topAngle -= topVel;
		if (topAngle <= 0) state = 0;
	}
}
#pragma endregion

#pragma region Star3D

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, GLdouble yVel, GLdouble zVel, glm::dvec3 traslationVec ) 
	:YRotVel(yVel),zRotVel(zVel), traslationVec(traslationVec)
{
	mMesh = Mesh::generateStar3DTexCor(re, np, h);

	mTexture = new Texture();
	mTexture->load("Bmps/baldosaP.bmp");

	yAngle = 0;
	zAngle = 0;
}

Star3D::~Star3D()
{
	delete mMesh;
	mMesh = nullptr;
}

void Star3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat* translate(mModelMat,traslationVec) * rotate(dmat4(1), radians(yAngle), dvec3(0, 1, 0)) * mModelMat *
						rotate(dmat4(1),radians(zAngle),dvec3(0,0,1) ); // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_REPLACE);

		mMesh->render();

		aMat = rotate(aMat,radians(180.0),dvec3(0,1,0));

		upload(aMat);
		mMesh->render();


		mTexture->unbind();
		//reset config
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Star3D::update()
{
	zAngle += zRotVel;
	yAngle += YRotVel;
}

#pragma endregion


#pragma region GlassParapet



GlassParapet::GlassParapet(GLdouble longitud)
{	
	mModelMat = dmat4(1);
	mMesh = Mesh::generateBoxOutlineTexCorTransparent(longitud);

	mTexture = new Texture();
	mTexture->load("Bmps/windowV.bmp");

}

GlassParapet::~GlassParapet()
{
	
	delete mMesh;
	mMesh = nullptr;
	
}

void GlassParapet::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {
		
		//modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat;

		upload(aMat);
		//bind front texture
		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_MODULATE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mMesh->render();

		mTexture->unbind();


		//reset config
		glLineWidth(1);
		//reset modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	

	}
}

#pragma endregion


#pragma region Grass


Grass::Grass(GLdouble w, GLdouble h, glm::dvec3 traslationVec )
	:traslationVec(traslationVec)
{
	mModelMat = dmat4(1);
	mMesh = Mesh::generaRectangleTexCor(w,h,1,1);

	mTexture = new Texture();
	mTexture->load("Bmps/grass.bmp",glm::u8vec3(0,0,0),0);
}

Grass::~Grass()
{

	delete mMesh;
	mMesh = nullptr;
}

void Grass::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {
		//set depth buffer
		//glDisable(GL_DEPTH_TEST);
		//glEnable(GL_DEPTH);


		glEnable(GL_ALPHA_TEST);

		glAlphaFunc(GL_GREATER, 0);
		//modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		//bind front texture
		//mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_REPLACE);//sino,no funciona con las 2 camaras
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		dmat4 aMat = modelViewMat*translate(mModelMat,traslationVec) * mModelMat * rotate(dmat4(1), radians(-90.0), dvec3(0, 0, 1));
		upload(aMat);
		mMesh->render();

		dmat4 aMat2 = modelViewMat * translate(mModelMat, traslationVec) * mModelMat * rotate(dmat4(1), radians(-120.0), dvec3(0, 1, 0)) * rotate(dmat4(1), radians(-90.0), dvec3(0, 0, 1));
		upload(aMat2);
		mMesh->render();

		dmat4 aMat3 = modelViewMat * translate(mModelMat, traslationVec) * mModelMat * rotate(dmat4(1), radians(120.0), dvec3(0, 1, 0)) * rotate(dmat4(1), radians(-90.0), dvec3(0, 0, 1));
		upload(aMat3);
		mMesh->render();

		mTexture->unbind();


		glBlendFunc(GL_ONE, GL_ZERO);
		//reset config
		glLineWidth(1);
		//reset modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		glDisable(GL_ALPHA_TEST);
		//glDisable(GL_DEPTH);
		//glEnable(GL_DEPTH_TEST);

	}
}


#pragma endregion

#pragma region Photo


//foto dinamica apartado 37
Photo::Photo(GLdouble w, GLdouble h)
{
	mModelMat = dmat4(1);
	mMesh = Mesh::generaRectangleTexCor(w, h, 1, 1);

	mTexture = new Texture();
	mTexture->loadColorBuffer(800, 600);

}

Photo::~Photo()
{

	delete mMesh;
	mMesh = nullptr;
}

void Photo::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {
		//modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		//bind front texture
		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_REPLACE);
		
		dmat4 aMat = modelViewMat * translate(dmat4(1),dvec3(0,0.1,0)) * mModelMat * rotate(dmat4(1), radians(-90.0), dvec3(0, 1, 0)) * rotate(dmat4(1), radians(90.0), dvec3(1, 0, 0));
		upload(aMat);
		mMesh->render();

		mTexture->unbind();

		//reset config
		glLineWidth(1);
		//reset modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}


void Photo::update() {
	mTexture->loadColorBuffer(800, 600);
}
#pragma endregion


#pragma region Rectangle Photo


//foto estatica, clase auxiliar
RectanglePhoto::RectanglePhoto(GLdouble w, GLdouble h, glm::dvec3 traslationVec)
	:traslationVec(traslationVec)
{
	mModelMat = dmat4(1);
	mMesh = Mesh::generaRectangleTexCor(w, h, 1, 1);

	mTexture = new Texture();
	mTexture->load("Bmps/photo.bmp");

}

RectanglePhoto::~RectanglePhoto()
{

	delete mMesh;
	mMesh = nullptr;
}

void RectanglePhoto::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {
		//modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		//bind front texture
		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_REPLACE);

		dmat4 aMat = modelViewMat*translate(mModelMat,traslationVec) * mModelMat * rotate(dmat4(1), radians(90.0), dvec3(1, 0, 0));
		upload(aMat);
		mMesh->render();

		mTexture->unbind();

		//reset config
		glLineWidth(1);
		//reset modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}



#pragma endregion


#pragma region QuadricEntities

Sphere::Sphere(GLdouble r) :
	r(r) {};




void Sphere::render(glm::dmat4 const& modelViewMat) const {
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Set color
	glEnable ( GL_COLOR_MATERIAL );
	glColor3f (red,green,blue);
	//set draw mode 
	gluQuadricDrawStyle (q, GLU_FILL);
	//creacion de la entidad quadrica
	gluSphere(q, r, 50, 50);
	// reset color
	glColor3f (1.0 , 1.0 , 1.0);
}


Cylinder::Cylinder(GLdouble baseR, GLdouble topR, GLdouble height)
	:baseRadio(baseR), topRadio(topR), height(height)
{}

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Set color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);

	//set draw mode 
	gluQuadricDrawStyle(q, GLU_FILL);
	//creacion de la entidad quadrica
	gluCylinder(q,baseRadio,topRadio,height, 50, 50);
	// reset color
	glColor3f(1.0, 1.0, 1.0);
}

Disk::Disk(GLdouble innerRadio, GLdouble outerRadio)
	:innerRadio(innerRadio),outerRadio(outerRadio)
{}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// set color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);

	//set draw mode
	gluQuadricDrawStyle(q, GLU_FILL);
	//creacion de la entidad quadrica
	gluDisk(q, innerRadio, outerRadio, 50, 50);
	// reset color
	glColor3f(1.0, 1.0, 1.0);
}


PartialDisk::PartialDisk(GLdouble innerRadio, GLdouble outerRadio, GLdouble startAngle, GLdouble sweepAngle)
	:innerRadio(innerRadio), outerRadio(outerRadio), startAngle(startAngle), sweepAngle(sweepAngle)
{
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// set color
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(red, green, blue);

	// set draw mode
	gluQuadricDrawStyle(q, GLU_FILL);

	//creacion de la entidad cuadrica
	gluPartialDisk(q, innerRadio, outerRadio, 50, 50,startAngle,sweepAngle);
	// reset color
	glColor3f(1.0, 1.0, 1.0);
}

#pragma endregion


#pragma region Compound Entity

CompoundEntity::CompoundEntity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (auto& e : gObjects) {
		delete e;
	}

	gObjects.clear();
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;

	for (auto& e : gObjects) {
		//upload(aMat);
		e->render(aMat);
	}
}

void CompoundEntity::update()
{
	for (auto& e : gObjects) e->update();
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}

#pragma endregion


#pragma region Advanced_TIE_X1
Advanced_TIE_X1::Advanced_TIE_X1()
{
	auto sphere = new Sphere(130);
	sphere->setColor(0,65/255.0,106/255.0);
	addEntity(sphere);

	
	auto eje = new Cylinder(20, 20, 440);
	dmat4 ejePos = translate(dmat4(1), dvec3(0, 0, -220)) ;
	eje->setModelMat(ejePos);
	eje->setColor(0, 65 / 255.0, 106 / 255.0);
	addEntity(eje);

	auto morro = new Advanced_TIE_X1_Morro();
	dmat4 morroPos = translate(dmat4(1), dvec3(0, 0, 0));
	morro->setModelMat(morroPos);
	addEntity(morro);
	

	auto leftWing = new WingAdvancedTIE();
	dmat4 leftWingPos = translate(dmat4(1), dvec3(0, 0, 85));
	leftWing->setModelMat(leftWingPos);
	addEntity(leftWing);

	auto rightWing = new WingAdvancedTIE();
	dmat4 rightWingPos = translate(dmat4(1), dvec3(0, 0, -85)) * rotate(dmat4(1),radians(180.0),dvec3(0,1,0));
	rightWing->setModelMat(rightWingPos);
	addEntity(rightWing);
	
}

Advanced_TIE_X1::~Advanced_TIE_X1()
{
}


#pragma endregion

#pragma region Advanced_TIE_X1_Morro

Advanced_TIE_X1_Morro::Advanced_TIE_X1_Morro()
{
	auto eje = new Cylinder(80, 80, 280);
	dmat4 ejePos = translate(dmat4(1), dvec3(-140, 0, 0)) * rotate(dmat4(1), radians(90.0), dvec3(0, 1, 0));
	eje->setModelMat(ejePos);
	eje->setColor(0, 65 / 255.0, 106 / 255.0);
	addEntity(eje);


	auto disk = new Disk(0, 80);
	dmat4 diskPos = translate(dmat4(1), dvec3(140, 0, 0)) * rotate(dmat4(1), radians(90.0), dvec3(0, 1, 0));
	disk->setModelMat(diskPos);
	disk->setColor(0, 65 / 255.0, 106 / 255.0);
	gObjects.push_back(disk);

}

Advanced_TIE_X1_Morro::~Advanced_TIE_X1_Morro()
{
}

#pragma endregion

#pragma region WingAdvancedTIE

WingAdvancedTIE::WingAdvancedTIE()
{
	mModelMat = dmat4(1);
	mMesh = Mesh::generateWingAdvancedTIE(150, 200);

	mTexture = new Texture();
	mTexture->load("Bmps/noche.bmp");
}

WingAdvancedTIE::~WingAdvancedTIE()
{
}

void WingAdvancedTIE::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		//modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		dmat4 aMat = modelViewMat * mModelMat;

		upload(aMat);
		//bind front texture
		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_MODULATE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mMesh->render();

		mTexture->unbind();


		//reset config
		glLineWidth(1);
		//reset modo de pintado
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

}
#pragma endregion

Cubo::Cubo(GLdouble w)
{
	mMesh = new IndexMesh();
	mMesh = IndexMesh::generateIndexedBox(w);
}

Cubo::~Cubo()
{
	delete mMesh;
	mMesh = nullptr;
}

void Cubo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat ; // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		//set color
		if (mColor.a != 0) {
			glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
		}

		mMesh->render();

		glColor4f(0,0,0,0);

		//reset config
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Cubo::update()
{
}

Sphere_mbr::Sphere_mbr(GLdouble radius, GLint pPunto, GLint meridianos)
{
	glm::dvec3* aux = new glm::dvec3[pPunto];

	double angle = 180.0 / (pPunto-1);

	for (int i = 0; i < pPunto; i++) {
		aux[i] = glm::dvec3(cos(radians(angle*i - 90)) * radius , sin(radians(angle * i -90)) * radius,0);
	}
	

	mMesh = MbR::generaIndexMbR(pPunto,meridianos,aux);
}

void Sphere_mbr::render(glm::dmat4 const& modelViewMat) const
{

	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		//set color
		if (mColor.a != 0) {
			glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
		}

		if (material != nullptr) {
			glColor3f(mColor.r, mColor.g, mColor.b);

			material->upload();
		}

		mMesh->render();

	

		glColor3f(1.0, 1.0, 1.0);

		glColor4f(0, 0, 0, 0);

		//reset config
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//reset del color material
		glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT);
		glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);

	}
}

//grosor es el radio del grosor
Toroid::Toroid(GLdouble grosor, GLdouble radius, GLint m, GLint p)
{
	dvec3* aux = new dvec3[p];

	double angle = 360.0 / (p - 1);

	for (int i = 0; i < p; i++) {         
		aux[i] = dvec3((radius +(grosor))+ (cos(radians(angle * i - 90)) * grosor), sin(radians(angle * i - 90)) * grosor, 0);
	}

	mMesh = MbR::generaIndexMbR(p, m, aux);
}

void Toroid::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//set config
		glLineWidth(2);

		//set color
		if (mColor.a != 0) {
			glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
		}

		mMesh->render();

		glColor4f(0, 0, 0, 0);

		//reset config
		glLineWidth(1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
