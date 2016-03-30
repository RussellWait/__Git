#pragma once

#include "LoadImage.h"
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"



struct SMS3DVertex
{
    unsigned char   m_ucFlags;
    CVector3        m_vVert;
    char            m_cBone;
    unsigned char   m_ucUnused;
};

struct SMS3DTriangle
{
    unsigned short  m_usFlags;
    unsigned short  m_usVertIndices[3];
    CVector3        m_vNormals[3];
    float           m_fTexCoords[2][3];
    unsigned char   m_ucSmoothing;
    unsigned char   m_ucGroup;
};

struct SMS3DMesh
{
    unsigned char   m_ucFlags;
    char            m_cName[32];
    unsigned short  m_usNumTris;
    unsigned short  *m_uspIndices;
    char            m_cMaterial;

    SMS3DMesh()
    {
        m_uspIndices = NULL;
    }

    ~SMS3DMesh()
    {
        if ( m_uspIndices )
        {
            delete[] m_uspIndices;
            m_uspIndices = NULL;
        }
    }
};

struct SMS3DMatrial
{
    char        m_cName[32];
    float       m_fAmbient[4];
    float       m_fDiffuse[4];
    float       m_fSpecular[4];
    float       m_fEmissive[4];
    float       m_fShininess;
    float       m_fTransparency;
    char        m_cMode;
    char        m_cTexture[128];
    char        m_cAlpha[128];
    CLoadImage  m_Texture;
};

struct SMS3DKeyFrame
{
    float   m_fTime;
    float   m_fParam[3];
};

struct SMS3DJoint
{
    unsigned char   m_ucpFlags;
    char            m_cName[32];
    char            m_cParent[32];
    float           m_fRotation[3];
    float           m_fPosition[3];
    unsigned short  m_usNumRotFrames;
    unsigned short  m_usNumTransFrames;

    SMS3DKeyFrame   *m_RotKeyFrames;
    SMS3DKeyFrame   *m_TransKeyFrames;

    short           m_sParent;

    CMatrix4X4      m_matLocal;
    CMatrix4X4      m_matAbs;
    CMatrix4X4      m_matFinal;

    unsigned short  m_usCurRotFrame;
    unsigned short  m_usCurTransFrame;

    SMS3DJoint()
    {
        m_RotKeyFrames      = NULL;
        m_TransKeyFrames    = NULL;
        m_usCurRotFrame     = 0;
        m_usCurTransFrame   = 0;
    }

    ~SMS3DJoint()
    {
        if ( m_RotKeyFrames )
        {
            delete[] m_RotKeyFrames;
            m_RotKeyFrames = NULL;
        }
        if ( m_TransKeyFrames )
        {
            delete[] m_TransKeyFrames;
            m_TransKeyFrames = NULL;
        }
    }
};

class CMS3D
{
public:
    CMS3D();
    CMS3D(const char *szFileName);
    ~CMS3D();

    bool Load(const char *szFileName);
    void Render();
    void Render(float fTime);
    void Animate(float fSpeed, float fStartTime, float fEndTime, bool bLoop);

    void SwapBoneDraw();
    void SwapMeshDraw();
    bool AreBonesEnabled();
    bool AreMeshesEnabled();


private:
    void Setup();
    void Reset();
    void RenderT();


    float           m_fTotalTime;
    bool            m_bDrawBones;
    bool            m_bDrawMesh;

    unsigned short  m_usNumVerts;
    unsigned short  m_usNumTriangles;
    unsigned short  m_usNumMeshes;
    unsigned short  m_usNumMaterials;
    unsigned short  m_usNumJoints;

    SMS3DVertex     *m_pVertices;
    SMS3DTriangle   *m_pTriangles;
    SMS3DMesh       *m_pMeshes;
    SMS3DMatrial    *m_pMaterials;
    SMS3DJoint      *m_pJoints;

    float           my_timer;
};
