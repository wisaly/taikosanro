#include <QKeyEvent>
#include <QTime>
#include <QGLWidget>
#include "mainwindow.h"
#include "measure.h"
#include "note.h"
#include "notecanvas.h"
#include "notechart.h"
#include "notefileparser.h"
#include "song.h"
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
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        chart_->play();
        event->accept();
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
    chart_->setBoundingRect(rect);
    ui->graphicsView->setSceneRect(rect);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewport(new QGLWidget);
}
