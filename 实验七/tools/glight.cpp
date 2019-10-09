#include "glight.h"

GLight::GLight()
{
    mLightIndex = 0;
    mLightType = gDirLight;
}

void GLight::init(int index, GLightType lightType)
{
    if(index < 0) index = 0;
    if(index > 8) index = 8;
    mLightType = lightType;
    mLightIndex = (GLenum) (GL_LIGHT0)+index;
    setDiffuse(1, 1, 1);
    setSpecular(1, 1, 1);
    setLightType(lightType);
}

int GLight::lightIndex()
{
    return((int)(mLightIndex-GL_LIGHT0));
}

void GLight::setLightType(GLightType lightType)
{
    if(mLightType == lightType) return ;
    
    mLightType = lightType; 
    switch(lightType)
    {
    case gDirLight: 
            setConstantAttenuation(1);
            setLinearAttenuation(0);
            setQuadraticAttenuation(0);
            setSpotDirection(0, 0, -1);
            setSpotExponent(0);
            setCutoffAngle(180);
            break;
    case gPointLight:
            setSpotDirection(0, 0, -1);
            setSpotExponent(0);
            setCutoffAngle(180);
            break;
    }
}

enum GLightType GLight::lightType()
{
    return mLightType; 
}

void GLight::turnOn()
{
    glEnable(mLightIndex);
}

void GLight::turnOff()
{
    glDisable(mLightIndex);
}

void GLight::setAmbient(const float *ambient)
{
    glLightfv(mLightIndex, GL_AMBIENT, ambient);
}

void GLight::setAmbient(float x, float y, float z, float w)
{
    float ambient[] = {x, y, z, w};
    glLightfv(mLightIndex, GL_AMBIENT, ambient);
}

void GLight::setDiffuse(const float *diffuse)
{
     glLightfv(mLightIndex, GL_DIFFUSE, diffuse);
}

void GLight::setDiffuse(float x, float y, float z, float w)
{
     float diffuse[] = {x, y, z, w};
     glLightfv(mLightIndex, GL_DIFFUSE, diffuse);
}

void GLight::setSpecular(const float *specular)
{
     glLightfv(mLightIndex, GL_SPECULAR, specular);
}

void GLight::setSpecular(float x, float y, float z, float w)
{
    float specular[] = {x, y, z, w};
    glLightfv(mLightIndex, GL_SPECULAR, specular);
}

void GLight::setPosition(const float *position, float w)
{
    float pos[] = {position[0], position[1], position[2], w};
    glLightfv(mLightIndex, GL_POSITION, pos);
}

void GLight::setPosition(float x, float y, float z, float w)
{
    float pos[] = {x, y, z, w};
    glLightfv(mLightIndex, GL_POSITION, pos);
}

void GLight::setPosition(const GPoint3d &position, float w)
{
    float pos[] = {(float)(position.x()), (float)(position.y()), 
                   (float)(position.z()), w};
    glLightfv(mLightIndex, GL_POSITION, pos);
}

void GLight::setSpotDirection(const float *direction)
{
    if(mLightType != gSpotLight) return ;
    glLightfv(mLightIndex, GL_SPOT_DIRECTION, direction);
}

void GLight::setSpotDirection(float x, float y, float z)
{
    float direction[] = {x, y, z};
    glLightfv(mLightIndex, GL_SPOT_DIRECTION, direction);
}

void GLight::setSpotDirection(const GVector3d &direction)
{
    if(mLightType != gSpotLight) return ;
    float v[] = {(float)direction.x(), (float)direction.y(), 
                 (float)direction.z()};
    glLightfv(mLightIndex, GL_SPOT_DIRECTION, v);
}

void GLight::setSpotExponent(float exp)
{
    if(mLightType != gSpotLight) return ;
    glLightf(mLightIndex, GL_SPOT_EXPONENT, exp);
}

void GLight::setCutoffAngle(float cutOff)
{
    if(mLightType != gSpotLight) return ;
    glLightf(mLightIndex, GL_SPOT_CUTOFF, cutOff);
}

void GLight::setConstantAttenuation(float constant)
{
    if(mLightType == gDirLight) return ;
    glLightf(mLightIndex, GL_CONSTANT_ATTENUATION, constant);
}

void GLight::setLinearAttenuation(float linear)
{
    if(mLightType == gDirLight) return ;
    glLightf(mLightIndex, GL_LINEAR_ATTENUATION, linear);
}

void GLight::setQuadraticAttenuation(float quadratic)
{
    if(mLightType == gDirLight) return ;
    glLightf(mLightIndex, GL_QUADRATIC_ATTENUATION, quadratic);
}

void GLight::ambient(float *ambient)
{
    glGetLightfv(mLightIndex, GL_AMBIENT, ambient);
}

void GLight::diffuse(float *diffuse)
{
    glGetLightfv(mLightIndex, GL_DIFFUSE, diffuse);
}

void GLight::specular(float *specualr)
{
    glGetLightfv(mLightIndex, GL_SPECULAR, specualr);
}

void GLight::position(float *pos)
{
    glGetLightfv(mLightIndex, GL_POSITION, pos);
}

void GLight::position(GPoint3d &pos)
{
    float v[4];
    glGetLightfv(mLightIndex, GL_POSITION, v);
    pos.set(v[0], v[1], v[2]);
}

void GLight::spotDirection(float *direction)
{
    glGetLightfv(mLightIndex, GL_SPOT_DIRECTION, direction);
}

void GLight::spotDirection(GVector3d &direction)
{
    float v[3];
    glGetLightfv(mLightIndex, GL_SPOT_DIRECTION, v);
    direction.set(v[0], v[1], v[2]);
}

float GLight::spotExponent()
{
    float exp;
    glGetLightfv(mLightIndex, GL_SPOT_EXPONENT, &exp);
    return exp;
}

float GLight::cutoffAngle()
{
    float cutoff;
    glGetLightfv(mLightIndex, GL_SPOT_CUTOFF, &cutoff);
    return cutoff;
}

float GLight::constantAttenuation()
{
    float constant;
    glGetLightfv(mLightIndex, GL_CONSTANT_ATTENUATION, &constant);
    return constant;
}

float GLight::linearAttenuation()
{
    float linear;
    glGetLightfv(mLightIndex, GL_LINEAR_ATTENUATION, &linear);
    return linear;
}

float GLight::quadraticAttenuation()
{
    float quadratic;
    glGetLightfv(mLightIndex, GL_QUADRATIC_ATTENUATION, &quadratic);
    return quadratic;
}

void GLight::setLightingEnabled(bool enable)
{
    if(enable)
    {
        glEnable(GL_LIGHTING);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }
}

bool GLight::lightingEnabled()
{
    GLint enable;
    glGetIntegerv(GL_LIGHTING, &enable);
    if(enable) return true;
	else return false;
}
