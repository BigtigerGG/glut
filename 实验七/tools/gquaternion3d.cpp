#include "gvector3d.h"
#include "gmatrix3d.h"
#include "gquaternion3d.h"

#include <stdio.h>

GQuaternion3d::GQuaternion3d()
{   
	mAxis[0] = mAxis[1] = mAxis[2] = mAxis[3] = 0;
}

GQuaternion3d::GQuaternion3d(double x, double y, double z, double w)
{
    mAxis[0] = x;
    mAxis[1] = y;
    mAxis[2] = z;
    mAxis[3] = w;
}

GQuaternion3d::GQuaternion3d(const double *v)
{
    mAxis[0] = v[0];
    mAxis[1] = v[1];
    mAxis[2] = v[2];
    mAxis[3] = v[3];
    
}

GQuaternion3d::GQuaternion3d(const GQuaternion3d &v)
{
    mAxis[0] = v.mAxis[0];
    mAxis[1] = v.mAxis[1];
    mAxis[2] = v.mAxis[2];
    mAxis[3] = v.mAxis[3];   
}

GQuaternion3d GQuaternion3d::fromRotation(const GVector3d &v, double theta)
{
	GQuaternion3d q; 
	double cosValue	= cos(theta/2);  
	double sinValue	= sin(theta/2);  
	q[0]	= sinValue * v.x();
	q[1]	= sinValue * v.y();
	q[2]	= sinValue * v.z();
	q[3]	= cosValue;
	return q;
}

void GQuaternion3d::set(const double *v)
{ 
    mAxis[0] = v[0];
    mAxis[1] = v[1];
    mAxis[2] = v[2];
    mAxis[3] = v[3];
}
void GQuaternion3d::set(double x,double y,double z,double w)
{
    mAxis[0] = x;
    mAxis[1] = y;
    mAxis[2] = z;
    mAxis[3] = w;
}

void GQuaternion3d::operator = (const GQuaternion3d &v)
{
      mAxis[0] = v.mAxis[0];
      mAxis[1] = v.mAxis[1];
      mAxis[2] = v.mAxis[2];
      mAxis[3] = v.mAxis[3];
}

GQuaternion3d GQuaternion3d::operator * (const GQuaternion3d &v) const
{
     GQuaternion3d q;
     double x2,y2,z2,w2;
     x2 = v.mAxis[0];
     y2 = v.mAxis[1];
     z2 = v.mAxis[2];
     w2 = v.mAxis[3];
     
     q.mAxis[0] = mAxis[3] * x2 + mAxis[0]* w2 + mAxis[1]* z2 - mAxis[2]* y2;
     q.mAxis[1] = mAxis[3] * y2 + mAxis[1]* w2 + mAxis[2]* x2 - mAxis[0]* z2;
     q.mAxis[2] = mAxis[3] * z2 + mAxis[2]* w2 + mAxis[0]* y2 - mAxis[1]* x2;
     q.mAxis[3] = mAxis[3] * w2 - mAxis[0]* x2 - mAxis[1]* y2 - mAxis[2]* z2;
     
     return(q);
}

void GQuaternion3d::operator *= (const GQuaternion3d &v)
{
     (*this) = (*this)*v;
}

double GQuaternion3d::getMagnitude() const
{
     return double(sqrt(mAxis[0]*mAxis[0] + mAxis[1]*mAxis[1] + 
                        mAxis[2]*mAxis[2] +mAxis[3]*mAxis[3]));
}

GQuaternion3d GQuaternion3d::getInverse() const
{
     GQuaternion3d q;
     double magnitude2 = mAxis[0]*mAxis[0] + mAxis[1]*mAxis[1] + mAxis[2]*mAxis[2] +mAxis[3]*mAxis[3];
     q.mAxis[0] = -mAxis[0]/magnitude2;
     q.mAxis[1] = -mAxis[1]/magnitude2;
     q.mAxis[2] = -mAxis[2]/magnitude2;
     q.mAxis[3] =  mAxis[3]/magnitude2;
     return(q);
}

GQuaternion3d GQuaternion3d::getConjugate() const
{
     GQuaternion3d q;
     q.mAxis[0] = -mAxis[0];
     q.mAxis[1] = -mAxis[1];
     q.mAxis[2] = -mAxis[2];
     q.mAxis[3] =  mAxis[3];
     return(q);
}

void  GQuaternion3d::normalize()
{
    double magnitude = sqrt(mAxis[0]*mAxis[0] + mAxis[1]*mAxis[1] + mAxis[2]*mAxis[2] +mAxis[3]*mAxis[3]);
    mAxis[0] /= magnitude;
    mAxis[1] /= magnitude;
    mAxis[2] /= magnitude;
    mAxis[3] /= magnitude;
}

GQuaternion3d  GQuaternion3d::getNormal() const
{
    GQuaternion3d q;
    double magnitude = sqrt(mAxis[0]*mAxis[0] + mAxis[1]*mAxis[1] + mAxis[2]*mAxis[2] +mAxis[3]*mAxis[3]);
    q.mAxis[0] = mAxis[0]/magnitude;
    q.mAxis[1] = mAxis[1]/magnitude;
    q.mAxis[2] = mAxis[2]/magnitude;
    q.mAxis[3] = mAxis[3]/magnitude;
    return(q);
}


GMatrix3d  GQuaternion3d::toMatrix() const
{
	GMatrix3d q;                
	double wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2, x, y, z,w;
	x = mAxis[0];
	y = mAxis[1];
	z = mAxis[2];
	w = mAxis[3];
   	x2 = x * 2; 
	y2 = y * 2; 
	z2 = z * 2;
	xx = x * x2;   xy = x * y2;   xz = x * z2;
	yy = y * y2;   yz = y * z2;   zz = z * z2;
	wx = w * x2;   wy = w * y2;   wz = w * z2;
	q[0] = 1 - (yy + zz); 	
	q[1] = xy + wz;              
	q[2] = xz - wy;		    		   
	q[3] = 0;                          
	q[4] = xy - wz;		    		   
	q[5] = 1 - (xx + zz);   
	q[6] = yz + wx;		    		   
	q[7] = 0;                          
	q[8] = xz + wy;		    		   
	q[9] = yz - wx;              
	q[10] = 1 - (xx + yy);	
	q[11] = 0;                       
	q[12] = 0;			        			       
	q[13] = 0;                        
	q[14] = 0;			        			       
	q[15] = 1;              
                                           
    return(q);     
}
