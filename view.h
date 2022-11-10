#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>

class View: public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget* parent);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void mouseFire();
};

#endif // VIEW_H
