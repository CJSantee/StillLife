//--------------------------------------------------------------------------
// CS3233-01 Homework #5
// Still Life Scene - My Desk 
// Colin Santee
// Due: December 7th, 2020
// Details: Program draws a lighted 3-dimensional scene of my general desk setup. 
// Objects include: a table, laptop, monitor, textbook, coffee cup, and the Utah Teapod!
// Runs with: g++ Scene.cpp camera.cpp -framework GLUT -framework OpenGL -Wno-deprecated
//--------------------------------------------------------------------------

// System-Dependent Includes
#ifdef _WIN32                       
   #include <GL/glut.h>             
#elif __linux__                     
   #include <GL/glut.h>              
#elif __APPLE__                     
   #define GL_SILENCE_DEPRECATION   
   #include <OpenGL/gl.h>           
   #include <GLUT/glut.h>           
#endif                              

#include <cmath>
#include <cstdio>
#include <math.h>
#include "camera.h"

using namespace std;

const double PI = 3.141592653589793;

int window;

// Global definitons of Display Lists
GLuint floorList;
GLuint tableList;
GLuint laptopList;
GLuint monitorList;
GLuint bookList;
GLuint cupList;
GLuint teapotList;

// Default color values
float black[] = {0.0f, 0.0f, 0.0f, 1.0f};
float specular_color[] = {0.5f, 0.5f, 0.5f, 1.0f};
float white[] = {1.0f, 1.0f, 1.0f, 1.0f};

// Front, Right, Back, Left, Top, Bottom
float cubeFaceList [6][3] = {{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f},
                {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}};

// Init function for GL Lighting setup
void init(){
    glEnable(GL_LIGHTING);    // Enable lighting.
    glEnable(GL_LIGHT0);      
    GLfloat lightpos[] = {.5, 1.0, 1.0, 0.};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    return;
}

// Draw Quad using Triangle Fans given 8 Vertices
// Input: Vertices of Quad
// B/F = Back/Front R/L = Right/Left T/B = Top/Bottom (i.e. : blt = BackLeftTop)
void triangleQuad(float* blt, float* brt, float* frt, float* flt, float* blb, float* brb, float* frb, float* flb){
    glBegin(GL_TRIANGLE_FAN);
        // Top
        glNormal3fv(cubeFaceList[4]);
        glVertex3fv(blt);
        glVertex3fv(flt);
        glVertex3fv(frt);
        glVertex3fv(brt);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        // Bottom
        glNormal3fv(cubeFaceList[5]);
        glVertex3fv(blb);
        glVertex3fv(flb);
        glVertex3fv(frb);
        glVertex3fv(brb);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        // Front
        glNormal3fv(cubeFaceList[0]);
        glVertex3fv(flt);
        glVertex3fv(frt);
        glVertex3fv(frb);
        glVertex3fv(flb);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        // Back
        glNormal3fv(cubeFaceList[2]);
        glVertex3fv(blt);
        glVertex3fv(brt);
        glVertex3fv(brb);
        glVertex3fv(blb);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        // Right
        glNormal3fv(cubeFaceList[1]);
        glVertex3fv(frt);
        glVertex3fv(brt);
        glVertex3fv(brb);
        glVertex3fv(frb);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        // Left
        glNormal3fv(cubeFaceList[3]);
        glVertex3fv(flt);
        glVertex3fv(blt);
        glVertex3fv(blb);
        glVertex3fv(flb);
    glEnd();
}

// Create the display lists for each object

void generateFloor(){

    floorList = glGenLists(1);
    glNewList(floorList, GL_COMPILE);
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f,  1.0f);
            glVertex3f( 1.0f, -1.0f,  1.0f);
            glVertex3f( 1.0f, -1.0f, -1.0f);
        glEnd();
    glEndList();

}

