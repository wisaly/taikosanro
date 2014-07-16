#include <QKeyEvent>
#include <QTime>
#include <QGLWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "measure.h"
#include "note.h"
#include "notecanvas.h"
#include "notechart.h"
#include "determineresult.h"
#include "taikoitem.h"
#include "../notefileparser.h"
#include "../song.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::TextAntialiasing);
    //ui->graphicsView->setViewport(new QGLWidget);

    NoteCanvas *canvas = new NoteCanvas();
    scene->addItem(canvas);
    canvas->setPos(200,50);

    TaikoItem *taikoItem = new TaikoItem;
    scene->addItem(taikoItem);
    taikoItem->setPos(0,42);
    taikoItem->connect(&keyController_,SIGNAL(hit(Ts::TaikoState)),SLOT(hit(Ts::TaikoState)));


    Song *song = new Song("../res/example.tja");
    song->parser().parse(Ts::ONI);
    chart_ = song->getChart(Ts::ONI);
    chart_->setParentItem(canvas);
    chart_->setBoundingRect(canvas->boundingRect());
    chart_->connect(&keyController_,SIGNAL(hit(Ts::TaikoState)),SLOT(hit(Ts::TaikoState)));

    determine_ = new DetermineResult();
    scene->addItem(determine_);
    determine_->connect(chart_,SIGNAL(determined(Ts::DetermineValue)),SLOT(determined(Ts::DetermineValue)));

    connect(&timer_,SIGNAL(timeout()),SLOT(timeout()));
    timer_.setTimerType(Qt::PreciseTimer);
    timer_.start(1000 / 60);

    fpsTimer_.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat())
    {
        if (event->key() == Qt::Key_Space)
        {
            qDebug() << "play";
            chart_->play();
            return;
        }
        else if (keyController_.keyPressed(event->key()))
        {
            return;
        }
        else if (event->key() == Qt::Key_Q)
        {
            determine_->determined(Ts::GREAT);
            return;
        }
    }

    event->ignore();
    QWidget::keyPressEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    QRectF rect = ui->graphicsView->rect().adjusted(0,0,-10,-10);
    //chart_->setBoundingRect(rect);
    ui->graphicsView->setSceneRect(rect);
}

void MainWindow::timeout()
{
    if (fpsTimer_.elapsed() >= 1000)
    {
        setWindowTitle(QString("time-%1 fps-%2").arg(QTime::currentTime().toString("hh:mm:ss")).arg(fpsCount_));
        fpsCount_ = 0;
        fpsTimer_.start();
    }
    fpsCount_++;
    ui->graphicsView->scene()->advance();
    keyController_.advance();
}
