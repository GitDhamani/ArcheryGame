#include "target.h"
#include <QGraphicsScene>
#include "mainwindow.h"
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QPropertyAnimation>

extern MainWindow* ptr;

Target::Target(QObject* parent): QObject(parent)
{
    setPixmap(QPixmap(":/Images/Target.png"));
    scale = 0.5;
    setScale(scale);
    setPos(ptr->scene->width()/2-boundingRect().width()*scale,-ptr->scene->height()/2
           + (ptr->scene->height()-boundingRect().height()*scale)/2);
    collidingRect = new QGraphicsRectItem(this);
    collidingRect->setPen(QPen(Qt::NoPen));
    collidingRect->setRect(0,0,25,boundingRect().height()-20);
    collidingRect->setBrush(QBrush(Qt::NoBrush));
    collidingRect->setPos(boundingRect().width()*7/8,10);
    name = "target";
}

void Target::shiftTarget()
{
    int from = -ptr->scene->height()/2;
    int to = ptr->scene->height()/2 - this->boundingRect().height()*scale;
    int randomheight;
    do
    {
    randomheight = QRandomGenerator::global()->bounded(from, to);
    } while (abs(scenePos().y()-randomheight) < 60);

    shiftpos = new QPropertyAnimation(this, "ypos", this);
    shiftpos->setStartValue(scenePos().y());
    shiftpos->setEndValue(randomheight);
    shiftpos->setEasingCurve(QEasingCurve::InOutQuad);
    shiftpos->setDuration(500);
    shiftpos->start();
    ptr->bow->readyToFire = false;

    connect(shiftpos, &QPropertyAnimation::finished, [=](){
        ptr->bow->readyToFire = true;
    });
}

qreal Target::ypos() const
{
    return m_ypos;
}

void Target::setYpos(qreal newYpos)
{
    if (qFuzzyCompare(m_ypos, newYpos))
        return;
    setPos(ptr->scene->width()/2-boundingRect().width()*scale,newYpos);
    m_ypos = newYpos;
    ptr->bow->arrow->shiftArrow(newYpos);
}
