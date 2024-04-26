#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

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

protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene

	GLuint mId;

	CompoundEntity* inventedNode1_;

	CompoundEntity* inventedNode2_;

	CompoundEntity* inventedNode3_;

	GLuint angle = 0;

};

#endif //_H_Scene_H_
