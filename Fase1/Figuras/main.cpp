#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

float translaX=0.0f;
float translaY=0.0f;
float translaZ=0.0f;
float rodaAng=0.0f;

float ratoX = 0.0f;
float ratoY = 0.0f;


void drawCone(float raio, float altura, int slices,int camadas){

    float angulo = ((2*M_PI)/slices);
    float xA,zA,xP,zP;
    xP=0; zP=raio;

    // este ciclo desenha o cone sem as fatias intermedias
    for (int i=1; i< slices+1;i++) {

        xA=xP; zA=zP;

        xP = raio * sin(i*angulo);
        zP = raio * cos(i*angulo);

        glBegin(GL_TRIANGLES);

        glColor3f(0.5+0.01*i,0.2+0.1*i,0.1+0.1*i);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(xA, 0.0f, zA);
        glVertex3f(xP, 0.0f, zP);

        glColor3f(0.2+0.1*i,0.1+0.1*i,0.5+0.01*i);
        glVertex3f(0.0f,3, 0.0f);
        glVertex3f(xA, 0.0f, zA);
        glVertex3f(xP, 0.0f, zP);
        glEnd();

    }

    float alturaintermedia = altura / camadas;
    float alturaaux = alturaintermedia;

    // este ciclo vai desenhar os circulos intermedios do cone
    //utiliza-se para isso semelhança de triangulos para calcular o raio intermedio e a altura vai aumentando de slice em slice
    for (int i=1; i< slices+1 && alturaaux <= altura ; i++) {

        float raiointermedio = raio * ((altura-alturaaux) /altura);

        for (int i=0; i<slices;i++) {

            xA = raiointermedio * sin(i*angulo);
            zA = raiointermedio * cos(i*angulo);

            xP = raiointermedio * sin((i+1)*angulo);
            zP = raiointermedio * cos((i+1)*angulo);

            glBegin(GL_TRIANGLES);

            glColor3f(0.5+0.01*i,0.2+0.1*i,0.1+0.1*i);
            glVertex3f(0.0f,alturaaux, 0.0f);
            glVertex3f(xA, alturaaux, zA);
            glVertex3f(xP, alturaaux, zP);

            glEnd();

        }


        alturaaux += alturaintermedia;
    }
}



void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    /* Desenhar eixos antes das transformações */
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glColor3f(0,1,1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glColor3f(1,0,1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);

    glEnd();

// put the geometric transformations here
    glTranslatef(translaX,translaY,translaZ);
    glRotatef(rodaAng,0,1,0);

// put drawing instructions here
    drawCone(1,3,299,200);

    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void processa_teclado (unsigned char key, int x, int y){

    glutPostRedisplay();

    switch(key){

        case('a'): translaX += 1.0f;break;
        case('w'): translaY += 1.0f;break;
        case('s'): translaY -= 1.0f;break;
        case('d'): translaX -= 1.0f;break;
        case('r'): rodaAng += 30; break;
        default: break;
    }

}

void funcao_auxiliar_rato(int x, int y){

}

void processa_rato(int button, int state, int x, int y) {

    glutMotionFunc(funcao_auxiliar_rato);
    glutPassiveMotionFunc(NULL);
    glutPostRedisplay();

    switch(state){

        case(GLUT_DOWN):
            ratoX = x;
            ratoY = y;
            break;
        case(GLUT_UP):
            translaX = (x-ratoX)*0.0005f;
            translaY = (y-ratoY)*0.0005f;
            break;
        default: break;
    }


}


int main(int argc, char **argv) {

// init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");

// Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
    glutKeyboardFunc(processa_teclado);

    glutMouseFunc(processa_rato);


//  OpenGL settings
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;
}