#pragma once

#include "LoadImage.h"


// 描述文件的头部
struct SMD2Header
{
    int     m_iMagicNum;            // MD2文件ID号
    int     m_iVersion;             // 版本号

    int     m_iSkinWidthPx;         // 纹理宽度
    int     m_iSkinHeightPx;        // 纹理高度
    int     m_iFrameSize;           // 框架大小

    int     m_iNumSkins;            // 纹理图张数
    int     m_iNumVertices;         // 顶点个数
    int     m_iNumTexCoords;        // 纹理坐标信息
    int     m_iNumTriangles;        // 三角形个数
    int     m_iNumGLCommands;       // opengl命令个数
    int     m_iNumFrames;           // 模型中框架个数

    int     m_iOffsetSkins;         // 纹理信息偏移量
    int     m_iOffsetTexCoords;     // 纹理坐标信息偏移量
    int     m_iOffsetTriangles;     // 三角形信息偏移量
    int     m_iOffsetFrames;        // 框架信息偏移量
    int     m_iOffsetGLCommands;    // opengl命令信息偏移量

    int     m_iFileSize;            // 整个文件大小
};


// 描述顶点信息
struct SMD2Vert 
{
    float           m_fVert[3];     // 坐标信息
    unsigned char   m_ucReserved;   // 保留位置，暂时没用
};

// MD2模型的框架信息
struct SMD2Frame
{
    float           m_fScale[3];    // 模型旋转信息
    float           m_fTrans[3];    // 模型位移信息
    char            m_caName[16];   // 框架名字
    SMD2Vert        *m_pVerts;      // 模型顶点信息

    SMD2Frame()
    {
        m_pVerts = NULL;
    }

    ~SMD2Frame()
    {
        if (m_pVerts)
        {
            delete[] m_pVerts;
        }
    }
};


// 三角形信息
struct SMD2Tri
{
    unsigned short  m_sVertIndices[3];      // 顶点坐标索引信息
    unsigned short  m_sTexIndices[3];       // 纹理坐标索引信息
};


// 纹理坐标信息
struct SMD2TexCoord
{
    float   m_fTex[2];      // 纹理图坐标
};


// 读取的纹理图
struct SMD2Skin
{
    char        m_caSkin[64];   // 名字
    CLoadImage  m_Image;        // 通过一个类调用一个方法，调用纹理图
};


class CMD2
{
public:
    // 读取MD2文件
    bool Load(const char *szFilename);
    
    // 绘制模型
    void Render();

    // 通过框架编号绘制模型的一部分
    void Render(unsigned int uiFrame);

    // 动画
    void Animate(float fSpeed = 30.0f,
                 unsigned int uiStartFrame = 0,
                 unsigned int uiEndFrame = 0,
                 bool bLoop = true);

    CMD2();
    ~CMD2();

    // 播放动画时用的
    float       my_timer;

private:
    SMD2Header      m_Header;       // 定义头部
    SMD2Frame       *m_pFrames;     // 定义框架信息
    SMD2Tri         *m_pTriangles;  // 定义三角形信息
    SMD2TexCoord    *m_pTexCoords;  // 定义纹理坐标信息
    SMD2Skin        *m_pSkins;      // 描述纹理信息
    SMD2Vert        *m_pVerts;      // 描述顶点信息

    unsigned int    m_uiSkin;       // 仓前纹理
};
