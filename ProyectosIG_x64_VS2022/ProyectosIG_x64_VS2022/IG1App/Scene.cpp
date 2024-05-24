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

	//CARGA DE TEXTURAS
	Texture* t = new Texture();
	t->load("Bmps/baldosaC.bmp");

	gTextures.push_back(t);

	t = new Texture();
	t->load("Bmps/container.bmp");

	gTextures.push_back(t);

	t = new Texture();
	t->load("Bmps/papelE.bmp");

	gTextures.push_back(t);

	t = new Texture();
	t->load("Bmps/baldosaP.bmp");

	gTextures.push_back(t);

	t = new Texture();
	t->load("Bmps/windowV.bmp");

	gTextures.push_back(t);

	t = new Texture();
	t->load("Bmps/grass.bmp", glm::u8vec3(0, 0, 0), 0);

	gTextures.push_back(t);

	t = new Texture();
	t->load("Bmps/photo.bmp");

	gTextures.push_back(t);

	t = new Texture();
	t->loadColorBuffer(800, 600);

	gTextures.push_back(t);

	//CARGA DE LUCES
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };

	dirLight = new DirLight();

	dirLight->setAmb(ambient);
	dirLight->setDiff(diffuse);
	dirLight->setSpec(specular);
	dirLight->setPosDir(posDir);

	gLights.push_back(dirLight);

	posLight = new PosLight();
	
	posLight->setAmb(ambient);
	posLight->setDiff(glm::fvec4{1.0,1.0,0.0,1.0});
	posLight->setSpec(specular);
	posLight->setPosDir(glm::fvec3{ 200, 200, 0 });
	
	gLights.push_back(posLight);
	
	spotLight = new SpotLight();

	spotLight->setAmb(ambient);
	spotLight->setDiff(diffuse);
	spotLight->setSpec(specular);
	spotLight->setPosDir(glm::fvec3{ 0,  200, 200 });
	spotLight->setAtte(1, 0, 0);

	gLights.push_back(spotLight);



	spotLight2 = new SpotLight();
			 
	spotLight2->setAmb(ambient);
	spotLight2->setDiff(diffuse);
	spotLight2->setSpec(specular);
	spotLight2->setPosDir(glm::fvec3{ 0,  100, 0 });
	spotLight2->setAtte(1, 0, 0);


	gLights.push_back(spotLight2);

	dirLight->disable();
	posLight->disable();
	spotLight->disable();
	spotLight2->disable();

}

void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}
	gObjects.resize(0);

	for (Abs_Entity* el : gTransparentObjects) {
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
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	

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

void Scene::rotate()
{

	if (mId == 68 || mId == 79) {
		inventedNode1->setModelMat(glm::rotate(inventedNode1->modelMat(),
			radians(2.0), dvec3(0, 1, 0)));

		_angle = (int)(_angle + 2) % 360;
	}
}

void Scene::orbit()
{
	if (mId == 68 || mId == 79) {
		inventedNode2->setModelMat(glm::rotate(inventedNode2->modelMat(),
			radians(1.0), dvec3(sin(radians(_angle)), 0, cos(radians(_angle)))));
	}
}

void
Scene::render(Camera const& cam) const
{
	//sceneDirLight(cam);
	//dirLight->disable();
	dirLight->upload(cam.viewMat());
	posLight->upload(cam.viewMat());
	spotLight->upload(cam.viewMat());

	if (mId == 79) {

		spotLight2->upload(cam.viewMat() * inventedNode3->modelMat() * inventedNode2->modelMat() * inventedNode1->modelMat());
	}

	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}

	for (Abs_Entity* el : gTransparentObjects) {
		el->render(cam.viewMat());
	}
}

