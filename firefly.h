#ifndef FIREFLY_H
#define FIREFLY_H

#include <QObject>
#include <QGraphicsItem>

class QPropertyAnimation;

class FireFly : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_PROPERTY(qreal radius READ radius WRITE setRadius)
public:
    FireFly(QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *) override;
    qreal radius() { return m_radius; }
    void setRadius(qreal r) { m_radius = r; update(); }
    void nudge();
    void refresh();
    void setShowClock(bool checked) { m_showClock = checked; }

protected:
    void advance(int phase) override;
    bool collidesWithItem(const QGraphicsItem *other,
                          Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const override;

private:
    qreal m_radius = 0;
    qreal m_angle = 0;
    qreal m_speed = 0;
    qreal m_time = 0;
    bool m_showClock = false;
    QPropertyAnimation *m_animation;

signals:
    void blink();
};

#endif // FIREFLY_H
