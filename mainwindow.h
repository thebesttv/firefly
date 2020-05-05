#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "firefly.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
private:
    int m_size;
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    QVector<FireFly*> fireflies;
};

#endif
