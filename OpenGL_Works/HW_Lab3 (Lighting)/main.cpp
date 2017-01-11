#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include<iostream>
using namespace std;



GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;

int rh=5,rw=5,rl=7;
float ex=3,ey=4,ez=13,lx=3,ly=4,lz=12;


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

static GLubyte quadIndices[5][4] =
{
    {0, 3, 2, 1},
    {0, 1, 5, 4},
    {0, 4, 7, 3},
    {2, 6, 7, 3},
    {4, 5, 6, 7}
};  // indeces for drawing the quad plane


static GLfloat colors[5][3] =
{
    {0.0, 0.0, 1.0},  //color for point index 0
    {1.0, 0.0, 0.0},  //color for point index 1
    {0.0, 1.0, 0.0},  //color for point index 2
    {0.0, 1.0, 1.0},  //color for point index 3
    {1.0, 0.0, 1.0}   //color for point index 4
};


GLfloat ambient[]    = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat diffuse_a[]    = { 1, 1, 1, 1.0};
GLfloat diffuse_b[]    = { 1, 1, 1, 1.0};
GLfloat diffuse_c[]    = { 1, 1, 1, 1.0};
GLfloat diffuse_d[]    = { 1, 1, 1, 1.0};

GLfloat specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess[] = { 10.0f };
bool ambient_on = true;
bool specular_on = true;
bool diffuse_on = true;

bool light_ambient_on_0 = true;
bool light_diffuse_on_0 = true;
bool light_specular_on_0 = true;

bool light_ambient_on_1 = true;
bool light_diffuse_on_1 = true;
bool light_specular_on_1 = true;

bool light_ambient_on_2 = true;
bool light_diffuse_on_2 = true;
bool light_specular_on_2 = true;

bool light_ambient_on_3 = true;
bool light_diffuse_on_3 = true;
bool light_specular_on_3 = true;

//bool light_1_on = true;

float linear_attenuation = 0.01f;
float constant_attenuation = 2.0f;

GLfloat light_position[] = { 3.0f, 3.0f, 3.0f, 1.0f };
GLfloat mat_zero[] = {0.0f, 0.0f, 0.0f, 1.0f};

void set_material(GLfloat* ambient_col, GLfloat* diffuse_col, GLfloat* specular_col, GLfloat* shininess)
{
    if (ambient_on == true)
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_col);
    else
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_zero);

    if (diffuse_on == true)
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  diffuse_col);
    else
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_zero);

    if (specular_on == true)
        glMaterialfv(GL_FRONT, GL_SPECULAR,  specular_col);
    else
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_zero);



    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

}

void set_light_offon(int light_id, bool light_on, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat* position,bool am_on,bool dif_on, bool spec_on)
{
    int id;
    if (light_id == 0)
        id = GL_LIGHT0;
    if (light_id == 1)
        id = GL_LIGHT1;
    if (light_id == 2)
        id = GL_LIGHT2;
    if (light_id == 3)
        id = GL_LIGHT3;

    if (light_on == true)
        glEnable(id);
    else
        glDisable(id);

    if (am_on == true)
        glLightfv(id, GL_AMBIENT,  ambient);
    else
        glLightfv(id, GL_AMBIENT,  mat_zero);

    if (dif_on == true)
        glLightfv(id, GL_DIFFUSE,  diffuse);
    else
        glLightfv(id, GL_DIFFUSE,  mat_zero);

    if (spec_on == true)
        glLightfv(id, GL_SPECULAR, specular);
    else
        glLightfv(id, GL_SPECULAR, mat_zero);

    glLightfv(id, GL_POSITION, position);

    glLightf(id, GL_LINEAR_ATTENUATION, linear_attenuation );
    glLightf(id,GL_CONSTANT_ATTENUATION, constant_attenuation);
}
void drawroom()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <5; i++)
    {
        if(i==0)
        {
            //glColor3fv(&colors[quadIndices[i][0]][0]);
            GLfloat diffuse_uw[]  = {149.0/255.0, 149.0/255.0, 149.0/255.0, 1.0};
            set_material(ambient,diffuse_uw,specular,shininess);
        }
        else if(i==1)
        {


            //glColor3fv(&colors[quadIndices[i][1]][0]);
            GLfloat diffuse_lw[]    = {0.0,1.0,0.0, 1.0};
            set_material(ambient,diffuse_lw,specular,shininess);
        }
        else if(i==2)
        {

            //glColor3fv(&colors[quadIndices[i][1]][0]);
            GLfloat diffuse_fw[]    = {1.0, 0.0, 0.0, 1.0};
            set_material(ambient,diffuse_fw,specular,shininess);
        }
        else if(i==3)
        {


            //glColor3fv(&colors[quadIndices[i][3]][0]);
            GLfloat diffuse_rw[]    = {.5, 0.0, 1, 1.0};
            set_material(ambient,diffuse_rw,specular,shininess);
        }
        else if(i==4)
        {


            //glColor3fv(&colors[quadIndices[i][4]][0]);
            GLfloat diffuse_tw[]    = {0.0, 0.0, 1.0, 1.0};
            set_material(ambient,diffuse_tw,specular,shininess);
        }

        glVertex3fv(&v_room[quadIndices[i][0]][0]);
        //glColor3fv(&colors[quadIndices[i][1]][0]);
        glVertex3fv(&v_room[quadIndices[i][1]][0]);
        //glColor3fv(&colors[quadIndices[i][2]][0]);
        glVertex3fv(&v_room[quadIndices[i][2]][0]);
        //glColor3fv(&colors[quadIndices[i][3]][1]);
        glVertex3fv(&v_room[quadIndices[i][3]][0]);

    }
    glEnd();
}


