#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include<iostream>
using namespace std;



GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;

float rh=4.8,rw=5,rl=10;
float ex=2,ey=2 ,ez=9,lx=2,ly=2,lz=8;




static GLfloat v_room[8][3] =
{
    {0.0, 0.0, 0.0},  //point index 0
    {0.0, 0.0, rw},  //point index 1
    {rl, 0.0, rw},  //point index 2
    {rl, 0.0, 0.0},  //point index 3
    {0.0, rh, 0.0},   //point index 4
    {0.0,rh,rw},    //point index 5
    {rl,rh,rw},     //point index 6
    {rl,rh,0.0}     //point index 7
};

static GLubyte quadIndices[5][4] = { {0, 3, 2, 1},
    {0, 1, 5, 4},
    {0, 4, 7, 3},
    {2, 6, 7, 3},
    {4, 5, 6, 7}
};  // indeces for drawing the quad plane


static GLfloat colors[8][3] =
{
    {0.823529 ,0.411765, 0.117647},  //rooftop
    {0.823529 ,0.411765, 0.117647},  //left wall
    {0.662745, 0.662745, 0.662745},  //floor
    {0.662745, 0.662745, 0.662745},  //color for point index 3
    {0.823529 ,0.411765, 0.117647},
    {0.823529 ,0.411765, 0.11764},
    {0.823529 ,0.411765, 0.11764},
    {0.823529 ,0.411765, 0.11764},

};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawRoom()
{

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_room[quadIndices[i][0]][0],v_room[quadIndices[i][0]][1],v_room[quadIndices[i][0]][2],
                    v_room[quadIndices[i][1]][0],v_room[quadIndices[i][1]][1],v_room[quadIndices[i][1]][2],
                    v_room[quadIndices[i][2]][0],v_room[quadIndices[i][2]][1],v_room[quadIndices[i][2]][2]);

        glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_room[quadIndices[i][0]][0]);
        glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_room[quadIndices[i][1]][0]);
        glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_room[quadIndices[i][2]][0]);
        glColor3fv(&colors[quadIndices[i][3]][1]);
        glVertex3fv(&v_room[quadIndices[i][3]][0]);



    }
    glEnd();
}


void Draw_Solid_Cylinder(float radius, float height, int slices, int stacks)
{
    GLUquadricObj* Quadric;
    Quadric = gluNewQuadric();
    gluQuadricDrawStyle(Quadric, GLU_FILL);
    gluQuadricOrientation(Quadric, GLU_INSIDE);

    gluCylinder(Quadric, radius, radius, height, slices, stacks);
    glRotatef(180, 1,0,0);
    gluDisk(Quadric, 0.0f, radius, slices, 1);
    glRotatef(180, 1,0,0);
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(Quadric, 0.0f, radius, slices, 1);
    glTranslatef(0.0f, 0.0f, height);

    gluDeleteQuadric(Quadric);
}

void draw_sofa(float x, float y , float z)
{
    glPushMatrix();
    glColor4f(0.862745, 0.862745, 0.862745,1);
    glTranslatef(x,y+.2501,.7);
    glScalef(2.5,.5,1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1,1,1,1);
    glTranslatef(x,y+.7,z-1.1);
    glScalef(2.4,1.2,.3);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glColor4f(0.913725,0.588235,0.478431,1);
    glTranslatef(1.4,.6,1);
    glScalef(.25,.45,1.2);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glColor4f(0.913725,0.588235,0.478431,1);
    glTranslatef(3.60,.6,1);
    glScalef(.25,.45,1.2);
    glutSolidCube(1);
    glPopMatrix();






}

