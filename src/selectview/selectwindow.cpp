
#include "selectwindow.h"
#include "ui_selectwindow.h"
#include <QDebug>
#include <QKeyEvent>

SelectWindow::SelectWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectWindow)
{
    ui->setupUi(this);

    //ui->graphicsView->installEventFilter(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    canvas_ = new SelectCanvas;
    scene->addItem(canvas_);
    canvas_->grabKeyboard();

    for (int i = 0;i < 100;i ++)
    {
        SelectItem *item  = canvas_->addItem();
        item->setTitle(QString("item %1").arg(i));
        item->setIndex(i+1);
        item->setTotal(100);
        item->setCatagory(QString("catagory %1").arg(i / 10));
    }
}

SelectWindow::~SelectWindow()
{
    delete ui;
}

void SelectWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    QRectF rect = ui->graphicsView->rect().adjusted(0,0,-10,-10);
    //chart_->setBoundingRect(rect);
    ui->graphicsView->setSceneRect(rect);
    canvas_->setRect(rect);
    canvas_->move(0);
}

void SelectWindow::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
}

bool SelectWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        this->keyPressEvent(dynamic_cast<QKeyEvent*>(event));
        return true;
    }
    else
    {
        return QWidget::eventFilter(obj,event);
    }
}
