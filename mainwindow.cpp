#include "mainwindow.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QAction>
#include <QToolBar>
#include <QCheckBox>
#include <QDebug>

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , m_scene(new QGraphicsScene(this))
    , m_view(new QGraphicsView(m_scene, this))
{
    m_scene->setBackgroundBrush(Qt::black);
    m_scene->setSceneRect(0, 0, 800, 800);
    setCentralWidget(m_view);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            m_scene, &QGraphicsScene::advance);
    timer->start(1000 / 40);

    m_size = 80;
    for(int i = 0; i < m_size; ++i) {
        auto f = new FireFly;
        f->setPos(QRandomGenerator::global()->generateDouble() * 800,
                  QRandomGenerator::global()->generateDouble() * 800);
        m_scene->addItem(f);
        fireflies.push_back(f);
    }

    setMinimumSize(sizeHint());

    QAction *refreshAction = new QAction("refresh");
    connect(refreshAction, &QAction::triggered, this, [this]() {
        for(auto f : fireflies)
            f->refresh();
    });

    QCheckBox *showClock = new QCheckBox("show clock");
    connect(showClock, &QCheckBox::stateChanged, [this](int state) {
        for(auto f : fireflies)
            f->setShowClock(state);
    });

    QToolBar *toolBar = addToolBar("Main ToolBar");
    toolBar->addWidget(showClock);
    toolBar->addAction(refreshAction);
}

MainWindow::~MainWindow()
{

}
