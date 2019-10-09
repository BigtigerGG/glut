#ifndef GPOLYGON2_H
#define GPOLYGON2_H

#include "gpoint2.h"
#include <vector>

using namespace std;

template <class T>
class GPolygon2
{
private:
    vector< GPoint2<T> > mPoints;

public:
    GPolygon2()
	{
	}

    GPolygon2(const GPolygon2<T> &other)
	{
		*this = other;
	}

	GPolygon2 & operator = (const GPolygon2<T> &other)
	{
		mPoints = other.mPoints;
		return *this;
	}
    
    GPoint2<T> at(int index) const
	{
		return mPoints.at(index);
	}

    bool set(int index, const GPoint2<T> &pt)
	{
		if(index < 0 || index >= count()) return false;

		mPoints[index] = pt;
		return true;
	}

	operator const GPoint2<T> * () const
	{
		vector< GPoint2<T> >::const_iterator it = mPoints.begin();
		return &(*it);
	}

	operator GPoint2<T> * ()
	{
		vector< GPoint2<T> >::iterator it = mPoints.begin();
		return &(*it);
	}

    void addFirst(const GPoint2<T> &pt)
	{
		mPoints.insert(mPoints.begin(), pt);
	}

    void addLast(const GPoint2<T> &pt)
	{
		mPoints.push_back(pt);   
	}

    bool insert(int index, const GPoint2<T> &pt)
	{
		if(index < 0 || index > count()) return false;
		mPoints.insert(mPoints.begin()+index, pt);
		return true;
	}
    
    bool removeFirst()
	{
		if(count() <= 0) return false;
		mPoints.erase(mPoints.begin());
		return true;
	}

    bool removeLast()
	{
		if(count() <= 0) return false;
		mPoints.pop_back();
		return true;
	}

    bool remove(int index)
	{
		if(index < 0 || index >= count()) return false;

		mPoints.erase(mPoints.begin()+index);
		return true;
	}
    
    void clear()
    { mPoints.clear(); }
    
    bool empty() const
    { return mPoints.empty(); }
    
    int count() const
    { return mPoints.size(); }
    
    int findByCoord(T x, T y, T w = 5, T h = 5)
	{
		for(int i=0; i<count(); i++)
		{
			if(abs(mPoints[i].x() - x) <= w &&
				abs(mPoints[i].y() - y) <= h)
			{
				return i;
			}
		}
		return -1;
	}
};

typedef GPolygon2<float> GPolygon2f;		// 浮点多边形
typedef GPolygon2<double> GPolygon2d;		// 双精度多边形
typedef GPolygon2<int> GPolygon2i;			// 整形多边形

#endif

