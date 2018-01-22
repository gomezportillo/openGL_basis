#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

// ==== Definicion de constantes y variables globales =============
static int upper_part = 15;
static int lower_part = 30;
static int base = 0;
static float spikes = 0.4;
static float spikes_gap = 0.01;
GLfloat color_white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat color_green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat color_blue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat color_red[] = {1.0, 0.0, 0.0, 1.0};

// ==== Función de callback del teclado ===========================
void teclado(unsigned char key, int x, int y)
{
  switch (key)
  {
    case 'q': upper_part++; break;

    case 'w': upper_part--; break;

    case 'a': lower_part++; break;

    case 's': lower_part--; break;

    case '1': base++; break;

    case '2': base--; break;

    case 'z':
    if ((spikes + spikes_gap) <= 0.4)
    {
      spikes += spikes_gap;
    }
    break;

    case 'x':
    if ((spikes - spikes_gap) >= 0.1)
    {
      spikes -= spikes_gap;
    }
    break;
  }
  glutPostRedisplay();
}

// ==== Función de dibujado =======================================
void dibujar()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0.0, 1.0, 6.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0);

  //BASE
  glRotatef(base, 0.0, 1.0, 0.0);
  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color_red);
  glutSolidTorus(0.15,1.5,4,8);
  glPopMatrix();

  //LOWER PART
  glTranslatef(-1.25, 0.0, 0.0);
  glRotatef(lower_part, 0.0, 0.0, 1.0);
  glTranslatef(1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.3, 1.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color_green);
  glutSolidCube(1.0);
  glPopMatrix();

  //UPPER PART
  glTranslatef(1.0,0.0,0.0);
  glRotatef(upper_part, 0.0, 0.0, 1.0);
  glTranslatef(1.0,0.0,0.0);
  glPushMatrix();
  glScalef (2.0, 0.3, 1.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color_blue);
  glutSolidCube(1.0);
  glPopMatrix();

  //SPIKES
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color_white);
  glTranslatef(1.0, 0.0, 0.0);
  glRotatef(90, 0.0, 1.0, 0.0);
  glPushMatrix();
  glTranslatef(spikes, 0.0, 0.0);
  glutSolidCone(0.1, 0.3, 16, 16);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-spikes, 0.0, 0.0);
  glutSolidCone(0.1, 0.3, 16, 16);
  glPopMatrix();
  glPopMatrix();

  glutSwapBuffers();
}

void escalar(int w, int h)
{
  // Viewport para dibujar en toda la ventana
  glViewport(0, 0, w, h);

  // Actualizamos en la matriz de proyección el ratio ancho/alto
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective( 60., (double)w/(double)h, 1., 20. );

  // Volvemos al modo Vista de Modelo
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
  GLfloat posluz[] = {0.0, 4.0, 8.0, 0.0};
  GLfloat luz[] = {1.0, 1.0, 1.0, 1.0};

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Robot");

  glClearColor(0.2, 0.2, 0.2, 1.0);
  glShadeModel(GL_FLAT);
  glLightfv(GL_LIGHT0, GL_POSITION, posluz);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, luz);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  // Registro de funciones de callback
  glutDisplayFunc(dibujar);
  glutReshapeFunc(escalar);
  glutKeyboardFunc(teclado);

  glutMainLoop();
  return 0;
}
