#include "gtexture2d.h"
#include "FreeImage.h"

GTexture2D::GTexture2D()
{
	mBindName = 0;
	mWidth = mHeight = 0;
}

GTexture2D::GTexture2D(const char *fileName)
{
	mBindName = 0;
	mWidth = mHeight = 0;
	loadTexImage(fileName);
}

GTexture2D::~GTexture2D()
{
    if(mBindName > 0)
    {
        glDeleteTextures(1, &mBindName);
    }
}

void GTexture2D::init()
{
    if(mBindName == 0)
    {
        glGenTextures(1, &mBindName);
    }
    use();
    setMagFilter(GL_LINEAR);
    setMinFilter(GL_LINEAR);
    setWrapS(GL_REPEAT);
    setWrapT(GL_REPEAT);
}

bool GTexture2D::loadTexImage(const char *fileName)
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(fileName, 0);
	FIBITMAP *pBitmap = FreeImage_Load(fif, fileName, 0);

	int w = FreeImage_GetWidth(pBitmap);
	int h = FreeImage_GetHeight(pBitmap);

	FIBITMAP *pBitmap32 = NULL;

	if(FreeImage_GetBPP(pBitmap) == 32)
	{
		pBitmap32 = pBitmap;
	}
	else
	{
		pBitmap32 = FreeImage_ConvertTo32Bits(pBitmap);
		FreeImage_Unload(pBitmap);
	}

	BYTE *bits = FreeImage_GetBits(pBitmap32);
	int pitch = FreeImage_GetPitch(pBitmap32);
	for(int i=0; i<h; i++)
	{
		for(int j=0; j<4*w; j+=4)
		{
			BYTE tmp = bits[j];
			bits[j] = bits[j+2];
			bits[j+2] = tmp;
		}
		bits += pitch;
	}

	bool ret = loadTexImage(FreeImage_GetBits(pBitmap32), w, h);
	FreeImage_Unload(pBitmap32);
	return ret;
}

bool GTexture2D::loadTexImage(const void* pixels, int width, int height)
{
	if(mBindName == 0) init();

	glBindTexture(GL_TEXTURE_2D, mBindName);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	int ret = glGetError();
	if(ret != GL_NO_ERROR) 
	{
		return false;
	}

	mWidth = width;
	mHeight = height;

	return true;
}

void GTexture2D::use()
{
    glBindTexture(GL_TEXTURE_2D, mBindName);
}

GLint GTexture2D::wrapS()
{
    GLint wraps;
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &wraps);
    return wraps;
}

void GTexture2D::setWrapS(GLint wrapS)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
}

GLint GTexture2D::wrapT()
{
    GLint wrapt;
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &wrapt);
    return wrapt;
}

void GTexture2D::setWrapT(GLint wrapT)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
}

GLint GTexture2D::minFilter()
{
    GLint minFilter;
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &minFilter);
    return minFilter;
}

void GTexture2D::setMinFilter(GLint minFilter)
{ 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
}
    
GLint GTexture2D::magFilter()
{
    GLint magFilter;
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &magFilter);
    return magFilter;
}

void GTexture2D::setMagFilter(GLint magFilter)
{ 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

GLint GTexture2D::envMode()
{
    GLint mode;
    glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &mode);
    return mode;
}

void GTexture2D::setEnvMode(GLint envMode)
{
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, envMode);    
}
