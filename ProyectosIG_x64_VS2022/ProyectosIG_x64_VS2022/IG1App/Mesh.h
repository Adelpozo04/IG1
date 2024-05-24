#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <vector>

class Mesh
{
public:
	//practica 1
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh
	static Mesh* generateRegularPolygon(GLuint num, GLdouble r); //creates a regular polygon
	static Mesh* generateTriangleRGB(GLdouble r); //creates a triangleRGB
	static Mesh* generateRectangle(GLdouble w, GLdouble h);
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h);
	static Mesh* generateCube(GLdouble longitud);

	//practica 2
	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h);
	static Mesh* generaRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generateBoxOutline(GLdouble length);
	static Mesh* generateBoxOutlineTexCor(GLdouble longitud);
	static Mesh* generateBoxOutlineTexCorTransparent(GLdouble longitud);
	static Mesh* generateStar3D(GLdouble re, GLuint np, GLdouble h);
	static Mesh* generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h);

	//practica 4
	static Mesh* generateWingAdvancedTIE(GLdouble radius, GLdouble width);

	//examen Pruebas

	static Mesh* generatePiramid(GLdouble h, GLdouble w);
	static Mesh* generatePiramidTexCord(GLdouble h, GLdouble w);

	static Mesh* generateRomboidTriangular(GLdouble h, GLdouble w, GLdouble th);
	static Mesh* generateRomboidTriangularTexCord(GLdouble h, GLdouble w, GLdouble th);


	Mesh() = default;
	virtual ~Mesh() = default;

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
	std::vector<glm::dvec3> const& normals() const { return vNormals; };

	void changePrimitive(GLuint primitive) {
		mPrimitive = primitive;
	}
protected:
	GLuint mPrimitive =
	  GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices; // vertex array
	std::vector<glm::dvec4> vColors;   // color array
	std::vector<glm::dvec3> vNormals;   // normals array
	std::vector<glm::dvec2> vTexCoords;
	virtual void draw() const;
};




class IndexMesh : public Mesh {

protected:
	GLuint* vIndices = nullptr; // tabla de índices
	GLuint nNumIndices = 0;

public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] vIndices; }

	virtual void render() const;
	virtual void draw() const;

	IndexMesh(const IndexMesh& m) = delete;            // no copy constructor
	IndexMesh& operator=(const IndexMesh& m) = delete; // no copy assignment


	static IndexMesh* generateIndexedBox(GLdouble l);

	void buildNormalVectors();

};


class MbR : public IndexMesh {

protected:

	int n;//, para el número de muestras que se toman al girar el perfil alrededor del eje Y
	glm::dvec3* perfil;//para el array de vértices que define el perfil que va a hacerse girar alrededor del eje Y
	int m;//para el número de puntos del perfil
		
public:

	MbR(int m,int n , glm::dvec3* perfil);


	static MbR* generaIndexMbR(int mm, int mn, glm::dvec3* perfil);


};

#endif //_H_Scene_H_
