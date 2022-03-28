#pragma once

#include <QOpenGLWidget>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "shader.h"
#include "mesh.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = Q_NULLPTR);
	~OpenGLWidget();
protected:
	// OpenGL management
	// -----------------
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
private:
	int _width;
	int _height;
	Shader* _shader;
	Mesh* _mesh;
};
