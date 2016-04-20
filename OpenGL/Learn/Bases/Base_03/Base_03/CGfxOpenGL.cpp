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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// ���ñ���ɫ

	return true;
}

bool CGfxOpenGL::Shutdown()
{
	return true;
}

// ���ô��ڿ��
void CGfxOpenGL::SetupProjection(int width, int height)
{
	// ���ڸ߶�����Ϊ1
	if ( 0 == height )
	{
		height = 1;
	}

	// ����λ�����С
	glViewport(0, 0, width, height);

	// ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// �����ӽǴ�С�����ڿ�߱ȣ�ǰ����ʾ����
	gluPerspective(52.0f, (GLfloat)width / (GLdouble)height, 1.0f, 1000.0f);

	// ����Ϊģ�;��󲢳�ʼ��
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

	// ���Ƶ�
	if ( Points == m_type )
	{

		gluLookAt(0.0f, 6.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		float pointSize = 0.5;
		
		// �����������λ����뾶�𽥱��ĵ�
		for ( float point = -4.0f; point < 5.0f; point += 0.5 )
		{
			glPointSize(pointSize);

			glBegin(GL_POINTS);
				glVertex3f(point, 0.0f, 0.0f);
			glEnd();

			pointSize += 1.0f;
		}
	}
	// ������
	else if ( Lines == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		float lineWidth = 0.5f;		// �߿�
		for ( float line = 0.0f; line < 7.0f; line += 0.5f )
		{
			// ����
			glLineWidth(lineWidth);
			glBegin(GL_LINES);
				glVertex3f(-5.0f, 0.0f, line - 3.0f);
				glVertex3f(-1.0f, 0.0f, line - 3.0f);
			glEnd();
			lineWidth += 1.0f;
		}

		// ��Ϊ����ģʽ
		short stipplePattern = 0xAAAA;	// ���ߵ���ʽ
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
	// ���������Σ��ı���
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
	// ���ƶ����
	else if ( Polygons == m_type )
	{
		gluLookAt(0.0f, 10.0f, 0.0f,
				  0.0f, 0.0f, 0.0f,
				  0.0f, 0.0f, -1.0f);

		glPolygonMode(GL_FRONT, GL_LINE);			// ������û���ģʽ
		glPushMatrix();
		glTranslatef(-4.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_BACK, GL_POINT);			// ������û���ģʽ
		glPushMatrix();
		glTranslatef(-2.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// ���涼�������ģʽ
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_BACK, GL_LINE);			// ������û���ģʽ
		glPushMatrix();
		glTranslatef(2.0f, 0.0f, 0.0f);
		glRotatef(m_angle, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0f, 0.0f, 1.0f);
		Draw2DSquare();
		glPopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// ���������û���ģʽ
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


// ��4X4�ĵ���
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

// ��������
void CGfxOpenGL::DrawTriangles()
{
	glBegin(GL_TRIANGLES);		// �����ʽ��������
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
		glBegin(GL_TRIANGLE_STRIP);	// ֻ�������εıߣ�ÿ�����������γ�һ�������Σ�
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

// ������
void CGfxOpenGL::DrawTriangleFan()
{
	// �Ե�һ����ΪԲ�ģ���ÿ�������������һ���㻭һ�������Σ�
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

// ���ı���
void CGfxOpenGL::DrawQuads()
{
	glBegin(GL_QUADS);
		for ( int x = 0; x < 3; x++ )
		{
			for ( int z = 0; z < 3; z++ )
			{
				// ָ���ĸ�����
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
				glVertex3f(x, 0.0f, z + 1.0f);
			}
		}
	glEnd();
}

// ���ı���
void CGfxOpenGL::DrawQuadStrip()
{
	for ( int x = 0; x < 3; x++ )
	{
		glBegin(GL_QUAD_STRIP);
			for ( int z = 0; z < 4; z++ )
			{
				// ָ�����ϡ�����������
				glVertex3f(x, 0.0f, z);
				glVertex3f(x + 1.0f, 0.0f, z);
			}
		glEnd();
	}
}

// �������
void CGfxOpenGL::Draw2DSquare()
{
	glBegin(GL_POLYGON);
		glVertex3f(-0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, -1.0f);
		glVertex3f(-0.5f, 0.0f, -1.0f);
	glEnd();
}

// �������
void CGfxOpenGL::DrawCircleApproximation(float radius, int numberOfSides, bool edgeOnly)
{
	if ( edgeOnly )
	{
		// ֻ���߲��û��߶ε�����
		glBegin(GL_LINE_STRIP);
	}
	else
	{
		// ���ģʽ
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
			// ֻ������Ҫ��ɱպ�
			glVertex3f(radius, 0.0f, 0.0f);
		}

	glEnd();
}
