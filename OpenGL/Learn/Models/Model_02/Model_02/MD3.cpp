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
	unsigned char *ucpBuffer	= NULL;
	unsigned char *ucpTmp		= NULL;
	int iFileSize				= 0;

	FILE *f = fopen(szFileName, "rb");
	if ( !f )
	{
		return false;
	}

	fseek(f, 0, SEEK_END);
	int iEnd = ftell(f);
	fseek(f, 0, SEEK_SET);
	int iBegin = ftell(f);
	iFileSize = iEnd - iBegin;

	ucpBuffer = new unsigned char[iFileSize];
	ucpTmp = ucpBuffer;
	if ( !ucpBuffer )
	{
		fclose(f);
		return false;
	}

	// 将文件内容读取到ucpBuffer中
	fread(ucpBuffer, 1, iFileSize, f);
	fclose(f);

	// 
	m_Header = *(SMD3Header *)ucpTmp;
	ucpTmp += sizeof(SMD3Header);


	if ( idP3 != m_Header.m_iID || versionP3 != m_Header.m_iVersion )
	{
		return false;
	}
	ucpTmp += m_Header.m_iNumFrame * 56;

	// 为读取tag分配空间
	m_pTags = new SMD3Tag[m_Header.m_iNumTags * m_Header.m_iNumFrame];

	// 存放插值后的tag
	m_pInterpTags = new SMD3Tag[m_Header.m_iNumTags];

	// tag要链接的模型，开始时每一个tag都是NULL
	m_ppAttachments = new CMD3 *[m_Header.m_iNumTags];
	for ( int i = 0; i < m_Header.m_iNumTags; i++ )
	{
		m_ppAttachments[i] = NULL;
	}

	for ( int i = 0; i < m_Header.m_iNumTags * m_Header.m_iNumFrame; i++ )
	{
		// 拷贝tag的名字
		memcpy(m_pTags[i].m_cName, ucpTmp, 64);
		ucpTmp += 64;

		// 拷贝tag中的位置，并存放于m_pTags[i].m_vecPos.Get()所返回的空间中
		memcpy(m_pTags[i].m_vecPos.Get(), ucpTmp, 12);
		ucpTmp += 12;

		// 拷贝tag中的旋转矩阵的信息，并存放于tem.Get()所返回的空间中
		CMatrix3X3 tmp;
		memcpy(tmp.Get(), ucpTmp, 36);
		ucpTmp += 36;

		// 将获取的矩阵转为四元素以便插值计算
		m_pTags[i].m_qRot.FromMatrix(tmp);
	}

	// 分贝存储网格的空间
	m_pMeshes = new SMD3Mesh[m_Header.m_iNumMeshes];
	unsigned char *ucpTmp2 = ucpTmp;
	for ( int i = 0; i < m_Header.m_iNumMeshes; i++ )
	{
		memcpy(&m_pMeshes[i].m_Header, ucpTmp2, sizeof(SMD3MeshHeader));
		ucpTmp2 += m_pMeshes[i].m_Header.m_iHeaderSize;

		// 分配存储图片的空间
		m_pMeshes[i].m_pSkins = new SMD3Skin[m_pMeshes[i].m_Header.m_iNumSkins];
		for ( int j = 0; j < m_pMeshes[i].m_Header.m_iNumSkins; j++ )
		{
			char cName[68];
			memcpy(cName, ucpTmp2, 68);
			cName[0] = 'M';
			ucpTmp2 += 68;

			// 查找字符'\\'在cName所指定字符串中从后往前第一次出现的位置并返回该位置
			char *cpStart = strrchr(cName, '\\');

			int cNameLen = strlen(cName);

			cName[cNameLen - 1] = 'p';
			cName[cNameLen - 2] = 'm';
			cName[cNameLen - 3] = 'b';

			if ( cpStart )
			{
				strcpy(m_pMeshes[i].m_pSkins[j].m_cName, cpStart + 1);
			}
			else
			{
				strcpy(m_pMeshes[i].m_pSkins[j].m_cName, cName);
			}

			m_pMeshes[i].m_pSkins[j].m_Image.LoadBMP(m_pMeshes[i].m_pSkins[j].m_cName);
		}

		m_pMeshes[i].m_pKeyFrames = new SMD3KeyFrame[m_pMeshes[i].m_Header.m_iNumMeshFrames];

		// 顶点存放的起始位置
		ucpTmp2 = ucpTmp + m_pMeshes[i].m_Header.m_iVertexOffset;

		// MD3中关键帧就是存放了一组顶点，所以我们按照关键帧的数量来读取相应的顶点
		for ( int j = 0; j < m_pMeshes[i].m_Header.m_iNumMeshFrames; j++ )
		{
			m_pMeshes[i].m_pKeyFrames[j].m_pVertices = new SMD3Vertex [m_pMeshes[i].m_Header.m_iNumVerts];
			for ( int k = 0; k < m_pMeshes[i].m_Header.m_iNumVerts; k++ )
			{
				short sTmp = *(short *)ucpTmp2;
				m_pMeshes[i].m_pKeyFrames[j].m_pVertices[k].m_fVert[0] = (float)sTmp / 64.0f;

				sTmp = *(short *)&ucpTmp2[2];
				m_pMeshes[i].m_pKeyFrames[j].m_pVertices[k].m_fVert[1] = (float)sTmp / 64.0f;

				sTmp = *(short *)&ucpTmp2[4];
				m_pMeshes[i].m_pKeyFrames[j].m_pVertices[k].m_fVert[2] = (float)sTmp / 64.0f;

				ucpTmp2 += 6;
				ucpTmp2 += 2;
			}
		}

		// 分配存放三角形的空间
		m_pMeshes[i].m_pFaces = new SMD3Face[m_pMeshes[i].m_Header.m_iNumTriangles];
		ucpTmp2 = ucpTmp + m_pMeshes[i].m_Header.m_iTriOffset;
		for ( int j = 0; j < m_pMeshes[i].m_Header.m_iNumTriangles; j++ )
		{
			memcpy(m_pMeshes[i].m_pFaces[j].m_uiIndices, ucpTmp2, 12);
			ucpTmp2 += 12;
		}

		// 读取纹理坐标
		m_pMeshes[i].m_pTexCoords = new SMD3TexCoord[m_pMeshes[i].m_Header.m_iNumVerts];
		ucpTmp2 = ucpTmp + m_pMeshes[i].m_Header.m_iUVOffset;
		for ( int j = 0; j < m_pMeshes[i].m_Header.m_iNumVerts; j++ )
		{
			memcpy(m_pMeshes[i].m_pTexCoords[j].m_fTexCoord, ucpTmp2, 8);
			ucpTmp2 += 8;
		}

		m_pMeshes[i].m_pInterp = NULL;
		ucpTmp += m_pMeshes[i].m_Header.m_iMeshSize;
		ucpTmp2 = ucpTmp;
	}

	if ( ucpBuffer )
	{
		delete[] ucpBuffer;
	}

	return true;
}

