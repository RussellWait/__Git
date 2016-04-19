#pragma once

#define PI          3.14159
#define TWO_PI      (PI * 2.0f)
#define HALF_PI     (PI / 2.0f)


class CGfxOpenGL
{
public:
    CGfxOpenGL();
    virtual ~CGfxOpenGL();

    bool Init();
    bool Shutdown();

    void SetupProjection(int width, int height);

    void Prepare(float dt);
    void Render();

private:
    int     m_windowWidth;
    int     m_windowHeight;
    float   m_angle;
};
