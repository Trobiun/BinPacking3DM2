#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <chrono>
#include <ctime>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "CH3D.h"
#include "MorceauParcoursLigne.h"
#include "Pos3D.h"
#include "MorceauParcoursVirage.h"
#include "MorceauParcours.h"
#include "Cars.h"
#include "Car.h"

#define KEY_LEFT 0
#define KEY_UP 1
#define KEY_RIGHT 2
#define KEY_DOWN 3
#define KEY_PAGE_UP 4
#define KEY_PAGE_DOWN 5

#define EPSILON 0.001

/* Variables globales                           */

static int wTx = 1024; // Resolution horizontale de la fenetre
static int wTy = 576; // Resolution verticale de la fenetre
static int wPx = 50; // Position horizontale de la fenetre
static int wPy = 50; // Position verticale de la fenetre
static float px = 0;
static float py = 30;
static float pz = 0;
static float ox = 0;
static float oy = 0;
static float oz = 0;
static const float blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
static bool keys[6] = {false};
static bool keyboardKeys[256] = {false};

static Cars *cars;
static Car *car;
std::chrono::time_point<std::chrono::system_clock> lastFrame;
//modeCamera = 1 ==> 1ère personne
//modeCamera = 2 ==> vue du dessus
//modeCamera = 3 ==> 3ème personne
//modeCamera = 4 ==> caméra libre ?
static int modeCamera = 3;
static int oldMX = -1, oldMY = -1;
static int deplMX = 0, deplMY = 0;

static const int nbMorceau = 16;

static MorceauParcours *parcours[nbMorceau];
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

static void reset() {
    px = 0;
    py = 30;
    pz = 0;
    ox = 0;
    oy = 0;
    oz = 0;
    if (cars != NULL) {
        delete cars;
    }
    if (car != NULL) {
        delete car;
    }
    cars = new Cars(1.0, 2.5, 5.0, Pos3D(0, 0, 0), 0);
    //    car = new Car(1.0, 2.5, 5.0, Pos3D(0, 0, 0), 0);
}

/* Scene dessinee                               */

static void scene(void) {
    for (int i = 0; i < nbMorceau; i++) {
        glPushMatrix();
        parcours[i]->modeliser();
        Pos3D flouboulou = parcours[i]->getPosition();
        glTranslated(flouboulou.x, flouboulou.y, flouboulou.z);
        glutSolidCube(0.5);
        glPopMatrix();
    }
    glPushMatrix();
    cars->model();
    //    car->model();
    glPopMatrix();
}
/* Fonction executee lors d'un rafraichissement */

/* de la fenetre de dessin                      */

static void display(void) {
    //printf("D\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = {0.0, 0.0, 10.0, 1.0};
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    Pos3D pos = cars->getPosition();
    if (modeCamera == 1) {
        //TODO : calculer la position de la caméra
        gluLookAt(px, py, pz, ox, 0, oz, 0.0, 0.0, -1.0);
    }
    if (modeCamera == 2) {
        gluLookAt(pos.x, py, pos.z, pos.x, 0, pos.z, 0.0, 0.0, -1.0);
    }
    if (modeCamera == 3) {

        double depX = cars->getDeplaceX() / 4;
        double depZ = cars->getDeplaceZ() / 4;
        gluLookAt(pos.x - depX + cars->length / 2, py / 3, pos.z - depZ + cars->width / 2,
                pos.x + depX + cars->length / 2, 0, pos.z + depZ + cars->width / 2, 0.0, 1.0, 0.0);
    }
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Attention erreur %d\n", error);
    }
}

/* Fonction executee lors d'un changement       */

/* de la taille de la fenetre OpenGL            */

