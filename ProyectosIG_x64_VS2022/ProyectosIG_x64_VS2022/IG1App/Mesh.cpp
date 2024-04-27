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

		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());

		}



		if (vTexCoords.size() > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());

		}


		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
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

	//a�adir otra vez el segundo verice(primero sin contar el centro)
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


Mesh* Mesh::generateWingAdvanceTie(GLdouble w, GLdouble h, GLdouble f) {

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 8;

	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	//posiciones de los puntos
	vector<glm::vec3> points;
	points.reserve(8);

	points.emplace_back(w, 3 * h / 4, -f/2);
	points.emplace_back(0, 3 * h / 4, -f / 2);
	points.emplace_back(w, h/2, 0);
	points.emplace_back(0, h/2, 0);

	points.emplace_back(w, -h / 2, 0);
	points.emplace_back(0, -h / 2, 0);
	points.emplace_back(w, -3 * h / 4, -f / 2);
	points.emplace_back(0, -3 * h / 4, -f / 2);

	mesh->vVertices.push_back(points[0]);
	mesh->vVertices.push_back(points[1]);
	mesh->vVertices.push_back(points[2]);
	mesh->vVertices.push_back(points[3]);
	mesh->vVertices.push_back(points[4]);
	mesh->vVertices.push_back(points[5]);
	mesh->vVertices.push_back(points[6]);
	mesh->vVertices.push_back(points[7]);

	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vColors.emplace_back(1.0, 1.0, 1.0, 0.5);
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

//INDEXMESH

void IndexMesh::render() const {
	// Comandos OpenGL para enviar datos de arrays a GPU
	 	Mesh::render();
	// Nuevos comandos para la tabla de �ndices
		if (vIndices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
		}

		
	// Comandos OpenGL para deshabilitar datos enviados
	// Nuevo comando para la tabla de �ndices :
		glDisableClientState(GL_INDEX_ARRAY);
}

// Comando para renderizar la malla indexada enviada
void IndexMesh::draw() const {
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndices);
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble w) {

	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 8;
	mesh->nNumIndices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);


	//posiciones de los puntos
	vector<glm::vec3> points;
	points.reserve(8);

	mesh->vVertices.emplace_back(-w, w, w);
	mesh->vVertices.emplace_back(-w, -w, w);
	mesh->vVertices.emplace_back(w, w, w);
	mesh->vVertices.emplace_back(w, -w, w);

	mesh->vVertices.emplace_back(w, w, -w);
	mesh->vVertices.emplace_back(w, -w, -w);
	mesh->vVertices.emplace_back(-w, w, -w);
	mesh->vVertices.emplace_back(-w, -w, -w);

	for (int i = 0; i < 8; ++i) {

		mesh->vNormals.push_back({ 0, 0, 0 });

	}

	GLuint vIndices[] = { 0, 1, 2, 1, 3, 2, 2, 3, 4, 
		3, 5, 4, 4, 5, 6, 5, 7, 6,
		0, 6, 1, 6, 7, 1,
		0, 2, 4, 4, 6, 0, 1, 5, 3, 1, 7, 5
	};

	mesh->vIndices[0] = 0;
	mesh->vIndices[1] = 1;
	mesh->vIndices[2] = 2;

	mesh->vIndices[3] = 1;
	mesh->vIndices[4] = 3;
	mesh->vIndices[5] = 2;

	mesh->vIndices[6] = 2;
	mesh->vIndices[7] = 3;
	mesh->vIndices[8] = 4;



	mesh->vIndices[9] = 3;
	mesh->vIndices[10] = 5;
	mesh->vIndices[11] = 4;

	mesh->vIndices[12] = 4;
	mesh->vIndices[13] = 5;
	mesh->vIndices[14] = 6;

	mesh->vIndices[15] = 5;
	mesh->vIndices[16] = 7;
	mesh->vIndices[17] = 6;



	mesh->vIndices[18] = 6;
	mesh->vIndices[19] = 7;
	mesh->vIndices[20] = 0;

	mesh->vIndices[21] = 7;
	mesh->vIndices[22] = 1;
	mesh->vIndices[23] = 0;



	mesh->vIndices[24] = 0;
	mesh->vIndices[25] = 2;
	mesh->vIndices[26] = 4;

	mesh->vIndices[27] = 4;
	mesh->vIndices[28] = 6;
	mesh->vIndices[29] = 0;


	mesh->vIndices[30] = 1;
	mesh->vIndices[31] = 5;
	mesh->vIndices[32] = 3;

	mesh->vIndices[33] = 1;
	mesh->vIndices[34] = 7;
	mesh->vIndices[35] = 5;

	
	for (int i = 0; i < mesh->nNumIndices / 3; i++) {

		dvec3 n;

		dvec3 v0 = mesh->vVertices[mesh->vIndices[(i * 3)]];
		dvec3 v1 = mesh->vVertices[mesh->vIndices[(i * 3) + 1]];
		dvec3 v2 = mesh->vVertices[mesh->vIndices[(i * 3) + 2]];

		n = glm::normalize(glm::cross((v2 - v1), (v0 - v1)));

		mesh->vNormals[vIndices[(i * 3)]] += n;
		mesh->vNormals[vIndices[(i * 3) + 1]] += n;
		mesh->vNormals[vIndices[(i * 3) + 2]] += n;
	}

	for (int i = 0; i < mesh->mNumVertices; i++) {
		mesh->vNormals[i] = glm::normalize(mesh->vNormals[i]);
	}
	

	for (int i = 0; i < 36; ++i) {
		mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	}

	return mesh;

}

