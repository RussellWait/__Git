#include "MD2.h"
#include <stdio.h>


extern CLoadImage   g_Skin;


CMD2::CMD2()
{
    m_pFrames       = NULL;
    m_pTriangles    = NULL;
    m_pTexCoords    = NULL;
    m_pSkins        = NULL;
    m_pVerts        = NULL;
    m_uiSkin        = 0;
}

CMD2::~CMD2()
{
    if ( m_pFrames )
    {
        delete[] m_pFrames;
        m_pFrames = NULL;
    }

    if ( m_pTriangles )
    {
        delete[] m_pTriangles;
        m_pTriangles = NULL;
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

    if ( m_pVerts )
    {
        delete[] m_pVerts;
        m_pVerts = NULL;
    }
}

bool CMD2::Load(const char *szFileName)
{
    unsigned char	*ucpBuffer	= NULL;
    unsigned char	*ucpPtr		= NULL;
    unsigned char	*ucpTmpPtr	= NULL;
    FILE			*f			= NULL;
    int				iFileSize	= 0;

    if ( !(f = fopen(szFileName, "rb")) )
    {
        return false;
    }

    // �ļ���С
    int iStart = ftell(f);
    fseek(f, 0, SEEK_END);
    int iEnd = ftell(f);
    fseek(f, 0, SEEK_SET);
    iFileSize = iEnd - iStart;

    // Ϊ�ļ����ݷ����ڴ�
    ucpBuffer = new unsigned char[iFileSize];
    ucpPtr = ucpBuffer;
    if ( !ucpBuffer )
    {
        return false;
    }

    // ��ȡ�ļ�����
    if ( fread(ucpBuffer, 1, iFileSize, f) != (unsigned)iFileSize )
    {
        delete[] ucpBuffer;
        fclose(f);
        return false;
    }
    fclose(f);

    // ��ȡͷ�ļ�����
    memcpy(&m_Header, ucpBuffer, sizeof(SMD2Header));

    // �ж��ļ��Ƿ���Ч
    if ( MD2_MAGIC_NUM != m_Header.m_iMagicNum || MD2_VERSION != m_Header.m_iVersion )
    {
        delete[] ucpBuffer;
        return false;
    }

    // ��ȡ�����Ϣ
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetFrames;
    m_pFrames = new SMD2Frame[m_Header.m_iNumFrames];
    for ( int i = 0; i < m_Header.m_iNumFrames; i++ )
    {
        float fScale[3];
        float fTrans[3];
        m_pFrames[i].m_pVerts = new SMD2Vert[m_Header.m_iNumVertices];

        memcpy(fScale, ucpTmpPtr, 12);
        ucpTmpPtr += 12;
        memcpy(fTrans, ucpTmpPtr, 12);
        ucpTmpPtr += 12;
        memcpy(m_pFrames[i].m_caName, ucpTmpPtr, 16);
        ucpTmpPtr += 16;

        for ( int j = 0; j < m_Header.m_iNumVertices; j++ )
        {
            m_pFrames[i].m_pVerts[j].m_fVert[0] = ucpTmpPtr[0] * fScale[0] + fTrans[0];
            m_pFrames[i].m_pVerts[j].m_fVert[1] = ucpTmpPtr[2] * fScale[2] + fTrans[2];
            m_pFrames[i].m_pVerts[j].m_fVert[2] = ucpTmpPtr[1] * fScale[1] + fTrans[1];
            m_pFrames[i].m_pVerts[j].m_ucReserved = ucpTmpPtr[3];
            ucpTmpPtr += 4;
        }
    }
    /************************************************************************/
    /* ��⣺
            ��ʵ�� �ļ��е�scale��trans����������verts�ĸ���ֵ��
            1.  ���õ�ǰ���ԣ�����ȫ�������Ҫռ�ÿռ�Ϊ���������Ϊm����������Ϊn����
            m * (12 + 12 + 16 + 4 * n) = 40*m + 4*m*n
            2.  ������ò�ʹ�������м�ֵ�����Ǽ�¼����������Ϣ������ȫ�����ռ�ÿռ�Ϊ��
            m * (16 + 12 * n) = 16*m + 12*m*n
            �Ƚ�: ���㲻��ʽ
            40*m + 4*m*n > 16*m + 12*m*n
            n < 3
            ����:   �ڶ�����С��3��ʱ�򣬲�����ȫ�����ķ�ʽ����ʡ�ռ䣨��ά����С��Ҫ3��������������
            ����3ʱ�����ֲ���ռ�ÿռ�һ���࣬���ڶ��ֲ��Բ���Ҫת�����㣬���Ը��ţ�
            ����3ʱ���õ�ǰ��������ʡ�ռ�.
            /************************************************************************/

    // ��ȡ��������Ϣ
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetTriangles;
    m_pTriangles = new SMD2Tri[m_Header.m_iNumTriangles];
    memcpy(m_pTriangles, ucpTmpPtr, sizeof(SMD2Tri) * m_Header.m_iNumTriangles);

    // ��ȡ����������Ϣ
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetTexCoords;
    m_pTexCoords = new SMD2TexCoord[m_Header.m_iNumTexCoords];
    short *sTexCoords = new short[m_Header.m_iNumTexCoords * 2];
    memcpy(sTexCoords, ucpTmpPtr, 4 * m_Header.m_iNumTexCoords);
    for ( int i = 0; i < m_Header.m_iNumTexCoords; i++ )
    {
        m_pTexCoords[i].m_fTex[0] = (float)sTexCoords[2 * i] / m_Header.m_iSkinWidthPx;
        m_pTexCoords[i].m_fTex[1] = (float)sTexCoords[2 * i + 1] / m_Header.m_iSkinHeightPx;
    }
    delete[] sTexCoords;

    // ��ȡ������Ϣ
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetSkins;
    m_pSkins = new SMD2Skin[m_Header.m_iNumSkins];
    for ( int i = 0; i < m_Header.m_iNumSkins; i++ )
    {
        memcpy(m_pSkins[i].m_caSkin, ucpTmpPtr, 64);
        char *szEnd = strchr(m_pSkins[i].m_caSkin, '/');
        if ( szEnd )
        {
            szEnd++;
            strcpy(m_pSkins[i].m_caSkin, szEnd);
        }
        m_pSkins[i].m_Image.LoadBMP(m_pSkins[i].m_caSkin);
        ucpTmpPtr += 64;
    }

    delete[] ucpBuffer;

    return true;
}

void CMD2::Render()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, g_Skin.m_texture[0]);
    glBegin(GL_TRIANGLES);

    for ( int i = 0; i < m_Header.m_iNumTriangles; i++ )
    {
        glTexCoord2f(m_pTexCoords[m_pTriangles[i].m_sTexIndices[0]].m_fTex[0],
                     1-m_pTexCoords[m_pTriangles[i].m_sTexIndices[0]].m_fTex[1]);
        glVertex3fv(m_pFrames[0].m_pVerts[m_pTriangles[i].m_sVertIndices[0]].m_fVert);

        glTexCoord2f(m_pTexCoords[m_pTriangles[i].m_sTexIndices[1]].m_fTex[0],
                     1-m_pTexCoords[m_pTriangles[i].m_sTexIndices[1]].m_fTex[1]);
        glVertex3fv(m_pFrames[0].m_pVerts[m_pTriangles[i].m_sVertIndices[1]].m_fVert);

        glTexCoord2f(m_pTexCoords[m_pTriangles[i].m_sTexIndices[2]].m_fTex[0],
                     1-m_pTexCoords[m_pTriangles[i].m_sTexIndices[2]].m_fTex[1]);
        glVertex3fv(m_pFrames[0].m_pVerts[m_pTriangles[i].m_sVertIndices[2]].m_fVert);
    }

    glEnd();
}

