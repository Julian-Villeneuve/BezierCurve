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
