#ifndef GMATERIAL_H
#define GMATERIAL_H

#include <windows.h>
#include <gl/gl.h>

class GMaterial
{
protected:
	GLenum mFaceType;                  // ��������(ǰ��/����/˫��) 
	float mAmbientColor[4];            // ��������� 
	float mDiffuseColor[4];            // ���������� 
	float mSpecularColor[4];           // ���淴������ 
	float mEmissiveColor[4];           // �������� 
	float mShininess;                  // ���淴���ָ�� 
	float mTransparency;               // ͸���� 
public:
	GMaterial();
	virtual ~GMaterial();

	void operator = (const GMaterial &mat);	// copy
	
	GLenum faceType()
	{ return mFaceType; }
	
	void setFaceType(GLenum faceType)
	{ mFaceType = faceType; }
	
    void	setAmbientColor(float r, float g, float b);
    void	setDiffuseColor(float r, float g, float b);
    void	setSpecularColor(float r, float g, float b);
    void	setEmissiveColor(float r, float g, float b);
	void	setAmbientColor(float color[3]);
    void	setDiffuseColor(float color[3]);
    void	setSpecularColor(float color[3]);
    void	setEmissiveColor(float color[3]);
    void	setShininess(float shininess);
    void	setTransparency(float transparency);    

    void	getAmbientColor(float *r, float *g, float *b);
    void	getDiffuseColor(float *r, float *g, float *b);
    void	getSpecularColor(float *r, float *g, float *b);
    void	getEmissiveColor(float *r, float *g, float *b);
    void	getAmbientColor(float color[3]);
    void	getDiffuseColor(float color[3]);
    void	getSpecularColor(float color[3]);
    void	getEmissiveColor(float color[3]);
    float	getShininess();
    float	getTransparency();

   	// �����ʸ���ͼ�ζ���
	void	apply(void);
};

#endif