void CMD2::Animate(float fSpeed /* = 30.0f */, unsigned int uiStartFrame /* = 0 */, unsigned int uiEndFrame /* = 0 */, bool bLoop /* = true */)
{
    static unsigned int uiLastFrame = 0;

    if ( !m_pVerts )
    {
        m_pVerts = new SMD2Vert[m_Header.m_iNumVertices];
    }

    // ���֡���Ƿ���ȷ
    if ( uiEndFrame >= (unsigned)m_Header.m_iNumFrames )
    {
        uiEndFrame = m_Header.m_iNumFrames - 1;
    }
    if ( uiStartFrame >= (unsigned)m_Header.m_iNumFrames )
    {
        uiStartFrame = 0;
    }

    // ÿ֮֡���ʱ����Ʋ����ڲ�ֵ
    if (my_timer < 1.0f)
    {
        my_timer = my_timer + 0.05f;
    }
    else
    {
        my_timer = 0.0f;
        uiLastFrame++;
        if (uiLastFrame >= uiEndFrame)
        {
            uiLastFrame = uiStartFrame;
        }
    }
    float fInterpValue = my_timer;

    // ��ǰ֡����һ֡
    SMD2Frame *pCurFrame = &m_pFrames[uiLastFrame];
    SMD2Frame *pNextFrame = &m_pFrames[uiLastFrame + 1];
    if (uiLastFrame == uiEndFrame)
    {
        pNextFrame = &m_pFrames[uiStartFrame];
    }

    // �����ֵ
    for ( int i = 0; i < m_Header.m_iNumVertices; i++ )
    {
        m_pVerts[i].m_fVert[0] = pCurFrame->m_pVerts[i].m_fVert[0] +
            (pNextFrame->m_pVerts[i].m_fVert[0] - pCurFrame->m_pVerts[i].m_fVert[0]) * fInterpValue;

        m_pVerts[i].m_fVert[1] = pCurFrame->m_pVerts[i].m_fVert[1] +
            (pNextFrame->m_pVerts[i].m_fVert[1] - pCurFrame->m_pVerts[i].m_fVert[1]) * fInterpValue;

        m_pVerts[i].m_fVert[2] = pCurFrame->m_pVerts[i].m_fVert[2] +
            (pNextFrame->m_pVerts[i].m_fVert[2] - pCurFrame->m_pVerts[i].m_fVert[2]) * fInterpValue;
    }

    // ��ʼ��ͼ
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, g_Skin.m_texture[0]);
    glBegin(GL_TRIANGLES);

    for ( int i = 0; i < m_Header.m_iNumTriangles; i++ )
    {
         glTexCoord2f(m_pTexCoords[m_pTriangles[i].m_sTexIndices[0]].m_fTex[0],
                      1-m_pTexCoords[m_pTriangles[i].m_sTexIndices[0]].m_fTex[1]);
         glVertex3fv(m_pVerts[m_pTriangles[i].m_sVertIndices[0]].m_fVert);
 
         glTexCoord2f(m_pTexCoords[m_pTriangles[i].m_sTexIndices[1]].m_fTex[0],
                      1-m_pTexCoords[m_pTriangles[i].m_sTexIndices[1]].m_fTex[1]);
         glVertex3fv(m_pVerts[m_pTriangles[i].m_sVertIndices[1]].m_fVert);
 
         glTexCoord2f(m_pTexCoords[m_pTriangles[i].m_sTexIndices[2]].m_fTex[0],
                      1-m_pTexCoords[m_pTriangles[i].m_sTexIndices[2]].m_fTex[1]);
         glVertex3fv(m_pVerts[m_pTriangles[i].m_sVertIndices[2]].m_fVert);
    }

    glEnd();
}
