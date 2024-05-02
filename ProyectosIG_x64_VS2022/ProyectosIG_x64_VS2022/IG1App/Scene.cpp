#include "Scene.h"
#include "CheckML.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights

	dirLight = new DirLight(GL_LIGHT0);

	glm::fvec4 posDir = { 1, 1, 1, 0 };

	dirLight->setPosDir(posDir);

	posLight = new PosLight(GL_LIGHT1);

	posLight->setPosDir({ 100, 300, 0 });

	posLight->setDiff({ 1.0, 1.0, 0.0, 1.0 });

	spotLight = new SpotLight(GL_LIGHT2);

	spotLight->setPosDir({ 0, 310, 0 });

	spotLight->setDiff({ 1.0, 1.0, 0.0, 1.0 });

	spotLight->setSpot({ 0, -1, 0 }, 180, 0);

	

	// 
	// Textures

	// Graphics objects (entities) of the scene

	//ejes
	//gObjects.push_back(new EjesRGB(400.0));
	
	//triangulo cian
	//gObjects.push_back(new RegularPolygon(3,100));
	//gObjects[1]->setColor(dvec4(0.0, 1.0, 1.0, 1.0));

	//circunferencia magenta
	//gObjects.push_back(new RegularPolygon(50,100));
	//gObjects[2]->setColor(dvec4(1.0, 0.0, 1.0, 1.0));

	//triangulo RGB
	//gObjects.push_back(new TriangleRGB(150));

	//rectangulo
	//gObjects.push_back(new Rectangle_RGB(100, 200));

	//cubo
	//gObjects.push_back(new Cube(100));

	//setScene(1);

	
}
void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}

	gObjects.resize(0);
}
void
Scene::setGL()
{
	// OpenGL basic setting

	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	
	
	glEnable(GL_DEPTH_TEST);          // enable Depth test
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);	
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
}

void
Scene::render(Camera const& cam) const
{
	dirLight->upload(cam.viewMat());

	posLight->upload(cam.viewMat());

	spotLight->upload(cam.viewMat());

	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}
	
}

void Scene::update()
{
	for (auto& o : gObjects) {
		o->update();

		if (mId = 66) {

			glm::dmat4 aux = inventedNode1_->modelMat();

			inventedNode1_->setModelMat(rotate(aux,
				radians(3.0), { 0.0, 0.0, 1.0 }));

			aux = inventedNode2_->modelMat();

			inventedNode2_->setModelMat(rotate(aux,
				radians(3.0), { 0.0, 0.0, 1.0 }));

		}
	}
}

void Scene::rotated() {


	if (mId = 67) {

		inventedNode1_->setModelMat(glm::rotate(inventedNode1_->modelMat(),
			radians(2.0), dvec3(0, 1, 0)));

		angle = (int)(angle + 2) % 360;
		
	}

}

void Scene::orbited() {

	if (mId = 67) {

		inventedNode2_->setModelMat(glm::rotate(inventedNode2_->modelMat(),
			radians(2.0), { -glm::sin(radians(angle)), 0.0, -glm::cos(radians(angle)) }));

	}

}

