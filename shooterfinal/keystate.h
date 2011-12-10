#ifndef _KEYSTATE__
#define _KEYSTATE__
//#include <irrlicht.h>
class KeyState
{
    private:
    //bool keys[sizeof(irr::EKEY_CODE)] ;     
        
    bool keyup;
    bool keydown;
    bool keyright;
    bool keyleft;
    bool keyz;
    bool keyx;
    bool keyesc;
    bool keyshift;
    
    public:
    KeyState();
    ~KeyState();    
        
    bool isUp();
    bool isDown();
    bool isRight();
    bool isLeft();
    bool isZ();
    bool isX();
    bool isEsc();
    bool isShift();

    void setUp(bool newup);
    void setDown(bool newdown);
    void setLeft(bool newleft);
    void setRight(bool newright);
    void setZ(bool newz);
    void setX(bool newx);
    void setEsc(bool newesc);
    void setShift(bool newshift);
    
    void clearKeys();
    void updateKeys();
};
#endif