void Scene::update()
{
	for (auto& o : gObjects) {
		o->update();
	}

	if (mId == 66 && inventedNode2 != nullptr && inventedNode1 != nullptr)
	{
		inventedNode2->setModelMat(glm::rotate(inventedNode2->modelMat(),
			radians(3.0), dvec3(0, 0, 1)));

		inventedNode1->setModelMat(glm::rotate(inventedNode1->modelMat(),
			radians(3.0), dvec3(0, 0, 1)));
	}

	if (mId == 68 ||mId == 79){
		if (rotateActive) rotate();
		if (orbitActive) orbit();
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
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)

	
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

		gObjects.push_back(new Ground(200, 400, gTextures[BALDOSAS]));

	}
	else if (mId == 24) {

		gObjects.push_back(new BoxOutLine(100, gTextures[CONTAINER], gTextures[PAPEL]));

	}
	else if (mId == 29) {

		gObjects.push_back(new Box(100,1, gTextures[CONTAINER], gTextures[PAPEL], dvec3(0,0,0)));

	}
	else if (mId == 26) {
		
		gObjects.push_back(new Star3D(100, 8, 80, 1, 2, gTextures[BALDOSAS2]));

	}
	else if (mId == 31) {

		gObjects.push_back(new GlassParapet(100, gTextures[WINDOW]));

	}
	else if (mId == 34) {

		gObjects.push_back(new Grass(100,100,gTextures[GRASS]));

	}
	else if(mId == 38) {

		gObjects.push_back(new Photo(100,100, gTextures[LIFEPHOTO]));

		gObjects.push_back(new Ground(400,400, gTextures[BALDOSAS]));

		gTransparentObjects.push_back(new Grass(100, 100, gTextures[GRASS], dvec3(160, 50, 160)));

		gObjects.push_back(new Box(35, 1, gTextures[CONTAINER], gTextures[PAPEL], dvec3(-160, 35.1, -160)));

		gObjects.push_back(new Star3D(40, 8, 30, 1, 2, gTextures[BALDOSAS2], dvec3(-160, 165.1, -160)));

		gObjects.push_back(new RectanglePhoto(100,100, gTextures[PHOTO], dvec3(150, 0.1, -150)));

		gTransparentObjects.push_back(new GlassParapet(200, gTextures[WINDOW]));

	}
	else if (mId == 57) { //ejercicio del granjero

		//cabeza naranja
		auto sphere = new Sphere(200);
		sphere->setColor(1.f,0.5,0);
		gObjects.push_back(sphere);

		//copa del sombrero
		auto copa = new Cylinder(100, 100, 100);	
		dmat4 copaPos = translate(dmat4(1), dvec3(0, 180, 0)) * glm::rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0));
		copa->setModelMat(copaPos);
		copa->setColor(1, 0, 0);
		gObjects.push_back(copa);

		//nariz
		auto nose = new Cylinder(50, 1, 100);
		dmat4 nosePos = translate(dmat4(1), dvec3(0, 30, 180)) ;
		nose->setModelMat(nosePos);
		nose->setColor(0, 0, 1);
		gObjects.push_back(nose);

		//ojo izq
		auto leftEye = new Cylinder(20, 1, 30);
		dmat4 leftEyePos = translate(dmat4(1), dvec3(-65, 120, 150));
		leftEye->setModelMat(leftEyePos);
		leftEye->setColor(0, 1, 1);
		gObjects.push_back(leftEye);
		//ojo der
		auto rightEye = new Cylinder(20, 1, 30);
		dmat4 rightEyePos = translate(dmat4(1), dvec3(65, 120, 150));
		rightEye->setModelMat(rightEyePos);
		rightEye->setColor(0.5, 0.2,0.7);
		gObjects.push_back(rightEye);

		//disco sombrero
		auto disk = new Disk(60, 140);
		dmat4 sombreroPos = translate(dmat4(1), dvec3(0, 180, 0)) * glm::rotate(dmat4(1),radians(-90.0),dvec3(1,0,0));
		disk->setModelMat(sombreroPos);
		disk->setColor(1, 0, 0);
		gObjects.push_back(disk);

		//sonrisa
		auto partialDisk = new PartialDisk(80, 100,90,180);
		dmat4 smilePos = translate(dmat4(1),dvec3(0,0,180));
		partialDisk->setModelMat(smilePos);
		partialDisk->setColor(0, 1, 0);
		gObjects.push_back(partialDisk);

	}
	else if (mId == 60) {//ejercicio del caza 

		glClearColor(0, 0,0, 1); // background color (alpha=1 -> opaque)

		gObjects.push_back(new Advanced_TIE_X1());
		
	}
	else if (mId == 63) {

		auto cubo = new Cubo(100);
		gObjects.push_back(cubo);
		cubo->setColor(dvec4(0, 1, 0, 1));
	}
	else if(mId == 66)
	{
		//circunferencia magenta
		gObjects.push_back(new RegularPolygon(50, 300));
		gObjects[0]->setColor(glm::dvec4(0.71, 0.58, 0.75, 1.0));
		//rectangulo
		gObjects.push_back(new Rectangle_RGB(400, 200));


		inventedNode1 = new CompoundEntity();
		TriangleRGB* tr = new TriangleRGB(100.f, dvec3(0, 0, 0), 0.0);
		inventedNode1->addEntity(tr);

		inventedNode2 = new CompoundEntity();

		inventedNode2->addEntity(inventedNode1);
		inventedNode1->setModelMat(translate(inventedNode2->modelMat(),
			dvec3(300, 0, 0)));

		gObjects.push_back(inventedNode2);
	}
	else if (mId == 67) {

		glClearColor(0, 0, 0, 1); // background color (alpha=1 -> opaque)


		//planeta
		auto sphere = new Sphere(2000);
		sphere->setColor(1.f, 233/255.0, 0);
		gObjects.push_back(sphere);

		auto caza = new Advanced_TIE_X1();

		caza->setModelMat(translate(dmat4(1), dvec3(0, 2150, 0)));
		gObjects.push_back(caza);

	}
	else if (mId == 68) {

		glClearColor(0, 0, 0, 1); // background color (alpha=1 -> opaque)

		//planeta
		auto sphere = new Sphere(2000);
		sphere->setColor(1.f, 233 / 255.0, 0);

		inventedNode1 = new CompoundEntity();
		auto caza = new Advanced_TIE_X1();
		caza->setModelMat(translate(inventedNode1->modelMat(), dvec3(0, 0, 0)));

		inventedNode1->addEntity(caza);

		inventedNode2 = new CompoundEntity();

		inventedNode2->addEntity(inventedNode1);
		inventedNode1->setModelMat(translate(inventedNode2->modelMat(),
			dvec3(0, 2150, 0)));

		inventedNode3 = new CompoundEntity();

		inventedNode3->addEntity(inventedNode2);
		
		inventedNode3->addEntity(sphere);

		sphere->setModelMat(translate(sphere->modelMat(), dvec3(0, 0, 0)));
		inventedNode2->setModelMat(translate(inventedNode2->modelMat(), dvec3(0, 0, 0)));

		inventedNode3->setModelMat(translate(inventedNode3->modelMat(), dvec3(0, -500, 0)));

		gObjects.push_back(inventedNode3);	
	}
	else if(mId == 71){
		
		auto sphere = new Sphere_mbr(100.0, 30, 30);
		sphere->setColor(dvec4(0, 1, 0, 1));
		gObjects.push_back(sphere);
	}
	else if (mId == 72) {
		
		auto toroid = new Toroid(50, 50, 16, 16);
		toroid->setColor(dvec4(0, 1, 1, 1));
		gObjects.push_back(toroid);
	}
	else if (mId == 74) {

		auto sphereCol = new Sphere_mbr(100.0, 30, 30);

		sphereCol->setColor(dvec4(1, 1, 0, 1));

		sphereCol->setModelMat(translate(sphereCol->modelMat(), dvec3(-100, 0, 100)));

		gObjects.push_back(sphereCol);

		auto sphereMat = new Sphere_mbr(100.0, 30, 30);

		sphereMat->setColor(dvec4(1, 1, 0, 1));
		
		Material* m = new Material();
		m->setGold();
		sphereMat->setMaterial(m);

		sphereMat->setModelMat(translate(sphereMat->modelMat(), dvec3(100, 0, -100)));

		gObjects.push_back(sphereMat);
			
	}
	else if (mId == 79) {
		glClearColor(0, 0, 0, 1); // background color (alpha=1 -> opaque)

		//planeta
		auto sphere = new Sphere(2000);
		sphere->setColor(1.f, 233 / 255.0, 0);

		inventedNode1 = new CompoundEntity();
		auto caza = new Advanced_TIE_X1();
		caza->setModelMat(translate(inventedNode1->modelMat(), dvec3(0, 0, 0)));

		inventedNode1->addEntity(caza);

		inventedNode2 = new CompoundEntity();

		inventedNode2->addEntity(inventedNode1);
		inventedNode1->setModelMat(translate(inventedNode2->modelMat(),
			dvec3(0, 2150, 0)));

		inventedNode3 = new CompoundEntity();

		inventedNode3->addEntity(inventedNode2);

		inventedNode3->addEntity(sphere);

		sphere->setModelMat(translate(sphere->modelMat(), dvec3(0, 0, 0)));
		inventedNode2->setModelMat(translate(inventedNode2->modelMat(), dvec3(0, 0, 0)));

		inventedNode3->setModelMat(translate(inventedNode3->modelMat(), dvec3(0, -500, 0)));

		gObjects.push_back(inventedNode3);
	}

}

