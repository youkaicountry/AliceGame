#ifndef _STAR__
#define _STAR__

class Star
{
    public:
       Star(double sx, double sy, double sz);
       ~Star();
       
       void update(double relvel);  //the physics simulation for the star
       
       double getX();
       void setX(double newx);
       
       double getY();
       void setY(double newy);
       
       double getZ();
       void setZ(double newz);
       
       int getSprite();
       void setSprite(int newsprite);
       
       
       
    private:
        double x, y, z;
        int sprite;
        
        
};

#endif
