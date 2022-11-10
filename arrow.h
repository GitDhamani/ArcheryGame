#ifndef ARROW_H
#define ARROW_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMediaPlayer>

class Arrow: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal opacity2 READ opacity2 WRITE setOpacity2)

public:
    Arrow(QObject* parent, int pos);
    ~Arrow();
    QTimer* moveArrow;
    void shiftArrow(int);
    QGraphicsSimpleTextItem* Bullseye;
    QGraphicsSimpleTextItem* Excellent;
    qreal opacity() const;
    void setOpacity(qreal newOpacity);
    QPropertyAnimation* dim;
    QPropertyAnimation* dim2;
    QMediaPlayer* player;
    QTimer* blinkTarget;
    QTimer* blinkFade;

    qreal opacity2() const;
    void setOpacity2(qreal newOpacity2);

private:
    float scale;
    int hitPosition;
    qreal m_opacity;
    qreal m_opacity2;
};

#endif // ARROW_H
