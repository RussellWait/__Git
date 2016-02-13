#pragma once

#include "LoadImage.h"


// �����ļ�ͷ��
struct SMD2Header
{
    // MD2�ļ�ID��
    int     m_iMagicNum;

    // �汾��
    int     m_iVersion;

    // ������
    int     m_iSkinWidthPx;
    int     m_iSkinHeightPx;

    // ������ܴ�С
    int     m_iFrameSize;

    // ������Ŀ
    int     m_iNumSkins;

    // ģ�Ͷ�����
    int     m_iNumVertices;

    // ����������Ϣ
    int     m_iNumTexCoords;

    // ģ��������������
    int     m_iNumTriangles;

    // opengl��������
    int     m_iNumCommands;

    // ģ���п������
    int     m_iNumFrames;

    // ������ϸƫ����
    int     m_iOffsetSkins;

    // ��������ƫ����
    int     m_iOffsetTexCoords;

    // ��������Ϣƫ����
    int     m_iOffsetTriangles;

    // �����Ϣƫ����
    int     m_iOffsetFrames;

    // opengl����ƫ����
    int     m_iOffsetCommands;

    // �ļ���С
    int     m_iFileSize;
};


// ����������Ϣ
struct SMD2Vert
{
    // ������Ϣ
    float   m_fVert[3];

    // ����λ�ã���ʱû��
    unsigned char m_ucReserved;
};


// MD2ģ�Ϳ����Ϣ
struct SMD2Frame
{
    // ģ����ת��Ϣ
    float   m_fScale[3];

    // ģ��λ����Ϣ
    float   m_fTrans[3];

    // �������
    char    m_caName[16];

    // ��ܶ�����Ϣ
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


// ��������Ϣ
struct SMD2Tri
{
    // ��������������Ϣ
    unsigned short m_sVertIndices[3];

    // ��������������Ϣ
    unsigned short m_sTexIndices[3];
};


// ����������Ϣ
struct SMD2TexCoord
{
    // ����ͼ����
    float   m_fTex[2];
};


// ��ȡ������ͼ����
struct SMD2Skin
{
    // ����
    char    m_caSkin[64];

    // ͨ��һ�������һ����������������ͼ
    CLoadImage  Image;
};


class CMd2
{
public:
    bool Load(const char *szFileName);

    // ����ģ�ͣ��趨����
    void Render();

    // ָ����Ⱦ������
    void Render(unsigned int uiFrame);

    // ����MD2�������������
    void Animate(float fSpeed = 30.0f,              // �����ٶ�
                 unsigned int uiStartFrame = 0,     // ��ʼ���
                 unsigned int uiEndFrame = 0,       // ��ֹ���
                 bool bLoop = true);                // ʱ��ѭ��

    CMd2();

    ~CMd2();

    // ���Ŷ�����ʱ��������Բ�ֵ������
    float   my_timer;


private:
    SMD2Header      m_Head;         // ����ͷ��
    SMD2Frame       *m_pFrame;      // ������
    SMD2Tri         *m_pTriangles;  // ������������Ϣ
    SMD2TexCoord    *m_pTexCoords;  // ��������������Ϣ
    SMD2Skin        *m_pSkins;      // ��������
    SMD2Vert        *m_pVerts;      // ����������Ϣ
    unsigned int    m_uiSkin;       // ��ǰ����
};
