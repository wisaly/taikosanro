#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QElapsedTimer>
#include <QWidget>
#include "stable.h"

namespace Ui {
class MainWindow;
}

class NoteChart;
class DetermineResult;
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);

signals:
    void hit(Ts::TaikoState state);
public slots:

private:
    Ui::MainWindow *ui;
    NoteChart *chart_;
    DetermineResult *determine_;
    QElapsedTimer fpsTimer_;
    int fpsCount_;
};

#endif // MAINWINDOW_H
