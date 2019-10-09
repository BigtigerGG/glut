#include "gvector3d.h"
#include "gmatrix3d.h"

GMatrix3d::GMatrix3d()
{
	for(int i=0; i<16; i++) 
	{
		mMatrix[i] = 0;
	}
	mMatrix[0] = mMatrix[5] = mMatrix[10] = mMatrix[15] = 1;
}

GMatrix3d::GMatrix3d(const double *mMatrix)
{
	for(int i=0; i<16; i++) this->mMatrix[i] = mMatrix[i];
}

GMatrix3d::GMatrix3d(const GMatrix3d &m)
{
	for(int i=0; i<16; i++) mMatrix[i] = m.mMatrix[i];
}

void GMatrix3d::operator = (const GMatrix3d &m)
{
	for(int i=0; i<16; i++) mMatrix[i] = m.mMatrix[i];
}

GMatrix3d GMatrix3d::operator * (const GMatrix3d &m) const
{
	GMatrix3d r;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			r.mMatrix[i*4+j] = 0;
			for(int k=0; k<4; k++)
			{
				r.mMatrix[i*4+j] += mMatrix[i*4+k]*m.mMatrix[k*4+j];
			}
		}
	}
	return r;
}

void GMatrix3d::operator *= (const GMatrix3d &m)
{
	(*this) = (*this)*m;
}

GMatrix3d GMatrix3d::getTranspose() const
{
	GMatrix3d m;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			m.mMatrix[j*4+i] = mMatrix[i*4+j];
		}
	}
	return m;
}

void GMatrix3d::transpose()
{
	(*this) = getTranspose();
}

GMatrix3d GMatrix3d::getInverse() const
{
    GMatrix3d m = *this;
    gInverseMatrix(m.mMatrix, 4);
    return m;
}

void GMatrix3d::inverse()
{
    (*this) = getInverse();
}

GMatrix3d GMatrix3d::createZero()
{
    GMatrix3d m;
    m.mMatrix[0] = m.mMatrix[5] = m.mMatrix[10] = m.mMatrix[15] = 0;
    return m;
}

GMatrix3d GMatrix3d::createIdentity()
{
	return GMatrix3d();
}

GMatrix3d GMatrix3d::createRotateX(double af)
{
	af *= ANGLE_TO_RADIAN;
	GMatrix3d m;
	m.mMatrix[5] = cos(af);
	m.mMatrix[6] = sin(af);
	m.mMatrix[9] = -m.mMatrix[6];
	m.mMatrix[10] = m.mMatrix[5];
	return m;
}

GMatrix3d GMatrix3d::createRotateY(double af)
{
	af *= ANGLE_TO_RADIAN;
	GMatrix3d m;
	m.mMatrix[0] = cos(af);
	m.mMatrix[2] = -sin(af);
	m.mMatrix[8] = -m.mMatrix[2];
	m.mMatrix[10] = m.mMatrix[0];
	return m;
}

GMatrix3d GMatrix3d::createRotateZ(double af)
{
	af *= ANGLE_TO_RADIAN;
	GMatrix3d m;
	m.mMatrix[0] = cos(af);
	m.mMatrix[1] = sin(af);
	m.mMatrix[4] = -m.mMatrix[1];
	m.mMatrix[5] = m.mMatrix[0];
	return m;
}

GMatrix3d GMatrix3d::createRotateX(double sinAF, double cosAF)
{
	GMatrix3d m;
	m.mMatrix[5] = cosAF;
	m.mMatrix[6] = sinAF;
	m.mMatrix[9] = -sinAF;
	m.mMatrix[10] = cosAF;
	return m;
}

GMatrix3d GMatrix3d::createRotateY(double sinAF, double cosAF)
{
	GMatrix3d m;
	m.mMatrix[0] = cosAF;
	m.mMatrix[2] = -sinAF;
	m.mMatrix[8] = sinAF;
	m.mMatrix[10] = cosAF;
	return m;
}

GMatrix3d GMatrix3d::createRotateZ(double sinAF, double cosAF)
{
	GMatrix3d m;
	m.mMatrix[0] = cosAF;
	m.mMatrix[1] = sinAF;
	m.mMatrix[4] = -sinAF;
	m.mMatrix[5] = cosAF;
	return m;
}

GMatrix3d GMatrix3d::createRotate(double theta, const GVector3d &v)
{
	GMatrix3d m;

	return m;
}

GMatrix3d GMatrix3d::createTranslate(double x, double y, double z)
{
	GMatrix3d m;
	m.mMatrix[12] = x;
	m.mMatrix[13] = y;
	m.mMatrix[14] = z;
	return m;
}

GMatrix3d GMatrix3d::createScale(double sx, double sy, double sz)
{
	GMatrix3d m;
	m.mMatrix[0] = sx;
	m.mMatrix[5] = sy;
	m.mMatrix[10] = sz;
	return m;
}

GMatrix3d GMatrix3d::createMirror(const GVector3d &v)
{
	GMatrix3d m;
	double len = v.getLength();
	if(IS_ZERO(len)) return m;

	m.mMatrix[0] = (v.x()*v.x()-1)*2/len/len;
	m.mMatrix[5] = (v.y()*v.y()-1)*2/len/len;
	m.mMatrix[10] = (v.z()*v.z()-1)*2/len/len;
	m.mMatrix[4] = m.mMatrix[1] = v.x()*v.y()*2/len/len;
	m.mMatrix[8] = m.mMatrix[2] = v.x()*v.z()*2/len/len;
	m.mMatrix[9] = m.mMatrix[6] = v.z()*v.y()*2/len/len;
	return m;
}

