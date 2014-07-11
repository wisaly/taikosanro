#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include "dirloader.h"
#include "selectcanvas.h"

#include <QWidget>

namespace Ui {
class SelectWindow;
}

class SelectWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SelectWindow(QWidget *parent = 0);
    ~SelectWindow();

    void showEvent(QShowEvent * event);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::SelectWindow *ui;
    SelectCanvas *canvas_;
    DirLoader loader_;
};

#endif // SELECTWINDOW_H
