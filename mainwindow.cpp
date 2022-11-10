#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "startbutton.h"
#include "bow.h"
#include "target.h"
#include "view.h"
#include "score.h"
#include <QGraphicsSimpleTextItem>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include "sound.h"


MainWindow* ptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Set up Window Dimensions and UI
    ui->setupUi(this);
    ptr = this;
    ui->statusbar->hide();
    ui->menubar->hide();
    setWindowTitle("Archery Game");
    setFixedSize(1020, 520);

    //Initialisation
    hasGameStarted = false;
    numArrows = 20;
    prevcount = 20;
    soundOn = 50;
    volshow = 0;

    //Set up Graphics Scene and Coordinate System
    scene = new QGraphicsScene(this);
    scene->setSceneRect(-500,-250, 1000, 500);

    //Add Start Button
    startButton = new StartButton(this);
    scene->addItem(startButton);

    //Add Bow
    bow = new Bow(this);
    scene->addItem(bow);

    //Add Target
    target = new Target(this);
    scene->addItem(target);

    //Add Title Text
    QGraphicsPixmapItem* title = new QGraphicsPixmapItem;
    title->setPixmap(QPixmap(":/Images/NewTitle.png"));
    title->setPos(-title->boundingRect().width()/2,-scene->height()/2 + 5);
    scene->addItem(title);

    //Add Score
    score = new Score(this);
    scene->addItem(score);

    //Add Arrow Count
    setArrowCount();

    //Connect Scene to View and Show
    view = new View(this);
    view->setScene(scene);
    ui->verticalLayout->addWidget(view);
    view->setRenderHint(QPainter::Antialiasing);

    //Start Pressed
    connect(startButton, &StartButton::startGame, this, &MainWindow::startGame);

    //Handle Mouse Fire
    connect(view, &View::mouseFire, bow, &Bow::fireBow);

    //Starting Sound
    QMediaPlayer* player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/Images/Strike2.wav"));
    player->setVolume(5);
    player->setPlaybackRate(1.5);
    player->play();

    //Add Sound Icon
    Sound* sound = new Sound(this);
    scene->addItem(sound);

    //Last Arrow Notification
    LastArrow = new QGraphicsPixmapItem;
    LastArrow->setPixmap(QPixmap(":/Images/LastArrow.png"));
    LastArrow->setPos(-155, 197);
    ptr->scene->addItem(LastArrow);
    LastArrow->setOpacity(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setArrowCount()
{
    int deltax = 0;
    for (int i =0; i< numArrows; i++)
    {
        arrows << new QGraphicsPixmapItem(QPixmap(":/Images/UpArrow.png"));
        scene->addItem(arrows[i]);
        arrows[i]->setPos(-200 + deltax,200);
        deltax += 20;
    }

}

void MainWindow::updateArrowCount()
{
    if (numArrows == prevcount)
        return;

    for (int i =0; i< prevcount; i++)
    {
        delete arrows[i];
    }

    arrows.clear();
    prevcount = numArrows;
    if (numArrows == 1)
        LastArrow->setOpacity(1);
    else
        LastArrow->setOpacity(0);

    if (numArrows == 0)
        ptr->bow->readyToFire = false;

    int deltax = 0;
    for (int i =0; i< numArrows; i++)
    {
        arrows << new QGraphicsPixmapItem(QPixmap(":/Images/UpArrow.png"));
        scene->addItem(arrows[i]);
        arrows[i]->setPos(-200 + deltax,200);
        deltax += 20;
    }
}

void MainWindow::startGame()
{
    hasGameStarted = true;
    bow->readyToFire = true;
    bow->startMotion();
    scene->removeItem(startButton);
    score->score = 0;
    score->updateScore();
    bow->GameOver->setOpacity(0);
}

