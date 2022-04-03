#pragma once

#include <QtWidgets/QMainWindow>
#include "openglwidget.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
private:
    Ui::MainWindowClass ui;
    OpenGLWidget* openglWidget;
};
