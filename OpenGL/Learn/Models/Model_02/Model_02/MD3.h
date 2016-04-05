#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "LoadImage.h"


const static int idP3 = 860898377;
const static int versionP3 = 15;


struct SMD3Header
{
    int     m_iID;              // ������idP3
    int     m_iVersion;         // ������versionP3
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

// ��Χ����Ϣ
struct SMD3Frame
{
    float   m_fMin[3];
    float   m_fMax[3];
};

// Tag����Ϣ������ת��ƽ�Ƶ���Ϣ
struct SMD3Tag
{
    char        m_cName[64];
    CVector3    m_vecPos;
    CQuaternion m_qRot;
};

// ����ͷ��Ϣ
struct SMD3MeshHeader
{
    char    m_cMeshID[4];
    char    m_cName[68];
    int     m_iNumMeshFrames;   // ���񶯻�֡��
    int     m_iNumSkins;        // ���񶯻���Ƥ��Ŀ
    int     m_iNumVerts;        // ������
    int     m_iNumTriangles;    // ��������
    int     m_iTriOffset;       // ������ƫ����
    int     m_iHeaderSize;
    int     m_iUVOffset;        // �������������
    int     m_iVertexOffset;    // ����ƫ����
    int     m_iMeshSize;
};

// ����
struct SMD3Vertex
{
    float m_fVert[3];
};

// ����������
struct SMD3Face
{
    unsigned int m_uiIndices[3];
};

// ��������
struct SMD3TexCoord
{
    float m_fTexCoord[2];
};

struct SMD3Skin
{
    char        m_cName[68];
    CLoadImage  m_Image;
};

// �ؼ�֡
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

// ������Ϣ
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
    SMD3Vertex      *m_pInterp;     // ��ֵ����
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
