#include "gmaterial.h"

GMaterial::GMaterial()
{
    mFaceType = GL_FRONT_AND_BACK;
	mShininess = 0.0f;
	mTransparency = 0.0f;

	mAmbientColor[0]=mAmbientColor[1]=mAmbientColor[2]=0.2f;
	mAmbientColor[3]=1.0f - mTransparency;	// alpha value

	mDiffuseColor[0]=mDiffuseColor[1]=mDiffuseColor[2]=0.8f;
	mDiffuseColor[3]=1.0f - mTransparency;	// alpha value

	mSpecularColor[0]=mSpecularColor[1]=mSpecularColor[2]=0.0f;
	mSpecularColor[3]=1.0f - mTransparency;	// alpha value

	mEmissiveColor[0]=mEmissiveColor[1]=mEmissiveColor[2]=0.0f;
	mEmissiveColor[3]=1.0f - mTransparency;	// alpha value
}

GMaterial::~GMaterial()
{
}
	
void GMaterial::apply()
{
	glMaterialfv(mFaceType, GL_AMBIENT, mAmbientColor );
	glMaterialfv(mFaceType, GL_DIFFUSE, mDiffuseColor );
	glMaterialfv(mFaceType, GL_SPECULAR,mSpecularColor);
	glMaterialfv(mFaceType, GL_EMISSION,mEmissiveColor);
	glMaterialf(mFaceType, GL_SHININESS, mShininess);

}

void GMaterial::operator = (const GMaterial &other)
{
	for( int i = 0; i < 4; i++)
	{
		mAmbientColor[i] = other.mAmbientColor[i];
		mDiffuseColor[i] = other.mDiffuseColor[i];
		mSpecularColor[i] = other.mSpecularColor[i];
		mEmissiveColor[i] = other.mEmissiveColor[i];
	}
	mShininess = other.mShininess;
	mTransparency	= other.mTransparency;
}

void GMaterial::setShininess(float shininess)
{
	mShininess=shininess;
}

void GMaterial::setTransparency(float transparency)   
{
	mTransparency=transparency;	
	mAmbientColor[3]=1.0f - mTransparency;	// alpha value
	mDiffuseColor[3]=1.0f - mTransparency;	// alpha value
	mSpecularColor[3]=1.0f - mTransparency;	// alpha value
	mEmissiveColor[3]=1.0f - mTransparency;	// alpha value
}

void GMaterial::setAmbientColor(float r, float g, float b)
{
	mAmbientColor[0]=r;
	mAmbientColor[1]=g;
	mAmbientColor[2]=b;
}

void GMaterial::setDiffuseColor(float r, float g, float b)
{
	mDiffuseColor[0]=r;
	mDiffuseColor[1]=g;
	mDiffuseColor[2]=b;
}

void GMaterial::setSpecularColor(float r, float g, float b)
{
	mSpecularColor[0]=r;
	mSpecularColor[1]=g;
	mSpecularColor[2]=b;
}

void GMaterial::setEmissiveColor(float r, float g, float b)
{
	mEmissiveColor[0]=r;
	mEmissiveColor[1]=g;
	mEmissiveColor[2]=b;
}

void GMaterial::setAmbientColor(float color[3])
{
	mAmbientColor[0]=color[0];
	mAmbientColor[1]=color[1];
	mAmbientColor[2]=color[2];
}

void GMaterial::setDiffuseColor(float color[3])
{
	mDiffuseColor[0]=color[0];
	mDiffuseColor[1]=color[1];
	mDiffuseColor[2]=color[2];
}

void GMaterial::setSpecularColor(float color[3])
{
	mSpecularColor[0]=color[0];
	mSpecularColor[1]=color[1];
	mSpecularColor[2]=color[2];
}

void GMaterial::setEmissiveColor(float color[3])
{
	mEmissiveColor[0]=color[0];
	mEmissiveColor[1]=color[1];
	mEmissiveColor[2]=color[2];
}

void GMaterial::getAmbientColor(float *r, float *g, float *b)
{
	*r=mAmbientColor[0];
	*g=mAmbientColor[1];
	*b=mAmbientColor[2];
}

void GMaterial::getAmbientColor(float color[3])
{
	color[0]=mAmbientColor[0];
	color[1]=mAmbientColor[1];
	color[2]=mAmbientColor[2];
}

void GMaterial::getDiffuseColor(float *r, float *g, float *b)
{
	*r=mDiffuseColor[0];
	*g=mDiffuseColor[1];
	*b=mDiffuseColor[2];
}

void GMaterial::getDiffuseColor(float color[3])
{
	color[0]=mDiffuseColor[0];
	color[1]=mDiffuseColor[1];
	color[2]=mDiffuseColor[2];
}

void GMaterial::getSpecularColor(float *r, float *g, float *b)
{
	*r=mSpecularColor[0];
	*g=mSpecularColor[1];
	*b=mSpecularColor[2];
}

void GMaterial::getSpecularColor(float color[3])
{
	color[0]=mSpecularColor[0];
	color[1]=mSpecularColor[1];
	color[2]=mSpecularColor[2];
}

void GMaterial::getEmissiveColor(float *r, float *g, float *b)
{
	*r=mEmissiveColor[0];
	*g=mEmissiveColor[1];
	*b=mEmissiveColor[2];
}

void GMaterial::getEmissiveColor(float color[3])
{
	color[0]=mEmissiveColor[0];
	color[1]=mEmissiveColor[1];
	color[2]=mEmissiveColor[2];
}

float GMaterial::getShininess()
{
	return mShininess;	
}

float GMaterial::getTransparency()
{
	return mTransparency;
}

