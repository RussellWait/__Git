#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>


class CLoadImage
{
public:
    unsigned int    m_uiWidth;          // 纹理宽高
    unsigned int    m_uiHeight;
    unsigned int    m_uiFileLen;        // 纹理文件大小
    char            *m_szFileName;      // 纹理名字
    GLuint          m_texture[1];       // 纹理编号

    CLoadImage()
    {
        m_szFileName = NULL;
    }

    ~CLoadImage()
    {}

    BOOL LoadBMP(char *szFileName);
};
