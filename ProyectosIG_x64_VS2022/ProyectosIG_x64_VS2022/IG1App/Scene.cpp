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
}
