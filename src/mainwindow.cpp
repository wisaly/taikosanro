#include "mainwindow.h"
#include "measure.h"
#include "note.h"
#include "notecanvas.h"
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
    Measure *m = new Measure(canvas,notes,0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
