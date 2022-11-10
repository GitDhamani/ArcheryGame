#include "startbutton.h"
#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QFont>

StartButton::StartButton(QObject* parent): QObject(parent)
{
    setRect(0,0,300,75);
    setPos(-rect().width()/2, -rect().height()/2);
    setPen(QPen(Qt::black, 3));
    setBrush(QBrush(Qt::NoBrush));
    text = new QGraphicsSimpleTextItem(this);
    text->setPos((rect().width() - text->boundingRect().width())/4 + 23,
                 (rect().height() - text->boundingRect().height())/2 - 27);
    text->setText("START");
    text->setPen(QPen(Qt::black));
    text->setFont(QFont("Century Gothic", 30));
    armed = 1;
}

void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (armed)
    emit startGame();
}
