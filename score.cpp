#include "score.h"
#include <QFont>
#include "mainwindow.h"

extern MainWindow* ptr;

Score::Score(QObject* parent): QObject(parent)
{
    score = 0;
    setFont(QFont("Arial", 50, 10));
    setPen(QPen(Qt::red));
    setBrush(QBrush(Qt::red));
    setText(QString::number(score));
    setPos(-boundingRect().width()/2,-ptr->scene->height()/2 + 60);
}

void Score::updateScore()
{
    setText(QString::number(score));
    setPos(-boundingRect().width()/2,-ptr->scene->height()/2 + 60);
}
