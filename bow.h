#ifndef BOW_H
#define BOW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "arrow.h"
#include <QPropertyAnimation>

class Bow: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal fade1 READ fade1 WRITE setFade1)
    Q_PROPERTY(qreal fade2 READ fade2 WRITE setFade2)

public:
    Bow(QObject* parent);
    void startMotion();
    void fireBow();
    void resetBow();
    Arrow* arrow;
    Arrow* prevArrow;
    bool readyToFire;
    int deltay;
    int prevspeed;
    QTimer* motion;
    void Restart();
    QTimer* restart;
    QGraphicsPixmapItem* GameOver;
    float scale;

    qreal fade1() const;
    void setFade1(qreal newFade1);

    qreal fade2() const;
    void setFade2(qreal newFade2);

private:

    qreal m_fade1;
    qreal m_fade2;
};

#endif // BOW_H
