#include "view.h"
#include "mainwindow.h"
#include <QMouseEvent>

extern MainWindow* ptr;

View::View(QWidget* parent): QGraphicsView(parent)
{
}

void View::mousePressEvent(QMouseEvent *event)
{
    //If the Sound Icon is being clicked, the View shouldn't fire an arrow, instead pass to parent.
    //Which will allow the sound Icon handler to eventually deal with.
    if (QGraphicsItem *item = itemAt(event->pos()))
    {
    QGraphicsView::mousePressEvent(event);
    return;
    }

    if (ptr->volshow)
    {
        ptr->scene->removeItem((QGraphicsItem*)(ptr->volptr));
        delete ptr->volptr;
        ptr->volshow = false;
        return;
    }

    if (ptr->hasGameStarted == false)
    {
        QGraphicsView::mousePressEvent(event);
    }
    else if (event->button() == Qt::LeftButton)
    {
        emit mouseFire();
    }

}