void draw_sofa(float x, float y, float z)
{
    glPushMatrix();
    GLfloat diffuse2[]    = { 1, 1, 1, 1 };
    set_material(ambient,diffuse2,specular,shininess);
    //glColor4f(1,1,1,1);
    glTranslatef(x,y,z);
    glScalef(3,0.75,1.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(1.0,0.5,0.5,1);
    GLfloat diffuse3[]= {250.0/255.0, 132.0/255.0, 5.0/255.0, 0.95};
    set_material(ambient,diffuse3,specular,shininess);
    glTranslatef(x,y+0.01,z+0.01);
    glScalef(2.75,.75,1.25);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    //glColor4f(1,0.0784314,0.576471,1);
    GLfloat diffuse4[]= {1,0.0784314,0.576471,1};
    set_material(ambient,diffuse4,specular,shininess);
    glTranslatef(x-1.40,y+0.50,z);
    glScalef(0.20,0.25,1.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(1,0.0784314,0.576471,1);
    set_material(ambient,diffuse4,specular,shininess);
    glTranslatef(1.40+x,y+0.50,z);
    glScalef(0.20,0.25,1.25);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(1,0.0784314,0.576471,1);
    set_material(ambient,diffuse4,specular,shininess);
    glTranslatef(0+x,y+0.50,z-.575);
    //cout<<z<<endl;
    glScalef(2.50,1.50,0.10);
    glutSolidCube(1);
    glPopMatrix();

}

void draw_table(float x, float y, float z)
{
    glPushMatrix();
    //glColor4f(0,0,1,1);
    GLfloat diffuse6[]= { 0.0,0.0,.5,1 };
    set_material(ambient,diffuse6,specular,shininess);
    glTranslatef(x+1,y+.625,z+0.30);
    glScalef(0.10,1.25,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(0,0,1,1);
    set_material(ambient,diffuse6,specular,shininess);
    glTranslatef(x+2,y+.625,z+0.30);
    glScalef(0.10,1.25,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(0,0,1,1);
    set_material(ambient,diffuse6,specular,shininess);
    glTranslatef(x+1,y+.625,z);
    glScalef(0.10,1.25,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(0,0,1,1);
    set_material(ambient,diffuse6,specular,shininess);
    glTranslatef(x+2,y+.625,z);
    glScalef(0.10,1.25,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(1,1,1,1);
    GLfloat diffuse7[]    = { 1,1,1,1 };
    set_material(ambient,diffuse7,specular,shininess);
    glTranslatef(x+1.50,y+1.25,z);
    glScalef(2,0.10,1.0);
    glutSolidCube(1);
    glPopMatrix();
}

void draw_shahidminar(float x, float y, float z)
{
    glPushMatrix();
    //glColor4f(0.80,0.80,1,1);
    GLfloat diffuse[]    = { 0.80f, 0.80f, 1.0f, 1.0f };
    set_material(ambient,diffuse,specular,shininess);
    glTranslatef(x-.50,0.5+y,z);
    //cout<<x<<endl;
    glScalef(1.50,0.10,0.50);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    GLfloat diffuse1[]    = { 1.0,1.0,1.0, 1.0f };
    set_material(ambient,diffuse1,specular,shininess);
    //glColor4f(0.698039,0.133333,0.133333,1);
    glTranslatef(x-1.0,.75+y,z);
    //cout<<y<<endl;
    glRotated(60,0,1,0);
    glScalef(0.30,.50,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    set_material(ambient,diffuse1,specular,shininess);
    //glColor4f(0.598039,0.103333,0.103333,1);
    glTranslatef(x-.60,0.80+y,z);
    //cout<<y<<endl;
    glScalef(0.10,1.0,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(0.598039,0.103333,0.103333,1);
    set_material(ambient,diffuse1,specular,shininess);
    glTranslatef(x-.80,0.80+y,z);
    //cout<<y<<endl;
    glScalef(0.10,1.0,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(0.598039,0.103333,0.103333,1);
    set_material(ambient,diffuse1,specular,shininess);
    glTranslatef(x-.40,0.80+y,z);
    //cout<<y<<endl;
    glScalef(0.10,1.0,0.10);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    //glColor4f(0.698039,0.133333,0.133333,1);
    set_material(ambient,diffuse1,specular,shininess);
    glTranslatef(x-.60,1.40+y,z);
    //cout<<y<<endl;
    glRotated(60,1,0,0);
    glScalef(0.50,.50,0.10);
    glutSolidCube(1);
    glPopMatrix();


    glPushMatrix();
    //glColor4f(0.698039,0.133333,0.133333,1);
    set_material(ambient,diffuse1,specular,shininess);
    glTranslatef(x-.20,.75+y,z);
    //cout<<y<<endl;
    glRotated(-60,0,1,0);
    glScalef(0.30,.50,0.10);
    glutSolidCube(1);
    glPopMatrix();


}





void circle(float x, float y, float radius)
{
    int i;
    int triangleAmount = 20;

    float twicePi = 2.0f * 3.1416;

    glBegin(GL_TRIANGLE_FAN);
    GLfloat diffuse5[]= {1.0,0.0,0.0};
    set_material(ambient,diffuse5,specular,shininess);
    glVertex2f(x, y); // center of circle
    for(i = 0; i <= triangleAmount; i++)
    {
        glVertex2f(
            x + (radius * cos(i *  twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void builddesign()
{
    glPushMatrix();

    glRotatef( theta, 1, 0, 0.0 );
    glRotatef( alpha, 0, 1, 0.0 );

    drawroom();

    draw_sofa(3.0,0.375,0.625);
    glTranslatef(0.0,0.0,5);
    glRotatef(270,0,1,0);
    glRotatef(180,0,1,0);
    draw_sofa(1.5,0.375,0.625);

    glRotatef(-270,0,1,0);
    glRotatef(-180,0,1,0);

    draw_table(2,0,-2);

    draw_shahidminar(4,0.80,-2.0);

    glTranslatef(1.375,-.25,-2);
    circle(2,2,.25);

    glPopMatrix();


}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5,5,-5,5, 4, 50);
    gluPerspective(65,1,0.50,20);
    //glOrtho(-5,5,-5,5, 4, 50);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
   // set_light(0,true,ambient,diffuse,specular,light_position);

    gluLookAt(ex,ey,ez, lx,ly,lz, 0,1,0);
    glViewport(0,0,400,400);
    set_light_offon(0,true,ambient,diffuse_a,specular,light_position,light_ambient_on_0,light_diffuse_on_0,light_specular_on_0);
    set_light_offon(1,false,ambient,diffuse_b,specular,light_position,light_ambient_on_1,light_diffuse_on_1,light_specular_on_1);
    set_light_offon(2,false,ambient,diffuse_c,specular,light_position,light_ambient_on_2,light_diffuse_on_2,light_specular_on_2);
    set_light_offon(3,false,ambient,diffuse_d,specular,light_position,light_ambient_on_3,light_diffuse_on_3,light_specular_on_3);

    builddesign();
    glViewport(400,0,400,400);
    set_light_offon(0,false,ambient,diffuse_a,specular,light_position,light_ambient_on_0,light_diffuse_on_0,light_specular_on_0);
    set_light_offon(1,true,ambient,diffuse_b,specular,light_position,light_ambient_on_1,light_diffuse_on_1,light_specular_on_1);
    set_light_offon(2,false,ambient,diffuse_c,specular,light_position,light_ambient_on_2,light_diffuse_on_2,light_specular_on_2);
    set_light_offon(3,false,ambient,diffuse_d,specular,light_position,light_ambient_on_3,light_diffuse_on_3,light_specular_on_3);

    builddesign();

    glViewport(0,400,400,400);
    set_light_offon(0,false,ambient,diffuse_a,specular,light_position,light_ambient_on_0,light_diffuse_on_0,light_specular_on_0);
    set_light_offon(1,false,ambient,diffuse_b,specular,light_position,light_ambient_on_1,light_diffuse_on_1,light_specular_on_1);
    set_light_offon(2,true,ambient,diffuse_c,specular,light_position,light_ambient_on_2,light_diffuse_on_2,light_specular_on_2);
    set_light_offon(3,false,ambient,diffuse_d,specular,light_position,light_ambient_on_3,light_diffuse_on_3,light_specular_on_3);

    builddesign();

    glViewport(400,400,400,400);
     set_light_offon(0,false,ambient,diffuse_a,specular,light_position,light_ambient_on_0,light_diffuse_on_0,light_specular_on_0);
    set_light_offon(1,false,ambient,diffuse_b,specular,light_position,light_ambient_on_1,light_diffuse_on_1,light_specular_on_1);
    set_light_offon(2,false,ambient,diffuse_c,specular,light_position,light_ambient_on_2,light_diffuse_on_2,light_specular_on_2);
    set_light_offon(3,true,ambient,diffuse_d,specular,light_position,light_ambient_on_3,light_diffuse_on_3,light_specular_on_3);

    builddesign();


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
        cam_angle = cam_angle - 0.01;
        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);
        break;
    case 'k':
        cam_angle = cam_angle + 0.01;
        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);
        break;

    case 't':
        ex = ex + cos(cam_angle) * 0.5;
        ez = ez + sin(cam_angle) * 0.5;

        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);
        break;
    case 'g':
        ex = ex - cos(cam_angle) * 0.5;
        ez = ez - sin(cam_angle) * 0.5;
        lx = ex + cos(cam_angle);
        ly = ey;
        lz = ez + sin(cam_angle);
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
        axis_x=1.0;
        axis_y=0.0;
        break;
    case '1':
         light_ambient_on_0=!light_ambient_on_0;
         break;

    case '2':
         light_ambient_on_1=!light_ambient_on_1;
         break;

    case '3':
         light_ambient_on_2=!light_ambient_on_2;
         break;

    case '4':
         light_ambient_on_3=!light_ambient_on_3;
         break;

    case '5':
         light_diffuse_on_0=!light_diffuse_on_0;
         break;
     case '6':
         light_diffuse_on_1=!light_diffuse_on_1;
         break;
     case '7':
         light_diffuse_on_2=!light_diffuse_on_2;
         break;

     case '8':
         light_diffuse_on_3=!light_diffuse_on_3;
         break;

     case 'a':
         light_specular_on_0=!light_specular_on_0;
         break;

    case 'b':
        light_specular_on_1=!light_specular_on_1;
         break;

    case 'c':
         light_specular_on_2=!light_specular_on_2;
         break;

    case 'd':
        light_specular_on_3=!light_specular_on_3;
         break;


    case 27:	// Escape key
        exit(1);
    }
}

void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.1;
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
    glutInitWindowSize(800,800);
    glutCreateWindow("Lighting_effect_on_different_portions");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glutKeyboardFunc(myKeyboardFunc);

    glutDisplayFunc(display);

    glutIdleFunc(animate);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glutMainLoop();

    return 0;
}

