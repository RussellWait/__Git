#include "MD3.h"
#include <stdio.h>


CMD3::CMD3()
{
    m_pTags         = NULL;
    m_pMeshes       = NULL;
    m_pInterpTags   = NULL;
    m_ppAttachments = NULL;

    m_uiLastFrame   = 0;
    m_fLastInterp   = 0.0f;
}

CMD3::~CMD3()
{
    if ( m_pTags )
    {
        delete[] m_pTags;
        m_pTags = NULL;
    }

    if ( m_pMeshes )
    {
        delete[] m_pMeshes;
        m_pMeshes = NULL;
    }

    if ( m_pInterpTags )
    {
        delete[] m_pInterpTags;
        m_pInterpTags = NULL;
    }

    if ( m_ppAttachments )
    {
        delete[] m_ppAttachments;
        m_ppAttachments = NULL;
    }
}


bool CMD3::Load(const char *szFileName)
{

}

void CMD3::Render()
{

}

void CMD3::Render()
{

}

void CMD3::Animate(unsigned int uiStartFrame, unsigned int uiEndFrame, int uiFPS /* = 10 */, bool bLoop /* = true */)
{

}

void CMD3::Attach(CMD3 *pModel, unsigned int uiTag)
{

}
