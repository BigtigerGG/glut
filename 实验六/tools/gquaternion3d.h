#ifndef GQUATERNION3D_H
#define GQUATERNION3D_H

#include <math.h>
#include "gmath.h"

class GMatrix3d;

class GVector3d;

class GQuaternion3d
{
protected:
	double mAxis[4];         //����ֱ��ʾx, y, z,w
public:
	GQuaternion3d();
	GQuaternion3d(double x, double y, double z, double w);
	GQuaternion3d(const double *v);
	GQuaternion3d(const GQuaternion3d &v);

	static GQuaternion3d fromRotation(const GVector3d &v, double theta);

	operator double * ()
	{ return mAxis; }
	operator const double * () const
	{ return mAxis; }

	double x() const	{ return mAxis[0]; }
	double y() const	{ return mAxis[1]; }
	double z() const	{ return mAxis[2]; }
    double w() const    { return mAxis[3]; }

	void setX(double x) { mAxis[0] = x; }
	void setY(double y) { mAxis[1] = y; }
	void setZ(double z) { mAxis[2] = z; }
	void setW(double w) { mAxis[3] = w; }
	void set(const double *v);
    void set(double x, double y, double z, double w);
	//----ʸ������--------------------------------------------------------------
	//���� = /
	void operator = (const GQuaternion3d &v);

	//����Ԫ�����
	GQuaternion3d operator * (const GQuaternion3d &v) const;
	void operator *= (const GQuaternion3d &v); 

    //��Ԫ����ģ	
	double getMagnitude() const;
	//��Ԫ������
	GQuaternion3d getInverse() const;
	//��Ԫ���󹲶�	
	GQuaternion3d getConjugate() const;
	//����Ԫ��ȼ۵���ת����
    GMatrix3d  toMatrix() const;
    //��һ�� 
    void  normalize();
    GQuaternion3d  getNormal() const;
};

#endif
