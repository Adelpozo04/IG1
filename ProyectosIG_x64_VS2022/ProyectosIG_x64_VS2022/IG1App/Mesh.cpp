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

		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
		}


		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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
	
	Mesh* mesh = generateRectangle(w, h);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	

	return mesh;
}

Mesh*
Mesh::generateRectangleTexCor(GLdouble w, GLdouble h) {


	Mesh* mesh = generateRectangle(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 1.0);
	mesh->vTexCoords.emplace_back(1.0, 0.0);


	return mesh;
}

Mesh*
Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLdouble rw, GLdouble rh) {


	Mesh* mesh = generateRectangle(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.0, rh);
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(rw, rh);
	mesh->vTexCoords.emplace_back(rw, 0.0);


	return mesh;
}


Mesh*
Mesh::generateCube(GLdouble w) {
	//generamos un cubo a partir de 12 triangulos
	//36 vertices

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);


	//posiciones de los puntos
	vector<glm::vec3> points;
	points.reserve(8);

	points.emplace_back(w, w, -w);
	points.emplace_back(w, -w, -w);
	points.emplace_back(-w, -w, -w);
	points.emplace_back(-w, w, -w);

	points.emplace_back(w, w, w);
	points.emplace_back(w, -w, w);
	points.emplace_back(-w, -w, w);
	points.emplace_back(-w, w, w);

	//FACE 0
	mesh->vVertices.push_back(points[5]);
	mesh->vVertices.push_back(points[1]);
	mesh->vVertices.push_back(points[0]);

	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[5]);

	//FACE 1
	mesh->vVertices.push_back(points[6]);
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[1]);

	mesh->vVertices.push_back(points[6]);
	mesh->vVertices.push_back(points[1]);
	mesh->vVertices.push_back(points[5]);

	//FACE 2
	mesh->vVertices.push_back(points[1]);
	mesh->vVertices.push_back(points[3]);	
	mesh->vVertices.push_back(points[0]);

	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[1]);

	//FACE 3
	mesh->vVertices.push_back(points[7]);
	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[0]);

	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[7]);

	//FACE 4
	mesh->vVertices.push_back(points[5]);
	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[7]);

	mesh->vVertices.push_back(points[6]);
	mesh->vVertices.push_back(points[5]);
	mesh->vVertices.push_back(points[7]);

	//FACE 5
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[7]);
	mesh->vVertices.push_back(points[3]);

	mesh->vVertices.push_back(points[6]);
	mesh->vVertices.push_back(points[7]);
	mesh->vVertices.push_back(points[2]);


	//COLORES PARA LOS VERTICES

	for (int i = 0; i < 6; ++i) {
		// Green for bottom face
		mesh->vColors.emplace_back(0.0f, 1.0f, 0.0f, 1.0f); // Green
	}
	for (int i = 0; i < 6; ++i) {
		// Blue for back face
		mesh->vColors.emplace_back(0.0f, 0.0f, 1.0f, 1.0f); // Blue
	}
	for (int i = 0; i < 6; ++i) {
		// Red for front face
		mesh->vColors.emplace_back(1.0f, 0.0f, 0.0f, 1.0f); // Red
	}
	for (int i = 0; i < 6; ++i) {
		//for bottom face
		mesh->vColors.emplace_back(0.0f, 0.0f, 1.0f, 1.0f); // Blue
	}
	for (int i = 0; i < 6; ++i) {
		// Blue for back face
		mesh->vColors.emplace_back(1.0f, 0.0f, 0.0f, 1.0f); // Red
	}
	for (int i = 0; i < 6; ++i) {
		// Red for front face
		mesh->vColors.emplace_back(0.0f, 1.0f, 0.0f, 1.0f); // Green
	}

	return mesh;
}

Mesh*
Mesh::generateBoxOutline(GLdouble w) {
	//generamos un cubo a partir de 12 triangulos
	//36 vertices

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vTexCoords.reserve(mesh->mNumVertices);


	//posiciones de los puntos
	vector<glm::vec3> points;
	points.reserve(8);

	points.emplace_back(w, w, -w); //1 1 0
	points.emplace_back(w, -w, -w); //1 0 0
	points.emplace_back(-w, -w, -w); // 0 0 0
	points.emplace_back(-w, w, -w); // 0 1 0

	points.emplace_back(w, w, w); // 1 1 1
	points.emplace_back(w, -w, w); // 1 0 1
	points.emplace_back(-w, -w, w); // 0 0 1
	points.emplace_back(-w, w, w); // 0 1 1

	//FACE 0
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[1]);

	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[5]);
	mesh->vVertices.push_back(points[4]);

	//FACE 1
	mesh->vVertices.push_back(points[6]);
	mesh->vVertices.push_back(points[7]);
	mesh->vVertices.push_back(points[2]);

	mesh->vVertices.push_back(points[3]);

	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 1.0);
	mesh->vTexCoords.emplace_back(1.0, 0.0);

	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 0.0);

	mesh->vTexCoords.emplace_back(1.0, 1.0);
	mesh->vTexCoords.emplace_back(1.0, 0.0);

	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 0.0);

	
	return mesh;
}

Mesh*
Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h) {
	
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->mNumVertices = np * 2 + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	double angle = 360.f / (mesh->mNumVertices - 2);

	GLdouble ri = re / 2;

	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);


	mesh->vTexCoords.emplace_back(0.5, 0.5);

	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(0.5, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 0.5);
	mesh->vTexCoords.emplace_back(1.0, 1.0);
	mesh->vTexCoords.emplace_back(0.5, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 1.0);
	mesh->vTexCoords.emplace_back(0.0, 0.5);

	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(0.5, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 0.0);
	mesh->vTexCoords.emplace_back(1.0, 0.5);
	mesh->vTexCoords.emplace_back(1.0, 1.0);


	

	for (int i = 0; i < mesh->mNumVertices - 1; i++) {

		if (i % 2 == 0) {
			mesh->vVertices.emplace_back(re * cos(glm::radians(i * angle)), re * sin(glm::radians(i * angle)), h);

		}
		else {
			mesh->vVertices.emplace_back(ri * cos(glm::radians(i * angle)), ri * sin(glm::radians(i * angle)), h);

		}
		
	}



	return mesh;
}

