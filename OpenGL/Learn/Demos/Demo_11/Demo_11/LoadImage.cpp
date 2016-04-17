#include "LoadImage.h"


BOOL CLoadImage::LoadBMP(char *szFileName)
{
    BOOL state = FALSE;

    AUX_RGBImageRec *textureImage[1];
    memset(textureImage, 0, sizeof(void *) * 1);

    if (textureImage[0] = auxDIBImageLoad(szFileName))
    {
        state = TRUE;

        m_szFileName    = szFileName;
        m_uiWidth       = textureImage[0]->sizeX;
        m_uiHeight      = textureImage[0]->sizeY;
        m_uiFileLen     = sizeof(textureImage[0]->data);

        glGenTextures(1, m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, m_uiWidth, m_uiHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
    }

    if ( textureImage[0] )
    {
        if ( textureImage[0]->data )
        {
            free(textureImage[0]->data);
        }
        free(textureImage[0]);
    }

    return state;
}