void CMD3::Render()
{
	int iNumMeshes = m_Header.m_iNumMeshes;
	for ( int i = 0; i < iNumMeshes; i++ )
	{
		SMD3TexCoord *pTexCoords = m_pMeshes[i].m_pTexCoords;
		SMD3Vertex *pVertices = m_pMeshes[i].m_pKeyFrames[0].m_pVertices;
		SMD3Face *pFaces = m_pMeshes[i].m_pFaces;

		int iNumTri = m_pMeshes[i].m_Header.m_iNumTriangles;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pMeshes[i].m_pSkins[0].m_Image.m_texture[0]);

		glBegin(GL_TRIANGLES);
		for ( int j = 0; j < iNumTri; j++ )
		{
			glTexCoord2fv(pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[0]].m_fTexCoord);
			glVertex3fv(pVertices[pFaces[j].m_uiIndices[0]].m_fVert);

			glTexCoord2fv(pTexCoords[pFaces[j].m_uiIndices[1]].m_fTexCoord);
			glVertex3fv(pVertices[pFaces[j].m_uiIndices[1]].m_fVert);

			glTexCoord2fv(pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[2]].m_fTexCoord);
			glVertex3fv(pVertices[pFaces[j].m_uiIndices[2]].m_fVert);
		}
		glEnd();
	}
}

void CMD3::RenderT()
{
	int iNumMeshes = m_Header.m_iNumMeshes;
	for ( int i = 0; i < iNumMeshes; i++ )
	{
		SMD3TexCoord *pTexCoords = m_pMeshes[i].m_pTexCoords;
		SMD3Face *pFaces = m_pMeshes[i].m_pFaces;

		// 插值后的顶点
		SMD3Vertex *pVertices = m_pMeshes[i].m_pInterp;

		int iNumTri = m_pMeshes[i].m_Header.m_iNumTriangles;

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pMeshes[i].m_pSkins[0].m_Image.m_texture[0]);

		glBegin(GL_TRIANGLES);
		for ( int j = 0; j < iNumTri; j++ )
		{
			glTexCoord2f(pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[0]].m_fTexCoord[0],
						 1-pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[0]].m_fTexCoord[1]);
			glVertex3fv(pVertices[pFaces[j].m_uiIndices[0]].m_fVert);

			glTexCoord2f(pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[1]].m_fTexCoord[0],
						 1 - pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[1]].m_fTexCoord[1]);
			glVertex3fv(pVertices[pFaces[j].m_uiIndices[1]].m_fVert);

			glTexCoord2f(pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[2]].m_fTexCoord[0],
						 1 - pTexCoords[m_pMeshes[i].m_pFaces[j].m_uiIndices[2]].m_fTexCoord[1]);
			glVertex3fv(pVertices[pFaces[j].m_uiIndices[2]].m_fVert);
		}
		glEnd();
	}

	int iNumTag = m_Header.m_iNumTags;
	for ( int i = 0; i < iNumTag; i++ )
	{
		if ( m_ppAttachments[i] )
		{
			CMatrix4X4 matTmp;
			matTmp.Identity();

			matTmp.FromQuaternion(m_pInterpTags[i].m_qRot);
			matTmp.SetTranslation(m_pInterpTags[i].m_vecPos.Get());

			// 将矩阵与堆栈中的矩阵相乘
			glPushMatrix();
			glMultMatrixf(matTmp.Get());
				m_ppAttachments[i]->RenderT();
			glPopMatrix();
		}
	}
}

