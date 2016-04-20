#include "CGfxOpenGL.h"


class Translation : public CGfxOpenGL
{
public:
    virtual bool Init();
    virtual void Prepare(float dt);
    virtual void Render();


private:
    void DrawPlane();

    float   m_zPos;
    bool    m_direction;
};
