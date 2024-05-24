#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

#include "Ilumination.h"


const int NUM_TEXTURES = 11;

enum Texts {
		BALDOSA_C,
		BALDOSA_F,
		BALDOSA_P,
		CONTAINER,
		GRASS,
		NOCHE,
		PAPEL_C,
		PAPEL_E,
		PHOTO,
		WINDOW_C,
		WINDOW_V
};


class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		free();
		resetGL();

		//eliminar las texturas

		for (auto& t : textures) delete t;

		textures.clear();


		//eliminar las luces
		delete dirLight;
		delete posLight;
		delete spotLight;
		delete spotLight2;	



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

	void EnablePosLight();
	void DisablePosLight();

	void EnableSpotLight();
	void DisableSpotLight();
	
	void EnableSpotLight2();
	void DisableSpotLight2();

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

	DirLight* dirLight = nullptr;
	PosLight* posLight = nullptr;
	SpotLight* spotLight = nullptr;
	SpotLight* spotLight2 = nullptr;


	std::vector<Texture*> textures;
};

#endif //_H_Scene_H_
