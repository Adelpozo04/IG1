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
	static Mesh* generateWingAdvanceTie(GLdouble w, GLdouble h, GLdouble f);



	Mesh() = default;
	virtual ~Mesh() = default;

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };

	void changePrimitive(GLuint primitive) {
		mPrimitive = primitive;
	}
protected:
	GLuint mPrimitive =
	  GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices; // vertex array
	std::vector<glm::dvec4> vColors;   // color array
	std::vector<glm::dvec2> vTexCoords;
	std::vector<glm::dvec3> vNormals;
	virtual void draw() const;
};



class IndexMesh : public Mesh {
protected:
	GLuint* vIndices = nullptr; // tabla de índices
	GLuint nNumIndices = 0;

public:

	IndexMesh() { mPrimitive = GL_TRIANGLES;
	
		vIndices = new GLuint[36];

	}
	~IndexMesh() { delete[] vIndices; }
	virtual void render() const;
	virtual void draw() const;

	//practica 4
	static IndexMesh* generateIndexedBox(GLdouble l);

private:

	static glm::dvec3 calculateNormals(IndexMesh* mesh);

};

class MbR : public IndexMesh {

public:
	MbR(int m_, int n_, glm::dvec3* perfil_) : n(n_), perfil(perfil_), m(m_) {
	

	
	};
	//~MbR();
	//virtual void render() const;
	//virtual void draw() const;

	static MbR* generaMallaIndexadaPorRevolucion(int mm, int nn, glm::dvec3* perfil);

private:

	int n;
	glm::dvec3* perfil;
	int m;
};


#endif //_H_Scene_H_
