#include "IG1App.h"
#include "CheckML.h"
#include <iostream>


using namespace std;

// static single instance (singleton pattern)

IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

void
IG1App::close()
{
	if (!mStop) { // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
		mStop = true;        // main loop stopped
	}
	free();
}

void IG1App::update_()
{
	if (mMouseCoord.x < mWinW/2 || !m2Vista) {
		mScene->update();
		mCamera->update();
	}
	else {
		mScene2->update();
		mCamera2->update();
	}

	glutPostRedisplay();
}

void IG1App::changeAutoUpdate()
{

	if (!autoUpdate) {
		glutIdleFunc(s_update);
		autoUpdate = true;
	}
	else {
		glutIdleFunc(NULL);
		autoUpdate = false;
	}
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWinId == 0) {      // if not initialized
		init();         // initialize the application
		glutMainLoop(); // enters the main event processing loop
		mStop = true;   // main loop has stopped
	}
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort =
	  new Viewport(mWinW, mWinH); // glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)

	mViewPort2 =
		new Viewport(mWinW, mWinH);

	mCamera = new Camera(mViewPort);
	mCamera2 = new Camera(mViewPort2);

	mScene = new Scene;
	mScene2 = new Scene;

	mCamera->set3D();

	mScene->init();
	//mScene2->init();

	mScene->setScene(68);
	//mCamera->set2D();//activar para el 66
	//mScene2->setScene(0);

}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);                   // GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH); // window size
	// glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |
	                  GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth
	                                                    // buffer and stencil buffer
	

	mWinId = glutCreateWindow(
	  "IG1App"); // with its associated OpenGL context, return window's identifier

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);

	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::free()
{ // release memory and resources
	delete mScene;
	mScene = nullptr;
	delete mScene2;
	mScene2 = nullptr;
	delete mCamera;
	mCamera = nullptr;
	delete mCamera2;
	mCamera2 = nullptr;
	delete mViewPort;
	mViewPort = nullptr;
	delete mViewPort2;
	mViewPort2 = nullptr;
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	if (!m2Vista) {

		mScene->render(*mCamera);
	}
	else {	
		mScene->render(*mCamera); // uploads the viewport and camera to the GPU	
		mScene2->render(*mCamera2); // uploads the viewport and camera to the GPU
	}
	
	glutSwapBuffers(); // swaps the front and back buffer

}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);
	mViewPort2->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
	mCamera2->setSize(mViewPort->width(), mViewPort2->height());
}

void
IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	//seleccion de camara actual
	auto& currentCam = ((mMouseCoord.x < mWinW / 2) || !m2Vista) ? mCamera : mCamera2;

	auto& currentScene = ((mMouseCoord.x < mWinW / 2) || !m2Vista) ? mScene : mScene2;

	switch (key) {
		case 27:                     // Escape key
			glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
			break;
		case '+':
			currentCam->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			currentCam->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			currentCam->set3D();
			break;
		case 'o':
			currentCam->set2D();
			break;
		case '0':
			currentCam->set2D();
			currentScene->setScene(0);
			break;
		case '1':
			currentScene->setScene(1);
			currentCam->set3D();
			break;
		case 'u':
			currentScene->update();
			break;
		case 'U':
			changeAutoUpdate();
			break;
		case 'F':
			savePhoto();
			break;
		//case 'a':
			//currentCam->moveLR(-5);
			//break;
		case 'd':
			currentCam->moveLR(5);
			break;
		//case 'w':
			//currentCam->moveUD(5);
			//break;
		//case 's':
			//currentCam->moveUD(-5);
			//break;
		case 'W':
			currentCam->moveFB(5);
			break;
		case 'S':
			currentCam->moveFB(-5);
			break;
		case 'p':
			currentCam->changePrj();
			break;
		case 'c':
			currentCam->setCenital();
			break;
		case 'k':
			changeM2Vista();
			break;
		case 'f':
			mScene->SwitchRotate();
			break;
		case 'g':
			mScene->SwitchOrbit();
			break;
		case 'q':
			mScene->EnableDirLight();
			break;
		case 'w':
			mScene->DisableDirLight();
			break;
		case 'a':
			mScene->EnablePosLight();
			break;
		case 's':
			mScene->DisablePosLight();
			break;
		case 'z':
			mScene->EnableSpotLight();
			break;
		case 'x':
			mScene->DisableSpotLight();
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
		                     // display()
}

void
IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	//seleccion de camara actual
	auto& currentCam = ((mMouseCoord.x < mWinW / 2) || !m2Vista) ? mCamera : mCamera2;


	switch (key) {
		case GLUT_KEY_RIGHT:
			if (mdf == GLUT_ACTIVE_CTRL)
				currentCam->pitchReal(-20); // rotates -1 on the X axis
			else
				currentCam->pitchReal(20); // rotates 1 on the X axis
			break;
		case GLUT_KEY_LEFT:
			if (mdf == GLUT_ACTIVE_CTRL)
				currentCam->yawReal(20); // rotates 1 on the Y axis
			else
				currentCam->yawReal(-20); // rotate -1 on the Y axis
			break;
		case GLUT_KEY_UP:
			currentCam->rollReal(20); // rotates 1 on the Z axis
			break;
		case GLUT_KEY_DOWN:
			currentCam->rollReal(-20); // rotates -1 on the Z axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
		                     // display()
}

void IG1App::savePhoto()
{
	Texture* tex = new Texture();

	tex->loadColorBuffer(800, 600);

	tex->saveData("Bmps/photo.bmp");
}

void IG1App::mouse(int button, int state, int x, int y)
{
	mMouseButt = button;
	mMouseCoord = glm::dvec2(x, y);
}


void IG1App::motion(int x, int y)
{
	glm::dvec2 diff = mMouseCoord - glm::dvec2(x,y);

	mMouseCoord = glm::dvec2(x, y);

	//seleccion de camara actual
	auto& currentCam = ((mMouseCoord.x < mWinW / 2) || !m2Vista) ? mCamera : mCamera2;

	if (mMouseButt == 0) {
		//rotar 
		currentCam->orbit(diff.x * 0.05, diff.y);
	}
	else {
		//mover
		currentCam->moveLR(diff.x);
		currentCam->moveUD(-diff.y);
	}


	glutPostRedisplay();
}

void IG1App::mouseWheel(int n, int d, int x, int y)
{
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	//seleccion de camara actual
	auto& currentCam = ((mMouseCoord.x < mWinW / 2) || !m2Vista) ? mCamera : mCamera2;


	if (mdf == 0) {
		currentCam->moveFB(d*40);
	}
	else if (mdf == GLUT_ACTIVE_CTRL) {

		currentCam->setScale(d);
	}

	glutPostRedisplay();

}

void IG1App::changeM2Vista()
{
	m2Vista = !m2Vista;

	if (m2Vista) {
		mViewPort->setPos(0, 0);
		mViewPort2->setPos(mWinW / 2, 0);

		mViewPort->setSize(mWinW / 2, mWinH);
		mViewPort2->setSize(mWinW / 2, mWinH);

		mCamera->setSize(mViewPort->width(), mViewPort->height());
		mCamera2->setSize(mViewPort2->width(), mViewPort2->height());

		mCamera->set3D();
		mCamera2->set2D();
	}
	else {
		mViewPort->setPos(0, 0);
		mViewPort->setSize(mWinW , mWinH);
		mCamera->setSize(mViewPort->width(), mViewPort->height());
		mCamera->set3D();
	}
}
