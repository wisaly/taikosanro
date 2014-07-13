#include <QKeyEvent>
#include <QTime>
#include <QGLWidget>
#include <QPropertyAnimation>
#include <QDebug>
#include "mainwindow.h"
#include "measure.h"
#include "note.h"
#include "notecanvas.h"
#include "notechart.h"
#include "determineresult.h"
#include "ui_mainwindow.h"
#include "../notefileparser.h"
#include "../song.h"

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

    Song *song = new Song("../res/example.tja");
    song->parser().parse(Ts::ONI);
    chart_ = song->getChart(Ts::ONI);
    chart_->setParentItem(canvas);
    chart_->connect(this,SIGNAL(hit(Ts::TaikoState)),SLOT(hit(Ts::TaikoState)));
    determine_->connect(chart_,SIGNAL(determined(Ts::DetermineValue)),SLOT(determined(Ts::DetermineValue)));


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
    QMap<int,Ts::TaikoState> keys;
    keys[Qt::Key_F] = Ts::DON_LEFT;
    keys[Qt::Key_J] = Ts::DON_RIGHT;
    keys[Qt::Key_D] = Ts::KA_LEFT;
    keys[Qt::Key_K] = Ts::KA_RIGHT;

    if (event->key() == Qt::Key_Space)
    {
        qDebug() << "play";
        chart_->play();

        event->accept();
    }
    else if (keys.contains(event->key()))
    {
        emit hit(keys[event->key()]);

        event->accept();
    }
    else if (event->key() == Qt::Key_Q)
    {
        determine_->determined(Ts::GREAT);
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
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::TextAntialiasing);
    //ui->graphicsView->setViewport(new QGLWidget);
}
