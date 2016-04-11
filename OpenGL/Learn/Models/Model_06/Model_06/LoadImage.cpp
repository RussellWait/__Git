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

	// 跳过12个字节到达存放图形宽高信息的位置
	ucpPtr += 12;
	// 由于TGA数据采用小端模式存储，所以将低位移到前面再加上高位才得到正确的数值
	uiWidth = (ucpPtr[1] << 8) + ucpPtr[0];
	uiHeight = (ucpPtr[3] << 8) + ucpPtr[2];
	
	uiBpp = ucpPtr[4];		// 一个像素的位数，即像素的深度
	ucpPtr += 6;			// 调到ImageData即存储像素的区域

	// 判断当前图片的像素位数，并设置相应的UIType（只判断24位与32位）
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

	// 根据信息计算TGA图像的大小并分配存储空间
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
			// Raw data 没有重复的“像素”，“像素”数量从0开始计算
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
				// 最高的一位是标志位，件127就是去掉最高的一位，后7位记录了像素重复的次数
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

	// 没压缩真彩图
	if ( 0 == memcmp(ucpBuffer, TGA_UHEADER, 3) )
	{
		LoadTGA(false, ucpBuffer, textrues_h);
		return true;
	}
	// 有压缩真彩图
	else if ( 0 == memcmp(ucpBuffer, TGA_CHEADER, 3) )
	{
		LoadTGA(true, ucpBuffer, textrues_h);
		return true;
	}

	return false;
}
