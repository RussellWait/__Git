#pragma once

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>


#define PI          3.14159
#define TWO_PI      (PI * 2.0f)
#define HALF_PI     (PI / 2.0f)


class CGfxOpenGL
{
public:
    CGfxOpenGL();
    virtual ~CGfxOpenGL();

    virtual bool Init();
    virtual bool Shutdown();

    virtual void SetupProjection(int width, int height);

    virtual void Prepare(float dt);
    virtual void Render();


private:
    int         m_windowWidth;
    int         m_windowHeight;
};
