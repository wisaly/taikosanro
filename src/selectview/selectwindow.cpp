#include "selectwindow.h"
#include "ui_selectwindow.h"

SelectWindow::SelectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectWindow)
{
    ui->setupUi(this);
}

SelectWindow::~SelectWindow()
{
    delete ui;
}
