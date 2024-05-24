#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

#include "Ilumination.h"


enum TexturesName {

	BALDOSAS,
	CONTAINER,
	PAPEL,
	BALDOSAS2,
	WINDOW,
	GRASS,
	PHOTO,
	LIFEPHOTO,
	WOOD
};

class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		free();
		resetGL();

		//BORRADO DE TEXTURAS

		for (Texture* tex : gTextures) {
			delete tex;
			tex = nullptr;
		}

		//BORRADO DE LUCES

		delete dirLight;
		dirLight = nullptr;

		delete posLight;
		posLight = nullptr;

		delete spotLight;
		spotLight = nullptr;

		delete spotLight2;
		spotLight2 = nullptr;
		
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

	void rotate();

	void orbit();

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

	std::vector<Abs_Entity*> gTransparentObjects;

	std::vector<Texture*> gTextures;

	std::vector<Light*> gLights;

	GLuint mId;

	CompoundEntity* inventedNode1 = nullptr;
	CompoundEntity* inventedNode2 = nullptr;
	CompoundEntity* inventedNode3 = nullptr;

	bool rotateActive = false;
	bool orbitActive = false;

	float _angle = 0.f;

	DirLight* dirLight = nullptr;
	PosLight* posLight = nullptr;
	SpotLight* spotLight = nullptr;
	SpotLight* spotLight2 = nullptr;



};

#endif //_H_Scene_H_
