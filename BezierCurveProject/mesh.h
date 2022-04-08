#pragma once

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "shader.h"
#include "camera.h"

// vertex struct that totally could be a class in this project
// -----------------------------------------------------------
struct Vertex {
	glm::vec3 pos;
	//glm::vec3 normal;
	//glm::vec2 texCoords;
};

// mesh class
// ----------
class Mesh : public QOpenGLFunctions_4_4_Core
{
public:
	// constructors
	// ------------
	Mesh::Mesh(std::vector<Vertex>* vertices, unsigned int numVertices);

	Mesh::Mesh(std::vector<Vertex>* vertices, std::vector<unsigned int> indices);

	void setupMesh();

	// mesh drawing method
	// -------------------
	void Draw(Shader* shader);

	void Mesh::DrawPolygon(Shader* shader);

	void Mesh::DrawTriangle(Shader* shader);

	// destructor
	// ----------
	virtual ~Mesh();

	// compute mesh triangles of the surface
	// -------------------------------------
	void Mesh::meshCompute();

	std::vector<Vertex>*       _vertices;
	std::vector<unsigned int> _indices;
	bool _destroyed = false;
protected:
private:

	Mesh(const Mesh& other);

	void operator=(const Mesh& other);

	enum
	{
		POSITION_VB,	// pos in vertex buffer
		NUM_BUFFERS		// number of buffers
	};

	// mesh Vertex Array Object
	GLuint _VAO;
	// mesh Vertex Buffer Object
	GLuint _VBO[NUM_BUFFERS];
	unsigned int _drawCount;
};

#endif // MESH_H