void Scene::setScene(GLuint id)
{
	free();

	mId = id;

	bool ejes = true;

	if (ejes) {
		gObjects.push_back(new EjesRGB(400.0));
	}


	if (mId == 0) {

		/*
		//circunferencia magenta
		gObjects.push_back(new RegularPolygon(50, 100));
		//gObjects[1]->setColor(glm::dvec4(0.71, 0.58, 0.75, 1.0));

		//triangulo RGB
		gObjects.push_back(new TriangleRGB(30, glm::dvec3(100, 0, 0),1.0));


		//rectangulo
		gObjects.push_back(new Rectangle_RGB(200, 100));
		*/
		
	}
	else if (mId == 1) {
		gObjects.push_back(new Cube(100,false,1.f));
	}
	else if (mId == 18) {
		gObjects.push_back(new Ground(200, 400));
	}
	else if (mId == 24) {
		gObjects.push_back(new BoxOutLine(100));
	}
	else if (mId == 29) {
		gObjects.push_back(new Box(100,1,dvec3(0,0,0)));
	}
	else if (mId == 26) {
		gObjects.push_back(new Star3D(100, 8, 80,1,2));
	}
	else if (mId == 31) {
		gObjects.push_back(new GlassParapet(100));

	}
	else if (mId == 34) {
		gObjects.push_back(new Grass(100,100));
	}
	else if(mId == 38) {
		

		gObjects.push_back(new Photo(100,100));
		gObjects.push_back(new Ground(400,400));
		gObjects.push_back(new Grass(100, 100, dvec3(160, 50, 160)));

		gObjects.push_back(new Box(35, 1, dvec3(-160, 35.1, -160)));
		gObjects.push_back(new Star3D(40, 8, 30, 1, 2, dvec3(-160, 165.1, -160)));
		gObjects.push_back(new RectanglePhoto(100,100,dvec3(150,0.1,-150)));
		gObjects.push_back(new GlassParapet(200));
	}
	else if (mId == 58) {


		Sphere* esfera = new Sphere(100, dvec3(1.0, 0.5, 0.0));

		gObjects.push_back(esfera);


		Cylinder* cilindro1 = new Cylinder(10, 0, 20, dvec3(0.0, 0.0, 1.0));

		glm::dmat4 mAux = cilindro1->modelMat();

		mAux = translate(mAux, dvec3(50, 50, 60));

		cilindro1->setModelMat(mAux);

		gObjects.push_back(cilindro1);


		Cylinder* cilindro2 = new Cylinder(10, 0, 20, dvec3(0.0, 0.0, 1.0));

		mAux = cilindro2->modelMat();

		mAux = translate(mAux, dvec3(-50, 50, 60));

		cilindro2->setModelMat(mAux);

		gObjects.push_back(cilindro2);


		PartialDisk* discoParcial = new PartialDisk(60, 80, 90, 180, dvec3(0.0, 1.0, 0.0));

		mAux = discoParcial->modelMat();

		mAux = translate(mAux, dvec3(0, 0, 80));

		discoParcial->setModelMat(mAux);

		gObjects.push_back(discoParcial);


		Disk* disco = new Disk(60, 100, dvec3(1.0, 0.0, 0.0));

		mAux = disco->modelMat();

		mAux = translate(mAux, dvec3(0, 80, 0));

		mAux = glm::rotate(mAux, radians(90.0), dvec3(1.0, 0.0, 0.0));

		disco->setModelMat(mAux);

		gObjects.push_back(disco);

	}
	else if (mId == 60) {

		CompoundEntity* nave = new CompoundEntity();

		
		Sphere* esfera = new Sphere(100, dvec3(0.0, 0.25, 0.42));

		nave->addEntity(esfera);


		Cylinder* cilindro0 = new Cylinder(20, 20, 80, dvec3(0.0, 0.25, 0.42));

		glm::dmat4 mAux = cilindro0->modelMat();

		mAux = translate(mAux, dvec3(0, 0, 80));

		cilindro0->setModelMat(mAux);

		nave->addEntity(cilindro0);


		Cylinder* cilindro1 = new Cylinder(20, 20, 80, dvec3(0.0, 0.25, 0.42));

		mAux = cilindro1->modelMat();

		mAux = glm::rotate(mAux, radians(180.0), dvec3(1.0, 0.0, 0.0));

		mAux = translate(mAux, dvec3(0, 0, 80));

		cilindro1->setModelMat(mAux);

		nave->addEntity(cilindro1);
		
		

		CompoundEntity* morro = new CompoundEntity();

		Cylinder* cilindro3 = new Cylinder(30, 30, 40, dvec3(0.0, 0.25, 0.42));


		Disk* disco = new Disk(0, 30, dvec3(0.0, 0.25, 0.42));

		mAux = disco->modelMat();

		mAux = translate(mAux, dvec3(0, 0, 0));

		disco->setModelMat(mAux);


		morro->addEntity(cilindro3);

		morro->addEntity(disco);


		mAux = morro->modelMat();

		mAux = translate(mAux, dvec3(120, 0, 0));

		mAux = glm::rotate(mAux, radians(270.0), dvec3(0.0, 1.0, 0.0));

		morro->setModelMat(mAux);


		nave->addEntity(morro);
		

		WingAdvancedTIE* wing = new WingAdvancedTIE(200, 200, 100);

		mAux = wing->modelMat();

		mAux = translate(mAux, dvec3(-100, 0, 160));

		wing->setModelMat(mAux);

		nave->addEntity(wing);


		WingAdvancedTIE* wing2 = new WingAdvancedTIE(200, 200, 100);

		mAux = wing2->modelMat();

		mAux = glm::rotate(mAux, radians(180.0), dvec3(0.0, 1.0, 0.0));

		mAux = translate(mAux, dvec3(-100, 0, 160));

		wing2->setModelMat(mAux);

		nave->addEntity(wing2);

		gObjects.push_back(nave);


		mAux = nave->modelMat();

		mAux = translate(mAux, dvec3(-100, 0, 0));

		nave->setModelMat(mAux);



	}
	else if (mId == 64) {

		IndexedBox* indBox = new IndexedBox(100);
		gObjects.push_back(indBox);
		indBox->setColor(dvec4(0.0, 1.0, 0.0, 1.0));
	}
	else if (mId == 66) {

		//circunferencia magenta
		gObjects.push_back(new RegularPolygon(50, 100));
		//gObjects[1]->setColor(glm::dvec4(0.71, 0.58, 0.75, 1.0));

		//rectangulo
		gObjects.push_back(new Rectangle_RGB(200, 100));

		CompoundEntity* inventedNode = new CompoundEntity();
		CompoundEntity* inventedNode2 = new CompoundEntity({0, 0, 1}, 5);
		TriangleRGB* tr = new TriangleRGB(30);
		inventedNode->addEntity(tr);
		inventedNode2->addEntity(inventedNode);

		glm::dmat4 mAux;

		mAux = inventedNode->modelMat();

		mAux = translate(mAux, dvec3(100, 0, 0));

		inventedNode->setModelMat(mAux);

		gObjects.push_back(inventedNode2);

		inventedNode1_ = inventedNode;

		inventedNode2_ = inventedNode2;


	}
	else if (mId == 67) {

		glClearColor(0.0, 0.0, 0.0, 1.0);

		CompoundEntity* nave = new CompoundEntity();


		Sphere* esfera = new Sphere(100, dvec3(0.0, 0.25, 0.42));

		nave->addEntity(esfera);


		Cylinder* cilindro0 = new Cylinder(20, 20, 80, dvec3(0.0, 0.25, 0.42));

		glm::dmat4 mAux = cilindro0->modelMat();

		mAux = translate(mAux, dvec3(0, 0, 80));

		cilindro0->setModelMat(mAux);

		nave->addEntity(cilindro0);


		Cylinder* cilindro1 = new Cylinder(20, 20, 80, dvec3(0.0, 0.25, 0.42));

		mAux = cilindro1->modelMat();

		mAux = glm::rotate(mAux, radians(180.0), dvec3(1.0, 0.0, 0.0));

		mAux = translate(mAux, dvec3(0, 0, 80));

		cilindro1->setModelMat(mAux);

		nave->addEntity(cilindro1);



		CompoundEntity* morro = new CompoundEntity();

		Cylinder* cilindro3 = new Cylinder(30, 30, 40, dvec3(0.0, 0.25, 0.42));


		Disk* disco = new Disk(0, 30, dvec3(0.0, 0.25, 0.42));

		mAux = disco->modelMat();

		mAux = translate(mAux, dvec3(0, 0, 0));

		disco->setModelMat(mAux);


		morro->addEntity(cilindro3);

		morro->addEntity(disco);


		mAux = morro->modelMat();

		mAux = translate(mAux, dvec3(120, 0, 0));

		mAux = glm::rotate(mAux, radians(270.0), dvec3(0.0, 1.0, 0.0));

		morro->setModelMat(mAux);


		nave->addEntity(morro);


		WingAdvancedTIE* wing = new WingAdvancedTIE(200, 200, 100);

		mAux = wing->modelMat();

		mAux = translate(mAux, dvec3(-100, 0, 160));

		wing->setModelMat(mAux);

		nave->addEntity(wing);


		WingAdvancedTIE* wing2 = new WingAdvancedTIE(200, 200, 100);

		mAux = wing2->modelMat();

		mAux = glm::rotate(mAux, radians(180.0), dvec3(0.0, 1.0, 0.0));

		mAux = translate(mAux, dvec3(-100, 0, 160));

		wing2->setModelMat(mAux);

		nave->addEntity(wing2);

		CompoundEntity* naveOrbit = new CompoundEntity({1.0, 1.0, 0.0}, 3.0);

		naveOrbit->addEntity(nave);

		inventedNode1_ = naveOrbit;

		CompoundEntity* naveOrbitPlanet = new CompoundEntity({ 1.0, 1.0, 0.0 }, 3.0);

		naveOrbitPlanet->addEntity(inventedNode1_);

		inventedNode2_ = naveOrbitPlanet;

		mAux = inventedNode1_->modelMat();

		mAux = translate(mAux, dvec3(0, 500, 0));

		inventedNode1_->setModelMat(mAux);

		mAux = nave->modelMat();

		mAux = scale(mAux, dvec3(0.1, 0.1, 0.1));

		nave->setModelMat(mAux);

		Sphere* planeta = new Sphere(300, dvec3(1.0, 0.8, 0.0));

		CompoundEntity* TotalScene = new CompoundEntity({ 1.0, 1.0, 0.0 }, 3.0);

		TotalScene->addEntity(planeta);

		TotalScene->addEntity(inventedNode2_);

		inventedNode3_ = TotalScene;

		gObjects.push_back(TotalScene);

	}
	else if (mId == 71) {


		SphereMbR* bola = new SphereMbR(100, 20, 20, {0, 0, 0});

		gObjects.push_back(bola);

	}
	else if (mId == 72) {

		ToroideMbR* donut = new ToroideMbR(100, 300, 12, 12);

		gObjects.push_back(donut);

	}
	else if (mId == 74) {

	
		SphereMbR* planetGold = new SphereMbR(100, 50, 50, {300, 0, 0});

		planetGold->setMaterial({0.24725, 0.1995, 0.0745, 1}, {0.628281, 0.555802, 0.366065, 1}, { 0.75164, 0.60648, 0.22648, 1 }, 51.2 );

		gObjects.push_back(planetGold);

		SphereMbR* planetColor = new SphereMbR(100, 50, 50, { 0, 0, 0 });

		gObjects.push_back(planetColor);

		

	}


}

void Scene::sceneDirLight(Camera const& cam) const{
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	//

	/*glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));*/
}
