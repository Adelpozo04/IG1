#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>

using namespace glm;

Camera::Camera(Viewport* vp)
  : mViewMat(1.0)
  , mProjMat(1.0)
  , xRight(vp->width() / 2.0)
  , xLeft(-xRight)
  , yTop(vp->height() / 2.0)
  , yBot(-yTop)
  , mViewPort(vp),
	mAng(0),
	mRadio(100),
	mSpeed(1)
{
	setPM();

	setAxes();
}

void
Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
	setAxes();
}

void
Camera::set2D()
{
	mEye = dvec3(0, 0, 500);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);

	mRadio = 100;
	setVM();
}

void
Camera::set3D()
{
	mEye = dvec3(500, 500, 500);
	mLook = dvec3(0, 10, 0);
	mUp = dvec3(0, 1, 0);
	mRadio = 1000;
	setVM();
}

void
Camera::pitch(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();

}

void
Camera::yaw(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();

}

void
Camera::roll(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();

}

void Camera::pitchReal(GLdouble a)
{
	//mViewMat = rotate(dmat4(1), glm::radians(a), glm::dvec3(1.0, 0, 0));
	mLook += mUpward *a;
	setVM();
}

void Camera::yawReal(GLdouble a)
{
	//mViewMat = rotate(dmat4(1), glm::radians(a), glm::dvec3(0, 1.0, 0));
	mLook += mRight * a;
	setVM();
}

void Camera::rollReal(GLdouble a)
{
	//mViewMat = rotate(dmat4(1), glm::radians(a), glm::dvec3(0, 0, 1.0));
	
	//mLook += mUp * a;

	mProjMat = rotate(mProjMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	setVM();
}

void Camera::moveLR(GLdouble cs)
{
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();	
}

void Camera::moveFB(GLdouble cs)
{
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}

void Camera::moveUD(GLdouble cs)
{
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM();
}

void Camera::update()
{
	//EJERCICIO 47
	/*
	mAng += mSpeed;

	rollReal(-mSpeed);

	mEye.x = cos(radians(mAng)) * mRadio;
	mEye.y = sin(radians(mAng)) * mRadio;

	mLook.x = cos(radians(mAng)) * mRadio;
	mLook.y = sin(radians(mAng)) * mRadio;

	setVM();
	*/
	

	//orbit(1,0);
}

void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	setVM();
}

void Camera::setCenital()
{
	mEye = dvec3(0, 1000, 0.1);
	mLook = dvec3(0, 10, 0);
	mUp = dvec3(0, 1, 0);

	setVM();
}

void Camera::setAxes()
{
	mRight = row(mViewMat,0);
	mUpward = row(mViewMat, 1);
	mFront = - row(mViewMat, 2);
}


void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft * mScaleFact,
		                 xRight * mScaleFact,
		                 yBot * mScaleFact,
		                 yTop * mScaleFact,
		                 mNearVal,
		                 mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		mProjMat =  frustum(xLeft * mScaleFact,
							xRight * mScaleFact,
							yBot * mScaleFact,
							yTop * mScaleFact, 
							500., 10000.);
	}
}

void
Camera::uploadPM() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
