#include <stdio.h>
#include "MS3D.h"


CMS3D::CMS3D()
{
    m_pVertices     = NULL;
    m_pTriangles    = NULL;
    m_pMeshes       = NULL;
    m_pMaterials    = NULL;
    m_bDrawMesh     = true;
    m_bDrawBones    = false;
}

CMS3D::CMS3D(const char *szFileName)
{

}

CMS3D::~CMS3D()
{
    if ( m_pVertices )
    {
        delete[] m_pVertices;
        m_pVertices = NULL;
    }

    if ( m_pTriangles )
    {
        delete[] m_pTriangles;
        m_pTriangles = NULL;
    }

    if ( m_pMeshes )
    {
        delete[] m_pMeshes;
        m_pMeshes = NULL;
    }

    if ( m_pMaterials )
    {
        delete[] m_pMaterials;
        m_pMaterials = NULL;
    }
}

bool CMS3D::Load(const char *szFileName)
{
    unsigned char   *ucpBuffer = NULL;
    unsigned char   *ucpPtr = NULL;

    FILE *f = fopen(szFileName, "rb");
    if ( !f )
    {
        return false;
    }

    fseek(f, 0, SEEK_END);
    int iEnd = ftell(f);
    fseek(f, 0, SEEK_SET);
    int iStart = ftell(f);
    unsigned int uiSize = iEnd - iStart;
    ucpBuffer = new unsigned char[uiSize];
    ucpPtr = ucpBuffer;
    
    if ( !ucpBuffer )
    {
        return false;
    }

    if ( fread(ucpBuffer, 1, uiSize, f) != uiSize )
    {
        delete[] ucpBuffer;
        return false;
    }

    if (memcmp(ucpPtr, "MS3D000000", 10) != 0)
    {
        delete[] ucpBuffer;
        return false;
    }

    ucpPtr += 10;
    if ( *(int *)ucpPtr != 3 && *(int *)ucpPtr != 4 )
    {
        delete[] ucpBuffer;
        return false;
    }
    ucpPtr += 4;

    m_usNumVerts = *(unsigned short *)ucpPtr;
    ucpPtr += 2;
    m_pVertices = new SMS3DVertex[m_usNumVerts];
    memcpy(m_pVertices, ucpPtr, m_usNumVerts * sizeof(SMS3DVertex));
    ucpPtr += m_usNumVerts * sizeof(SMS3DVertex);

    m_usNumMeshes = *(unsigned short *)ucpPtr;
    ucpPtr += 2;
    m_pMeshes = new SMS3DMesh[m_usNumMeshes];
    for ( int i = 0; i < m_usNumMeshes; i++ )
    {
        memcpy(&m_pMeshes[i], ucpPtr, 35);
        ucpPtr += 35;
        m_pMeshes[i].m_uspIndices = new unsigned short[m_pMeshes[i].m_usNumTris];
        memcpy(m_pMeshes[i].m_uspIndices, ucpPtr, m_pMeshes[i].m_usNumTris * 2);
        ucpPtr += m_pMeshes[i].m_usNumTris * 2;
        m_pMeshes[i].m_cMaterial = ucpPtr[0];
        ucpPtr++;
    }

    m_usNumMaterials = *(unsigned short *)ucpPtr;
    ucpPtr += 2;
    m_pMaterials = new SMS3DMatrial[m_usNumMaterials];
    for ( int i = 0; i < m_usNumMaterials; i++ )
    {
        memcpy(&m_pMaterials[i], ucpPtr, 361);
        ucpPtr += 361;
        if ( m_pMaterials[i].m_cTexture[0] != '\0' )
        {
            m_pMaterials[i].m_Texture.LoadBMP(&m_pMaterials[i].m_cTexture[2]);
        }
    }

    ucpPtr += 4;
    ucpPtr += 8;

    m_usNumJoints = *(unsigned short *)ucpPtr;
    ucpPtr += 2;
    m_pJoints = new SMS3DJoint[m_usNumJoints];
    for ( int i = 0; i < m_usNumJoints; i++ )
    {
        memcpy(&m_pJoints[i], ucpPtr, 93);
        ucpPtr += 93;
        m_pJoints[i].m_RotKeyFrames = new SMS3DKeyFrame[m_pJoints[i].m_usNumRotFrames];
        m_pJoints[i].m_TransKeyFrames = new SMS3DKeyFrame[m_pJoints[i].m_usNumRotFrames];
        memcpy(m_pJoints[i].m_RotKeyFrames, ucpPtr, m_pJoints[i].m_usNumRotFrames * sizeof(SMS3DKeyFrame));
        ucpPtr += m_pJoints[i].m_usNumRotFrames * sizeof(SMS3DKeyFrame);
        memcpy(m_pJoints[i].m_TransKeyFrames, ucpPtr, m_pJoints[i].m_usNumRotFrames * sizeof(SMS3DKeyFrame));
        ucpPtr += m_pJoints[i].m_usNumRotFrames * sizeof(SMS3DKeyFrame);
    }

    for ( int i = 0; i < m_usNumJoints; i++ )
    {
        if ( m_pJoints[i].m_cParent[0] != '\0' )
        {
            for ( int j = 0; j < m_usNumJoints; j++ )
            {
                if ( 0 == strcmp(m_pJoints[j].m_cName, m_pJoints[i].m_cName) )
                {
                    m_pJoints[i].m_sParent = j;
                }
            }
        }
        else
        {
            m_pJoints[i].m_sParent = -1;
        }
    }

    Setup();

    delete[] ucpBuffer;
    return true;
}

