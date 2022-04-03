#pragma once

#include <iostream>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_4_Core>
#include "shader.h"
#include "mesh.h"
#include "curve.h"

class OpenGLPatch : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
	Q_OBJECT

public:
	OpenGLPatch(QWidget *parent = Q_NULLPTR);
	~OpenGLPatch();

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
	vector<glm::vec3> _controlPointsList;
	Curve* _curve1, *_curve2, *_curve3, *_curve4;
	vector<glm::vec3> test1;
};
