#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    openglWidget = new OpenGLWidget(this);
    openglWidget->resize(openglWidget->sizeHint());
    openglWidget->setFocus();

    setCentralWidget(openglWidget);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // press space to open/reset the bezier curve simulation
	if (event->key() == Qt::Key_Space)
	{
        if (_curveScreen)
        {
            _curveScreen = false;
            openglPatch = new OpenGLPatch(this);
            openglPatch->resize(openglPatch->sizeHint());
            openglPatch->setFocus();

            setCentralWidget(openglPatch);
        }
        else
        {
            _curveScreen = true;
            openglWidget = new OpenGLWidget(this);
            openglWidget->resize(openglWidget->sizeHint());
            openglWidget->setFocus();

            setCentralWidget(openglWidget);
        }
        
	}

    /*if (event->key() == Qt::Key_R)
    {
        if (!_curveScreen)
        {
            openglPatch->randomize();
        }
    }*/

}