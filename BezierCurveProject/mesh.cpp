#include "mesh.h"
#include <iostream>

// mesh constructor for curve
// --------------------------
Mesh::Mesh(std::vector<Vertex>* vertices, unsigned int numVertices)
{
    initializeOpenGLFunctions();

    _vertices = vertices;
    _drawCount = numVertices;

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    std::vector<float> data;
    for (Vertex v : *vertices) {
        data.push_back(v.pos.x);
        data.push_back(v.pos.y);
        data.push_back(v.pos.z);
    }

    glGenBuffers(NUM_BUFFERS, _VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);
}

// mesh constructor for surface
// ----------------------------
Mesh::Mesh(std::vector<Vertex>* vertices, std::vector<unsigned int> indices)
{
    initializeOpenGLFunctions();

    _vertices = vertices;
    _indices = indices;
    _drawCount = indices.size();

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    std::vector<float> data;
    for (Vertex v : *vertices) {
        data.push_back(v.pos.x);
        data.push_back(v.pos.y);
        data.push_back(v.pos.z);
    }
    glGenBuffers(NUM_BUFFERS, _VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO[POSITION_VB]);
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
	glDeleteVertexArrays(1, &_VAO);
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    std::vector<float> data;
    for (Vertex v : *_vertices) {
        data.push_back(v.pos.x);
        data.push_back(v.pos.y);
        data.push_back(v.pos.z);
    }
    glGenBuffers(NUM_BUFFERS, _VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);
}

// mesh drawing method
// -------------------
void Mesh::Draw(Shader* shader)
{
    shader->Bind();

	glBindVertexArray(_VAO);

    glColor3ub(0, 0, 0);
	glDrawArrays(GL_LINES, 0, _drawCount);

	glBindVertexArray(0);
    shader->Unbind();
}

void Mesh::DrawPolygon(Shader* shader)
{
    shader->Bind();

    glBindVertexArray(_VAO);

    glColor3ub(0, 0, 0);
    glDrawArrays(GL_LINE_STRIP, 0, _drawCount);

    glBindVertexArray(0);
    shader->Unbind();
}

void Mesh::DrawTriangle(Shader* shader)
{
    shader->Bind();
    glBindVertexArray(_VAO);

    glColor3ub(0, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, _drawCount);

    glBindVertexArray(0);
    shader->Unbind();
}

void Mesh::meshCompute()
{
    _indices.clear();
    for (int i = 1; i < _drawCount; i++)
    {
        for (int j = 0; j < _drawCount - 1; j++)
        {
            _indices.push_back(i * _drawCount + j);
            _indices.push_back(i * (_drawCount - 1) + j);
            _indices.push_back(i * (_drawCount - 1) + (j+1));
        }
    }
}