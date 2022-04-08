#pragma once

#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include "openglwidget.h"
#include "openglpatch.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

    void MainWindow::keyPressEvent(QKeyEvent* event);
private:
    Ui::MainWindowClass ui;
    OpenGLWidget* openglWidget;
    OpenGLPatch* openglPatch;
    bool _curveScreen = true;
    QStackedWidget* stackedWidget;
};
