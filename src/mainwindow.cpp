#include <QKeyEvent>
#include "mainwindow.h"
#include "measure.h"
#include "note.h"
#include "notecanvas.h"
#include "notechart.h"
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

    chart_ = new NoteChart(canvas);
    chart_->setBoundingRect(ui->graphicsView->rect());

    NoteTypeList notes;
    notes << Note::RedMarker
          << Note::RedMarker
          << Note::BlueMarker
          << Note::BlueMarker
          << Note::RedMarker
          << Note::RedMarker
          << Note::BlueMarker
          << Note::BlueMarker
          << Note::Blank
          << Note::Blank
          << Note::Blank
          << Note::Blank;

    chart_->createMeasure(notes,100,4,3);

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
        startTimer(1000 / 60);
        chart_->play();
        event->accept();
    }
    else
    {
        event->ignore();
        QWidget::keyPressEvent(event);
    }
}
