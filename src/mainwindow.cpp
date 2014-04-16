#include "mainwindow.h"
#include "note.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    scene->addItem(new Note(Note::RedMarker));
    Note *n = new Note(Note::RedMarker);
    scene->addItem(n);
    n->setPos(10,0);
    n = new Note(Note::BlueMarker);
    scene->addItem(n);
    n->setPos(20,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
