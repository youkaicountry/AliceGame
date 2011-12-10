#ifndef _SPRITENOTE__
#define _SPRITENOTE__

class SpriteNote  //each one of these is a note to the graphics engine
                  //telling it what to draw where.
{
    private:
    int x, y;
    int sprite;
    
    public:
    SpriteNote(int sx, int sy, int ssprite);
    ~SpriteNote();
    
    int getX();
    void setX(int newx);
    
    int getY();
    void setY(int newy);
    
    int getSprite();
    void setSprite(int newsprite);
};

#endif
