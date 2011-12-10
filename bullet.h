#ifndef _BULLET__
#define _BULLET__

class Bullet
{
    private:
        double x, y;
        double xaccel, yaccel;
        double xvel, yvel;
        double radius;
        int sprite;
        bool arclengthrotation; //use real distance, or just angle for rotation
        double rcenterx, rcentery;
        double rvel;
        double raccel;
        double radialaccel;
        double radialvel;
        double damage; 
        
    public:
        Bullet(double sx, double sy, double sxaccel, double syaccel, 
               double sxvel, double syvel, double sradius, double sdamage, int ssprite); //for non rotating
        
        Bullet(double sx, double sy, double sxaccel, double syaccel,
               double sxvel, double syvel, bool sarclengthrotation,
               double srcenterx, double srcentery, double rvel, double sraccel,
               double sradialaccel, double sradialvel,
               double sradius,double damage, int ssprite); //for rotating
        ~Bullet();
        
        double oldx, oldy;
        double effvelx, effvely;
        
        double getX();
        void setX(double newx);
        
        double getY();
        void setY(double newy);
        
        double getXVel();
        void setXVel(double newxvel);
        
        double getYVel();
        void setYVel(double newyvel);
        
        double getXAccel();
        void setXAccel(double newxaccel);
        
        double getYAccel();
        void setYAccel(double newyaccel);
        
        double getRotationCenterX();
        void setRotationCenterX(double newrcenterx);
        
        double getRotationCenterY();
        void setRotationCenterY(double newrcentery);
        
        bool getArcLengthRotation();
        void setArcLengthRotation(bool newarclengthrotation);
        
        double getRotationalVelocity();
        void setRotationalVelocity(double newrvel);
        
        double getRotationalAcceleration();
        void setRotationalAcceleration(double newraccel);
        
        double getRadialAcceleration();
        void setRadialAcceleration(double newradaccel);
        
        double getRadialVelocity();
        void setRadialVelocity(double newradvel);
        
        double getRadius();
        void setRadius(double newradius);
        
        int getSprite();
        void setSprite(int newsprite);
        
        double getDamage();
        void setDamage(double newdamage);
        
        
        void update(); //updates the bullet via a physics loop
}; 

#endif
