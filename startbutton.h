#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QObject>
#include <QGraphicsRectItem>

class StartButton: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    StartButton(QObject* parent);
    QGraphicsSimpleTextItem* text;
    bool armed;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void startGame();
};

#endif // STARTBUTTON_H
