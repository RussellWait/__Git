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
	char m_caName[16];
	SMD2Vert *m_pVerts;

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

};

struct SMD2Coord
{

};

struct SMD2Skin
{

};


class CMD2
{

};
