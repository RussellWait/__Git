#pragma once

#include "CGfxOpenGL.h"


class Translation : public CGfxOpenGL
{
public:
    virtual bool Init() override;
    virtual void Prepare(float dt) override;
    virtual void Render() override;


private:
    void DrawPlane();

    float   m_zPos;
    bool    m_direction;
};
