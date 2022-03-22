#include <Windows.h>
#include <GLFW/glfw3.h>


#include <math.h>
#include <cmath>
#include <vector>

float angle = 0.5;
const int triangle = 1;
float pi = 3.14159265;
int steps = 100;
float xalfa = 0.1;
float zalfa = 0.1;
POINTFLOAT position = { 0,0 };
float normals[] = { 0,0,1, 0,0,1,0,0,1 };
GLuint verticeindex[] = { 1,2,3, 3, 0, 1 };

void MoveCamera()
{
    if (GetKeyState(VK_UP) < 0) xalfa = ++xalfa > 180 ? 180 : xalfa;
    if (GetKeyState(VK_DOWN) < 0) xalfa = --xalfa < 0 ? 0 : xalfa;
    if (GetKeyState(VK_LEFT) < 0) zalfa++;
    if (GetKeyState(VK_RIGHT) > 0) zalfa--;
    glRotatef(-xalfa, 1, 0, 0);
    glRotatef(-zalfa, 0, 0, 1);
    glTranslatef(-position.x, position.y, -3);
}


void sphere_entry(int du, int dv) {

    float gu = 3.1415926535 / du, gv = 2.0 * 3.1415926535 / (dv - 1);

    float x, y, z, r;

    glPushMatrix();
#define MAKE_R(z2) sqrt(0.5 - (z2))
#define MAKE_Z(z_step) cos((z_step) *gu)
#define MAKE_Y(x_step,r) (r)*sin((x_step)* gv)
#define MAKE_X(x_step,r) (r)*cos((x_step)* gv)
    // сфера
    glBegin(GL_QUADS);
    for (int z_step = 0; z_step < du; ++z_step) {
        for (int x_step = 0; x_step < dv; ++x_step) {

            z = MAKE_Z(z_step);
            r = MAKE_R(z * z);
            x = MAKE_X(x_step, r);
            y = MAKE_Y(x_step, r);
            glVertex3f(x, y, z);

            z = MAKE_Z(z_step + 1);
            r = MAKE_R(z * z);
            x = MAKE_X(x_step, r);
            y = MAKE_Y(x_step, r);
            glVertex3f(x, y, z);

            z = MAKE_Z(z_step + 1);
            r = MAKE_R(z * z);
            x = MAKE_X(x_step + 1, r);
            y = MAKE_Y(x_step + 1, r);
            glVertex3f(x, y, z);

            z = MAKE_Z(z_step);
            r = MAKE_R(z * z);
            x = MAKE_X(x_step + 1, r);
            y = MAKE_Y(x_step + 1, r);
            glVertex3f(x, y, z);
        }

    }

    glEnd();
#undef MAKE_Y
#undef MAKE_Z
#undef MAKE_X
#undef MAKE_R
    glPopMatrix();
}

void drawCircle(float xPos, float yPos, float radius, float r, float g, float b)
{
    float prevX = xPos;
    float prevY = yPos + radius;
    for (int i = 0; i <= steps; i++)
    {
        float newX = xPos + radius * sin(angle * i);
        float newY = yPos + radius * cos(angle * i);
        glBegin(GL_TRIANGLES);
        glColor3f(r, g, b);
        glVertex2f(xPos, yPos);
        glVertex2f(prevX, prevY);
        glVertex2f(newX, newY);
        glEnd();

        prevX = newX;
        prevY = newY;

    }
}


void drawPiramide(float sizez) 
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(sizez/2, (-sizez*sqrt(6))/8, (-sizez*sqrt(3))/6);
    glVertex3f(0, (-sizez * sqrt(6)) / 8, (sizez*sqrt(3))/3);
    glVertex3f(0, (sizez*sqrt(6))/4, 0);
    //Треугольник Правая сторона

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(sizez / 2, (-sizez * sqrt(6)) / 8, (-sizez * sqrt(3)) / 6);
    glVertex3f(0, (-sizez * sqrt(6)) / 8, (sizez * sqrt(3)) / 3);
    glVertex3f(-sizez / 2, (-sizez * sqrt(6)) / 8, (-sizez * sqrt(3)) / 6);
    //Треугольник Задняя сторона

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-sizez / 2, (-sizez * sqrt(6)) / 8, (-sizez * sqrt(3)) / 6);
    glVertex3f(0, (-sizez * sqrt(6)) / 8, (sizez * sqrt(3)) / 3);
    glVertex3f(0, (sizez * sqrt(6)) / 4, 0);
    //Треугольник Левая сторона.

    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-sizez / 2, (-sizez * sqrt(6)) / 8, (-sizez * sqrt(3)) / 6);
    glVertex3f(sizez / 2, (-sizez * sqrt(6)) / 8, (-sizez * sqrt(3)) / 6);
    glVertex3f(0, (sizez * sqrt(6)) / 4, 0);
    glEnd();
}

void drawCube(float size)
{
    glBegin(GL_QUADS);
    // front face
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    // left face
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    // back face
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    // right face
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    // top face
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, size / 2);
    glVertex3f(-size / 2, size / 2, -size / 2);
    glVertex3f(size / 2, size / 2, -size / 2);
    // bottom face
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, size / 2);
    glVertex3f(-size / 2, -size / 2, -size / 2);
    glVertex3f(size / 2, -size / 2, -size / 2);
    glEnd();
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);//включить освещение
    glEnable(GL_LIGHT0);
    
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_BLEND);//смешиивание цветов
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // автоматическое приведение нормалей к

    // единичной длине

    glEnable(GL_NORMALIZE);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

        //Пирамида
        glPopMatrix();
        glPushMatrix();
        glLoadIdentity();
        glTranslated(0.7,0.5,0);
        glRotated(angle, 1, 1, 1);
        drawPiramide(0.5);
        glPopMatrix();
        
        //Куб
        glPushMatrix();
        glLoadIdentity();
        glTranslated(-0.5, -0.5, -0.5);
        glRotated(angle, 1, 1, 1);
        drawCube(0.5);
        glPopMatrix();
        
        //Сфера
        glPushMatrix();
        glLoadIdentity();
        glTranslated(-0.5,0.5,0);
        glRotated(angle, 1, 1, 1);
        glColor3f(.6f, .05f, .95f);
        sphere_entry(64, 64);
        glPopMatrix();
        
        
        //Освещение
        glPushMatrix();
        //glRotated(-angle, 0, 1, 0);
        glEnable(GL_LIGHT0);
        GLfloat light1_diffuse[] = { 0.0, 0.0, 2.0 };
        GLfloat light1_position[] = { 0.0, 0.0, -2.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, light1_position);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light1_diffuse);

        glPopMatrix();
        //угол
        angle += .02f;
        angle = angle > 360.0f ? 0.0f : angle;
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}