void CMS3D::Render()
{

}

void CMS3D::Render(float fTime)
{

}

void CMS3D::Animate(float fSpeed, float fStartTime, float fEndTime, bool bLoop)
{
    static bool bFirstTime = true;

    my_timer += 0.009f;
    float fTime = my_timer * fSpeed;

    if ( fTime > fEndTime )
    {
        if ( bLoop )
        {
            my_timer = 0.0f;
        }
        else
        {
            fTime = fEndTime;
        }
    }

    for ( int i = 0; i < m_usNumJoints; i++ )
    {
        CMatrix4X4 matTmp;
        SMS3DJoint *pJoint = &m_pJoints[i];
        unsigned int uiFrame = 0;

        if ( 0 == pJoint->m_usNumRotFrames && 0 == pJoint->m_TransKeyFrames )
        {
            pJoint->m_matFinal = pJoint->m_matAbs;
            continue;
        }

        while ( uiFrame < pJoint->m_usNumRotFrames && pJoint->m_TransKeyFrames[uiFrame].m_fTime < fTime )
        {
            uiFrame++;
        }

        float fTranslation[3];
        float fDeltaT = 1;
        float fInterp = 0;

        if ( 0 == uiFrame )
        {
            memcpy(fTranslation, pJoint->m_TransKeyFrames[0].m_fParam, sizeof(float[3]));
        }
        else if ( uiFrame == pJoint->m_usNumRotFrames )
        {
            memcpy(fTranslation, pJoint->m_TransKeyFrames[uiFrame - 1].m_fParam, sizeof(float[3]));
        }
        else
        {
            SMS3DKeyFrame *pkCur = &pJoint->m_TransKeyFrames[uiFrame];
            SMS3DKeyFrame *pkPrev = &pJoint->m_TransKeyFrames[uiFrame - 1];

            fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
            fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

            fTranslation[0] = pkPrev->m_fParam[0] + (pkCur->m_fParam[0] - pkPrev->m_fParam[0]) * fInterp;
            fTranslation[1] = pkPrev->m_fParam[1] + (pkCur->m_fParam[1] - pkPrev->m_fParam[1]) * fInterp;
            fTranslation[2] = pkPrev->m_fParam[2] + (pkCur->m_fParam[2] - pkPrev->m_fParam[2]) * fInterp;
        }

        uiFrame = 0;
        while ( uiFrame < pJoint->m_usNumRotFrames && pJoint->m_RotKeyFrames[uiFrame].m_fTime < fTime )
        {
            uiFrame++;
        }

        if ( 0 == uiFrame )
        {
            matTmp.SetRotation(pJoint->m_RotKeyFrames[0].m_fParam);
        }
        else if ( uiFrame == pJoint->m_usNumTransFrames )
        {
            matTmp.SetRotation(pJoint->m_RotKeyFrames[uiFrame - 1].m_fParam);
        }
        else
        {
            SMS3DKeyFrame *pkCur = &pJoint->m_RotKeyFrames[uiFrame];
            SMS3DKeyFrame *pkPrev = &pJoint->m_RotKeyFrames[uiFrame - 1];

            fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
            fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;

            CQuaternion qCur;
            CQuaternion qPrev;
            qCur.FromEulers(pkCur->m_fParam);
            qPrev.FromEulers(pkPrev->m_fParam);
            CQuaternion qFinal = SLERP(qPrev, qCur, fInterp);
            matTmp = qFinal.ToMatrix4();
        }

        matTmp.SetTranslation(fTranslation);

        CMatrix4X4 matFinal = pJoint->m_matLocal * matTmp;
        if (-1 == pJoint->m_sParent)
        {
            pJoint->m_matFinal = matFinal;
        }
        else
        {
            pJoint->m_matFinal = m_pJoints[pJoint->m_sParent].m_matFinal * matFinal;
        }
    }

    RenderT();
}

