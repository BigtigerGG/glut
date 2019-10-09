#ifndef GRECT2_H
#define GRECT2_H

#include "gpoint2.h"

template <class T>
class GRect2 
{
protected:
	GPoint2<T> mPoints[2];

public:
	GRect2()
	{
		mPoints[0].set(0, 0);
		mPoints[1].set(0, 0);
	}

	GRect2(T x0, T y0, T x1, T y1)
	{
		mPoints[0].set(x0, y0);
		mPoints[1].set(x1, y1);
	}

	GRect2(const GRect2<T> &other)
	{
		*this = other;
	}

	GRect2<T> & operator = (const GRect2<T> &other)
	{
		mPoints[0] = other.mPoints[0];
		mPoints[1] = other.mPoints[1];
		return *this;
	}

	operator const GPoint2<T> * () const
	{ return mPoints; }

	operator GPoint2<T> * ()
	{ return mPoints; }

	T width() const			
	{ return mPoints[1].x() - mPoints[0].x(); }

	T height() const			
	{ return mPoints[1].y() - mPoints[0].y(); }

	T x0()	const				{ return mPoints[0].x(); }
	T y0()	const				{ return mPoints[0].y(); }
	T x1()	const				{ return mPoints[1].x(); }
	T y1()	const				{ return mPoints[1].y(); }
	GPoint2<T> leftTop() const		{ return mPoints[0]; }
	GPoint2<T> rightBottom() const	{ return mPoints[1]; }

	void setX0(T x)
	{ mPoints[0].setX(x); }
	void setY0(T y)
	{ mPoints[0].setY(y); }
	void setX1(T x)
	{ mPoints[1]. setX(x); }
	void setY1(T y)
	{ mPoints[1].setY(y); }

	void setLeftTop(T x0, T y0)
	{ mPoints[0].set(x0, y0); }
	void setLeftTop(const GPoint2<T> &pt)
	{ mPoints[0] = pt; }

	void setRightBottom(T x1, T y1)
	{ mPoints[1].set(x1, y1); }
	void setRightBottom(const GPoint2<T> &pt)
	{ mPoints[1] = pt; }

	void set(T x0, T y0, T x1, T y1)
	{
		mPoints[0].set(x0, y0);
		mPoints[1].set(x1, y1);
	}

	void set(const GPoint2<T> &pt0, const GPoint2<T> &pt1)
	{
		mPoints[0] = pt0;
		mPoints[1] = pt1;
	}

	void set(const GRect2<T> &other)
	{
		*this = other;
	}
};

typedef GRect2<double> GRect2d;
typedef GRect2<int> GRect2i;
typedef GRect2<float> GRect2f;

#endif
