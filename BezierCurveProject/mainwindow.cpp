#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    openglWidget = new OpenGLWidget(this);
    openglWidget->resize(openglWidget->sizeHint());
    //openglWidget->setFocus();

    setCentralWidget(openglWidget);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // press C to open/reset the bezier curve simulation
	if (event->key() == Qt::Key_C)
	{
        openglWidget = new OpenGLWidget(this);
        openglWidget->resize(openglWidget->sizeHint());
        //openglWidget->setFocus();

        setCentralWidget(openglWidget);
	}
    
    // press P to open/reset the bezier patch simulation
    if (event->key() == Qt::Key_P)
	{
        openglPatch = new OpenGLPatch(this);
        openglPatch->resize(openglPatch->sizeHint());
        //openglPatch->setFocus();

        setCentralWidget(openglPatch);
	}
}