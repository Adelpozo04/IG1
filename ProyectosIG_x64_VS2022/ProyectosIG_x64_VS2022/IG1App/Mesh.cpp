#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

#pragma region Mesh

#pragma region Draw && render

void Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void Mesh::render() const
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

		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}


		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

#pragma endregion

#pragma region Generate meshs

Mesh* Mesh::createRGBAxes(GLdouble l)
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

Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r) {

	Mesh* mesh = new Mesh();

	//importante, primitiva para pintar
	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	double angle = 360.f / mesh->mNumVertices;

	for (int i = 0; i < mesh->mNumVertices; i++) {

		if (i % 2 == 0) {

			mesh->vVertices.emplace_back(100 + (r * cos(glm::radians(i * angle))), r * sin(glm::radians(i * angle)), 0.0);

		}
		else{

			mesh->vVertices.emplace_back(100 + (r * cos(glm::radians(i * angle))) / 2, (r * sin(glm::radians(i * angle))) / 2, 0.0);

		}
		

	}

	return mesh;
}

Mesh* Mesh::generateTriangleRGB(GLdouble r) {

	Mesh* mesh = generateRegularPolygon(3, r);

	//importante, primitiva para pintar
	mesh->mPrimitive = GL_TRIANGLES;

	//colores de los vertices
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h) {

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

Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h) {
	
	Mesh* mesh = generateRectangle(w, h);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	

	return mesh;
}

Mesh* Mesh::generateCube(GLdouble w) {
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

	vector<glm::dvec4> colors{ {0.0f, 1.0f, 0.0f, 1.0f} , {0.0f, 0.0f, 1.0f, 1.0f},{1.0f, 0.0f, 0.0f, 1.0f} };

	for (int i = 0; i < 36; i++) {
		int index = i / 6;

		if (index == 0 || index == 5) mesh->vColors.push_back(colors[0]);
		else if (index == 1 || index == 3)mesh->vColors.push_back(colors[1]);
		else if (index == 2 || index == 4)mesh->vColors.push_back(colors[2]);
	}

	return mesh;
}

Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h)
{
	Mesh* m = Mesh::generateRectangle(w, h);

	m->vTexCoords.reserve(m->mNumVertices);
	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(1, 1);
	m->vTexCoords.emplace_back(1, 0);
	return m;

}

Mesh* Mesh::generaRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* m = Mesh::generateRectangle(w, h);

	m->vTexCoords.reserve(m->mNumVertices);

	
	m->vTexCoords.emplace_back(0, rh);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(rw, rh);
	m->vTexCoords.emplace_back(rw, 0);
	return m;
	
}

Mesh* Mesh::generateBoxOutline(GLdouble w)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;

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


	
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[1]);
	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[5]);
	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[6]);
	mesh->vVertices.push_back(points[7]);
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[3]);

	return mesh;
}

Mesh* Mesh::generateBoxOutlineTexCor(GLdouble longitud)
{

	Mesh* m = generateBoxOutline(longitud);

	m->vTexCoords.reserve(m->mNumVertices);


	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(1, 1);
	m->vTexCoords.emplace_back(1, 0);

	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(1, 1);
	m->vTexCoords.emplace_back(1, 0);

	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(0, 0);

	return m;
}

Mesh* Mesh::generateBoxOutlineTexCorTransparent(GLdouble longitud)
{
	
	Mesh* mesh = generateBoxOutlineTexCor(longitud);

	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vColors.emplace_back(1.0, 1.0, 1.0, 0.5);
	}

	return mesh;
	
}

Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->mNumVertices =(np*2) + 2;

	mesh->vVertices.reserve(mesh->mNumVertices);

	//punto de origen de la estrella(primer vertice)
	mesh->vVertices.emplace_back(0, 0, 0);

	float angle = 360.0 / np;
	GLdouble ri = re / 2.0;

	for (int i = 0; i < np; i++) {
		mesh->vVertices.emplace_back(re * cos(glm::radians(i * angle)), re * sin(glm::radians(i * angle)), h);
		mesh->vVertices.emplace_back(ri * cos(glm::radians((i * angle)+ angle/2)), ri * sin(glm::radians((i * angle)+angle/2)), h);
	}

	//añadir otra vez el segundo verice(primero sin contar el centro)
	mesh->vVertices.emplace_back(re * cos(glm::radians(0.)), re * sin(glm::radians( 0.)), h);



	return mesh;
}

Mesh* Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = generateStar3D(re, np, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	vector<vec2> texPoints{ {0,0},{0.5,0},{0,0 },{0,0.5} };

	mesh->vTexCoords.emplace_back(0.5, 0.5);

	for (int i = 0; i < mesh->mNumVertices; i++) {

		mesh->vTexCoords.push_back(texPoints[i % 4]);
	} 

	return mesh;
}