MbR* MbR::generaMallaIndexadaPorRevolucion(int mm, int nn, glm::dvec3* perfil) {
	 
	MbR* mesh = new MbR(mm, nn, perfil);
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->mNumVertices = nn * mm;
	mesh->nNumIndices = nn * (mm - 1) * 6;
	mesh->vIndices = new GLuint[mesh->nNumIndices];

	dvec3* vs = new dvec3 [mesh->mNumVertices ];

	for (int i = 0; i < nn; i++) {
		// Generar la muestra i- �sima de v�rtices
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));
		for (int j = 0; j < mm; j++) {
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			vs[i * mm + j] = dvec3(x, perfil[j].y, z);
		}
	}

	for (int i = 0; i < mesh->mNumVertices; ++i) {

		mesh->vVertices.push_back(vs[i]);

		mesh->vColors.push_back({ 1.0, 0.0, 0.0, 1.0 });

	}

	for (int i = 0; i < mesh->nNumIndices; ++i) {

		mesh->vNormals.push_back({ 0, 0, 0 });

	}
	
	int indiceMayor = 0;
	
	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn; i++) {
		// El contador j recorre los v�rtices del perfil ,
		// de abajo arriba . Las caras cuadrangulares resultan
		// al unir la muestra i- �sima con la (i +1)% nn - �sima
		
		for (int j = 0; j < mm - 1; j++) {
			// El contador indice sirve para llevar cuenta
						// de los �ndices generados hasta ahora . Se recorre
						// la cara desde la esquina inferior izquierda

			int indice = i * mm + j;

			mesh-> vIndices[indiceMayor] = indice;
			indiceMayor++;
			mesh-> vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			mesh-> vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice + 1;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
		}

	}

	// Los cuatro �ndices son entonces :
	//indice, (indice + mm) % (nn * mm), (indice + mm + 1) % (nn * mm), indice + 1;

	for (int i = 0; i < mesh->nNumIndices / 3; i++) {

		dvec3 n;

		dvec3 v0 = mesh->vVertices[mesh->vIndices[(i * 3)]];
		dvec3 v1 = mesh->vVertices[mesh->vIndices[(i * 3) + 1]];
		dvec3 v2 = mesh->vVertices[mesh->vIndices[(i * 3) + 2]];

		n = glm::normalize(glm::cross((v2 - v1), (v0 - v1)));

		mesh->vNormals[mesh->vIndices[(i * 3)]] += n;
		mesh->vNormals[mesh->vIndices[(i * 3) + 1]] += n;
		mesh->vNormals[mesh->vIndices[(i * 3) + 2]] += n;
	}

	for (int i = 0; i < mesh->nNumIndices; i++) {
		mesh->vNormals[i] = glm::normalize(mesh->vNormals[i]);
	}


	return mesh;

}
