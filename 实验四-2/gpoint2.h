#ifndef GPOINT2_H
#define GPOINT2_H

template <class T>
class GPoint2
{
public:
    T mX, mY;

public:
    GPoint2()
	{
		mX = mY = 0;
	}
	
	GPoint2(T x, T y)
	{
		mX = x;
		mY = y;
	}
    
    T x() const
    { return mX; }
    
    T y() const
    { return mY; }
    
    void setX(T x)
    { mX = x; }
    
    void setY(T y)
    { mY = y; }
    
    void set(T x, T y)
    { mX = x;   mY = y; }
	
	GPoint2 & operator = (const GPoint2 &other)
	{
		mX = other.mX;
		mY = other.mY;
		return *this;
	}
};

typedef GPoint2<double> GPoint2d;
typedef GPoint2<int> GPoint2i;
typedef GPoint2<float> GPoint2f;

#endif
