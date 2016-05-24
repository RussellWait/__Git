#pragma once

#include "CGfxOpenGL.h"


class Rotation : public CGfxOpenGL
{
public:
    virtual bool Init() override;
    virtual void Prepare(float dt) override;
    virtual void Render() override;

private:
    void DrawPlane();
    void DrawAxes();

    float m_xAxisAngle;
    float m_yAxisAngle;
};
