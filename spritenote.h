#ifndef _SPRITENOTE__
#define _SPRITENOTE__

class SpriteNote  //each one of these is a note to the graphics engine
                  //telling it what to draw where.
{
    private:
    
    public:
    int sprite;
    int x, y;
    float pitch;
    float roll;
    float yaw;
    SpriteNote(int sx, int sy, int ssprite);
    SpriteNote(int sx, int sy, float npitch, float nroll, float nyaw, int ssprite);
    ~SpriteNote();
    
    int getX();
    void setX(int newx);
    
    int getY();
    void setY(int newy);
    
    float getPitch();
    void setPitch(float npitch);
    
    float getRoll();
    void setRoll(float nroll);
    
    float getYaw();
    void setYaw(float nyaw);
    
    int getSprite();
    void setSprite(int newsprite);
};

#endif
