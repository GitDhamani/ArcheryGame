#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Target: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal ypos READ ypos WRITE setYpos)

public:
    Target(QObject* parent);
    void shiftTarget();
    qreal ypos() const;
    void setYpos(qreal newYpos);
    float scale;
    QPropertyAnimation* shiftpos;
    QString name;
    QGraphicsRectItem* collidingRect;

private:
    qreal m_ypos;
};

#endif // TARGET_H
