#include "CGfxOpenGL.h"

#include <math.h>
#include <windows.h>
#include <gl/GL.H>
#include <gl/GLU.H>


CGfxOpenGL::CGfxOpenGL(PrimType type)
{
    m_type = type;
	m_angle = 0.0f;
}

CGfxOpenGL::~CGfxOpenGL()
{}

bool CGfxOpenGL::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// 设置背景色

	return true;
}

bool CGfxOpenGL::Shutdown()
{
	return true;
}

// 设置窗口宽高
void CGfxOpenGL::SetupProjection(int width, int height)
{
	// 窗口高度至少为1
	if ( 0 == height )
	{
		height = 1;
	}

	// 窗口位置与大小
	glViewport(0, 0, width, height);

	// 投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置视角大小，窗口宽高比，前后显示界限
	gluPerspective(52.0f, (GLfloat)width / (GLdouble)height, 1.0f, 1000.0f);

	// 设置为模型矩阵并初始化
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_windowWidth = width;
	m_windowHeight = height;
}

void CGfxOpenGL::Prepare(float dt)
{

}

void CGfxOpenGL::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// 绘制点
	if ( Points == m_type )
	{

		gluLookAt(0.0f, 6.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		float pointSize = 0.5;
		
		// 从左至右依次画出半径逐渐变大的点
		for ( float point = -4.0f; point < 5.0f; point += 0.5 )
		{
			glPointSize(pointSize);

			glBegin(GL_POINTS);
				glVertex3f(point, 0.0f, 0.0f);
			glEnd();

			pointSize += 1.0f;
		}
	}
	// 绘制线
	else if ( Lines == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		float lineWidth = 0.5f;		// 线宽
		for ( float line = 0.0f; line < 7.0f; line += 0.5f )
		{
			// 画线
			glLineWidth(lineWidth);
			glBegin(GL_LINES);
				glVertex3f(-5.0f, 0.0f, line - 3.0f);
				glVertex3f(-1.0f, 0.0f, line - 3.0f);
			glEnd();
			lineWidth += 1.0f;
		}

		// 设为虚线模式
		short stipplePattern = 0xAAAA;	// 虚线的样式
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(2, stipplePattern);

		lineWidth = 0.5f;
		for ( float line = 0.0f; line < 7.0f; line += 0.5f )
		{
			glLineWidth(lineWidth);
			glBegin(GL_LINES);
				glVertex3f(1.0f, 0.0f, line - 3.0f);
				glVertex3f(5.0f, 0.0f, line - 3.0f);
			glEnd();
			lineWidth += 1.0f;
		}

		glDisable(GL_LINE_STIPPLE);
	}
	// 绘制三角形，四边形
	else if ( TrianglesQuads == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		// top left
		glPushMatrix();
		glTranslated(-6.0f, 0.0f, -4.0f);
		DrawPoints();
		glPopMatrix();

		// top middle
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glTranslatef(-2.0f, 0.0f, -4.0f);
		DrawTriangles();
		glPopMatrix();

		// top right
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glTranslatef(2.0f, 0.0f, -4.0f);
		DrawQuads();
		glPopMatrix();

		// bottom left
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glTranslatef(-6.0f, 0.0f, 0.5f);
		DrawTriangleStrip();
		glPopMatrix();

		// bottom middle
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glTranslatef(-2.0f, 0.0f, 0.5f);
		DrawTriangleFan();
		glPopMatrix();

		// bootom right
		glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glTranslatef(2.0f, 0.0f, 0.5f);
		DrawQuadStrip();
		glPopMatrix();
	}
	// 绘制多边形
	else if ( Polygons == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		glPolygonMode(GL_FRONT, GL_LINE);			// 正面采用画边模式
		glPushMatrix();
		glTranslatef(-4.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_BACK, GL_POINT);			// 背面采用画点模式
		glPushMatrix();
		glTranslatef(-2.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// 两面都采用填充模式
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_BACK, GL_LINE);			// 背面采用画边模式
		glPushMatrix();
		glTranslatef(2.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// 正反都采用画边模式
		glPushMatrix();
		glTranslatef(4.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 1.0f, 0.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		m_angle += 0.2f;
	}
	else if ( OnYourOwn1 == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		DrawCircleApproximation(2.0f, 10, true);
	}
}


// 画4X4的点阵
void CGfxOpenGL::DrawPoints()
{
	glPointSize(4.0f);
	glBegin(GL_POINTS);
		for ( int x = 0; x < 4; x++ )
		{
			for ( int z = 0; z < 4; z++ )
			{
				glVertex3f(x, 0, z);
			}
		}
	glEnd();
}

// 画三角形
void CGfxOpenGL::DrawTriangles()
{
	glBegin(GL_TRIANGLES);		// 填充形式的三角形
		for ( int x = 0; x < 3; x++ )
		{
			for ( int z = 0; z < 3; z++ )
			{
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
				glVertex3f(x, 0.0f, z + 1.0f);
			}
		}
	glEnd();
}

void CGfxOpenGL::DrawTriangleStrip()
{
	for ( int x = 0; x < 3; x++ )
	{
		glBegin(GL_TRIANGLE_STRIP);	// 只画三角形的边（每相邻三个点形成一个三角形）
			for ( int z = 0; z < 3; z++ )
			{
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
				glVertex3f(x, 0.0f, z + 1.0f);
				glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
			}
		glEnd();
	}
}

// 话扇形
void CGfxOpenGL::DrawTriangleFan()
{
	// 以第一个点为圆心，（每相邻两个点与第一个点画一个三角形）
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0f, 0.0f, 0.0f);
		for ( int x = 4; x > 0; x-- )
		{
			glVertex3f(x - 1.0f, 0.0f, 3.0f);
		}
		for ( int z = 4; z > 0; z-- )
		{
			glVertex3f(3.0f, 0.0f, z - 1.0f);
		}
	glEnd();
}

// 画四边形
void CGfxOpenGL::DrawQuads()
{
	glBegin(GL_QUADS);
		for ( int x = 0; x < 3; x++ )
		{
			for ( int z = 0; z < 3; z++ )
			{
				// 指明四个顶点
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
				glVertex3f(x, 0.0f, z + 1.0f);
			}
		}
	glEnd();
}

// 画四边形
void CGfxOpenGL::DrawQuadStrip()
{
	for ( int x = 0; x < 3; x++ )
	{
		glBegin(GL_QUAD_STRIP);
			for ( int z = 0; z < 4; z++ )
			{
				// 指明左上、右下两个点
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
			}
		glEnd();
	}
}

// 画多边形
void CGfxOpenGL::Draw2DSquare()
{
	glBegin(GL_POLYGON);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.0f, -1.0f);
	glEnd();
}

// 花多边形
void CGfxOpenGL::DrawCircleApproximation(float radius, int numberOfSides, bool edgeOnly)
{
	if ( edgeOnly )
	{
		// 只画边采用画线段的形势
		glBegin(GL_LINE_STRIP);
	}
	else
	{
		// 填充模式
		glBegin(GL_POLYGON);
	}

		float piceAngle = 2.0f * PI / numberOfSides;

		for ( int vertex = 0; vertex < numberOfSides; vertex++ )
		{
			float angle = piceAngle * vertex;
			glVertex3f(cosf(angle) * radius, 0.0f, sinf(angle) * radius);
		}

		if ( edgeOnly )
		{
			// 只画边需要完成闭合
			glVertex3f(radius, 0.0f, 0.0f);
		}

	glEnd();
}
