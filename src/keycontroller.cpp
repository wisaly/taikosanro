#include "keycontroller.h"

KeyController::KeyController()
{
    acceptKeys_[Qt::Key_F] = Ts::DON_LEFT;
    acceptKeys_[Qt::Key_J] = Ts::DON_RIGHT;
    acceptKeys_[Qt::Key_D] = Ts::KA_LEFT;
    acceptKeys_[Qt::Key_K] = Ts::KA_RIGHT;
}

bool KeyController::keyPressed(int key)
{
    if (!acceptKeys_.contains(key))
        return false;

    state_ |= acceptKeys_[key];

    return true;
}

void KeyController::advance()
{
    if (state_ != 0)
    {
        emit hit((Ts::TaikoState)state_);
        state_ = 0;
    }
}
