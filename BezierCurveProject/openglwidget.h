#pragma once

#include <QWidget>
#include "ui_openglwidget.h"

class OpenGLWidget : public QWidget
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = Q_NULLPTR);
	~OpenGLWidget();

private:
	Ui::OpenGLWidget ui;
};