void generateTable(){

    float tableHeight  = 0.0;
    float tableSize    = 1.28;
    float tableDepth   = 0.07;

    float legSize      = 0.1;

    tableList = glGenLists(1);
    glNewList(tableList, GL_COMPILE);
        // Table Top Cords: 
        float backLeftTop[3]        = {0.0-(tableSize/2), tableHeight, 0.0-(tableSize/2)};
        float backLeftBottom[3]     = {0.0-(tableSize/2), tableHeight-tableDepth, 0.0-(tableSize/2)};
        float backRightTop[3]       = {0.0+(tableSize/2), tableHeight, 0.0-(tableSize/2)};
        float backRightBottom[3]    = {0.0+(tableSize/2), tableHeight-tableDepth, 0.0-(tableSize/2)};
        float frontLeftTop[3]       = {0.0-(tableSize/2), tableHeight, 0.0+(tableSize/2)};
        float frontLeftBottom[3]    = {0.0-(tableSize/2), tableHeight-tableDepth, 0.0+(tableSize/2)};
        float frontRightTop[3]      = {0.0+(tableSize/2), tableHeight, 0.0+(tableSize/2)};
        float frontRightBottom[3]   = {0.0+(tableSize/2), tableHeight-tableDepth, 0.0+(tableSize/2)};
        
        // Generate Table Top Shape with Triangles
        triangleQuad(backLeftTop, backRightTop, frontRightTop, frontLeftTop, backLeftBottom, backRightBottom, frontRightBottom, frontLeftBottom);
        
        // Draw Back Left Leg
        for(int i = 0; i < 3; i++){
            backLeftTop[i]   = backLeftBottom[i];
            backRightTop[i]  = backLeftBottom[i];
            frontLeftTop[i]  = backLeftBottom[i];
            frontRightTop[i] = backLeftBottom[i];
        }

        backRightTop[0]  += legSize;
        frontLeftTop[2]  += legSize;
        frontRightTop[0] += legSize;
        frontRightTop[2] += legSize;

        for(int i = 0; i < 3; i++){
            backLeftBottom[i]   = (i==1) ? -0.999 : backLeftTop[i];
            backRightBottom[i]  = (i==1) ? -0.999 : backRightTop[i];
            frontLeftBottom[i]  = (i==1) ? -0.999 : frontLeftTop[i];
            frontRightBottom[i] = (i==1) ? -0.999 : frontRightTop[i];
        }
        triangleQuad(backLeftTop, backRightTop, frontRightTop, frontLeftTop, backLeftBottom, backRightBottom, frontRightBottom, frontLeftBottom);

        // Draw Back Right Leg
        backLeftTop[0]      += (tableSize-legSize);
        backLeftBottom[0]   += (tableSize-legSize);
        backRightTop[0]     += (tableSize-legSize);
        backRightBottom[0]  += (tableSize-legSize);
        frontLeftTop[0]     += (tableSize-legSize);
        frontLeftBottom[0]  += (tableSize-legSize);
        frontRightTop[0]    += (tableSize-legSize);
        frontRightBottom[0] += (tableSize-legSize);
        triangleQuad(backLeftTop, backRightTop, frontRightTop, frontLeftTop, backLeftBottom, backRightBottom, frontRightBottom, frontLeftBottom);

        // Draw Front Right Leg
        backLeftTop[2]      += (tableSize-legSize);
        backLeftBottom[2]   += (tableSize-legSize);
        backRightTop[2]     += (tableSize-legSize);
        backRightBottom[2]  += (tableSize-legSize);
        frontLeftTop[2]     += (tableSize-legSize);
        frontLeftBottom[2]  += (tableSize-legSize);
        frontRightTop[2]    += (tableSize-legSize);
        frontRightBottom[2] += (tableSize-legSize);
        triangleQuad(backLeftTop, backRightTop, frontRightTop, frontLeftTop, backLeftBottom, backRightBottom, frontRightBottom, frontLeftBottom);

        // Draw Front Left Leg
        backLeftTop[0]      -= (tableSize-legSize);
        backLeftBottom[0]   -= (tableSize-legSize);
        backRightTop[0]     -= (tableSize-legSize);
        backRightBottom[0]  -= (tableSize-legSize);
        frontLeftTop[0]     -= (tableSize-legSize);
        frontLeftBottom[0]  -= (tableSize-legSize);
        frontRightTop[0]    -= (tableSize-legSize);
        frontRightBottom[0] -= (tableSize-legSize);
        triangleQuad(backLeftTop, backRightTop, frontRightTop, frontLeftTop, backLeftBottom, backRightBottom, frontRightBottom, frontLeftBottom);

    glEndList();
}

