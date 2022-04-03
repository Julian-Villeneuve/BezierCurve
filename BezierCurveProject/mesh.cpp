#include "mesh.h"
#include <iostream>

// mesh constructor
// ----------------
Mesh::Mesh(std::vector<Vertex>* vertices, unsigned int numVertices)
{
    initializeOpenGLFunctions();

    m_drawCount = numVertices;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    std::vector<float> data;
    for (Vertex v : *vertices) {
        data.push_back(v.pos.x);
        data.push_back(v.pos.y);
        data.push_back(v.pos.z);
    }
    glGenBuffers(NUM_BUFFERS, m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);
}

// mesh destructor
// ---------------
Mesh::~Mesh()
{
    _destroyed = true;
	glDeleteVertexArrays(1, &m_VAO);
}

// mesh drawing method
// -------------------
void Mesh::Draw()
{
	glBindVertexArray(m_VAO);

    glColor3ub(0, 0, 0);
	glDrawArrays(GL_LINE_STRIP, 0, m_drawCount);

	glBindVertexArray(0);
}

// control polygon drawing method
// ------------------------------
void Mesh::DrawControl()
{
    glBindVertexArray(m_VAO);

    glColor3ub(255, 0, 0);
    glDrawArrays(GL_LINE_STRIP, 0, m_drawCount);

    glBindVertexArray(0);
}