void Scene::sceneDirLight(Camera const& cam) const {

	//enable del sistema de luces
	glEnable(GL_LIGHTING);

	//enable de la luz 0
	glEnable(GL_LIGHT0);
	
	//subir la matriz de la camara, por si la camara se mueve
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));

	//posicion,y componentes (amibient,diffuse,specular) de la luz 0
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };

	//setear la poscion y las componentes a la luz 0
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));

	
}

void Scene::SwitchRotate()
{
	rotateActive = !rotateActive;
}

void Scene::SwitchOrbit()
{
	orbitActive = !orbitActive;
}

void Scene::EnableDirLight()
{
	if (dirLight != nullptr) {
		dirLight->enable();
	}
}

void Scene::DisableDirLight()
{
	if (dirLight != nullptr) {
		dirLight->disable();
	}
}

void Scene::EnablePosLight()
{
	if (posLight != nullptr) {
		posLight->enable();
	}
}

void Scene::DisablePosLight()
{
	if (posLight != nullptr) {
		posLight->disable();
	}
}

void Scene::EnableSpotLight()
{
	if (spotLight != nullptr) {
		spotLight->enable();
	}
}

void Scene::DisableSpotLight()
{
	if (spotLight != nullptr) {
		spotLight->disable();
	}
}

void Scene::EnableSpotLight2()
{
	if (spotLight2 != nullptr) {
		spotLight2->enable();
	}
}

void Scene::DisableSpotLight2()
{

	if (spotLight2 != nullptr) {
		spotLight2->disable();
	}
}
