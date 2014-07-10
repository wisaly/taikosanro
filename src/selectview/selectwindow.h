#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

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

private:
    Ui::SelectWindow *ui;
};

#endif // SELECTWINDOW_H
