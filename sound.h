#ifndef SOUND_H
#define SOUND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "volume.h"

class Sound: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Sound(QObject* parent);
    Volume* vol;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
};

#endif // SOUND_H
