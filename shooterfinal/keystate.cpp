#include "keystate.h"

KeyState::KeyState()
{
    //for(int x=0; x< sizeof(irr::EKEY_CODE); x++) keys[x] = false;
    keydown = false;
    keyup = false;
    keyz = false;
    keyx = false;
    keyesc = false;
    keyleft = false;
    keyright = false;
    keyshift = false;
    return;
}

KeyState::~KeyState()
{
    return;
}

bool KeyState::isUp()
{
    return keyup;
}

bool KeyState::isDown()
{
    return keydown;
}

bool KeyState::isLeft()
{
    return keyleft;
}

bool KeyState::isRight()
{
    return keyright;
}

bool KeyState::isZ()
{
    return keyz;
}

bool KeyState::isX()
{
    return keyx;
}

bool KeyState::isEsc()
{
    return keyesc;
}

bool KeyState::isShift()
{
   return keyshift;
}

void KeyState::setUp(bool newup)
{
    keyup = newup;
}

void KeyState::setDown(bool newdown)
{
    keydown = newdown;
}

void KeyState::setLeft(bool newleft)
{
    keyleft = newleft;
}

void KeyState::setRight(bool newright)
{
    keyright = newright;
}

void KeyState::setZ(bool newz)
{
    keyz = newz;
}

void KeyState::setX(bool newx)
{
    keyx = newx;
}

void KeyState::setEsc(bool newesc)
{
    keyesc = newesc;
}

void KeyState::setShift(bool newshift)
{
   keyshift = newshift;
   return;
}

void KeyState::clearKeys()
{
    keyup = false;
    keydown = false;
    keyright = false;
    keyleft = false;
    keyz = false;
    keyright = false;
    keyesc = false;
    keyshift = false;
    return;
}

void updateKeys()
{
    return;
}
