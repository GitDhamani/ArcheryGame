#include "arrow.h"
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QGraphicsSimpleTextItem>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include "target.h"
#include <QTimer>

extern MainWindow* ptr;

Arrow::Arrow(QObject* parent, int pos): QObject(parent)
{
    setPixmap(QPixmap(":/Images/Arrow.png"));
    scale = 0.4;
    setScale(scale);
    setPos(-ptr->scene->width()/2,  ptr->bow->scenePos().y() + ptr->bow->boundingRect().height()*ptr->bow->scale/2);


    if (ptr->soundOn > 0)
    {
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/Images/Fire2.wav"));
    player->setVolume(ptr->soundOn);
    player->setPlaybackRate(1);
    player->play();
    }

    moveArrow = new QTimer(this);
    moveArrow->setInterval(10);
    moveArrow->start();

    Bullseye = new QGraphicsSimpleTextItem();
    Bullseye->setText("BullsEye!");
    Bullseye->setFont(QFont("Arial", 50, 10));
    Bullseye->setPen(QPen(Qt::red));
    Bullseye->setBrush(QBrush(QColor("#a60053")));
    Bullseye->setPos(-Bullseye->boundingRect().width()/2,
           -Bullseye->boundingRect().height()/2 - 50);
    ptr->scene->addItem(Bullseye);
    Bullseye->setOpacity(0);

    Excellent = new QGraphicsSimpleTextItem();
    Excellent->setText("Excellent!");
    Excellent->setFont(QFont("Arial", 50, 10));
    Excellent->setPen(QPen(Qt::blue));
    Excellent->setBrush(QBrush(Qt::blue));
    Excellent->setPos(-Excellent->boundingRect().width()/2,
           -Excellent->boundingRect().height()/2 - 50);
    ptr->scene->addItem(Excellent);
    Excellent->setOpacity(0);

    //Bullseye Text
    dim = new QPropertyAnimation(this, "opacity", this);
    dim->setStartValue(1);
    dim->setEndValue(0);
    dim->setEasingCurve(QEasingCurve::InOutQuad);
    dim->setDuration(500);

    //Excellent Text
    dim2 = new QPropertyAnimation(this, "opacity2", this);
    dim2->setStartValue(1);
    dim2->setEndValue(0);
    dim2->setEasingCurve(QEasingCurve::InOutQuad);
    dim2->setDuration(500);

    //blink target
    blinkTarget = new QTimer(this);
    blinkTarget->setInterval(100);

    //blink fade
    blinkFade = new QTimer(this);
    blinkFade->setInterval(800);
    blinkFade->setSingleShot(true);

    connect(dim, &QPropertyAnimation::finished, [=](){
        delete Bullseye;
    });

    connect(dim2, &QPropertyAnimation::finished, [=](){
        delete Excellent;
    });

    connect(moveArrow, &QTimer::timeout, [=](){
         moveBy(75,0);
        if(scenePos().x() > ptr->width()/2)
        {
            moveArrow->stop();
            ptr->bow->resetBow();
        }

        QList<QGraphicsItem*> list = collidingItems();

            if (list.count()!=0)
            {
                Target* targetptr = dynamic_cast<Target*>(list[0]);
                if (targetptr)
            {
                if (ptr->soundOn > 0)
                {
                player->setMedia(QUrl("qrc:/Images/Strike2.wav"));
                player->setVolume(ptr->soundOn*0.5);
                player->setPlaybackRate(1.5);
                player->play();
                }
                moveBy(25,0);
                moveArrow->stop();
                ptr->bow->resetBow();


                //this->setParent(ptr->target);
                hitPosition = scenePos().y() - ptr->target->scenePos().y();
                if (hitPosition >= 95 && hitPosition <= 115)
                {
                    if(ptr->bow->scenePos().y() <
                            ptr->scene->height()/2 - (ptr->bow->boundingRect().height()*scale))
                    if(ptr->bow->scenePos().y() > -ptr->scene->height()/2)

                    {
                         int randomspeed;
                    do
                    {
                        randomspeed = QRandomGenerator::global()->bounded(3,6);
                    } while(randomspeed == ptr->bow->prevspeed);

                    if (ptr->bow->deltay < 0)
                    ptr->bow->deltay = randomspeed * -1;
                    if (ptr->bow->deltay > 0)
                    ptr->bow->deltay = randomspeed;
                    ptr->bow->prevspeed = randomspeed;
                    }
                }

                ptr->target->shiftTarget();
                if (hitPosition >= 100 && hitPosition <= 108)
                {
                    ptr->score->score +=10;
                    ptr->score->updateScore();
                    dim->start();
                    ptr->numArrows+=2;
                    ptr->updateArrowCount();

                    if (ptr->soundOn>0)
                    {
                    player->setMedia(QUrl("qrc:/Images/Bullseye3.wav"));
                    player->setVolume(ptr->soundOn*0.4);
                    player->setPlaybackRate(1);
                    player->play();

                    //ptr->target->setPixmap(QPixmap(":/Images/Target2.png"));
                    blinkTarget->start();
                    blinkFade->start();
                    int blink = 0;
                    connect(blinkTarget, &QTimer::timeout, [=]() mutable{
                        if (blink)
                        {
                        ptr->target->setPixmap(QPixmap(":/Images/Target.png"));
                        blink = 0;
                        } else
                        {
                        blink = 1;
                        ptr->target->setPixmap(QPixmap(":/Images/Target2.png"));
                        }
                    });

                    connect(blinkFade, &QTimer::timeout, [=](){
                        blinkTarget->stop();
                        ptr->target->setPixmap(QPixmap(":/Images/Target.png"));
                    });



                    }

                }

                if (hitPosition >= 95 && hitPosition < 100)
                {
                    ptr->score->score+=5;
                    ptr->score->updateScore();
                    dim2->start();
                }

                if (hitPosition > 108 && hitPosition <= 115)
                {
                    ptr->score->score+=5;
                    ptr->score->updateScore();
                    dim2->start();
                }
            }
            }

            if(ptr->numArrows == 0)
            ptr->bow->restart->start();

    });
}

Arrow::~Arrow()
{
    blinkTarget->stop();
    blinkFade->stop();
    ptr->target->setPixmap(QPixmap(":/Images/Target.png"));
}

void Arrow::shiftArrow(int val)
{
    setPos(scenePos().x(),val + hitPosition);
}

qreal Arrow::opacity() const
{
    return m_opacity;
}

void Arrow::setOpacity(qreal newOpacity)
{
    m_opacity = newOpacity;
    Bullseye->setOpacity(newOpacity);
}

qreal Arrow::opacity2() const
{
    return m_opacity2;
}

void Arrow::setOpacity2(qreal newOpacity2)
{
    m_opacity2 = newOpacity2;
    Excellent->setOpacity(newOpacity2);
}
