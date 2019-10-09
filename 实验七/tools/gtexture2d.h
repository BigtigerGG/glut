#ifndef GTEXTURE2D_H
#define GTEXTURE2D_H

#include <windows.h>
#include <gl/gl.h>

class GTexture2D            // 二维纹理处理类 
{
public:
	GLuint	mBindName;	    // glGenTextures获得的纹理名称  
	int		mWidth;			// 图像宽度
	int		mHeight;		// 图像高度
	
public:
    GTexture2D();
	GTexture2D(const char *fileName);
    ~GTexture2D();
    
    void init();
    
    GLuint bindName()
    { return mBindName; }
    
    void use();
    
    GLint wrapS();
    void setWrapS(GLint wrapS);
    
    GLint wrapT();
    void setWrapT(GLint wrapT);
    
    GLint minFilter();
    void setMinFilter(GLint minFilter);
    
    GLint magFilter();
    void setMagFilter(GLint magFilter);
    
    GLint envMode();
    
    void setEnvMode(GLint envMode);

	bool loadTexImage(const void* pixels, int width, int height);

	bool loadTexImage(const char *fileName);

	int width()
	{ return mWidth; }

	int height()
	{ return mHeight; }
};

#endif
