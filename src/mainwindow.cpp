#include <QKeyEvent>
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
    NoteFileParser *parser = new NoteFileParser("../res/example.tja",song);
    chart_ = song->chartAt(0);

    startTimer(1000 / 60);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
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
    QRectF rect = ui->graphicsView->rect().adjusted(0,0,-100,-10);
    chart_->setBoundingRect(rect);
    ui->graphicsView->setSceneRect(rect);
}
