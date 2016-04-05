#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "LoadImage.h"


const static int idP3 = 860898377;
const static int versionP3 = 15;


struct SMD3Header
{
    int     m_iID;              // 必须是idP3
    int     m_iVersion;         // 必须是versionP3
    char    m_cFileName[68];
    int     m_iNumFrame;
    int     m_iNumTags;
    int     m_iNumMeshes;
    int     m_iMaxSkins;
    int     m_iHeaderSize;
    int     m_iTagStart;
    int     m_iTagEnd;
    int     m_iFileSize;
};

// 包围盒信息
struct SMD3Frame
{
    float   m_fMin[3];
    float   m_fMax[3];
};

// Tag的信息包含旋转与平移的信息
struct SMD3Tag
{
    char        m_cName[64];
    CVector3    m_vecPos;
    CQuaternion m_qRot;
};

// 网格头信息
struct SMD3MeshHeader
{
    char    m_cMeshID[4];
    char    m_cName[68];
    int     m_iNumMeshFrames;   // 网格动画帧数
    int     m_iNumSkins;        // 网格动画的皮数目
    int     m_iNumVerts;        // 顶点数
    int     m_iNumTriangles;    // 三角形数
    int     m_iTriOffset;       // 三角形偏移量
    int     m_iHeaderSize;
    int     m_iUVOffset;        // 纹理坐标便宜量
    int     m_iVertexOffset;    // 顶点偏移量
    int     m_iMeshSize;
};

// 顶点
struct SMD3Vertex
{
    float m_fVert[3];
};

// 三角形索形
struct SMD3Face
{
    unsigned int m_uiIndices[3];
};

// 纹理坐标
struct SMD3TexCoord
{
    float m_fTexCoord[2];
};

struct SMD3Skin
{
    char        m_cName[68];
    CLoadImage  m_Image;
};

// 关键帧
struct SMD3KeyFrame
{
    SMD3KeyFrame()
    {
        m_pVertices = NULL;
    }

    ~SMD3KeyFrame()
    {
        if ( m_pVertices )
        {
            delete[] m_pVertices;
            m_pVertices = NULL;
        }
    }

    SMD3Vertex	*m_pVertices;
};

// 网格信息
struct SMD3Mesh
{
    SMD3Mesh()
    {
        m_pKeyFrames    = NULL;
        m_pFaces        = NULL;
        m_pTexCoords    = NULL;
        m_pSkins        = NULL;
        m_pInterp       = NULL;
    }

    ~SMD3Mesh()
    {
        if ( m_pKeyFrames )
        {
            delete[] m_pKeyFrames;
            m_pKeyFrames = NULL;
        }

        if ( m_pFaces )
        {
            delete[] m_pFaces;
            m_pFaces = NULL;
        }

        if ( m_pTexCoords )
        {
            delete[] m_pTexCoords;
            m_pTexCoords = NULL;
        }

        if ( m_pSkins )
        {
            delete[] m_pSkins;
            m_pSkins = NULL;
        }

        if ( m_pInterp )
        {
            delete[] m_pInterp;
            m_pInterp = NULL;
        }
    }

    SMD3MeshHeader  m_Header;
    SMD3KeyFrame    *m_pKeyFrames;
    SMD3Face        *m_pFaces;
    SMD3TexCoord    *m_pTexCoords;
    SMD3Skin        *m_pSkins;
    SMD3Vertex      *m_pInterp;     // 插值顶点
};


class CMD3
{
public:
    CMD3();
    ~CMD3();

    bool Load(const char *szFileName);
    void Render();
    void RenderT();
    void Animate(unsigned int uiStartFrame, unsigned int uiEndFrame, int uiFPS = 10, bool bLoop = true);
    void Attach(CMD3 *pModel, unsigned int uiTag);

private:
    unsigned int    m_uiLastFrame;
    float           m_fLastInterp;
    SMD3Header      m_Header;
    SMD3Tag         *m_pTags;
    SMD3Mesh        *m_pMeshes;
    SMD3Tag         *m_pInterpTags;
    CMD3            **m_ppAttachments;
    float           my_timer;
};
