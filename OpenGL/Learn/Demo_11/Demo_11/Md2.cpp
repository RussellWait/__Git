#include "Md2.h"
#include <stdio.h>


extern CLoadImage g_Skin;


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
    if (m_pFrames)
    {
        delete[] m_pFrames;
        m_pFrames = NULL;
    }

    if (m_pTexCoords)
    {
        delete[] m_pTexCoords;
        m_pTexCoords = NULL;
    }

    if (m_pTriangles)
    {
        delete[] m_pTriangles;
        m_pTriangles = NULL;
    }

    if (m_pSkins)
    {
        delete[] m_pSkins;
        m_pSkins = NULL;
    }

    if (m_pVerts)
    {
        delete[] m_pVerts;
        m_pVerts = NULL;
    }
}

bool CMD2::Load(const char *szFilename)
{
    unsigned char *ucpBuffer = NULL;    // 存放MD2模型里面所有内容的地址
    unsigned char *ucpPtr = NULL;       // 读取MD2模型各个部分的起始位置
    unsigned char *ucpTmpPtr = NULL;    // 读取MD2模型其中一个部分的内容的信息
    int iFileSize = 0;                  // MD2文件大小
    FILE *f = NULL;                     // 打开的文件

    // 只读形式打开文件
    if ( !(f = fopen(szFilename, "rb")) )
    {
        return false;
    }

    // 计算文件大小
    int iStart = ftell(f);
    fseek(f, 0, SEEK_END);
    int iEnd = ftell(f);
    fseek(f, 0, SEEK_SET);
    iFileSize = iEnd - iStart;

    // 存放MD2文件中所有内容
    ucpBuffer = new unsigned char[iFileSize];
    ucpPtr = ucpBuffer;
    if (!ucpBuffer)
    {
        return false;
    }

    // 读取MD2文件的所有内容到我们定制的区域
    if ( fread(ucpBuffer, 1, iFileSize, f) != (unsigned)iFileSize)
    {
        delete[] ucpBuffer;
        return false;
    }
    fclose(f);

    // 读取文件头信息
    memcpy(&m_Header, ucpPtr, sizeof(SMD2Header));

    // 判断ID号与版本号（规定为844121161和8）
    if ( 844121161 != m_Header.m_iMagicNum || 8 != m_Header.m_iVersion)
    {
        delete[] ucpBuffer;
        return false;
    }

    // 读取框架信息
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetFrames;
    m_pFrames = new SMD2Frame[m_Header.m_iNumFrames];

    for ( int i = 0; i < m_Header.m_iNumFrames; i++ )
    {
        // 旋转信息
        float fScale[3];
        // 位移信息
        float fTrangs[3];
        // 顶点信息
        m_pFrames[i].m_pVerts = new SMD2Vert[m_Header.m_iNumVertices];

        memcpy(fScale, ucpTmpPtr, 12);
        ucpTmpPtr += 12;

        memcpy(fTrangs, ucpTmpPtr, 12);
        ucpTmpPtr += 12;

        memcpy(m_pFrames[i].m_caName, ucpTmpPtr, 16);
        ucpTmpPtr += 16;

        for ( int j = 0; j < m_Header.m_iNumVertices; j++ )
        {
            // MD2顶点是经过压缩的，要进行解压缩操作
            m_pFrames[i].m_pVerts[j].m_fVert[0] = ucpTmpPtr[0] * fScale[0] + fTrangs[0];
            m_pFrames[i].m_pVerts[j].m_fVert[1] = ucpTmpPtr[2] * fScale[2] + fTrangs[2];
            m_pFrames[i].m_pVerts[j].m_fVert[2] = ucpTmpPtr[1] * fScale[1] + fTrangs[1];
            m_pFrames[i].m_pVerts[j].m_ucReserved = ucpTmpPtr[3];
            ucpTmpPtr += 4;
        }
    }

    // 读取三角形信息
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetTriangles;
    m_pTriangles = new SMD2Tri[m_Header.m_iNumTriangles];
    memcpy(m_pTriangles, ucpTmpPtr, 12 * m_Header.m_iNumTriangles);

    // 读取纹理坐标信息
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetTexCoords;
    m_pTexCoords = new SMD2TexCoord[m_Header.m_iNumTexCoords];
    short *sTexCoords = new short[m_Header.m_iNumTexCoords * 2];
    memcpy(sTexCoords, ucpTmpPtr, 4 * m_Header.m_iNumTexCoords);

    for ( int i = 0; i < m_Header.m_iNumTriangles; i++ )
    {
        m_pTexCoords[i].m_fTex[0] = (float)sTexCoords[2 * i] / m_Header.m_iSkinWidthPx;
        m_pTexCoords[i].m_fTex[1] = (float)sTexCoords[2 * i + 1] / m_Header.m_iSkinHeightPx;
    }
    delete[] sTexCoords;

    // 读取纹理信息
    ucpTmpPtr = ucpPtr + m_Header.m_iOffsetSkins;
    m_pSkins = new SMD2Skin[m_Header.m_iNumSkins];

    for ( int i = 0; i < m_Header.m_iNumSkins; i++ )
    {
        memcpy(m_pSkins[i].m_caSkin, ucpTmpPtr, 64);
        // 去掉 '/' 只要文件名
        char *szEnd = strchr(m_pSkins[i].m_caSkin, '/');
        if (szEnd)
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
        // 纹理坐标
        glTexCoord2f(m_pTexCoords[m_pTriangles[x].m_sTexIndices[0].m_fTex[0]],
                     1-m_pTexCoords[m_pTriangles[x].m_sTexIndices[0].m_fTex[1]]);
        glVertex3fv(m_pFrames[0].m_pVerts[m_pTriangles[x].m_sVertIndices[0]]->m_fVert);

        glTexCoord2f();
    }

    glEnd();
}

