#ifndef KEYCONTROLLER_H
#define KEYCONTROLLER_H
#include <QHash>
#include "controller.h"

class KeyController : public Controller
{
public:
    KeyController();

    bool keyPressed(int key);

    void advance();
private:

    QHash<int,Ts::TaikoState> acceptKeys_;
};

#endif // KEYCONTROLLER_H
