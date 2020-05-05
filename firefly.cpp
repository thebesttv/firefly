#include "firefly.h"
#include <QTimer>
#include <QPainter>
#include <QGradient>
#include <QDebug>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QGraphicsScene>

FireFly::FireFly(QObject *parent)
    : QObject(parent)
{
    m_time = QRandomGenerator::global()->bounded(800);
    m_animation = new QPropertyAnimation(this, "radius");
    m_animation->setDuration(400);
    m_animation->setKeyValueAt(0, 0);
    m_animation->setKeyValueAt(0.2, 40);
    m_animation->setKeyValueAt(1, 0);
    m_speed = 2.5;
}

QRectF FireFly::boundingRect() const
{
    return QRectF(-50, -50, 100, 100);
}

void FireFly::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    if(m_showClock) {
        painter->setPen(QPen(Qt::white, 2));
        painter->drawEllipse(QPointF(0, 0), 20, 20);

        // draw clock hand
        painter->save();
        painter->rotate(360 * m_time / 800);
        painter->drawLine(0, 0, 0, -20);
        painter->restore();
    }

    QColor centralColor(Qt::yellow);
    QColor borderColor(0, 0, 0, 0); // fully transparent
    QRadialGradient radialGrad(QPointF(0, 0), m_radius);
    radialGrad.setColorAt(0, centralColor);
    radialGrad.setColorAt(1, borderColor);

    // draw flash
    painter->setPen(Qt::NoPen);
    painter->setBrush(radialGrad);
    painter->drawEllipse(QPointF(0, 0), m_radius, m_radius);
}

void FireFly::nudge()
{
    // <b> most important </b>
    m_time += m_time * 0.018;
}

void FireFly::refresh()
{
    m_time = QRandomGenerator::global()->bounded(800);
}

void FireFly::advance(int phase)
{
    if(phase == 0) {
        m_time += 20;
        if(m_time >= 800)
            for(auto p : scene()->collidingItems(this)) {
                static_cast<FireFly*>(p)->nudge();
            }
        return;
    }

    m_angle += 0.5 - QRandomGenerator::global()->generateDouble();
    double dx = m_speed * ::cos(m_angle);
    double dy = m_speed * ::sin(m_angle);
    double x = pos().x() + dx, y = pos().y() + dy;
    if(x < -40)
        x += scene()->width();
    else if(x > scene()->width() + 40)
        x -= scene()->width();
    if(y < -40)
        y += scene()->height();
    else if(y > scene()->height() + 40)
        y -= scene()->height();

    setPos(x, y);
//    setPos(mapToScene(dx, dy));

    if(m_time >= 800) {
        m_animation->start();
        m_time = 0;
    }
    update();
}

bool FireFly::collidesWithItem(const QGraphicsItem *other,
                               Qt::ItemSelectionMode) const
{
    qreal dx = pos().x() - other->pos().x();
    qreal dy = pos().y() - other->pos().y();
    qreal dis = dx * dx + dy * dy;
    return dis <= 200 * 200;
}