Mesh* Mesh::generateWingAdvancedTIE(GLdouble radius, GLdouble width)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 8;

	mesh->vVertices.reserve(mesh->mNumVertices);

	float angle = -25;

	mesh->vVertices.emplace_back(width / 2, -radius, 0);
	mesh->vVertices.emplace_back(-width / 2, -radius, 0);
	mesh->vVertices.emplace_back(width / 2, -(radius + (sin(radians(angle))*radius)), cos(radians(angle)) *radius);
	mesh->vVertices.emplace_back(-width / 2, -(radius + (sin(radians(angle)) * radius)), cos(radians(angle)) * radius);

	mesh->vVertices.emplace_back(width / 2, (radius + (sin(radians(angle)) * radius)), cos(radians(angle)) * radius);
	mesh->vVertices.emplace_back(-width / 2, (radius + (sin(radians(angle)) * radius)), cos(radians(angle)) * radius);
	mesh->vVertices.emplace_back(width / 2, radius, 0);
	mesh->vVertices.emplace_back(-width / 2, radius, 0);

	//colores
	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vColors.emplace_back(1.0, 1.0, 1.0, 0.8);
	}


	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);

	return mesh;
}

Mesh* Mesh::generatePiramid(GLdouble h, GLdouble w)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 9;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);


	//posiciones de los puntos
	vector<glm::vec3> points;
	points.reserve(5);

	points.emplace_back(-w, 0, -w);
	points.emplace_back(w, 0, -w);
	points.emplace_back(w, 0, w);
	points.emplace_back(-w, 0, w);

	points.emplace_back(0, h, 0);

	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[1]);
	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[0]);


	return mesh;
}

Mesh* Mesh::generatePiramidTexCord(GLdouble h, GLdouble w)
{
	
	Mesh* m = generatePiramid(h, w);

	m->vTexCoords.reserve(m->mNumVertices);

	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(0.5, 0);
	m->vTexCoords.emplace_back(0.5, 0.5);
	m->vTexCoords.emplace_back(1, 0);

	m->vTexCoords.emplace_back(1, 0.5);
	m->vTexCoords.emplace_back(0.5, 0.5);
	m->vTexCoords.emplace_back(1, 1);
	m->vTexCoords.emplace_back(0.5, 1);

	m->vTexCoords.emplace_back(0.5, 0.5);

	return m;

}

Mesh* Mesh::generateRomboidTriangular(GLdouble h, GLdouble w, GLdouble th)
{
	
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 11;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);


	//posiciones de los puntos
	vector<glm::vec3> points;
	points.reserve(6);

	points.emplace_back(-w, 0, h);
	points.emplace_back(0, th, h);
	points.emplace_back(w, 0, h);
	
	points.emplace_back(-w, 0, -h);
	points.emplace_back(0, th, -h);
	points.emplace_back(w, 0, -h);

	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[1]);
	mesh->vVertices.push_back(points[2]);

	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[5]);
	mesh->vVertices.push_back(points[3]);

	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[1]);

	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[4]);


	return mesh;

}

Mesh* Mesh::generateRomboidTriangularTexCord(GLdouble h, GLdouble w, GLdouble th)
{
	
	Mesh* m = generateRomboidTriangular(h, w, th);

	m->vTexCoords.reserve(m->mNumVertices);

	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(0.5, 0);
	m->vTexCoords.emplace_back(0.5, 0.5);
	m->vTexCoords.emplace_back(1, 0);

	m->vTexCoords.emplace_back(1, 0.5);
	m->vTexCoords.emplace_back(0.5, 0.5);
	m->vTexCoords.emplace_back(1, 1);
	m->vTexCoords.emplace_back(0.5, 1);

	m->vTexCoords.emplace_back(0.5, 0.5);
	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(0, 0.5);


	return m;

}

IndexMesh* IndexMesh::generateCristal(GLdouble altoCuerpo, GLdouble anchoCuerpo, GLdouble altoPicos)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 10;
	mesh->nNumIndices = 48;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vNormals.reserve(mesh->mNumVertices);


	mesh->vVertices.emplace_back(-anchoCuerpo, altoCuerpo, anchoCuerpo);
	mesh->vVertices.emplace_back(anchoCuerpo, altoCuerpo, anchoCuerpo);
	mesh->vVertices.emplace_back(anchoCuerpo, altoCuerpo, -anchoCuerpo);
	mesh->vVertices.emplace_back(-anchoCuerpo, altoCuerpo, -anchoCuerpo);
	mesh->vVertices.emplace_back(0, altoCuerpo + altoPicos, 0);

	mesh->vVertices.emplace_back(-anchoCuerpo, -altoCuerpo, anchoCuerpo);
	mesh->vVertices.emplace_back(anchoCuerpo, -altoCuerpo, anchoCuerpo);
	mesh->vVertices.emplace_back(anchoCuerpo, -altoCuerpo, -anchoCuerpo);
	mesh->vVertices.emplace_back(-anchoCuerpo, -altoCuerpo, -anchoCuerpo);
	mesh->vVertices.emplace_back(0, -altoCuerpo - altoPicos, 0);


	mesh->vIndices = new GLuint[48];



	GLuint arr[48] = { 0, 1, 4,  4, 1, 2,  2, 3, 4,

		3, 0, 4,  0, 5, 1,  5, 6, 1,  1, 6, 7,  7, 2, 1,  2, 7, 8,  2, 8, 3,  3, 8, 5,  

		3, 5, 0,  5, 9, 6,  6, 9, 7,  7, 9, 8,  8, 9, 5
	};

	for (int i = 0; i < mesh->nNumIndices; i++) {
		mesh->vIndices[i] = arr[i];
	}

	mesh->buildNormalVectors();


	return mesh;
}

