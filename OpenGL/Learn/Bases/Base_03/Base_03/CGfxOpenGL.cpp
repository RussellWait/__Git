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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return true;
}

bool CGfxOpenGL::Shutdown()
{
	return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
	if ( 0 == height )
	{
		height = 1;
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(52.0f, (GLfloat)width / (GLdouble)height, 1.0f, 1000.0f);

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

		gluLookAt(0.0f, 6.0f, 0.1f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);

		float pointSize = 0.5;
		
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
		gluLookAt(0.0f, 10.0f, 0.1f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);

		float lineWidth = 0.5f;
		for ( float line = 0.0f; line < 7.0f; line += 0.5f )
		{
			glLineWidth(lineWidth);
			glBegin(GL_LINES);
				glVertex3f(-5.0f, 0.0f, line - 3.0f);
				glVertex3f(-1.0f, 0.0f, line - 3.0f);
			glEnd();
			lineWidth += 1.0f;
		}

		short stipplePattern = 0xAAAA;
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
	else if ( TrianglesQuads == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.1f,
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
	else if ( Polygons == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.1f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);

		glPolygonMode(GL_FRONT, GL_LINE);
		glPushMatrix();
		glTranslatef(-4.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_BACK, GL_POINT);
		glPushMatrix();
		glTranslatef(-2.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_BACK, GL_LINE);
		glPushMatrix();
		glTranslatef(2.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
		gluLookAt(0.0f, 10.0f, 0.1f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 1.0f, 0.0f);

		glColor3f(1.0f, 1.0f, 1.0f);

		DrawCircleApproximation(2.0f, 10, true);
	}
}



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

void CGfxOpenGL::DrawTriangles()
{
	glBegin(GL_TRIANGLES);
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
		glBegin(GL_TRIANGLE_STRIP);
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

void CGfxOpenGL::DrawTriangleFan()
{
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

void CGfxOpenGL::DrawQuads()
{
	glBegin(GL_QUADS);
		for ( int x = 0; x < 3; x++ )
		{
			for ( int z = 0; z < 3; z++ )
			{
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
				glVertex3f(x, 0.0f, z + 1.0f);
			}
		}
	glEnd();
}

void CGfxOpenGL::DrawQuadStrip()
{
	for ( int x = 0; x < 3; x++ )
	{
		glBegin(GL_QUAD_STRIP);
			for ( int z = 0; z < 4; z++ )
			{
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
			}
		glEnd();
	}
}

void CGfxOpenGL::Draw2DSquare()
{
	glBegin(GL_POLYGON);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.0f, -1.0f);
	glEnd();
}

void CGfxOpenGL::DrawCircleApproximation(float radius, int numberOfSides, bool edgeOnly)
{
	if ( edgeOnly )
	{
		glBegin(GL_LINE_STRIP);
	}
	else
	{
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
			glVertex3f(radius, 0.0f, 0.0f);
		}

	glEnd();
}
