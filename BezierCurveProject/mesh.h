#pragma once

#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>

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
	// constructor
	// -----------
	Mesh::Mesh(std::vector<Vertex>* vertices, unsigned int numVertices);

	// mesh drawing method
	// -------------------
	void Draw();

	void Mesh::DrawControl();

	// destructor
	// ----------
	virtual ~Mesh();

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
	GLuint m_VAO;
	// mesh Vertex Buffer Object
	GLuint m_VBO[NUM_BUFFERS];
	unsigned int m_drawCount;
};

#endif // MESH_H