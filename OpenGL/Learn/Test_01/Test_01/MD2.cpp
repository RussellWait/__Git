#include "MD2.h"
#include <stdio.h>


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

    if (m_pTriangles)
    {
        delete[] m_pTriangles;
        m_pTriangles = NULL;
    }

    if (m_pTexCoords)
    {
        delete[] m_pTexCoords;
        m_pTexCoords = NULL;
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
	iFileSize = iEnd = iStart;
}

void CMD2::Render()
{}

void CMD2::Animate(float fSpeed /* = 30.0f */, unsigned int uiStartFrame /* = 0 */, unsigned int uiEndFrame /* = 0 */, bool bLoop /* = true */)
{

}
