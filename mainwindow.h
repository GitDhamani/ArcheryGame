#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "view.h"
#include "bow.h"
#include "target.h"
#include "score.h"
#include "startbutton.h"
#include "volume.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene* scene;
    View* view;
    Bow* bow;
    Target* target;
    bool hasGameStarted;
    Score* score;
    void setArrowCount();
    void updateArrowCount();
    int numArrows;
    int prevcount;
    QVector<QGraphicsPixmapItem*> arrows;
    StartButton* startButton;
    int soundOn;
    QGraphicsPixmapItem* LastArrow;
    bool volshow;
    Volume* volptr;

private:
    Ui::MainWindow *ui;
    void startGame();
};
#endif // MAINWINDOW_H
