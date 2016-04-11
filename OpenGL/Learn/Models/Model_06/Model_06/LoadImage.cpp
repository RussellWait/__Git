#include "LoadImage.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>
#include <gl/GLAUX.H>


const char TGA_UHEADER[] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const char TGA_CHEADER[] = {0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0};

bool LoadTGA(bool bCompressed, unsigned char *ucpBuffer, unsigned int *textrues_h)
{
	unsigned int	uiBpp			= 0;
	unsigned int	uiType			= 0;
	unsigned int	uiImageSize		= 0;
	unsigned char	*ucpPtr			= ucpBuffer;
	unsigned char	*ucpData		= NULL;
	unsigned int	uiWidth			= 0;
	unsigned int	uiHeight		= 0;

	// ����12���ֽڵ�����ͼ�ο����Ϣ��λ��
	ucpPtr += 12;
	// ����TGA���ݲ���С��ģʽ�洢�����Խ���λ�Ƶ�ǰ���ټ��ϸ�λ�ŵõ���ȷ����ֵ
	uiWidth = (ucpPtr[1] << 8) + ucpPtr[0];
	uiHeight = (ucpPtr[3] << 8) + ucpPtr[2];
	
	uiBpp = ucpPtr[4];		// һ�����ص�λ���������ص����
	ucpPtr += 6;			// ����ImageData���洢���ص�����

	// �жϵ�ǰͼƬ������λ������������Ӧ��UIType��ֻ�ж�24λ��32λ��
	if ( 24 == uiBpp )
	{
		uiType = GL_RGB;
	}
	else if ( 32 == uiBpp )
	{
		uiType = GL_RGBA;
	}
	else
	{
		delete[] ucpBuffer;
		return false;
	}

	// ������Ϣ����TGAͼ��Ĵ�С������洢�ռ�
	uiImageSize = uiHeight * uiWidth * (uiBpp / 8);
	ucpData = new unsigned char[uiImageSize];

	if ( !ucpData )
	{
		delete[] ucpBuffer;
		return false;
	}

	if ( !bCompressed )
	{
		for ( int i = 0; i < uiImageSize; i += (uiBpp / 8) )
		{
			// swap red and blue bytes
			ucpData[i]		= ucpPtr[i + 2];
			ucpData[i + 1]	= ucpPtr[i + 1];
			ucpData[i + 2]	= ucpPtr[i];

			if ( 32 == uiBpp )
			{
				ucpData[i + 3] = ucpPtr[i + 3];
			}
		}
	}
	else
	{
		unsigned int uiDataPos = 0;
		
		do 
		{
			// Raw data û���ظ��ġ����ء��������ء�������0��ʼ����
			if ( ucpPtr[0] < 128 )
			{
				unsigned int uiCount = ucpPtr[0] * (uiBpp / 8) + 1;
				ucpPtr++;
				for ( unsigned int i = 0; i < uiCount; i += (uiBpp / 8) )
				{
					ucpData[uiDataPos]		= ucpPtr[2];
					ucpData[uiDataPos + 1]	= ucpPtr[1];
					ucpData[uiDataPos + 2]	= ucpPtr[0];
					ucpPtr += 3;
					uiDataPos += 3;
				
					if ( 32 == uiBpp )
					{
						ucpData[uiDataPos] = ucpPtr[3];
						ucpPtr++;
						uiDataPos++;
					}
				}
			}
			else
			{
				// ��ߵ�һλ�Ǳ�־λ����127����ȥ����ߵ�һλ����7λ��¼�������ظ��Ĵ���
				unsigned int uiCount = (ucpPtr[0] -= 127) * (uiBpp / 8);
				ucpPtr++;
				for ( unsigned int i = 0; i < uiCount; i += (uiBpp / 8) )
				{
					ucpData[uiDataPos]		= ucpPtr[2];
					ucpData[uiDataPos + 1]	= ucpPtr[1];
					ucpData[uiDataPos + 2]	= ucpPtr[0];
					uiDataPos += 3;
				
					if ( 32 == uiBpp )
					{
						ucpData[uiDataPos] = ucpPtr[3];
						uiDataPos++;
					}
				}

				ucpPtr += 3;
				if ( 32 == uiBpp )
				{
					ucpPtr++;
				}
			}
		} while ( uiDataPos < uiImageSize );
	}

	glGenTextures(1, textrues_h);
	glBindTexture(GL_TEXTURE_2D, *textrues_h);

	glTexImage2D(GL_TEXTURE_2D, 0, uiBpp / 8, uiWidth, uiHeight, 0, uiType, GL_UNSIGNED_BYTE, ucpData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] ucpData;
	delete[] ucpBuffer;

	return true;
}

bool Load(char *fileName, unsigned int *textrues_h)
{
	FILE *f;
	unsigned int uiFileLen;
	unsigned char *ucpBuffer;

	if ( !(f = fopen(fileName, "rb")) )
	{
		int len = strlen(fileName);
		fileName[len - 4] = '\0';
		strcat(fileName, "_s.tga");
		if ( !(f = fopen(fileName, "rb")) )
		{
			return false;
		}
	}

	fseek(f, 0, SEEK_END);
	int iEnd = ftell(f);
	fseek(f, 0, SEEK_SET);
	int iBegin = ftell(f);
	uiFileLen = iEnd - iBegin;

	ucpBuffer = new unsigned char[uiFileLen];

	if (!ucpBuffer)
	{
		return false;
	}

	// get data
	if ( fread(ucpBuffer, 1, uiFileLen, f) != uiFileLen )
	{
		if ( ucpBuffer )
		{
			delete[] ucpBuffer;
		}

		return false;
	}

	// ûѹ�����ͼ
	if ( 0 == memcmp(ucpBuffer, TGA_UHEADER, 3) )
	{
		LoadTGA(false, ucpBuffer, textrues_h);
		return true;
	}
	// ��ѹ�����ͼ
	else if ( 0 == memcmp(ucpBuffer, TGA_CHEADER, 3) )
	{
		LoadTGA(true, ucpBuffer, textrues_h);
		return true;
	}

	return false;
}
