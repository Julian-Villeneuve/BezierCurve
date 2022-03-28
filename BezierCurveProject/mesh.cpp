#include "mesh.h"

// mesh constructor
// ----------------
Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	initializeOpenGLFunctions();

	m_drawCount = numVertices;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(NUM_BUFFERS, m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

// mesh destructor
// ---------------
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
}

// mesh drawing method
// -------------------
void Mesh::Draw()
{
	glBindVertexArray(m_VAO);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}