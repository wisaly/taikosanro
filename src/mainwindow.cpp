#include <QKeyEvent>
#include <QTime>
#include <QGLWidget>
#include <QPropertyAnimation>
#include "mainwindow.h"
#include "measure.h"
#include "note.h"
#include "notecanvas.h"
#include "notechart.h"
#include "notefileparser.h"
#include "song.h"
#include "determineresult.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    NoteCanvas *canvas = new NoteCanvas();
    scene->addItem(canvas);

    determine_ = new DetermineResult(canvas);

    Song *song = new Song(canvas);
    new NoteFileParser("../res/example.tja",song);
    chart_ = song->chartAt(0);

    startTimer(1000 / 60);
    fpsTimer_.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (fpsTimer_.elapsed() >= 1000)
    {
        setWindowTitle(QString("time-%1 fps-%2").arg(QTime::currentTime().toString("hh:mm:ss")).arg(fpsCount_));
        fpsCount_ = 0;
        fpsTimer_.start();
    }
    fpsCount_++;
    ui->graphicsView->scene()->advance();

    Ts::DetermineValue result = chart_->hitTest(Ts::NO_ACT);
    determine_->showResult(result);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMap<int,Ts::TaikoState> keys;
    keys[Qt::Key_F] = Ts::DON_LEFT;
    keys[Qt::Key_J] = Ts::DON_RIGHT;
    keys[Qt::Key_D] = Ts::KA_LEFT;
    keys[Qt::Key_K] = Ts::KA_RIGHT;

    if (event->key() == Qt::Key_Space)
    {
        chart_->play();

        event->accept();
    }
    else if (keys.contains(event->key()))
    {
        Ts::DetermineValue result = chart_->hitTest(keys[event->key()]);
        determine_->showResult(result);

        event->accept();
    }
    else if (event->key() == Qt::Key_Q)
    {
//        Note *note = new Note(chart_,Note::RedMarker,0);
//        QPropertyAnimation *animation = new QPropertyAnimation(note, "pos");
//        animation->setDuration(1000);
//        animation->setStartValue(QPoint(0,0));
//        animation->setEndValue(QPoint(100,0));

//        animation->start();
    }
    else
    {
        event->ignore();
        QWidget::keyPressEvent(event);
    }
}

void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    QRectF rect = ui->graphicsView->rect().adjusted(0,0,-10,-10);
    //chart_->setBoundingRect(rect);
    ui->graphicsView->setSceneRect(rect);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::TextAntialiasing);
    //ui->graphicsView->setViewport(new QGLWidget);
}
