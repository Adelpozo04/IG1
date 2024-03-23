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
	mScene->update();
	mCamera->update();
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
	mCamera = new Camera(mViewPort);
	mScene = new Scene;

	mCamera->set3D();
	mScene->init();
	mScene->setScene(38);

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
	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer
	if (!m2Vista) {

		mScene->render(*mCamera);

	}
	else {
	
		// para renderizar las vistas utilizamos una c�mara auxiliar :
		Camera auxCam = *mCamera; // copiando mCamera
		// el puerto de vista queda compartido (se copia el puntero )
		Viewport auxVP = *mViewPort; // lo copiamos en una var. aux . para *�

		mViewPort->setSize(mWinW / 2, mWinH );
		auxCam.setSize(mViewPort->width(), mViewPort->height());

		auxCam.set3D();
		mScene->render(auxCam); // uploads the viewport and camera to the GPU

		mViewPort->setPos(mWinW/2, 0);

		auxCam.setCenital();
		mScene->render(auxCam); // uploads the viewport and camera to the GPU


		*mViewPort = auxVP; // * restaurar el puerto de vista ( NOTA )

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

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
		case 27:                     // Escape key
			glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
			break;
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		case '0':
			mCamera->set2D();
			mScene->setScene(0);
			break;
		case '1':
			mScene->setScene(1);
			mCamera->set3D();
			break;
		case 'u':
			mScene->update();
			break;
		case 'U':
			changeAutoUpdate();
			break;
		case 'F':
			savePhoto();
			break;
		case 'a':
			mCamera->moveLR(-5);
			break;
		case 'd':
			mCamera->moveLR(5);
			break;
		case 'w':
			mCamera->moveUD(5);
			break;
		case 's':
			mCamera->moveUD(-5);
			break;
		case 'W':
			mCamera->moveFB(5);
			break;
		case 'S':
			mCamera->moveFB(-5);
			break;
		case 'p':
			mCamera->changePrj();
			break;
		case 'c':
			mCamera->setCenital();
			break;
		case 'k':
			m2Vista = !m2Vista;
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

	switch (key) {
		case GLUT_KEY_RIGHT:
			if (mdf == GLUT_ACTIVE_CTRL)
				mCamera->pitchReal(-20); // rotates -1 on the X axis
			else
				mCamera->pitchReal(20); // rotates 1 on the X axis
			break;
		case GLUT_KEY_LEFT:
			if (mdf == GLUT_ACTIVE_CTRL)
				mCamera->yawReal(20); // rotates 1 on the Y axis
			else
				mCamera->yawReal(-20); // rotate -1 on the Y axis
			break;
		case GLUT_KEY_UP:
			mCamera->rollReal(20); // rotates 1 on the Z axis
			break;
		case GLUT_KEY_DOWN:
			mCamera->rollReal(-20); // rotates -1 on the Z axis
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

	if (mMouseButt == 0) {
		//rotar 
		mCamera->orbit(diff.x * 0.05, diff.y);
	}
	else {
		//mover
		mCamera->moveLR(diff.x);
		mCamera->moveUD(-diff.y);
	}


	glutPostRedisplay();
}

void IG1App::mouseWheel(int n, int d, int x, int y)
{
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	if (mdf == 0) {
		mCamera->moveFB(d*40);
	}
	else if (mdf == GLUT_ACTIVE_CTRL) {

		mCamera->setScale(d);
	}

	glutPostRedisplay();

}
