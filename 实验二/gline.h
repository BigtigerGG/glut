#ifndef GLINE2_H
#define GLINE2_H

#include "gpoint2.h"

template <class T>
class GLine2
{
public:
	GPoint2<T>	mBeginPt, mEndPt;

public:
	GLine2() : mBeginPt(0, 0), mEndPt(0, 0)
	{
	}

	GLine2(const GPoint2<T> &beginPt, const GPoint2<T> &endPt)
	{
		mBeginPt = beginPt;
		mEndPt = endPt;
	}

	GLine2(T x0, T y0, T x1, T y1) : mBeginPt(x0, y0), mEndPt(x1, y1)
	{
	}

	GLine2(const GLine2 &other)
	{
		*this = other;
	}

	const GPoint2<T> & getBeginPt() const
	{
		return mBeginPt;
	}

	void setBeginPt(const GPoint2<T> &pt)
	{
		mBeginPt = pt;
	}

	const GPoint2<T> & getEndPt() const
	{
		return mEndPt;
	}

	void setEndPt(const GPoint2<T> &pt)
	{
		mEndPt = pt;
	}

	void set(const GPoint2<T> &beginPt, const GPoint2<T> &endPt)
	{
		mBeginPt = beginPt;
		mEndPt = endPt;
	}

	void set(T x0, T y0, T x1, T y1)
	{
		mBeginPt.set(x0, y0);
		mEndPt.set(x1, y1);
	}

	GLine2 & operator = (const GLine2 &other)
	{
		mBeginPt = other.mBeginPt;
		mEndPt = other.mEndPt;
		return *this;
	}
};

typedef GLine2<double> GLine2d;
typedef GLine2<int> GLine2i;
typedef GLine2<float> GLine2f;

#endif