void CMS3D::SwapBoneDraw()
{

}

void CMS3D::SwapMeshDraw()
{

}

bool CMS3D::AreBonesEnabled()
{
    return false;
}

bool CMS3D::AreMeshesEnabled()
{
    return false;
}

void CMS3D::Setup()
{
    for ( int i = 0; i < m_usNumJoints; i++ )
    {
        m_pJoints[i].m_matLocal.SetRotation(m_pJoints[i].m_fRotation);
        m_pJoints[i].m_matLocal.SetTranslation(m_pJoints[i].m_fPosition);

        if ( -1 != m_pJoints[i].m_sParent )
        {
            m_pJoints[i].m_matAbs = m_pJoints[m_pJoints[i].m_sParent].m_matAbs * m_pJoints[i].m_matLocal;
        }
        else
        {
            m_pJoints[i].m_matAbs = m_pJoints[i].m_matLocal;
        }
        m_pJoints[i].m_matFinal = m_pJoints[i].m_matAbs;
    }

    for ( int i = 0; i < m_usNumVerts; i++ )
    {
        if ( -1 == m_pVertices[i].m_cBone )
        {
            continue;
        }

        CMatrix4X4 *mat = &m_pJoints[m_pVertices[i].m_cBone].m_matFinal;
        mat->InverseTranslateVec(m_pVertices[i].m_vVert.Get());
        mat->InverseRotateVec(m_pVertices[i].m_vVert.Get());
    }

    for ( int i = 0; i < m_usNumTriangles; i++ )
    {
        SMS3DTriangle *pTri = &m_pTriangles[i];
        for ( int j = 0; j < 3; j++ )
        {
            SMS3DVertex *pVert = &m_pVertices[pTri->m_usVertIndices[j]];
            if ( -1 == pVert->m_cBone )
            {
                continue;
            }

            SMS3DJoint *pJoint = &m_pJoints[pVert->m_cBone];
            pJoint->m_matFinal.InverseRotateVec(pTri->m_vNormals[j].Get());
        }
    }
}

void CMS3D::Reset()
{

}

void CMS3D::RenderT()
{
    glEnable(GL_TEXTURE_2D);

    for ( int i = 0; i < m_usNumMeshes; i++ )
    {
        if (m_pMeshes[i].m_cMaterial >= 0)
        {
            SMS3DMatrial *pCurMat = &m_pMaterials[m_pMeshes[i].m_cMaterial];
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, pCurMat->m_Texture.m_texture[0]);
        }

        CVector3 vecVertex;

        glBegin(GL_TRIANGLES);

        for ( int j = 0; j < m_pMeshes[i].m_usNumTris; j++ )
        {
            SMS3DTriangle *pTri = &m_pTriangles[m_pMeshes[i].m_uspIndices[j]];
            for ( int k = 0; k < 3; k++ )
            {
                SMS3DVertex *pVert = &m_pVertices[pTri->m_usVertIndices[k]];
                if ( -1 == pVert->m_cBone )
                {
                    glTexCoord2f(pTri->m_fTexCoords[0][k], 1 - pTri->m_fTexCoords[1][k]);
                    glVertex3fv(pVert->m_vVert.Get());
                }
                else
                {
                    glTexCoord2f(pTri->m_fTexCoords[0][k], 1.0 - pTri->m_fTexCoords[1][k]);
                    SMS3DJoint *pJoint = &m_pJoints[pVert->m_cBone];
                    
                    vecVertex = pVert->m_vVert;
                    vecVertex.Transform4(pJoint->m_matFinal);
                    glVertex3fv(vecVertex.Get());
                }
            }
        }

        glEnd();
    }
}
