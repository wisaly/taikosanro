#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QElapsedTimer>
#include <QWidget>
#include <QTimer>
#include "../keycontroller.h"
#include "../stable.h"

namespace Ui {
class MainWindow;
}

class NoteChart;
class DetermineResult;
class HitLight;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent * event);

signals:
public slots:
    void timeout();
    void testhit(Ts::TaikoState state);

private:
    Ui::MainWindow *ui;
    NoteChart *chart_;
    DetermineResult *determine_;
    QTimer timer_;
    QElapsedTimer fpsTimer_;
    int fpsCount_;
    KeyController keyController_;
    HitLight *hitLight_;
};

#endif // MAINWINDOW_H
