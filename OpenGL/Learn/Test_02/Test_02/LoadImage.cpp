#include "LoadImage.h"


BOOL CLoadImage::LoadBMP(char *szFileName)
{
    BOOL state = FALSE;

    AUX_RGBImageRec *textureImg[1];
    memset(textureImg, 0, sizeof(AUX_RGBImageRec) * 1);

    if ( textureImg[0] = auxDIBImageLoad(szFileName) )
    {
        state = TRUE;

        m_szFileName = szFileName;
        m_uiWidth = textureImg[0]->sizeX;
        m_uiHeight = textureImg[0]->sizeY;
        m_uiFileLen = sizeof(textureImg[0]->data);

        glGenTextures(1, m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture[0]);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, m_uiWidth, m_uiHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImg[0]->data);

        // ÎÆÀíËõ·Å
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // ²ã¼¶ÌùÍ¼
        //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, textureImg[0]->data);
    }

    if ( textureImg[0] )
    {
        if ( textureImg[0]->data )
        {
            free(textureImg[0]->data);
        }
        free(textureImg[0]);
    }

    return state;
}
