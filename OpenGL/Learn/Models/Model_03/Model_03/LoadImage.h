#pragma once

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>


class CLoadImage
{
public:
    unsigned int    m_uiWidth;
    unsigned int    m_uiHeight;
    unsigned int    m_uiFileLen;
    char            *m_szFileName;
    GLuint          m_texture[1];

    CLoadImage()
    {
        m_szFileName = NULL;
    }

    ~CLoadImage()
    {}

    BOOL LoadBMP(char *szFileName);
};
