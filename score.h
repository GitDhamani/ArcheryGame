#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include <QGraphicsSimpleTextItem>

class Score: public QObject, public QGraphicsSimpleTextItem
{
    Q_OBJECT
public:
    Score(QObject* parent);
    int score;
    void updateScore();
};

#endif // SCORE_H
