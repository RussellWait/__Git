#pragma once


// �����ļ�ͷ��
struct SMD2Header
{
    // MD2�ļ�ID��
    int m_iMagicNum;

    // �汾��
    int m_iVersion;

    // ��ʾ����Ŀ�� ��Ȼ��ͬ������Ա�����
    // ��ÿ��MD2�ļ�ģ��ͬһʱ��ֻ��ʹ��һ������
    int m_iSkinWidthPx;
    int m_iSkinHeightPx;

    // ������ܵĴ�С�����Ƕ�ȡ��ʱ��һ��Ҫ֪��������Ŀռ�
    int m_iFrameSize;

    // ��������
    int m_iNumSkine;

    // ģ�Ͷ�����
    int m_iNumVertices;

    // �����������Ϣ
    int m_iNumTexCoords;

    // ģ����һ���ж��ٸ�������
    int m_iNumTriangles;

    // �ж���opengl������
    int m_iNumGLCommands;

    // ģ�����ж��ٸ����
    int m_iNumFrames;

    // ������Ϣ��ƫ����
    int m_iOffsetSkins;

    // ����������Ϣ��ƫ����
    int m_iOffsetTexCoords;

    // ��������Ϣ��ƫ����
    int m_iOffsetTriangles;

    // �����Ϣ��ƫ����
    int m_iOffsetFrames;

    // opengl������Ϣ��ƫ����
    int m_iOffsetGLCommands;

    // �����ļ��Ĵ�С
    int m_iFileSize;
};

// ����������Ϣ��x, y, z������Ϣ��
struct SMD2Vert
{
    // ������Ϣ
    float m_fvert[3];

    // ����λ�ã���ʱû����
    unsigned char m_ucReserved;
};

// MD2ģ�͵Ŀ����Ϣ
struct SMD2Frame
{
    // ģ����ת����Ϣ
    float m_fScale[3];

    // ģ��λ�Ƶ���Ϣ
    float m_fTrans[3];

    // ������������ܵ�����
    char m_caName[16];

    // ÿ����ܶ����Լ��Ķ�����Ϣ
    SMD2Vert *m_pVerts;

    // ���캯��
    SMD2Frame()
    {
        m_pVerts = 0;
    }

    // ��������
    ~SMD2Frame()
    {
        if ( m_pVerts )
        {
            delete[] m_pVerts;
        }
    }
};

// �����ε���Ϣ�����Ƶ�ʱ���������Ⱦ����ҵ������Σ�
// �Ӷ���ȡ�����εĵ��������Ϣ��Ȼ�����ģ��
struct SMD2Tri
{
    // ����������������Ϣ
    unsigned short m_sVertIndices[3];

    // ����������������Ϣ
    unsigned short m_sTexIndices[3];
};

// �����������Ϣ
struct SMD2TexCoord
{
    // ����ͼ������
    float m_fTex[2];
};

// ��ȡ������ͼ������
struct SMD2Skin
{
    char m_caSkin[64];
};

class Md2
{
public:
    // ������Դ
    bool load(const char *szFileName);

    // ���ڻ���ģ�ͣ��趨�������
    void Render();

    // ����һ�����֣����ǵ�ǰҪ��Ⱦ�����ĸ����
    void Render(unsigned int uiFame);

    // ����MD2�������������
    void Animate(float fSpeed = 30.0f,              // �����ٶ�
                 unsigned int uiStartFrame = 0,     // ��һ����ܱ��
                 unsigned int uiEndframe = 0,       // ���һ����ܱ��
                 bool bLoop = true);                // ʱ��ѭ������

    // ����������
    Md2();
    ~Md2();

    // ���Ŷ�����ʱ��������Բ�ֵ�����������
    float   m_timer;

private:
    // ����ͷ��
    SMD2Header  m_Head;

    // ������
    SMD2Frame   *m_pFrames;

    // ���������ε���Ϣ
    SMD2Tri     *m_pTriangles;

    // �������������������Ϣ
    SMD2TexCoord    *m_pTexCoords;

    // ��������
    SMD2Skin        *m_pSkins;

    // ��������
    SMD2Vert        *m_pVerts;

    unsigned int    m_uiSkin;
};
