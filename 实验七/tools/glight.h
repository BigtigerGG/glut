#ifndef GLIGHT_H
#define GLIGHT_H

#include <windows.h>
#include <math.h>
#include "gl\gl.h"
#include "gl\glu.h"
#include "gmath.h"
#include "gpoint3d.h"
#include "gvector3d.h"

#define MAX_LIGHTS 8

enum GLightType                       // 光源类型 
{
     gPointLight,
     gDirLight,
     gSpotLight,
};

class GLight                            // 光源类 
{
public:
    GLenum mLightIndex;                 // 光源的索引号
    enum GLightType mLightType;         // 光源类型 
protected:
    void apply();
public:
    GLight();
    
    void init(int index, GLightType lightType);

    void turnOn();
    void turnOff();
   
    void setLightType(enum GLightType x);
    
    void setAmbient(const float *ambient);
    void setAmbient(float x, float y, float z, float w = 1);
    
    void setDiffuse(const float *diffuse);
    void setDiffuse(float x, float y, float z, float w = 1);
    
    void setSpecular(const float *specular);
    void setSpecular(float x, float y, float z, float w = 1);
    
    void setPosition(const float *postion, float w = 1);
    void setPosition(float x, float y, float z, float w = 1);
    void setPosition(const GPoint3d &position, float w = 1);
    
    void setSpotDirection(const float *direction);
    void setSpotDirection(float x, float y, float z);
    void setSpotDirection(const GVector3d &direction);
    
    void setSpotExponent(float x);
    void setCutoffAngle(float x);
    void setConstantAttenuation(float x);
    void setLinearAttenuation(float x);
    void setQuadraticAttenuation(float x);

    int lightIndex();
    enum GLightType lightType();
    void ambient(float *ambient);
    void diffuse(float *diffuse);
    void specular(float *specular);
    void position(float *pos);
    void position(GPoint3d &pos);
    void spotDirection(float *direction);
    void spotDirection(GVector3d &direction);
    float spotExponent();
    float cutoffAngle();
    float constantAttenuation();
    float linearAttenuation();
    float quadraticAttenuation();

    // 允许/关闭光照效果 
    static void setLightingEnabled(bool enable = true);
    
    // 得到是否允许光照效果 
    static bool lightingEnabled(); 
};


#endif
