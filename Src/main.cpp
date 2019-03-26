#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "CH3D.h"
#include "MorceauParcoursLigne.h"
#include "Pos3D.h"
#include "MorceauParcoursVirage.h"
#include "MorceauParcours.h"

#define PI 3.14159265359

/* Variables globales                           */

static int wTx = 480; // Resolution horizontale de la fenetre
static int wTy = 480; // Resolution verticale de la fenetre
static int wPx = 50; // Position horizontale de la fenetre
static int wPy = 50; // Position verticale de la fenetre
static float px = 0;
static float py = 10;
static float pz = 0;
static const float blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
static MorceauParcours *parcours[2];

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */

/* du programme                                 */

static void init(void) {
    glClearColor(0.25F, 0.25F, 0.25F, 1.0F);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, blanc);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}

/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();
	parcours[0]->modeliser();
    glPopMatrix();
    glPushMatrix();
    Pos3D pos = parcours[1]->getPosition();
    glTranslatef(pos.c[0], pos.c[1], pos.c[2]);
	parcours[1]->modeliser();
    glPopMatrix();
}
/* Fonction executee lors d'un rafraichissement */

/* de la fenetre de dessin                      */

static void display(void) {
    printf("D\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = {0.0, 0.0, 10.0, 1.0};
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    gluLookAt(px, py, pz, px, 0, pz, 0.0, 0.0, 1.0);
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}

/* Fonction executee lors d'un changement       */

/* de la taille de la fenetre OpenGL            */

static void reshape(int tx, int ty) {
    printf("R\n");
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = (double) tx / ty;
    if (ratio >= 1.0)
        gluPerspective(80.0, ratio, 1.0, 30.0);
    else
        gluPerspective(80.0 / ratio, ratio, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */

/* n'est en file d'attente                      */

static void idle(void) {
    printf("I\n");
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */

/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
        case 0x1B:
            exit(0);
            break;
    }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */

/*   - touches de fonction                      */

static void special(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            pz -= 0.1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            pz += 0.1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            px -= 0.1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            px += 0.1;
            glutPostRedisplay();
            break;
            //        case GLUT_KEY_PAGE_UP:
            //            pz -= 0.1;
            //            glutPostRedisplay();
            //            break;
            //        case GLUT_KEY_PAGE_DOWN:
            //            pz += 0.1;
            //            glutPostRedisplay();
            //            break;
        case GLUT_KEY_F1:
            px = 0.0;
            py = 10.0;
            pz = 0.0;
            glutPostRedisplay();
            break;
    }
}

/* Fonction executee lors de l'utilisation      */

/* de la souris sur la fenetre                  */

static void mouse(int buton, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", buton, state, x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* avec un boutton presse                       */

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* sans boutton presse                          */

static void passiveMouseMotion(int x, int y) {
    printf("PM %4d %4d\n", x, y);
}

/* Fonction executee automatiquement            */

/* lors de l'execution de la fonction exit()    */

static void clean(void) {
 //   delete ligneTest;
//    delete virage;
    printf("Bye\n");
}

static void createParcours() {
	Pos3D pos = Pos3D(10.0,0.0,10.0);
	Pos3D pos2 = Pos3D(5.0, 0.0, 5.0);
	Pos3D pos3 = Pos3D();
	parcours[0] = new MorceauParcoursLigne(pos, 2, 5, MorceauParcours::Direction::EST);
	parcours[1] = new MorceauParcoursVirage(pos2, 2, 5, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
}
/* Fonction principale                          */

int main(int argc, char **argv) {
    atexit(clean);
    glutInit(&argc, argv);
	createParcours();    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Projet Kart");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return (0);
}
