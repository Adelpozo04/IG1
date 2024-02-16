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
	gObjects.push_back(new EjesRGB(400.0));

	/*
	PoligonoRegular* pol = new PoligonoRegular(100, 200);

	pol->setColor(0.71, 0.58, 0.75, 1.0);

	PoligonoRegular* tri = new PoligonoRegular(3, 200);

	tri->setColor(0.0, 1.0, 1.0, 1.0);

	gObjects.push_back(pol);

	gObjects.push_back(tri);
	*/

	//gObjects.push_back(new RBGTriangle(200));

	//gObjects.push_back(new RGBRectangle(50, 100));

	gObjects.push_back(new Cube(100));

	//gObjects.push_back(new RGBRectangle(50, 100));
		
}
void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}
}
void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}
}

void
Scene::setScene(GLuint id) {

	gObjects.clear();

	gObjects.push_back(new EjesRGB(400.0));

	if (id == 0) {

		gObjects.push_back(new Cube(100));

	}
	else if (id == 1) {

		gObjects.push_back(new RGBRectangle(100, 200));

		gObjects.push_back(new RBGTriangle(20, 200, 0));

		PoligonoRegular* pol = new PoligonoRegular(100, 200);

		pol->setColor(0.71, 0.58, 0.75, 1.0);

		gObjects.push_back(pol);

	}

}

void
Scene::update() {

	for (auto it = gObjects.begin(); it != gObjects.end(); ++it) {

		(*it)->update();

	}

}
