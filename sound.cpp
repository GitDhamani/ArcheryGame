#include "sound.h"
#include "mainwindow.h"
#include <QGraphicsSceneWheelEvent>

extern MainWindow* ptr;

Sound::Sound(QObject* parent): QObject(parent)
{
    setPixmap(QPixmap(":/Images/Speaker4.ico"));

    setPos(-245, 203);
    setScale(0.33);
    setTransformationMode(Qt::SmoothTransformation);
}

void Sound::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!ptr->volshow)
    {
    vol = new Volume(ptr->scene);
    ptr->volshow = true;
    }
    else
    {
        ptr->scene->removeItem((QGraphicsItem*)(ptr->volptr));
        delete vol;
        ptr->volshow = false;
    }
}

void Sound::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if (event->delta() > 0)
    {
        if(vol->topy < 102)
            return;
        vol->topy-=vol->volincrement;
        vol->rect2.setCoords(vol->topx, vol->topy, vol->topx+10, 202);
        vol->volrect->setRect(vol->rect2);
    }
    else
    {

        if(vol->topy > 200)
            return;
        vol->topy+=vol->volincrement;
        vol->rect2.setCoords(vol->topx, vol->topy, vol->topx+10, 202);
        vol->volrect->setRect(vol->rect2);
    }

    ptr->soundOn = 200 - vol->topy;
}
