#pragma once

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>

// vertex class that totally could be a struct in this project
// -----------------------------------------------------------
class Vertex
{
public:
	Vertex(const glm::vec3& pos)
	{
		this->_pos = pos;
	}
protected:
private:
	glm::vec3 _pos;
};

// mesh class
// ----------
class Mesh : public QOpenGLFunctions_4_4_Core
{
public:
	// constructor
	// -----------
	Mesh(Vertex* vertices, unsigned int numVertices);

	// mesh drawing method
	// -------------------
	void Draw();

	// destructor
	// ----------
	virtual ~Mesh();
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
	GLuint m_VAO;
	// mesh Vertex Buffer Object
	GLuint m_VBO[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif // MESH_H