void draw_table(float x,float y,float z){
    glPushMatrix();
    glColor4f(0.647059,0.164706, 0.164706,1);
    glTranslatef(3,1,3);
    glScalef(2,.1,1);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(2.1,.6,3.45);
    glColor4f(0.7866,.67543,.7321,1);
    glScalef(0,.7,-.1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(2.1,.6,3);
    glColor4f(0.7866,.67543,.7321,1);
    glScalef(0,.7,-.1);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(4,.6,3.45);
    glColor4f(0.7866,.67543,.7321,1);
    glScalef(0,.7,-.1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(4,.6,2.7);
    glColor4f(0.7866,.67543,.7321,1);
    glScalef(0,.7,-.1);
    glutSolidCube(1);
    glPopMatrix();

}


void draw_shahed_minar()
{
    glPushMatrix();
    glColor4f(0.411765, 0.411765, 0.411765,1);
    glTranslatef(3,1.2,3);
    glScalef(1.2,.1,.7);
    glutSolidCube(1);
    glPopMatrix();


    //Center
     glPushMatrix();
    glColor3f( 0.741176, 0.717647, 0.419608);
    glTranslatef(3.05,2.20,3.1);
     glRotatef(45,1,0,0);
    glScalef(.2,.3,-.1);
    glutSolidCube(1);
     glRotatef(-45,1,0,0);
    glPopMatrix();




     glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(2.95,1.6,3);
    glScalef(.01,.9,-.05);
    glutSolidCube(1);
    glPopMatrix();

    glColor4f(1,0,0,1);
    glPushMatrix();
    glTranslatef(3.05,1.7,2.9);
    glutSolidSphere(0.1,20,20);
    glPopMatrix();

     glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(3.05,1.6,3);
    glScalef(.01,.9,-.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(3.13,1.6,3);
    glScalef(.01,.9,-.05);
    glutSolidCube(1);
    glPopMatrix();




    //left




     glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(2.6,1.5,3);
    glScalef(.01,.6,-.05);
    glutSolidCube(1);
    glPopMatrix();



     glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(2.7,1.5,3);
    glScalef(.01,.6,-.05);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(2.8,1.5,3);
    glScalef(.01,.6,-.05);
    glutSolidCube(1);
    glPopMatrix();

    //Right


    glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(3.30,1.5,3);
    glScalef(.01,.6,-.05);
    glutSolidCube(1);
    glPopMatrix();


     glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(3.40,1.5,3);
    glScalef(.01,.6,-.05);
    glutSolidCube(1);
    glPopMatrix();

     glPushMatrix();
    glColor4f(1,1,1,.7);
    glTranslatef(3.50,1.5,3);
    glScalef(.01,.6,-.05);
    glutSolidCube(1);
    glPopMatrix();







}

void draw_almirah()
{

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5,5,-5,5, 4, 50);
    gluPerspective(65,1,1,100);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(ex,ey,ez, lx,ly,lz, 0,1,0);
    glViewport(0,0,800,800);
    glPushMatrix();

    glRotatef( theta, 1, 0, 0.0 );
    glRotatef( alpha, 0, 1, 0.0 );
    drawRoom();
    //drawsofa();
    draw_sofa(2.5,0,1.5);
    draw_table(0,0,0);
    draw_shahed_minar();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

float mm,xx,yy,zz;
float cam_angle = 270/180.0f * 3.1416;

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'j':
        cam_angle = cam_angle - 0.01f;

        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);


        break;
    case 'k':
        cam_angle = cam_angle + 0.05f;

        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);

        break;

    case 't':
        ex = ex + cos(cam_angle) * 0.5f;
        ez = ez + sin(cam_angle) * 0.5f;

        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);

        break;
    case 'g':
        ex = ex - cos(cam_angle) * 0.5f;
        ez = ez - sin(cam_angle) * 0.5f;

        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);
        cout<<lx<<'\t'<<ly<<'\t'<<lz<<'\t'<<'\n';
        break;

    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1;
        axis_y=0.0;
        break;

    case 27:	// Escape key
        exit(1);
    }
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(1200,1200);
    glutCreateWindow("Room");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glutKeyboardFunc(myKeyboardFunc);

    glutDisplayFunc(display);

    glutIdleFunc(animate);


    glutMainLoop();

    return 0;
}
