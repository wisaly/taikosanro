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

    NoteChart *n = new NoteChart(canvas);
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
          << Note::Blank
          << Note::RedMarker
          << Note::RedMarker
          << Note::BlueMarker
          << Note::BlueMarker
          << Note::RedMarker
          << Note::RedMarker
          << Note::BlueMarker
          << Note::BlueMarker;

    n->createMeasure(notes,100,4,4);

    startTimer(1000);
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
