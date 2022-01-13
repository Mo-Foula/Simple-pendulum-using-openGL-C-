/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 32;
static int stacks = 32;

static double rx = 3,ry = 3;
static double angleLeft = 270;
static double angleRight = 270;
static bool leftIncreasing = false;
static bool leftDecreasing = false;
static bool rightIncreasing = true;
static bool rightDecreasing = false;
static bool stopMovement = true;


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void color(int R,int G,int B){
    double r=R/255.0,g=G/255.0,b=B/255.0;
    //       0 -> 1
    glColor3d(r,g,b);
}

void drawCircle(double x,double y,double z){

/// sphere
    glPushMatrix();
      //  glRotated(60,1,0,0);

    glTranslated(x,y,z);
        // glscaled(2,0.5,1) 7ydrb el x f 2 w y2sm el y 3la 2 w kda 7y3ml shakl bydawy
    glutSolidSphere(1.1,slices,stacks);

    glPopMatrix();

}
/*void drawHalfCircle(double x, double y,double rx, double ry,double startAngle,double endAngle){
    glBegin(GL_POLYGON);
    color(214,57,57);
           // glColor3f(1.0f,1.0f, 1.0f);
            double xc = x,yc = y;
            for(int i = min(endAngle,startAngle); i <= max(startAngle,endAngle); i++)
            {
                //glColor3f(1.0f ,1.0f - color, 1.0f);
                //glColor3d(sin(i)/2.0+0.5 ,cos(i)/2.0+0.5 , 1.0);
                              //  glColor3d(0 ,1 , 1.0);
                glVertex3d(rx*sin(i*3.14/180)+xc,ry*cos(i*3.14/180)+yc,-30);
            }
            glEnd();
}*/
void drawLine(double x1,double y1,double x2, double y2,double z){

glBegin(GL_LINES);
    glVertex3d(x1, y1,z);
    glVertex3d(x2, y2,z);
glEnd();

}
static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    //color(40,41,54);
    glColor3d(0,0,0);
   glLineWidth(10);

    glBegin(GL_POLYGON);

    glVertex3d(0,0,0);
    glVertex3d(-0.5,0,0);
    glVertex3d(-0.5,-0.3,0);
    glVertex3d(0,-0.3,0);

    glEnd();




    */


    color(102,110,222);

    glLineWidth(2);

    drawLine(2.25,0,2.25,5,-31);
    drawCircle(2.2,0,-30);


    drawLine(0,0,0,5,-31);
    drawCircle(0,0,-30);


    drawLine(-2.25,0,-2.25,5,-31);
    drawCircle(-2.2,0,-30);

/* */
    if(stopMovement && leftIncreasing){
        angleLeft-=3;
        if(angleLeft <= 179){
            angleLeft = 180;
            leftIncreasing = false;
            leftDecreasing = true;
        }
    }

    if(stopMovement && leftDecreasing){
        angleLeft+=3;
        if(angleLeft >= 271){
            angleLeft = 270;
            leftDecreasing = false;
            rightIncreasing = true;
        }
    }
    if(stopMovement && rightIncreasing){
        angleRight+=3;
        if(angleRight >= 361){
            angleRight = 360;
            rightIncreasing = false;
            rightDecreasing = true;
        }
    }
    if(stopMovement && rightDecreasing){
        angleRight-=3;
        if(angleRight <= 271){
            angleRight = 270;
            rightDecreasing = false;
            leftIncreasing = true;
        }
    }


    //glVertex2f(rx*sin(i)+xc,ry*cos(i)+yc);


    ///Left most sphere
    drawLine(rx*cos(angleLeft*3.14/180)-4.5,(rx)*sin(angleLeft*3.14/180)+3,-4.5,5,-31);

    drawCircle(rx*cos(angleLeft*3.14/180)-4.5,(rx)*sin(angleLeft*3.14/180)+3,-30);



    ///Right most sphere
    drawLine(ry*cos(angleRight*3.14/180)+4.5,(ry)*sin(angleRight*3.14/180)+3,4.5,5,-31);
    drawCircle(ry*cos(angleRight*3.14/180)+4.5,ry*sin(angleRight*3.14/180) + 3,-30);


    ///Top line

    glLineWidth(20);
    drawLine(-4.8,5,4.8,5,-31);

    //drawHalfCircle(-4.8,5,10,10,1,360);
    //drawHalfCircle(5,10,50,50,1,360);


    /*
*/


    /*
    glColor3d(1,0,0);

     glPushMatrix();
         glTranslated(-2.4,1.2,-6);
         glRotated(60,1,0,0);
         glRotated(a,0,0,1);
         glutSolidSphere(1,slices,stacks);
     glPopMatrix();

     glPushMatrix();
         glTranslated(0,1.2,-6);
         glRotated(60,1,0,0);
         glRotated(a,0,0,1);
         glutSolidCone(1,1,slices,stacks);
     glPopMatrix();

     glPushMatrix();
         glTranslated(2.4,1.2,-6);
         glRotated(60,1,0,0);
         glRotated(a,0,0,1);
         glutSolidTorus(0.2,0.8,slices,stacks);
     glPopMatrix();

     glPushMatrix();
         glTranslated(-2.4,-1.2,-6);
         glRotated(60,1,0,0);
         glRotated(a,0,0,1);
         glutWireSphere(1,slices,stacks);
     glPopMatrix();

     glPushMatrix();
         glTranslated(0,-1.2,-6);
         glRotated(60,1,0,0);
         glRotated(a,0,0,1);
         glutWireCone(1,1,slices,stacks);
     glPopMatrix();

     glPushMatrix();
         glTranslated(2.4,-1.2,-6);
         glRotated(60,1,0,0);
         glRotated(a,0,0,1);
         glutWireTorus(0.2,0.8,slices,stacks);
     glPopMatrix();
     */

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ' :
        stopMovement = !stopMovement;
        break;
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
        }
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */
static void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            stopMovement = !stopMovement;
            break;
    }
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
