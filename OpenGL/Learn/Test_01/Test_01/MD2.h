#pragma once

#include "LoadImage.h"


struct SMD2Header
{
	int	m_iMagicNum;	// Always IDP2£¨844121161£©
	int m_iVersion;		// 8

	int m_iSkinWidthPx;
	int m_iSkinHeightPx;
	int m_iFrameSize;

	int m_iNumSkins;
	int m_iNumVertices;
	int m_iNumTexCoords;
	int m_iNumTriangles;
	int m_iNumGLCommands;
	int m_iNumFrames;

	int m_iOffsetSkins;
	int m_iOffsetTexCoords;
	int m_iOffsetTriangles;
	int m_iOffsetFrames;
	int m_iOffsetGLCommands;

	int m_iFileSize;
};

struct SMD2Vert
{
	float	m_fVert[3];
	unsigned char m_ucReserved;
};

struct SMD2Frame
{
//     float       m_fScale[3];
//     float       m_fTrans[3];
	char        m_caName[16];
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

struct SMD2Tri
{
    unsigned short m_sVertIndices[3];
    unsigned short m_sTexIndices[3];
};

struct SMD2TexCoord
{
    float m_fTex[2];
};

struct SMD2Skin
{
    char m_caSkin[64];
    CLoadImage m_Image;
};


class CMD2
{
public:
    CMD2();
    ~CMD2();

    bool Load(const char *szFileName);
    void Render();
    void Render(unsigned int uiFrame);
    void Animate(float fSpeed = 30.0f, unsigned int uiStartFrame = 0, unsigned int uiEndFrame = 0, bool bLoop = true);

    float my_timer;

private:
    SMD2Header      m_Header;
    SMD2Frame       *m_pFrames;
    SMD2Tri         *m_pTriangles;
    SMD2TexCoord    *m_pTexCoords;
    SMD2Skin        *m_pSkins;
    SMD2Vert        *m_pVerts;

    unsigned int    m_uiSkin;
};
