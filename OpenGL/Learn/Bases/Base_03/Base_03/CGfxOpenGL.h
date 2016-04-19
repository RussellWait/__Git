#pragma once

#define PI          3.14159
#define TWO_PI      (PI * 2.0f)
#define HALF_PI     (PI / 2.0f)


// 绘制不同图元的枚举
typedef enum
{
    Points,
    Lines,
    Triangles,
    Polygons,
    OnYourOwn1,
} PrimType;


class CGfxOpenGL
{
public:
    CGfxOpenGL(PrimType type);
    virtual ~CGfxOpenGL();

    bool Init();
    bool Shutdown();

    void SetupProjection(int width, int height);

    void Prepare(float dt);
    void Render();

private:
    int         m_windowWidth;
    int         m_windowHeight;
    float       m_angle;

    PrimType    m_type;
};