#pragma endregion

#pragma endregion


#pragma region IndexMesh



void IndexMesh::render() const
{
	if (vVertices.size() > 0 ) { // transfer data

		// Comandos OpenGL para enviar datos de arrays a GPU
		// Nuevos comandos para la tabla de índices

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

		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
	
		if (vIndices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
		}

		draw();

		// Comandos OpenGL para deshabilitar datos enviados
		// Nuevo comando para la tabla de índices :
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void IndexMesh::draw() const
{
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndices);

}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble w)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 8;
	mesh->nNumIndices = 36;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vNormals.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-w, w, w);
	mesh->vVertices.emplace_back(-w, -w, w);
	mesh->vVertices.emplace_back(w, w, w);
	mesh->vVertices.emplace_back(w, -w, w);

	mesh->vVertices.emplace_back(w, w, -w);
	mesh->vVertices.emplace_back(w, -w, -w);
	mesh->vVertices.emplace_back(-w, w, -w);
	mesh->vVertices.emplace_back(-w, -w, -w);

	mesh->vIndices = new GLuint[36];


	
	GLuint arr[36] = { 0, 1, 2, 1, 3, 2, 2, 3, 4,

	3, 5, 4, 4, 5, 6, 5, 7, 6,

		//diagonal como el resto en la cara lateral izquierda

		//6, 7, 0, 7, 1, 0,

		//diagonal al contrario del resto en la cara lateral izquierda

		0, 6, 1, 6, 7, 1,

		0, 2, 4, 4, 6, 0, 1, 5, 3, 1, 7, 5
	};
	

	for (int i = 0; i < mesh->nNumIndices; i++) {
		mesh->vIndices[i] = arr[i];
	}

	/*
	
	mesh->vIndices[0] = 0;
	mesh->vIndices[1] = 4;
	mesh->vIndices[2] = 5;

	mesh->vIndices[3] = 5;
	mesh->vIndices[4] = 1;
	mesh->vIndices[5] = 0;

	
	mesh->vIndices[6] = 6;
	mesh->vIndices[7] = 2;
	mesh->vIndices[8] = 1;

	mesh->vIndices[9] = 6;
	mesh->vIndices[10] = 1;
	mesh->vIndices[11] = 5;

	mesh->vIndices[12] = 1;
	mesh->vIndices[13] = 3;
	mesh->vIndices[14] = 0;

	mesh->vIndices[15] = 2;
	mesh->vIndices[16] = 3;
	mesh->vIndices[17] = 1;

	mesh->vIndices[18] = 7;
	mesh->vIndices[19] = 4;
	mesh->vIndices[20] = 0;

	mesh->vIndices[21] = 0;
	mesh->vIndices[22] = 3;
	mesh->vIndices[23] = 7;

	mesh->vIndices[24] = 5;
	mesh->vIndices[25] = 4;
	mesh->vIndices[26] = 7;

	mesh->vIndices[27] = 6;
	mesh->vIndices[28] = 5;
	mesh->vIndices[29] = 7;

	mesh->vIndices[30] = 2;
	mesh->vIndices[31] = 7;
	mesh->vIndices[32] = 3;
	
	mesh->vIndices[33] = 6;
	mesh->vIndices[34] = 7;
	mesh->vIndices[35] = 2;

	*/

	/*
	for (int i = 0; i < 8; i++) {
		mesh->vNormals.emplace_back(1, 1, 1, 1);
	}
	*/

	mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBoxTexture(GLdouble l)
{
	
	IndexMesh* m = generateIndexedBox(l);

	m->vTexCoords.reserve(m->mNumVertices);


	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(1, 1);
	m->vTexCoords.emplace_back(1, 0);

	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(1, 1);
	m->vTexCoords.emplace_back(1, 0);

	return m;


}

