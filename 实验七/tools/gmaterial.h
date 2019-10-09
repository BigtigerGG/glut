#ifndef GMATERIAL_H
#define GMATERIAL_H

#include <windows.h>
#include <gl/gl.h>

class GMaterial
{
protected:
	GLenum mFaceType;                  // 材质类型(前面/背面/双面) 
	float mAmbientColor[4];            // 环境光参数 
	float mDiffuseColor[4];            // 漫反射光参数 
	float mSpecularColor[4];           // 镜面反射光参数 
	float mEmissiveColor[4];           // 辐射光参数 
	float mShininess;                  // 镜面反射光指数 
	float mTransparency;               // 透明度 
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

   	// 将材质赋给图形对象
	void	apply(void);
};

#endif
