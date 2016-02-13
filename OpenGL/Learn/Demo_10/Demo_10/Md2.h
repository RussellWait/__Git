#pragma once

#include "LoadImage.h"


// 描述文件头部
struct SMD2Header
{
    // MD2文件ID号
    int     m_iMagicNum;

    // 版本号
    int     m_iVersion;

    // 纹理宽高
    int     m_iSkinWidthPx;
    int     m_iSkinHeightPx;

    // 描述框架大小
    int     m_iFrameSize;

    // 纹理数目
    int     m_iNumSkins;

    // 模型顶点数
    int     m_iNumVertices;

    // 纹理坐标信息
    int     m_iNumTexCoords;

    // 模型中三角形总数
    int     m_iNumTriangles;

    // opengl命令总数
    int     m_iNumCommands;

    // 模型中框架总数
    int     m_iNumFrames;

    // 纹理详细偏移量
    int     m_iOffsetSkins;

    // 纹理坐标偏移量
    int     m_iOffsetTexCoords;

    // 三角形信息偏移量
    int     m_iOffsetTriangles;

    // 框架信息偏移量
    int     m_iOffsetFrames;

    // opengl命令偏移量
    int     m_iOffsetCommands;

    // 文件大小
    int     m_iFileSize;
};


// 描述顶点信息
struct SMD2Vert
{
    // 坐标信息
    float   m_fVert[3];

    // 保留位置，暂时没用
    unsigned char m_ucReserved;
};


// MD2模型框架信息
struct SMD2Frame
{
    // 模型旋转信息
    float   m_fScale[3];

    // 模型位移信息
    float   m_fTrans[3];

    // 框架名字
    char    m_caName[16];

    // 框架顶点信息
    SMD2Vert    *m_pVerts;

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
    // 顶点坐标索引信息
    unsigned short m_sVertIndices[3];

    // 纹理坐标索引信息
    unsigned short m_sTexIndices[3];
};


// 纹理坐标信息
struct SMD2TexCoord
{
    // 纹理图坐标
    float   m_fTex[2];
};


// 读取的纹理图名字
struct SMD2Skin
{
    // 名字
    char    m_caSkin[64];

    // 通过一个类调用一个方法，调用纹理图
    CLoadImage  Image;
};


class CMd2
{
public:
    bool Load(const char *szFileName);

    // 绘制模型，设定纹理
    void Render();

    // 指定渲染纹理部分
    void Render(unsigned int uiFrame);

    // 处理MD2动画方面的内容
    void Animate(float fSpeed = 30.0f,              // 播放速度
                 unsigned int uiStartFrame = 0,     // 起始框架
                 unsigned int uiEndFrame = 0,       // 终止框架
                 bool bLoop = true);                // 时候循环

    CMd2();

    ~CMd2();

    // 播放动画的时候进行线性插值计算用
    float   my_timer;


private:
    SMD2Header      m_Head;         // 定义头部
    SMD2Frame       *m_pFrame;      // 定义框架
    SMD2Tri         *m_pTriangles;  // 定义三角形信息
    SMD2TexCoord    *m_pTexCoords;  // 定义纹理坐标信息
    SMD2Skin        *m_pSkins;      // 描述纹理
    SMD2Vert        *m_pVerts;      // 描述顶点信息
    unsigned int    m_uiSkin;       // 当前纹理
};
