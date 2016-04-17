#pragma once


// 描述文件头部
struct SMD2Header
{
    // MD2文件ID号
    int m_iMagicNum;

    // 版本号
    int m_iVersion;

    // 表示纹理的宽高 虽然不同纹理可以被导入
    // 但每个MD2文件模型同一时间只能使用一张纹理
    int m_iSkinWidthPx;
    int m_iSkinHeightPx;

    // 描述框架的大小，我们读取的时候一定要知道分配多大的空间
    int m_iFrameSize;

    // 纹理张数
    int m_iNumSkine;

    // 模型定点数
    int m_iNumVertices;

    // 纹理坐标的信息
    int m_iNumTexCoords;

    // 模型中一共有多少个三角形
    int m_iNumTriangles;

    // 有多少opengl的命令
    int m_iNumGLCommands;

    // 模型中有多少个框架
    int m_iNumFrames;

    // 纹理信息的偏移量
    int m_iOffsetSkins;

    // 纹理坐标信息的偏移量
    int m_iOffsetTexCoords;

    // 三角形信息的偏移量
    int m_iOffsetTriangles;

    // 框架信息的偏移量
    int m_iOffsetFrames;

    // opengl命令信息的偏移量
    int m_iOffsetGLCommands;

    // 整个文件的大小
    int m_iFileSize;
};

// 描述顶点信息（x, y, z坐标信息）
struct SMD2Vert
{
    // 坐标信息
    float m_fvert[3];

    // 保留位置，暂时没有用
    unsigned char m_ucReserved;
};

// MD2模型的框架信息
struct SMD2Frame
{
    // 模型旋转的信息
    float m_fScale[3];

    // 模型位移的信息
    float m_fTrans[3];

    // 用来存放这个框架的名字
    char m_caName[16];

    // 每个框架都有自己的顶点信息
    SMD2Vert *m_pVerts;

    // 构造函数
    SMD2Frame()
    {
        m_pVerts = 0;
    }

    // 析构函数
    ~SMD2Frame()
    {
        if ( m_pVerts )
        {
            delete[] m_pVerts;
        }
    }
};

// 三角形的信息，绘制的时候我们首先就是找到三角形，
// 从而读取三角形的点和纹理信息，然后绘制模型
struct SMD2Tri
{
    // 顶点坐标索引的信息
    unsigned short m_sVertIndices[3];

    // 纹理坐标索引的信息
    unsigned short m_sTexIndices[3];
};

// 纹理坐标的信息
struct SMD2TexCoord
{
    // 纹理图的坐标
    float m_fTex[2];
};

// 读取的纹理图的名字
struct SMD2Skin
{
    char m_caSkin[64];
};

class Md2
{
public:
    // 载入资源
    bool load(const char *szFileName);

    // 用于绘制模型，设定纹理操作
    void Render();

    // 接收一个名字，我们当前要渲染的是哪个框架
    void Render(unsigned int uiFame);

    // 处理MD2动画方面的内容
    void Animate(float fSpeed = 30.0f,              // 播放速度
                 unsigned int uiStartFrame = 0,     // 第一个框架编号
                 unsigned int uiEndframe = 0,       // 最后一个框架编号
                 bool bLoop = true);                // 时候循环播放

    // 构造与析构
    Md2();
    ~Md2();

    // 播放动画的时候进行线性插值计算所需变量
    float   m_timer;

private:
    // 定义头部
    SMD2Header  m_Head;

    // 定义框架
    SMD2Frame   *m_pFrames;

    // 定义三角形的信息
    SMD2Tri     *m_pTriangles;

    // 定义描述纹理坐标的信息
    SMD2TexCoord    *m_pTexCoords;

    // 描述纹理
    SMD2Skin        *m_pSkins;

    // 描述顶点
    SMD2Vert        *m_pVerts;

    unsigned int    m_uiSkin;
};
