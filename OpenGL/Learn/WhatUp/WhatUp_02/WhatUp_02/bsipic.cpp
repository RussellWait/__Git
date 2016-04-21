
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "bsipic.h"
#include <time.h>


#define FRAND	((rand()%256) / 255.0f)


GLfloat r=0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bsipic::bsipic()
{  
	srand((unsigned)time(0));

	g_text = gluNewQuadric();
	LoadT8("aa.BMP", g_cactus[0]);
	LoadT8("bb.BMP", g_cactus[1]);
}

bsipic::~bsipic()
{}

void bsipic::light0(float x,float y,float z,float a)
{
	GLfloat light_position[] = {x,y,z,a};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void bsipic::airplane(float x,float y,float z)
{ 
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(-r, 0.0, 1.0, 0.0);
	glTranslatef(30,0,0);		 
	glRotatef(30, 0.0, 0.0, 1.0);
	//=============================================
	glPushMatrix();//
		glRotatef(-r*30, 0.0, 0.0, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		Box(1.0f,0.1f,0.02f);		
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);
	glTranslatef(0.0f,0.0f,-0.5f);
	gluSphere(g_text, 0.4f, 8, 8); 
	//=============================================
	glTranslatef(0.0f,-0.0f,-2);
	gluCylinder(g_text,0.4,0.4,2.0,8,4);
	//=====================================================
	glRotatef(-180, 1.0, 0.0, 0.0);
	glTranslatef(0.0f,-0.0f,0.0f);
	gluCylinder(g_text,0.4,0.1,1.5,8,4);
	//======================================================
	glBindTexture(GL_TEXTURE_2D, g_cactus[0]);//
	glTranslatef(0.0f,-0.8f,1.2f);
	Box(1.0,0.05f,0.3f);
	glTranslatef(0.0f,0.1f,0.0f);
	Box(0.05f,0.6f,0.30f);	
	//======================================================
	glTranslatef(0.0f,0.7f,-1.9f);
	Box(3,0.05f,0.5f);	
	//======================================================
	glDisable(GL_TEXTURE_2D);
 glPopMatrix();
}

void bsipic::Box(float x,float y,float z)
{ glPushMatrix();
  glScalef(x,y,z);
  glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);// 前
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 后
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);// 上
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 下
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);// 左
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);// 右
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
 glDisable(GL_TEXTURE_2D);
 glPopMatrix();
}

void bsipic::picter(float x,float y,float z)
{
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glTranslatef(x,y+0.5f,z);
	glColor3f(0.0f,1.0f,0.2f);
	auxSolidCube(1);	
	glTranslatef(0.0f,0.8f,0.0f);
	glColor3f(0.0f,0.0f,1.0f);
	auxSolidBox(.2f,1.3f,.2f);	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x,y+2.5f,z);
	glRotatef(r-90,0.0,1.0,0.0);
	//=======================================
	glColor3f(1.0f,1.0f,1.0f);	
	glRotatef(45, 1.0, 0.0, 0.0);
	auxWireCone(1.5,0.6f);	
	//=======================================
	glRotatef(180, 1.0, 0.0, 0.0);
	glTranslatef(0.0f,0.0f,-0.7f); 
	auxWireCone(0.2f,2.0f);
	glColor3f(FRAND,0,0);		
	glTranslatef(0.0f,0.0f,2.0f);
	auxSolidSphere(0.1f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x,y+10.0f,z);
	glRotatef(r, 0.0, 1.0, 0.0);
	glTranslatef(15,0,0);	
	//=============================================
	glColor3f(1.0f,0.0f,0.0f);
	glRotatef(180, 0.0, 1.0, 0.0);
	auxSolidCone(.2,0.6);
	//=============================================
	glColor3f(1.0f,1.0f,1.0f);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(0.0f,-1.0f,0);
	auxSolidCylinder(.2f,1);
	glRotatef(-270, 1.0, 0.0, 0.0);
	glColor3f(FRAND+.6f,0.2f,0.0f);
	glTranslatef(0.0f,-0.0f,-0.2f); 
	auxSolidCone(.2,1.5);
	glPopMatrix();
	glPopAttrib();
	r+=0.5f; if ( r > 360 ) r=0;
}

bool bsipic::LoadT8(char *filename, GLuint &texture)
{	
	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);
	if(pImage == NULL)		return false;
	glGenTextures(1, &texture);		
	glBindTexture    (GL_TEXTURE_2D,texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4, pImage->sizeX, 
					  pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	free(pImage->data);
	free(pImage);	
	return true;
}