void IndexMesh::buildNormalVectors()
{
	
	for (int i = 0; i < mNumVertices; i++) {
		vNormals.push_back(dvec3(0, 0, 0));
	}
	
	for (int i = 0; i < nNumIndices/3; i++) {

		dvec3 n;
		dvec3 v0 = vVertices[vIndices[(i*3)]];
		dvec3 v1 = vVertices[vIndices[((i * 3)+1)]];
		dvec3 v2 = vVertices[vIndices[((i * 3)+2)]];
		
		n = normalize(cross((v2 - v1), (v0 - v1)));

		vNormals[vIndices[(i * 3)]] += n;
		vNormals[vIndices[(i * 3) +1]] += n;
		vNormals[vIndices[(i * 3) +2]] += n;
	}


	for (int i = 0; i < mNumVertices; i++) {
		vNormals[i] = glm::normalize(vNormals[i]);
	}
}


#pragma endregion



MbR::MbR(int m, int n, glm::dvec3* perfil)
	:m(m),n(n), perfil(perfil)
{


}

MbR* MbR::generaIndexMbR(int mm, int nn, glm::dvec3* perfil)
{

	MbR* mesh = new MbR(mm, nn, perfil);

	// Definir la primitiva como GL_TRIANGLES
	mesh->mPrimitive = GL_TRIANGLES;
	// Definir el número de vértices como nn*mm
	mesh->mNumVertices = nn * mm;

	mesh->vNormals.reserve(mesh->nNumIndices);

	// Usar un vector auxiliar de vértices	
	dvec3 * vs = new dvec3 [mesh->mNumVertices];

	for (int i = 0; i < nn; i++) {
		// Generar la muestra i- ésima de vértices
		GLdouble theta = i * (360.0 / nn);
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));
		for (int j = 0; j < mm; j++) {
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			vs[i*(mm) + j] = dvec3(x, perfil[j].y, z);
		}

	}

	//volcar vertices
	mesh->vVertices.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices;i++) {
		mesh->vVertices.push_back( vs[i]);
	}

	int indiceMayor = 0;

	mesh->nNumIndices = nn * (mm - 1) * 6;

	mesh->vIndices = new GLuint[mesh->nNumIndices];

	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn; i++) {
		// El contador j recorre los vértices del perfil ,
		// de abajo arriba . Las caras cuadrangulares resultan
		// al unir la muestra i- ésima con la (i +1)% nn - ésima
		for (int j = 0; j < mm - 1; j++) {
			// El contador indice sirve para llevar cuenta
			// de los índices generados hasta ahora . Se recorre
			// la cara desde la esquina inferior izquierda
			int indice = i * mm + j;
			// Los cuatro índices son entonces :
			//indice, (indice + mm) % (nn * mm), (indice + mm + 1) % (nn * mm), indice + 1

			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;

			
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice + 1;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
		}
	}

	mesh->buildNormalVectors();


	delete vs;

	vs = nullptr;

	return mesh;
}

MbR* MbR::generaIndexMbR(int mm, int nn, GLdouble anglesRot, glm::dvec3* perfil)
{

	MbR* mesh = new MbR(mm, nn, perfil);

	// Definir la primitiva como GL_TRIANGLES
	mesh->mPrimitive = GL_TRIANGLES;
	// Definir el número de vértices como nn*mm
	mesh->mNumVertices = nn * mm;

	// Usar un vector auxiliar de vértices	
	dvec3* vs = new dvec3[mesh->mNumVertices];

	for (int i = 0; i < nn; i++) {
		// Generar la muestra i- ésima de vértices
		GLdouble theta = i * (anglesRot / (nn - 1));
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));
		for (int j = 0; j < mm; j++) {
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			vs[i * (mm)+j] = dvec3(x, perfil[j].y, z);
		}

	}

	//volcar vertices
	mesh->vVertices.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vVertices.push_back(vs[i]);
	}

	int indiceMayor = 0;

	mesh->nNumIndices = (nn - 1) * (mm - 1) * 6;

	mesh->vIndices = new GLuint[mesh->nNumIndices];

	mesh->vNormals.reserve(mesh->nNumIndices);

	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn - 1; i++) {
		// El contador j recorre los vértices del perfil ,
		// de abajo arriba . Las caras cuadrangulares resultan
		// al unir la muestra i- ésima con la (i +1)% nn - ésima
		for (int j = 0; j < mm - 1; j++) {
			// El contador indice sirve para llevar cuenta
			// de los índices generados hasta ahora . Se recorre
			// la cara desde la esquina inferior izquierda
			int indice = i * mm + j;
			// Los cuatro índices son entonces :
			//indice, (indice + mm) % (nn * mm), (indice + mm + 1) % (nn * mm), indice + 1

			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;


			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice + 1;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
		}
	}

	mesh->buildNormalVectors();


	delete vs;

	vs = nullptr;

	return mesh;
}

