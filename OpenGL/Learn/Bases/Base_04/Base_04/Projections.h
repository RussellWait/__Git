#pragma once

#include "CGfxOpenGL.h"


class Projections : public CGfxOpenGL
{
public:
    virtual bool Init() override;
    virtual void Render() override;
    virtual void SetupProjection(int width, int height) override;

private:
    void DrawCube(float xPos, float yPos, float zPos);
    void UpdateProjection(bool toggle = FALSE);
};