void CMD3::Animate(unsigned int uiStartFrame, unsigned int uiEndFrame, int uiFPS /* = 10 */, bool bLoop /* = true */)
{
	int iNumMeshes = m_Header.m_iNumMeshes;

	if ( m_uiLastFrame < uiStartFrame )
	{
		m_uiLastFrame = uiStartFrame;
	}

	if ( uiEndFrame >= (unsigned)m_Header.m_iNumFrame )
	{
		uiEndFrame = m_Header.m_iNumFrame - 1;
	}

	if ( m_uiLastFrame > uiEndFrame )
	{
		m_uiLastFrame = uiStartFrame;
	}

	// 每帧之间的时间控制并用于插值
	if ( my_timer < 1.0f )
	{
		my_timer = my_timer + 0.05f;
	}
	else
	{
		my_timer = 0.0f;
		m_uiLastFrame++;
		if (m_uiLastFrame >= uiEndFrame)
		{
			m_uiLastFrame = uiStartFrame;
		}
	}

	float fInterp = my_timer;

	unsigned int uiNextFrame = m_uiLastFrame + 1;
	if ( m_uiLastFrame == uiEndFrame - 1 )
	{
		uiNextFrame = uiStartFrame;
	}

	for ( int i = 0; i < m_Header.m_iNumTags; i++ )
	{
		if ( uiStartFrame == uiEndFrame )
		{
			memcpy(&m_pInterpTags[i], &m_pTags[m_uiLastFrame * m_Header.m_iNumTags + i], sizeof(SMD3Tag));
		}
		else
		{
			SMD3Tag *pLastTag = &m_pTags[m_uiLastFrame * m_Header.m_iNumTags + i];
			SMD3Tag *pNextTag = &m_pTags[uiNextFrame * m_Header.m_iNumTags + i];
			m_pInterpTags[i].m_qRot = SLERP(pLastTag->m_qRot, pNextTag->m_qRot, fInterp);

			float *fVec = m_pInterpTags[i].m_vecPos.Get();
			fVec[0] = pLastTag->m_vecPos.Get()[0] + (pNextTag->m_vecPos.Get()[0] - pLastTag->m_vecPos.Get()[0]) * fInterp;
			fVec[1] = pLastTag->m_vecPos.Get()[1] + (pNextTag->m_vecPos.Get()[1] - pLastTag->m_vecPos.Get()[1]) * fInterp;
			fVec[2] = pLastTag->m_vecPos.Get()[2] + (pNextTag->m_vecPos.Get()[2] - pLastTag->m_vecPos.Get()[2]) * fInterp;
		}
	}

	for ( int i = 0; i < iNumMeshes; i++ )
	{
        if ( !m_pMeshes[i].m_pInterp )
        {
            m_pMeshes[i].m_pInterp = new SMD3Vertex[m_pMeshes[i].m_Header.m_iNumVerts];
        }

        SMD3Vertex *pVertices = m_pMeshes[i].m_pInterp;

        if ( uiStartFrame == uiEndFrame )
        {
            memcpy(m_pMeshes[i].m_pInterp, m_pMeshes[i].m_pKeyFrames[m_uiLastFrame].m_pVertices, sizeof(SMD3Vertex) * m_pMeshes[i].m_Header.m_iNumVerts);
        }
        else
        {
            SMD3KeyFrame *pLastFrame = &m_pMeshes[i].m_pKeyFrames[m_uiLastFrame];
            SMD3KeyFrame *pNextFrame = &m_pMeshes[i].m_pKeyFrames[uiNextFrame];

            int iNumVerts = m_pMeshes[i].m_Header.m_iNumVerts;
            for ( int j = 0; j < iNumVerts; j++ )
            {
                pVertices[j].m_fVert[0] = pLastFrame->m_pVertices[j].m_fVert[0] + (pNextFrame->m_pVertices[j].m_fVert[0] - pLastFrame->m_pVertices[j].m_fVert[0]) * fInterp;
                pVertices[j].m_fVert[1] = pLastFrame->m_pVertices[j].m_fVert[1] + (pNextFrame->m_pVertices[j].m_fVert[1] - pLastFrame->m_pVertices[j].m_fVert[1]) * fInterp;
                pVertices[j].m_fVert[2] = pLastFrame->m_pVertices[j].m_fVert[2] + (pNextFrame->m_pVertices[j].m_fVert[2] - pLastFrame->m_pVertices[j].m_fVert[2]) * fInterp;
            }
        }
	}
}

void CMD3::Attach(CMD3 *pModel, unsigned int uiTag)
{
	m_ppAttachments[uiTag] = pModel;
}
