
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "baiscobj.h"
GLfloat r=0;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
baiscobj::baiscobj()
{	g_eye[0]= MAP;//
	g_eye[2]=-MAP;//
	g_Angle=0;
	g_elev=0;
	g_text = gluNewQuadric();
	LoadT8("aa.BMP",g_cactus[0]);
	LoadT8("bb.BMP",g_cactus[1]);
}
baiscobj::~baiscobj()
{

}
void baiscobj::light0()
{	GLfloat light_position[] = {1.0,10.0,-51.0,10.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}
BOOL baiscobj::DisplayScene()
{ float speed=0.2f;	
  if (KEY_DOWN(VK_SHIFT))  speed   =speed*4;
  if (KEY_DOWN(VK_LEFT))   g_Angle-=speed*2;
  if (KEY_DOWN(VK_RIGHT))  g_Angle+=speed*2;
  rad_xz = float (3.13149* g_Angle/180.0f);
  if (KEY_DOWN(33)) g_elev +=0.2f;
  if (KEY_DOWN(34)) g_elev -=0.2f;
  if (g_elev<-100)	g_elev  =-100;
  if (g_elev> 100)	g_elev  = 100;
  if (KEY_DOWN(VK_UP))
  { g_eye[2]+=sin(rad_xz)*speed;
    g_eye[0]+=cos(rad_xz)*speed;
  }
  if (KEY_DOWN(VK_DOWN))
  { g_eye[2]-=sin(rad_xz)*speed;
    g_eye[0]-=cos(rad_xz)*speed;
  }
  if (g_eye[0]<-(MAP*2-20))	g_eye[0]= -(MAP*2-20);
  if (g_eye[0]> (MAP*2-20))	g_eye[0]=  (MAP*2-20);
  if (g_eye[2]<-(MAP*2-20))	g_eye[2]= -(MAP*2-20);
  if (g_eye[2]> (MAP*2-20))	g_eye[2]=  (MAP*2-20);
  g_eye[1] =1.8;

  g_look[0] = float(g_eye[0] + 100*cos(rad_xz));
  g_look[2] = float(g_eye[2] + 100*sin(rad_xz));
  g_look[1] = g_eye[1];

  gluLookAt(g_eye[0],g_eye[1],g_eye[2],g_look[0],g_look[1]+g_elev,g_look[2],0.0,1.0,0.0);
  return TRUE;
}
GLvoid baiscobj::DrawGround()
{ glPushAttrib(GL_CURRENT_BIT);
  glEnable(GL_BLEND);
  glPushMatrix();
  glColor3f(0.5f, 0.7f, 1.0f);
  glTranslatef(0,0.0f,0);
  int size0=(int)(MAP*2);
  glBegin(GL_LINES);
	for (int x = -size0; x < size0;x+=4)
		{glVertex3i(x, 0, -size0); glVertex3i(x, 0,  size0);}
	for (int z = -size0; z < size0;z+=4)
		{glVertex3i(-size0, 0, z); glVertex3i( size0, 0, z);}
  glEnd();
  glPopMatrix();
  glDisable(GL_BLEND);
  glPopAttrib();
}
//==========================================================================
void baiscobj::picter(float x,float y,float z)
{glPushAttrib(GL_CURRENT_BIT);
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
/* glPushMatrix();
	glTranslatef(x,y+10.0f,z);
	glRotatef(r, 0.0, 1.0, 0.0);
	glTranslatef(x/15,0,0);
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
 glEnable(GL_TEXTURE_2D);*/
 glPopAttrib();
 r+=0.5f;if(r>360) r=0;

}
void baiscobj::airplane(float x,float y,float z)
{ glPushMatrix();
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
	glBindTexture(GL_TEXTURE_2D, g_cactus[1]);//
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
void baiscobj::Box(float x,float y,float z)
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
bool baiscobj::LoadT8(char *filename, GLuint &texture)
{	AUX_RGBImageRec *pImage = NULL;
	pImage = auxDIBImageLoad(filename);
	if(pImage == NULL)		return false;
	glGenTextures(1, &texture);	
	glBindTexture    (GL_TEXTURE_2D,texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D,4, pImage->sizeX, 
					  pImage->sizeY,GL_RGB, GL_UNSIGNED_BYTE,pImage->data);
	free(pImage->data);
	free(pImage);	
	return true;
}