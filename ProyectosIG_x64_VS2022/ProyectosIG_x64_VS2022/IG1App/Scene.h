#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		free();
		resetGL();
	};

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	void init();

	void render(Camera const& cam) const;

	void update();

	void setScene(GLuint id);

	void sceneDirLight(Camera const& cam) const;

	void rotated();

	void orbited();

	void changeLightsDir(bool on) { 
		
		if (on) {
			dirLight->enable();
		}
		else {
			dirLight->disable();
		}
	
	}

	void changeLightsPos(bool on) {

		if (on) {
			posLight->enable();
		}
		else {
			posLight->disable();
		}

	}

	void changeLightsSpot(bool on) {

		if (on) {
			spotLight->enable();
		}
		else {
			spotLight->disable();
		}

	}

protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene

	GLuint mId;

	CompoundEntity* inventedNode1_;

	CompoundEntity* inventedNode2_;

	CompoundEntity* inventedNode3_;

	float angle = 0;

	DirLight* dirLight;

	PosLight* posLight;

	SpotLight* spotLight;


};

#endif //_H_Scene_H_
