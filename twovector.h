#ifndef _TWOVECTOR__
#define _TWOVECTOR__

class TwoVector
{
    private:
    double x, y;

    public:
    TwoVector();
    TwoVector(double sx, double xy);
    ~TwoVector();
    double getLength();
    TwoVector normalize(); //normalized THIS vector and returns new vector
    TwoVector scale(double scaler); //scales THIS vector and returns new vector
    
    double getX();
    void setX(double newx);
    
    double getY();
    void setY(double newy);
};


#endif
