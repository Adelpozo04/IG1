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
		mesh->vVertices.emplace_back(r* cos(glm::radians(i*angle)), r* sin(glm::radians( i*angle)), 0.0);
		//mesh->vColors.emplace_back(1.0, 1.0, 0.0, 1.0);
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


	return mesh;
}

#pragma endregion

#pragma endregion


#pragma region IndexMesh



void IndexMesh::render() const
{
}

void IndexMesh::draw() const
{
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
	IndexMesh* iMesh = new IndexMesh();


	return iMesh;
}


#pragma endregion
