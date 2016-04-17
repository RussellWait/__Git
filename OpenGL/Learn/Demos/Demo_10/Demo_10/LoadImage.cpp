#include "LoadImage.h"


BOOL CLoadImage::LoadBMP(char *szFileName)
{
    BOOL status = FALSE;

    AUX_RGBImageRec *textureImage[1];
    if (textureImage[0] = auxDIBImageLoad(szFileName))
    {
        status = TRUE;
        m_szFileName = szFileName;

        glGenTextures(1, m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
    }

    if (textureImage[0])
    {
        if (textureImage[0]->data)
        {
            free(textureImage[0]->data);
        }
        free(textureImage[0]);
    }

    return status;
}
