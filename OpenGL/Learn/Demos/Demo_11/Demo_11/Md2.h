#pragma once

#include "LoadImage.h"


// �����ļ���ͷ��
struct SMD2Header
{
    int     m_iMagicNum;            // MD2�ļ�ID��
    int     m_iVersion;             // �汾��

    int     m_iSkinWidthPx;         // ������
    int     m_iSkinHeightPx;        // ����߶�
    int     m_iFrameSize;           // ��ܴ�С

    int     m_iNumSkins;            // ����ͼ����
    int     m_iNumVertices;         // �������
    int     m_iNumTexCoords;        // ����������Ϣ
    int     m_iNumTriangles;        // �����θ���
    int     m_iNumGLCommands;       // opengl�������
    int     m_iNumFrames;           // ģ���п�ܸ���

    int     m_iOffsetSkins;         // ������Ϣƫ����
    int     m_iOffsetTexCoords;     // ����������Ϣƫ����
    int     m_iOffsetTriangles;     // ��������Ϣƫ����
    int     m_iOffsetFrames;        // �����Ϣƫ����
    int     m_iOffsetGLCommands;    // opengl������Ϣƫ����

    int     m_iFileSize;            // �����ļ���С
};


// ����������Ϣ
struct SMD2Vert 
{
    float           m_fVert[3];     // ������Ϣ
    unsigned char   m_ucReserved;   // ����λ�ã���ʱû��
};

// MD2ģ�͵Ŀ����Ϣ
struct SMD2Frame
{
    float           m_fScale[3];    // ģ����ת��Ϣ
    float           m_fTrans[3];    // ģ��λ����Ϣ
    char            m_caName[16];   // �������
    SMD2Vert        *m_pVerts;      // ģ�Ͷ�����Ϣ

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


// ��������Ϣ
struct SMD2Tri
{
    unsigned short  m_sVertIndices[3];      // ��������������Ϣ
    unsigned short  m_sTexIndices[3];       // ��������������Ϣ
};


// ����������Ϣ
struct SMD2TexCoord
{
    float   m_fTex[2];      // ����ͼ����
};


// ��ȡ������ͼ
struct SMD2Skin
{
    char        m_caSkin[64];   // ����
    CLoadImage  m_Image;        // ͨ��һ�������һ����������������ͼ
};


class CMD2
{
public:
    // ��ȡMD2�ļ�
    bool Load(const char *szFilename);
    
    // ����ģ��
    void Render();

    // ͨ����ܱ�Ż���ģ�͵�һ����
    void Render(unsigned int uiFrame);

    // ����
    void Animate(float fSpeed = 30.0f,
                 unsigned int uiStartFrame = 0,
                 unsigned int uiEndFrame = 0,
                 bool bLoop = true);

    CMD2();
    ~CMD2();

    // ���Ŷ���ʱ�õ�
    float       my_timer;

private:
    SMD2Header      m_Header;       // ����ͷ��
    SMD2Frame       *m_pFrames;     // ��������Ϣ
    SMD2Tri         *m_pTriangles;  // ������������Ϣ
    SMD2TexCoord    *m_pTexCoords;  // ��������������Ϣ
    SMD2Skin        *m_pSkins;      // ����������Ϣ
    SMD2Vert        *m_pVerts;      // ����������Ϣ

    unsigned int    m_uiSkin;       // ��ǰ����
};