void generateLaptop(){
    float laptopWidth   = 0.45;

    float laptopHeight  = laptopWidth * 0.5625;

    float offSetX       = -0.22;
    float offSetZ       =  0.1;

    float tableHeight   = 0.0;
    float laptopDepth   = 0.03;

    laptopList = glGenLists(1);
    glNewList(laptopList, GL_COMPILE);
        glPushMatrix();

        glRotatef(6.0f, 0.0f, 1.0f, 0.0f);
        float backLeftTop[3]        = {0.0-(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ};
        float backLeftBottom[3]     = {0.0-(laptopWidth/2)+offSetX, tableHeight, 0.0-(laptopHeight/2)+offSetZ};
        float backRightTop[3]       = {0.0+(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ};
        float backRightBottom[3]    = {0.0+(laptopWidth/2)+offSetX, tableHeight, 0.0-(laptopHeight/2)+offSetZ};
        float frontLeftTop[3]       = {0.0-(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0+(laptopHeight/2)+offSetZ};
        float frontLeftBottom[3]    = {0.0-(laptopWidth/2)+offSetX, tableHeight, 0.0+(laptopHeight/2)+offSetZ};
        float frontRightTop[3]      = {0.0+(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0+(laptopHeight/2)+offSetZ};
        float frontRightBottom[3]   = {0.0+(laptopWidth/2)+offSetX, tableHeight, 0.0+(laptopHeight/2)+offSetZ};
        triangleQuad(backLeftTop, backRightTop, frontRightTop, frontLeftTop, backLeftBottom, backRightBottom, frontRightBottom, frontLeftBottom);

        float degree = 90.0;

        float screenBackLeftTop[3]        = {0.0-(laptopWidth/2)+offSetX, tableHeight+laptopHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ-laptopDepth};
        float screenBackLeftBottom[3]     = {0.0-(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ-laptopDepth};
        float screenBackRightTop[3]       = {0.0+(laptopWidth/2)+offSetX, tableHeight+laptopHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ-laptopDepth};
        float screenBackRightBottom[3]    = {0.0+(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ-laptopDepth};
        float screenFrontLeftTop[3]       = {0.0-(laptopWidth/2)+offSetX, tableHeight+laptopHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ};
        float screenFrontLeftBottom[3]    = {0.0-(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ};
        float screenFrontRightTop[3]      = {0.0+(laptopWidth/2)+offSetX, tableHeight+laptopHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ};
        float screenFrontRightBottom[3]   = {0.0+(laptopWidth/2)+offSetX, tableHeight+laptopDepth, 0.0-(laptopHeight/2)+offSetZ};
        triangleQuad(screenBackLeftTop, screenBackRightTop, screenFrontRightTop, screenFrontLeftTop, screenBackLeftBottom, screenBackRightBottom, screenFrontRightBottom, screenFrontLeftBottom);

        // Hinge
        glBegin(GL_TRIANGLE_FAN);
            glNormal3i(0, -1, -1);
            glVertex3fv(backLeftBottom);
            glVertex3fv(backRightBottom);
            glVertex3fv(screenBackRightBottom);
            glVertex3fv(screenBackLeftBottom);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
            // Right Side of Hinge
            glNormal3fv(cubeFaceList[1]);
            glVertex3fv(backRightBottom);
            glVertex3fv(backRightTop);
            glVertex3fv(screenBackRightBottom);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
            glNormal3fv(cubeFaceList[3]);
            glVertex3fv(backLeftBottom);
            glVertex3fv(backLeftTop);
            glVertex3fv(screenBackLeftBottom);
        glEnd();

    glEndList();
}

void generateMonitor(){
    float monitorWidth  = 0.6;

    float monitorHeight = monitorWidth * 0.5625;

    float baseWidth     = 0.35;
    float baseHeight    = 0.2;
    float standWidth    = 0.15;
    float standHeight   = 0.35;

    float offSetX       = 0.22;
    float offSetZ       = -0.25;

    float tableHeight   = 0.0;
    float monitorDepth  = 0.03;

    monitorList = glGenLists(1);
    glNewList(monitorList, GL_COMPILE);
        glPushMatrix();

        glRotatef(-10.0f, 0.0f, 1.0f, 0.0f);
        float baseBackLeftTop[3]        = {0.0-(baseWidth/2)+offSetX, tableHeight+monitorDepth, 0.0-(baseHeight/2)+offSetZ};
        float baseBackLeftBottom[3]     = {0.0-(baseWidth/2)+offSetX, tableHeight, 0.0-(baseHeight/2)+offSetZ};
        float baseBackRightTop[3]       = {0.0+(baseWidth/2)+offSetX, tableHeight+monitorDepth, 0.0-(baseHeight/2)+offSetZ};
        float baseBackRightBottom[3]    = {0.0+(baseWidth/2)+offSetX, tableHeight, 0.0-(baseHeight/2)+offSetZ};
        float baseFrontLeftTop[3]       = {0.0-(baseWidth/2)+offSetX, tableHeight+monitorDepth, 0.0+(baseHeight/2)+offSetZ};
        float baseFrontLeftBottom[3]    = {0.0-(baseWidth/2)+offSetX, tableHeight, 0.0+(baseHeight/2)+offSetZ};
        float baseFrontRightTop[3]      = {0.0+(baseWidth/2)+offSetX, tableHeight+monitorDepth, 0.0+(baseHeight/2)+offSetZ};
        float baseFrontRightBottom[3]   = {0.0+(baseWidth/2)+offSetX, tableHeight, 0.0+(baseHeight/2)+offSetZ};
        triangleQuad(baseBackLeftTop, baseBackRightTop, baseFrontRightTop, baseFrontLeftTop, baseBackLeftBottom, baseBackRightBottom, baseFrontRightBottom, baseFrontLeftBottom);
        float standBackLeftTop[3]       = {0.0-(standWidth/2)+offSetX, tableHeight+monitorDepth+standHeight, 0.0-(monitorDepth/2)+offSetZ};
        float standBackLeftBottom[3]    = {0.0-(standWidth/2)+offSetX, tableHeight+monitorDepth, 0.0-(monitorDepth/2)+offSetZ};
        float standBackRightTop[3]      = {0.0+(standWidth/2)+offSetX, tableHeight+monitorDepth+standHeight, 0.0-(monitorDepth/2)+offSetZ};
        float standBackRightBottom[3]   = {0.0+(standWidth/2)+offSetX, tableHeight+monitorDepth, 0.0-(monitorDepth/2)+offSetZ};
        float standFrontLeftTop[3]      = {0.0-(standWidth/2)+offSetX, tableHeight+monitorDepth+standHeight, 0.0+(monitorDepth/2)+offSetZ};
        float standFrontLeftBottom[3]   = {0.0-(standWidth/2)+offSetX, tableHeight+monitorDepth, 0.0+(monitorDepth/2)+offSetZ};
        float standFrontRightTop[3]     = {0.0+(standWidth/2)+offSetX, tableHeight+monitorDepth+standHeight, 0.0+(monitorDepth/2)+offSetZ};
        float standFrontRightBottom[3]  = {0.0+(standWidth/2)+offSetX, tableHeight+monitorDepth, 0.0+(monitorDepth/2)+offSetZ};
        triangleQuad(standBackLeftTop, standBackRightTop, standFrontRightTop, standFrontLeftTop, standBackLeftBottom, standBackRightBottom, standFrontRightBottom, standFrontLeftBottom);
        float screenBackLeftTop[3]        = {0.0-(monitorWidth/2)+offSetX, tableHeight+standHeight+(monitorHeight/2), 0.0+(monitorDepth/2)+offSetZ};
        float screenBackLeftBottom[3]     = {0.0-(monitorWidth/2)+offSetX, tableHeight+standHeight-(monitorHeight/2), 0.0+(monitorDepth/2)+offSetZ};
        float screenBackRightTop[3]       = {0.0+(monitorWidth/2)+offSetX, tableHeight+standHeight+(monitorHeight/2), 0.0+(monitorDepth/2)+offSetZ};
        float screenBackRightBottom[3]    = {0.0+(monitorWidth/2)+offSetX, tableHeight+standHeight-(monitorHeight/2), 0.0+(monitorDepth/2)+offSetZ};
        float screenFrontLeftTop[3]       = {0.0-(monitorWidth/2)+offSetX, tableHeight+standHeight+(monitorHeight/2), 0.0+(monitorDepth/2)+monitorDepth+offSetZ};
        float screenFrontLeftBottom[3]    = {0.0-(monitorWidth/2)+offSetX, tableHeight+standHeight-(monitorHeight/2), 0.0+(monitorDepth/2)+monitorDepth+offSetZ};
        float screenFrontRightTop[3]      = {0.0+(monitorWidth/2)+offSetX, tableHeight+standHeight+(monitorHeight/2), 0.0+(monitorDepth/2)+monitorDepth+offSetZ};
        float screenFrontRightBottom[3]   = {0.0+(monitorWidth/2)+offSetX, tableHeight+standHeight-(monitorHeight/2), 0.0+(monitorDepth/2)+monitorDepth+offSetZ};
        triangleQuad(screenBackLeftTop, screenBackRightTop, screenFrontRightTop, screenFrontLeftTop, screenBackLeftBottom, screenBackRightBottom, screenFrontRightBottom, screenFrontLeftBottom);

        glPopMatrix();
    glEndList();

}

void generateBook(){
    float bookWidth  = 0.28;
    float bookHeight = bookWidth * 1.2941;
    float bookDepth  = 0.065; 
    float coverDepth = 0.015;

    int numPages     = 5;

    float offSetX       = 0.3;
    float offSetZ       = 0.25;

    float tableHeight   = 0.0;

    bookList = glGenLists(1);
    glNewList(bookList, GL_COMPILE);
        // Cover
        float coverBackLeftTop[3]        = {0.0-(bookWidth/2)+offSetX, tableHeight+bookDepth+coverDepth, 0.0-(bookHeight/2)+offSetZ};
        float coverBackLeftBottom[3]     = {0.0-(bookWidth/2)+offSetX, tableHeight+bookDepth           , 0.0-(bookHeight/2)+offSetZ};
        float coverBackRightTop[3]       = {0.0+(bookWidth/2)+offSetX, tableHeight+bookDepth+coverDepth, 0.0-(bookHeight/2)+offSetZ};
        float coverBackRightBottom[3]    = {0.0+(bookWidth/2)+offSetX, tableHeight+bookDepth           , 0.0-(bookHeight/2)+offSetZ};
        float coverFrontLeftTop[3]       = {0.0-(bookWidth/2)+offSetX, tableHeight+bookDepth+coverDepth, 0.0+(bookHeight/2)+offSetZ};
        float coverFrontLeftBottom[3]    = {0.0-(bookWidth/2)+offSetX, tableHeight+bookDepth           , 0.0+(bookHeight/2)+offSetZ};
        float coverFrontRightTop[3]      = {0.0+(bookWidth/2)+offSetX, tableHeight+bookDepth+coverDepth, 0.0+(bookHeight/2)+offSetZ};
        float coverFrontRightBottom[3]   = {0.0+(bookWidth/2)+offSetX, tableHeight+bookDepth           , 0.0+(bookHeight/2)+offSetZ};
        triangleQuad(coverBackLeftTop, coverBackRightTop, coverFrontRightTop, coverFrontLeftTop, coverBackLeftBottom, coverBackRightBottom, coverFrontRightBottom, coverFrontLeftBottom);

        // Backing
        float endBackLeftTop[3]        = {0.0-(bookWidth/2)+offSetX, tableHeight+coverDepth, 0.0-(bookHeight/2)+offSetZ};
        float endBackLeftBottom[3]     = {0.0-(bookWidth/2)+offSetX, tableHeight           , 0.0-(bookHeight/2)+offSetZ};
        float endBackRightTop[3]       = {0.0+(bookWidth/2)+offSetX, tableHeight+coverDepth, 0.0-(bookHeight/2)+offSetZ};
        float endBackRightBottom[3]    = {0.0+(bookWidth/2)+offSetX, tableHeight           , 0.0-(bookHeight/2)+offSetZ};
        float endFrontLeftTop[3]       = {0.0-(bookWidth/2)+offSetX, tableHeight+coverDepth, 0.0+(bookHeight/2)+offSetZ};
        float endFrontLeftBottom[3]    = {0.0-(bookWidth/2)+offSetX, tableHeight           , 0.0+(bookHeight/2)+offSetZ};
        float endFrontRightTop[3]      = {0.0+(bookWidth/2)+offSetX, tableHeight+coverDepth, 0.0+(bookHeight/2)+offSetZ};
        float endFrontRightBottom[3]   = {0.0+(bookWidth/2)+offSetX, tableHeight           , 0.0+(bookHeight/2)+offSetZ};
        triangleQuad(endBackLeftTop, endBackRightTop, endFrontRightTop, endFrontLeftTop, endBackLeftBottom, endBackRightBottom, endFrontRightBottom, endFrontLeftBottom);

        // Pages
        float pageBottomLeft[3]  = {endFrontLeftTop[0], endFrontLeftTop[1], endFrontLeftTop[2]};
        float pageBottomRight[3] = {endFrontRightTop[0], endFrontRightTop[1], endFrontRightTop[2]};
        float pageTopLeft[3]     = {endBackLeftTop[0], endBackLeftTop[1], endBackLeftTop[2]};
        float pageTopRight[3]    = {endBackRightTop[0], endBackRightTop[1], endBackRightTop[2]};
        for(int i = 0; i < numPages; i++){
            glBegin(GL_TRIANGLE_FAN);
                glNormal3fv(cubeFaceList[4]);
                glVertex3fv(pageBottomLeft);
                glVertex3fv(pageBottomRight);
                glVertex3fv(pageTopRight);
                glVertex3fv(pageTopLeft);
            glEnd();
            float increment = (coverBackLeftBottom[1] - endBackLeftTop[1])/numPages;
            pageBottomLeft[1]  += increment;
            pageBottomRight[1] += increment;
            pageTopLeft[1]     += increment;
            pageTopRight[1]    += increment;
        }

        // Binding
        glBegin(GL_TRIANGLE_FAN);
        // Top
            glNormal3i(-1, 1, 0);
            glVertex3f(coverFrontLeftBottom[0]-(bookDepth/2), coverFrontLeftBottom[1]-(bookDepth/2), coverFrontLeftBottom[2]);
            glVertex3f(coverFrontLeftBottom[0]-(bookDepth/2), coverFrontLeftBottom[1]-(bookDepth/2), coverBackLeftBottom[2]);
            glVertex3fv(coverBackLeftTop);
            glVertex3fv(coverFrontLeftTop);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
            // Bottom
            glNormal3i(-1, -1, 0);
            glVertex3f(coverFrontLeftBottom[0]-(bookDepth/2), coverFrontLeftBottom[1]-(bookDepth/2), coverFrontLeftBottom[2]);
            glVertex3f(coverFrontLeftBottom[0]-(bookDepth/2), coverFrontLeftBottom[1]-(bookDepth/2), coverBackLeftBottom[2]);
            glVertex3fv(endBackLeftBottom);
            glVertex3fv(endFrontLeftBottom);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
            // Front
            glNormal3fv(cubeFaceList[0]);
            glVertex3f(coverFrontLeftBottom[0]-(bookDepth/2), coverFrontLeftBottom[1]-(bookDepth/2), coverFrontLeftBottom[2]);
            glVertex3fv(endFrontLeftBottom);
            glVertex3fv(coverFrontLeftTop);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);
            // Back
            glNormal3fv(cubeFaceList[2]);
            glVertex3f(coverFrontLeftBottom[0]-(bookDepth/2), coverFrontLeftBottom[1]-(bookDepth/2), coverBackLeftBottom[2]);
            glVertex3fv(endBackLeftBottom);
            glVertex3fv(coverBackLeftTop);
        glEnd();
    glEndList();
    
}

void generateCup(){
    float offsetX = 0.5;
    float offsetZ = 0;
    float cup_height = 0.15;
    float cup_width = 0.06;
    float table_height = 0.0;

    cupList = glGenLists(1);
    glNewList(cupList, GL_COMPILE);
        const int faces = 12;
        float point[faces*2][3];
        
        glPushMatrix();
        // Create a vertex list.
        for (int pt = 0; pt<faces; pt++) {
            double degrees, radians;
            degrees = pt * 360/faces;
            radians = degrees * PI / 180;
            point[pt][0] = point[pt+faces][0] = cos(radians);  // x
            point[pt][1] = table_height + cup_height;  // y
            point[pt+faces][1] = table_height + 0.001;  // y
            point[pt][2] = point[pt+faces][2] = sin(radians);  // z
        }

        glTranslated(offsetX, 0.001, offsetZ);
        glScaled(cup_width, 1.0, cup_width);
        
        // Draw the far end of the cylinder.
        glBegin(GL_TRIANGLE_FAN);
        glNormal3i(0,0,1);
        for (int pt = faces-1; pt>=0; pt--) {
            glVertex3fv(point[pt+faces]);
        }
        glEnd();
        
        // Draw sides of the cylinder.
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= faces; i++) {
            glNormal3f(point[i%faces][0], 0.0f, point[i%faces][1]);
            glVertex3fv(point[i%faces]);
            glVertex3fv(point[i%faces + faces]);
        }
        glEnd();

        glPopMatrix();

        glPushMatrix();


        // CUP HANDLE
        int hfaces = 15;
        float hpoint[hfaces*2][3];
        float handle_width = 0.03;
        // Create a vertex list.
        for (int pt = 0; pt<hfaces; pt++) {
            double degrees, radians;
            degrees = pt * 180/hfaces;
            radians = degrees * PI / 180;
            hpoint[pt][0] = hpoint[pt+hfaces][0] = cos(radians);  // x
            hpoint[pt][1] = hpoint[pt+hfaces][1] = sin(radians);  // y
            hpoint[pt][2] = handle_width/2;  // z
            hpoint[pt+hfaces][2] = -handle_width/2;  // z
        }

        glTranslated(offsetX+0.045, 0.08, offsetZ);
        glScaled(cup_height/2.5, cup_height/2.5, 1.0);
        glRotatef(-84.0f, 0.0f, 0.0f, 1.0f);

        // Draw sides of the cylinder.
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= hfaces; i++) {
            glNormal3f(hpoint[i%hfaces][0], hpoint[i%hfaces][1], 0.0f);
            glVertex3fv(hpoint[i%hfaces]);
            glVertex3fv(hpoint[i%hfaces + hfaces]);
        }
        glEnd();

        glPopMatrix();

    glEndList();

}

void generateTeapot(){
    teapotList = glGenLists(1);
    glNewList(teapotList, GL_COMPILE);
        glPushMatrix();
        glTranslated(-0.25, 0.115, -0.35);
        glRotated(25, 0.0, 1.0, 0.0);
        glutSolidTeapot(0.15);
        glPopMatrix();
    glEndList();
}

void display() {
    glClearColor(0.286f, 0.509f, 0.58f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    cameraSetLimits(-1.5, 1.5, -1.5, 1.5, -1.5, 1.5);
    cameraApply();

    // Draw the Scene Elements
    float floor_color[] = {0.35f, 0.20f, 0.12f, 1.0f};  // Color of the floor: brown
    glMaterialfv(GL_FRONT, GL_DIFFUSE, floor_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT, floor_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);

    // Call the display list for the floor object
    glCallList(floorList);

    float table_color[] = { 0.82f, 0.70f, 0.55f, 1.0f }; // Color of the table: tan
    glMaterialfv(GL_FRONT, GL_DIFFUSE, table_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT, table_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 40);

    glCallList(tableList);

    float laptop_color[] = { 0.77f, 0.78f, 0.78f, 1.0f }; // Color of the laptop: Silver
    glMaterialfv(GL_FRONT, GL_DIFFUSE, laptop_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, table_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 70);
    glCallList(laptopList);

    float monitor_color[] = { 0.39f, 0.4f, 0.41f, 1.0f }; // Color of the monitor: Gray
    glMaterialfv(GL_FRONT, GL_DIFFUSE, monitor_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, monitor_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glCallList(monitorList);

    float book_color[] = { 0.8f, 0.6f, 0.5f, 1.0f }; // Color of the book: Red-ish
    glMaterialfv(GL_FRONT, GL_DIFFUSE, book_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, book_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);
    glCallList(bookList);

    float gold[] = { 1.0f, 0.7f, 0.5f, 1.0f }; // Color of the cup & teapot : Bronze-ish
    float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gold);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glMaterialfv(GL_FRONT, GL_AMBIENT, gold);
    glMateriali(GL_FRONT, GL_SHININESS, 60);
    glCallList(cupList);

    glCallList(teapotList);

    glFlush();  // Render now
}

/* Main function: GLUT runs as sizes[i] console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitWindowSize(800, 800);               // Set the window's initial tableSize & tableHeight
    glutInitWindowPosition(100, 100);           // Position the window's initial top-left corner
    window = glutCreateWindow("My Desk Scene");      // Create sizes[i] window with the given title
    glutDisplayFunc(display);                   // Register display callback handler for window re-paint
    init();
    generateFloor();                            // Create the display list for the floor
    generateTable();
    generateLaptop();
    generateMonitor();
    generateBook();
    generateCup();
    generateTeapot();
    glutMainLoop();                             // Enter the infinitely event-processing loop
    return 0;
}
