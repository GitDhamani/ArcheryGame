#include "bow.h"
#include <QGraphicsScene>
#include "mainwindow.h"
#include <QTimer>
#include "arrow.h"
#include <QGraphicsPixmapItem>

extern MainWindow* ptr;

Bow::Bow(QObject* parent): QObject(parent)
{
    setPixmap(QPixmap(":/Images/BowLoaded.png"));
    scale = 0.4;
    setScale(scale);
    setPos(-ptr->scene->width()/2,-ptr->scene->height()/2
           + (ptr->scene->height()-boundingRect().height()*scale)/2);
    GameOver = new QGraphicsPixmapItem();
    GameOver->setOpacity(0);
    GameOver->setPixmap(QPixmap(":/Images/GameOver.png"));
    GameOver->setScale(0.5);
    GameOver->setPos(-GameOver->boundingRect().width()*0.5/2, 100);
    ptr->scene->addItem(GameOver);

    //Set initial speed for the motion
    deltay = -3;

    readyToFire = true;
    prevArrow = nullptr;
    prevspeed = -3;

    motion = new QTimer(this);
    motion->setInterval(10);

    restart = new QTimer(this);
    restart->setInterval(200);
    restart->setSingleShot(true);

    QPropertyAnimation* Fadeout = new QPropertyAnimation(this, "fade1", this);
    Fadeout->setStartValue(1);
    Fadeout->setEndValue(0);
    Fadeout->setEasingCurve(QEasingCurve::Linear);
    Fadeout->setDuration(1000);

    QPropertyAnimation* Fadein = new QPropertyAnimation(this, "fade2", this);
    Fadein->setStartValue(0);
    Fadein->setEndValue(1);
    Fadein->setEasingCurve(QEasingCurve::InOutQuad);
    Fadein->setDuration(600);

    connect(restart, &QTimer::timeout, this, [=](){
        ptr->startButton->armed = false;
        ptr->hasGameStarted = false;
        Fadeout->start();

        connect(Fadeout, &QPropertyAnimation::finished, [=](){
            Restart();
            Fadein->start();

            connect(Fadein, &QPropertyAnimation::finished, [=](){
                ptr->startButton->armed = true;

            });

        });
    });


}

void Bow::startMotion()
{
    motion->start();
    connect(motion, &QTimer::timeout, [=](){
       if(scenePos().y() < -ptr->scene->height()/2)
           deltay = -deltay;

     if(scenePos().y() > ptr->scene->height()/2 - (boundingRect().height()*scale))
            deltay = -deltay;
     this->moveBy(0,deltay);
    });
}

void Bow::fireBow()
{
    if (readyToFire)
    {
    setPixmap(QPixmap(":/Images/BowEmpty.png"));
    if(prevArrow != nullptr)
    delete prevArrow;
    arrow = new Arrow(ptr->bow, scenePos().y());
    prevArrow = arrow;
    ptr->scene->removeItem(ptr->target);
    ptr->scene->addItem(prevArrow);
    ptr->scene->addItem(ptr->target);
    readyToFire = false;
    }
}

void Bow::resetBow()
{
    setPixmap(QPixmap(":/Images/BowLoaded.png"));
    readyToFire = true;
    ptr->numArrows--;
    ptr->updateArrowCount();
}

void Bow::Restart()
{
        motion->stop();
        delete motion;
        motion = new QTimer(this);
        motion->setInterval(10);
        ptr->target->shiftpos->stop();

        //reset the Bow's position
        setPos(-ptr->scene->width()/2,-ptr->scene->height()/2
               + (ptr->scene->height()-boundingRect().height()*scale)/2);

        //reset the target's position
        ptr->target->setPos(ptr->scene->width()/2-ptr->target->boundingRect().width()*ptr->target->scale,-ptr->scene->height()/2
               + (ptr->scene->height()-ptr->target->boundingRect().height()*ptr->target->scale)/2);

        //remove previous Arrow
        ptr->scene->removeItem(prevArrow);

        deltay = -3;
        prevspeed = -3;
        readyToFire = false;
        ptr->hasGameStarted = false;
        ptr->startButton->setOpacity(0);
        ptr->scene->addItem(ptr->startButton);
        ptr->startButton->text->setText("Try Again");
        ptr->startButton->text->setPos((ptr->startButton->rect().width() - ptr->startButton->text->boundingRect().width())/3 + 21,
                     (ptr->startButton->rect().height() - ptr->startButton->text->boundingRect().height())/2 - 4);
        ptr->numArrows = 20;
        ptr->updateArrowCount();

}

qreal Bow::fade1() const
{
    return m_fade1;
}

void Bow::setFade1(qreal newFade1)
{
    m_fade1 = newFade1;
    setOpacity(newFade1);
    ptr->target->setOpacity(newFade1);
    if (newFade1 < 0.34)
        ptr->scene->removeItem(prevArrow);
}

qreal Bow::fade2() const
{
    return m_fade2;
}

void Bow::setFade2(qreal newFade2)
{
    m_fade2 = newFade2;
    setOpacity(newFade2);
    ptr->target->setOpacity(newFade2);
    ptr->startButton->setOpacity(newFade2);
    GameOver->setOpacity(newFade2);
}