static void reshape(int tx, int ty) {
    //printf("R\n");
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = (double) tx / ty;
    if (ratio >= 1.0) {
        gluPerspective(80.0, ratio, 1.0, 100.0);
    }
    else {
        gluPerspective(80.0 / ratio, ratio, 1.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */

/* n'est en file d'attente                      */

static void idle(void) {
    //printf("I\n");
    std::chrono::time_point<std::chrono::system_clock> test = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = test - lastFrame;
    double diffDouble = diff.count();
    //    printf("%lf\n", diffDouble);
    if (keys[KEY_UP]) {
        pz -= 1;
        if (modeCamera == 1) {
            oz = pz;
        }
    }
    if (keys[KEY_DOWN]) {
        pz += 1;
        if (modeCamera == 1) {
            oz = pz;
        }
    }
    if (keys[KEY_LEFT]) {
        px -= 1;
        if (modeCamera == 1) {
            ox = px;
        }
        glutPostRedisplay();
    }
    if (keys[KEY_RIGHT]) {
        px += 1;
        if (modeCamera == 1) {
            ox = px;
        }
    }
    if (keys[KEY_PAGE_UP]) {
        py -= 1;
        //oy = py;
    }
    if (keys[KEY_PAGE_DOWN]) {
        py += 1;
        //oy = py;
    }
    if (keyboardKeys['z']) {
        cars->accelerate(1, diffDouble);
        //        car->accelerate(1, diffDouble);
    }

    if (keyboardKeys['s']) {
        cars->accelerate(-1, diffDouble);
        //        car->accelerate(-1, diffDouble);
    }

    if (!keyboardKeys['z'] && !keyboardKeys['s']) {
        cars->accelerate(0, diffDouble);
        //        car->accelerate(0, diffDouble);
    }
    if (keyboardKeys['d']) {
        cars->moveD(diffDouble);
        //        car->moveD();
        //        printf("on tourne a droite\n");
    }
    if (keyboardKeys['q']) {
        cars->moveG(diffDouble);
        //        car->moveG();
        //        printf("on tourne a gauche\n");
    }
    cars->move(diffDouble);
    //    car->move(diffDouble);
    lastFrame = test;
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */

/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    //printf("K  %4c %4d %4d\n", key, x, y);
    if (key == 0x1B) {
        exit(0);
    }
    if (key == 13) {
        reset();
    }
    if (key == '1') {
        modeCamera = 1;
        glutPostRedisplay();
    }
    if (key == '2') {
        modeCamera = 2;
        glutPostRedisplay();
    }
    if (key == '3') {

        modeCamera = 3;
        glutPostRedisplay();
    }
    keyboardKeys[key] = true;
}

static void keyboardUp(unsigned char key, int x, int y) {

    keyboardKeys[key] = false;
}

static void specialUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            keys[KEY_LEFT] = false;
            break;
        case GLUT_KEY_UP:
            keys[KEY_UP] = false;
            break;
        case GLUT_KEY_RIGHT:
            keys[KEY_RIGHT] = false;
            break;
        case GLUT_KEY_DOWN:
            keys[KEY_DOWN] = false;
            break;
        case GLUT_KEY_PAGE_UP:
            keys[KEY_PAGE_UP] = false;
            break;
        case GLUT_KEY_PAGE_DOWN:
            keys[KEY_PAGE_DOWN] = false;

            break;
    }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */

/*   - touches de fonction                      */

static void special(int key, int x, int y) {
    //printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
        case GLUT_KEY_LEFT:
            keys[KEY_LEFT] = true;
            break;
        case GLUT_KEY_UP:
            keys[KEY_UP] = true;
            break;
        case GLUT_KEY_RIGHT:
            keys[KEY_RIGHT] = true;
            break;
        case GLUT_KEY_DOWN:
            keys[KEY_DOWN] = true;
            break;
        case GLUT_KEY_PAGE_UP:
            keys[KEY_PAGE_UP] = true;
            break;
        case GLUT_KEY_PAGE_DOWN:
            keys[KEY_PAGE_DOWN] = true;

            break;
    }
}

/* Fonction executee lors de l'utilisation      */

/* de la souris sur la fenetre                  */

static void mouse(int buton, int state, int x, int y) {
    //printf("M  %4d %4d %4d %4d\n", buton, state, x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* avec un boutton presse                       */

static void mouseMotion(int x, int y) {
    //printf("MM %4d %4d\n", x, y);
    if (oldMX < 0) {
        oldMX = x;
    }
    if (oldMY < 0) {
        oldMY = y;
    }
    if (x < oldMX) {
        deplMX = -1;
    }
    if (x > oldMX) {
        deplMX = 1;
    }
    int diffX = x - oldMX;
    int diffY = y - oldMY;
    px += diffX % 3;
    pz += diffY % 3;
    if (modeCamera == 1) {

        ox = px;
        oz = pz;
    }
    oldMX = x;
    oldMY = y;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* sans boutton presse                          */

static void passiveMouseMotion(int x, int y) {
    //printf("PM %4d %4d\n", x, y);
}

/* Fonction executee automatiquement            */

/* lors de l'execution de la fonction exit()    */

static void clean(void) {
    if (cars != NULL) {
        delete cars;
    }
    if (car != NULL) {
        delete car;
    }
    //printf("Bye\n");
}

static void createParcours() {
	/*
		parcours[0] = new MorceauParcoursLigne(Pos3D(24.0, 0.0, 0.0), 16, 18, MorceauParcours::Direction::EST);
		parcours[1] = new MorceauParcoursVirage(Pos3D(42.0, 0.0, -8.0), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
		parcours[2] = new MorceauParcoursLigne(Pos3D(50.0, 0.0, -32.0), 16, 24, MorceauParcours::Direction::NORD);
		parcours[3] = new MorceauParcoursVirage(Pos3D(74.0, 0.0, -32.0), 16, 24, MorceauParcours::Direction::NORD, MorceauParcours::Direction::EST);
		parcours[4] = new MorceauParcoursVirage(Pos3D(74.0, 0.0, -32.0), 16, 24, MorceauParcours::Direction::EST, MorceauParcours::Direction::SUD);
		parcours[5] = new MorceauParcoursVirage(Pos3D(124.0, 0.0, -32.0), 16, 34, MorceauParcours::Direction::SUD, MorceauParcours::Direction::EST);
		parcours[6] = new MorceauParcoursLigne(Pos3D(124.0, 0.0, -6.0), 16, 42, MorceauParcours::Direction::EST);
		parcours[7] = new MorceauParcoursVirage(Pos3D(166.0, 0.0, 18.0), 16, 24, MorceauParcours::Direction::EST, MorceauParcours::Direction::SUD);
		parcours[8] = new MorceauParcoursVirage(Pos3D(174.0, 0.0, 18.0), 16, 16, MorceauParcours::Direction::SUD, MorceauParcours::Direction::OUEST);
		parcours[9] = new MorceauParcoursLigne(Pos3D(0.0, 0.0, 26.0), 16, 174, MorceauParcours::Direction::EST);
		parcours[10] = new MorceauParcoursVirage(Pos3D(0.0, 0.0, -16.0), 16, 50, MorceauParcours::Direction::OUEST, MorceauParcours::Direction::NORD);
		parcours[11] = new MorceauParcoursLigne(Pos3D(-50.0, 0.0, -56.0), 16, 40, MorceauParcours::Direction::NORD);
		parcours[12] = new MorceauParcoursVirage(Pos3D(-21.0, 0.0, -56.0), 16, 29, MorceauParcours::Direction::NORD, MorceauParcours::Direction::EST);
		parcours[13] = new MorceauParcoursVirage(Pos3D(-21.0, 0.0, -56.0), 16, 29, MorceauParcours::Direction::EST, MorceauParcours::Direction::SUD);
		parcours[14] = new MorceauParcoursLigne(Pos3D(0.0, 0.0, -56.0), 16, 40, MorceauParcours::Direction::NORD);
		parcours[15] = new MorceauParcoursVirage(Pos3D(24.0, 0.0, -16.0), 16, 24, MorceauParcours::Direction::SUD, MorceauParcours::Direction::EST);
	*/
	int posLastx = 0;
	int posLastz = 0;
	parcours[0] = new MorceauParcoursLigne(Pos3D(posLastz = 0.0, 0.0, posLastx = 0.0), 16, 254, MorceauParcours::Direction::EST);
	parcours[1] = new MorceauParcoursVirage(Pos3D(posLastx += 254.0, 0.0, posLastz += -8.0), 16, 24, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[2] = new MorceauParcoursLigne(Pos3D(posLastx += (24.0 - 16.0), 0.0, posLastz += -64.0), 16, 64, MorceauParcours::Direction::NORD);
	parcours[3] = new MorceauParcoursVirage(Pos3D(posLastx += 54.0, 0.0, posLastz), 16, 54, MorceauParcours::Direction::NORD, MorceauParcours::Direction::EST);
	parcours[4] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz += -54.0 * 2 + 16.0), 16, 54, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[5] = new MorceauParcoursLigne(Pos3D(posLastx += 54.0 - 16.0, 0.0, posLastz += -64.0), 16, 64, MorceauParcours::Direction::NORD);
	parcours[6] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[7] = new MorceauParcoursVirage(Pos3D(posLastx += 66, 0.0, posLastz), 16, 66, MorceauParcours::Direction::NORD, MorceauParcours::Direction::EST);
	parcours[8] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 66, MorceauParcours::Direction::EST, MorceauParcours::Direction::SUD);
	parcours[9] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[10] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[11] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[12] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[13] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[14] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
	parcours[15] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);

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
    glutIgnoreKeyRepeat(0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    lastFrame = std::chrono::system_clock::now();
    reset();

    glutMainLoop();
    return (0);
}
