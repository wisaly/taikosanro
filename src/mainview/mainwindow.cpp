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
#include "hitlight.h"
#include "comboitem.h"
#include "combobubble.h"
#include "hitbubble.h"
#include "scoreboard.h"
#include "soulgauge.h"
#include "../notefileparser.h"
#include "../song.h"
#include "../pixmapnumber.h"
#include "../pixmapmanager.h"

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

    hitLight_ = new HitLight();
    hitLight_->setPos(PixmapManager::getPos(Ts::mv::HITLIGHT_POS));
    hitLight_->setCourse(Ts::ONI);
    scene->addItem(hitLight_);

    NoteCanvas *canvas = new NoteCanvas();
    scene->addItem(canvas);
    canvas->setPos(PixmapManager::getPos(Ts::mv::CANVAS_POS));

    Song *song = new Song("../res/example.tja");
    song->parser().parse(Ts::ONI);
    chart_ = song->getChart(Ts::ONI);
    chart_->setParentItem(canvas);
    chart_->setBoundingRect(canvas->boundingRect());
    chart_->connect(&keyController_,SIGNAL(hit(Ts::TaikoState)),SLOT(hit(Ts::TaikoState)));

    TaikoItem *taikoItem = new TaikoItem;
    scene->addItem(taikoItem);
    taikoItem->setPos(PixmapManager::getPos(Ts::mv::TAIKO_POS));
    taikoItem->connect(&keyController_,SIGNAL(hit(Ts::TaikoState)),SLOT(hit(Ts::TaikoState)));

    ComboItem *comboNumber = new ComboItem;
    scene->addItem(comboNumber);
    comboNumber->setPos(PixmapManager::getPos(Ts::mv::COMBO_POS));
    comboNumber->connect(chart_->score(),SIGNAL(comboChanged(int)),SLOT(comboChanged(int)));

    HitBubble *hitBubble = new HitBubble;
    scene->addItem(hitBubble);
    hitBubble->setPos(PixmapManager::getPos(Ts::mv::BUBBLE_POS));
    hitBubble->connect(chart_->score(),SIGNAL(consecutiveChanged(int)),SLOT(consecutiveChanged(int)));

    ComboBubble *comboBubble = new ComboBubble;
    scene->addItem(comboBubble);
    comboBubble->setPos(PixmapManager::getPos(Ts::mv::BUBBLE_POS));
    comboBubble->connect(chart_->score(),SIGNAL(comboChanged(int)),SLOT(comboChanged(int)));

    ScoreBoard *scoreBoard = new ScoreBoard;
    scene->addItem(scoreBoard);
    scoreBoard->setPos(PixmapManager::getPos(Ts::mv::SCOREBOARD_POS));
    scoreBoard->connect(chart_->score(),SIGNAL(scoreAdded(int)),SLOT(scoreAdded(int)));
    scoreBoard->connect(chart_->score(),SIGNAL(scoreChanged(int)),SLOT(scoreChanged(int)));

    SoulGauge *soulGauge = new SoulGauge;
    scene->addItem(soulGauge);
    soulGauge->setCourse(Ts::ONI);
    soulGauge->setPos(PixmapManager::getPos(Ts::mv::SOULGAUGE_POS));
    soulGauge->connect(chart_->score(),SIGNAL(soulChanged(int)),SLOT(soulChanged(int)));

    determine_ = new DetermineResult();
    scene->addItem(determine_);
    determine_->connect(chart_,SIGNAL(determined(Ts::DetermineValue)),SLOT(determined(Ts::DetermineValue)));
    hitLight_->connect(chart_,SIGNAL(determined(Ts::DetermineValue)),SLOT(determined(Ts::DetermineValue)));

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
        else if (event->key() == Qt::Key_E)
        {
            hitLight_->determined(Ts::GREAT);
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
    keyController_.advance();
    ui->graphicsView->scene()->advance();
}

void MainWindow::testhit(Ts::TaikoState state)
{
    if ((state & Ts::DON_BOTH) == Ts::DON_BOTH ||
            (state & Ts::KA_BOTH) == Ts::KA_BOTH)
    {
        determine_->determined(Ts::GREAT);
    }
    else if ((state & Ts::DON_BOTH) || (state & Ts::KA_BOTH))
    {
        determine_->determined(Ts::GOOD);
    }
}
