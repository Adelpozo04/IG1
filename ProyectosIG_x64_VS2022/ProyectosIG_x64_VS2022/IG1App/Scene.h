#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

#include "Ilumination.h"


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

	void SwitchRotate();

	void SwitchOrbit();

	void EnableDirLight();
	void DisableDirLight();

protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene

	GLuint mId;

	CompoundEntity* inventedNode1 = nullptr;
	CompoundEntity* inventedNode2 = nullptr;
	CompoundEntity* inventedNode3 = nullptr;

	bool rotateActive = false;
	bool orbitActive = false;

	float _angle = 0.f;

	void rotate();

	void orbit();

	DirLight* dirLight;

};

#endif //_H_Scene_H_
