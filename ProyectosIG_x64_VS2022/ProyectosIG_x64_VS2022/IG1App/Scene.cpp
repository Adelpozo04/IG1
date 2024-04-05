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

}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

void
Scene::render(Camera const& cam) const
{
	sceneDirLight(cam);
	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}


	
}

void Scene::update()
{
	for (auto& o : gObjects) {
		o->update();
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

		//circunferencia magenta
		gObjects.push_back(new RegularPolygon(50, 100));
		gObjects[0]->setColor(glm::dvec4(0.71, 0.58, 0.75, 1.0));

		//triangulo RGB
		gObjects.push_back(new TriangleRGB(30, glm::dvec3(100, 0, 0),1.0));


		//rectangulo
		gObjects.push_back(new Rectangle_RGB(200, 100));
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
	else if (mId == 57) {

		auto sphere = new Sphere(200);

		sphere->setColor(1.f,0.5,0);

		gObjects.push_back(sphere);


		auto copa = new Cylinder(100, 100, 100);
		
		dmat4 copaPos = translate(dmat4(1), dvec3(0, 180, 0)) * rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0));

		copa->setModelMat(copaPos);

		copa->setColor(1, 0, 0);

		gObjects.push_back(copa);


		
		auto disk = new Disk(60, 140);
		dmat4 sombreroPos = translate(dmat4(1), dvec3(0, 180, 0)) * rotate(dmat4(1),radians(-90.0),dvec3(1,0,0));
		
		disk->setModelMat(sombreroPos);

		disk->setColor(1, 0, 0);

		gObjects.push_back(disk);

		
		
		auto partialDisk = new PartialDisk(80, 100,90,180);
		dmat4 smilePos = translate(dmat4(1),dvec3(0,0,180));
		partialDisk->setModelMat(smilePos);
		partialDisk->setColor(0, 1, 0);

		gObjects.push_back(partialDisk);
		
		

	}
}

void Scene::sceneDirLight(Camera const& cam) const {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}