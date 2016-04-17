#pragma once

#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>


class CLoadImage
{
public:
    unsigned int    m_uiWidth;          // 描述纹理宽度
    unsigned int    m_uiHeight;         // 描述纹理高度
    unsigned int    m_uiFileLen;        // 纹理文件大小
    char            *m_szFileName;      // 纹理名称
    GLuint          m_texture[1];       // 纹理ID

    CLoadImage()
    {
        m_szFileName = NULL;
    }

    ~CLoadImage() {}

    // 读取md2所需的纹理图
    BOOL LoadBMP(char *szFileName);
};
