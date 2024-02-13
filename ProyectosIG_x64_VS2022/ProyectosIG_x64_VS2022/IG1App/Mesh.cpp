#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::render() const
{
	if (vVertices.size() > 0) { // transfer data
		// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(
		  3, GL_DOUBLE, 0, vVertices.data()); // number of coordinates per vertex, type of
		                                      // each coordinate, stride, pointer
		if (vColors.size() > 0) {             // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(
			  4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
			                                    // each component, stride, pointer
		}

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	//importante, primitiva para pintar
	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}


Mesh*
Mesh::generateRegularPolygon(GLuint num, GLdouble r) {

	Mesh* mesh = new Mesh();

	//importante, primitiva para pintar
	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	double angle = 360.f / mesh->mNumVertices;

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vVertices.emplace_back(r* cos(glm::radians(i*angle)), r* sin(glm::radians( i*angle)), 0.0);
		//mesh->vColors.emplace_back(1.0, 1.0, 0.0, 1.0);
	}

	return mesh;
}

Mesh*
Mesh::generateTriangleRGB(GLdouble r) {

	Mesh* mesh = generateRegularPolygon(3, r);

	//importante, primitiva para pintar
	mesh->mPrimitive = GL_TRIANGLES;

	//colores de los vertices
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* 
Mesh::generateRectangle(GLdouble w, GLdouble h) {

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-w / 2.f, -h / 2.f, 0.f);
	mesh->vVertices.emplace_back(+w / 2.f, -h / 2.f, 0.f);
	mesh->vVertices.emplace_back(-w / 2.f, +h / 2.f, 0.f);
	mesh->vVertices.emplace_back(+w / 2.f, +h / 2.f, 0.f);

	//colores de los vertices
	/*
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	*/

	return mesh;
}

Mesh*
Mesh::generateRGBRectangle(GLdouble w, GLdouble h) {

	/*

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 24;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	// Front face
	mesh->vVertices.emplace_back(-w, -w, w);
	mesh->vVertices.emplace_back(w, -w, w);
	mesh->vVertices.emplace_back(-w, w, w);
	mesh->vVertices.emplace_back(w, w, w);

	// Bottom face
	mesh->vVertices.emplace_back(-w, -w, -w);
	mesh->vVertices.emplace_back(w, -w, -w);
	mesh->vVertices.emplace_back(-w, -w, w);
	mesh->vVertices.emplace_back(w, -w, w);

	// Back face
	mesh->vVertices.emplace_back(w, -w, -w);
	mesh->vVertices.emplace_back(-w, -w, -w);
	mesh->vVertices.emplace_back(w, w, -w);
	mesh->vVertices.emplace_back(-w, w, -w);

	// Top face
	mesh->vVertices.emplace_back(w, w, w);
	mesh->vVertices.emplace_back(-w, w, w);
	mesh->vVertices.emplace_back(w, w, -w);
	mesh->vVertices.emplace_back(-w, w, -w);

	// Right face
	mesh->vVertices.emplace_back(w, -w, w);
	mesh->vVertices.emplace_back(w, -w, -w);
	mesh->vVertices.emplace_back(w, w, w);
	mesh->vVertices.emplace_back(w, w, -w);

	// Left face
	mesh->vVertices.emplace_back(-w, -w, -w);
	mesh->vVertices.emplace_back(-w, -w, w);
	mesh->vVertices.emplace_back(-w, w, -w);
	mesh->vVertices.emplace_back(-w, w, w);


	/*
	
	// Now add colors for each face
	for (int i = 0; i < 4; ++i) {
		// Red for front face
		mesh->vColors.emplace_back(1.0f, 0.0f, 0.0f, 1.0f); // Red
	}
	for (int i = 0; i < 4; ++i) {
		// Green for bottom face
		mesh->vColors.emplace_back(0.0f, 1.0f, 0.0f, 1.0f); // Green
	}
	for (int i = 0; i < 4; ++i) {
		// Blue for back face
		mesh->vColors.emplace_back(0.0f, 0.0f, 1.0f, 1.0f); // Blue
	}
	for (int i = 0; i < 4; ++i) {
		// Yellow for top face
		mesh->vColors.emplace_back(1.0f, 1.0f, 0.0f, 1.0f); // Yellow
	}
	for (int i = 0; i < 4; ++i) {
		// Cyan for right face
		mesh->vColors.emplace_back(0.0f, 1.0f, 1.0f, 1.0f); // Cyan
	}
	for (int i = 0; i < 4; ++i) {
		// Magenta for left face
		mesh->vColors.emplace_back(1.0f, 0.0f, 1.0f, 1.0f); // Magenta
	}
	*/


	
	Mesh* mesh = generateRectangle(w, h);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	

	return mesh;
}


Mesh*
Mesh::generateCube(GLdouble longitud) {
	Mesh* mesh = nullptr;




	return mesh;
}