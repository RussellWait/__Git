#include "LoadImage.h"


CLoadImage::CLoadImage()
{
    m_szFileName = NULL;
}

CLoadImage::~CLoadImage()
{}

BOOL CLoadImage::LoadBMP(char *szFileName)
{
    BOOL status = FALSE;

    AUX_RGBImageRec *textureImage[1];
    memset(textureImage, 0, sizeof(void *) * 1);

    if ( textureImage[0] = auxDIBImageLoad(szFileName) )
    {
        status = TRUE;

        m_szFileName    = szFileName;
        m_uiWidth       = textureImage[0]->sizeX;
        m_uiHeight      = textureImage[0]->sizeY;
        m_uiFileLen     = sizeof(textureImage[0]->data);
        glGenTextures(1, m_texture);

        glBindTexture(GL_TEXTURE_2D, m_texture[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, m_uiWidth, m_uiHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    if ( textureImage[0] )
    {
        if ( textureImage[0]->data )
        {
            free(textureImage[0]->data);
        }
        free(textureImage[0]);
    }

    return status;
}
