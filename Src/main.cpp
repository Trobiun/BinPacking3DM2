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
static bool camera4Move = true;
static float zoom = 1;
static double normeCamera = 1.0;
static float px = 0;
static float py = 30;
static float pz = 0;
static float ox = 0;
static float oy = 0;
static float oz = 0;
static float camDepX = 0;
static float camDepY = 30;
static float camDepZ = 0;
static const float blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
static bool keys[6] = {false};
static bool keyboardKeys[256] = {false};

static Cars *cars;
static Car *car;
std::chrono::time_point<std::chrono::system_clock> lastFrame;
//modeCamera = 1 ==> 1ère personne
//modeCamera = 2 ==> vue du dessus
//modeCamera = 3 ==> 3ème personne
//modeCamera = 4 ==> caméra libre
static int modeCamera = 3;
static int oldMX = -1, oldMY = -1;
static int deplMX = 0, deplMY = 0;

static const int nbMorceau = 24;

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
    camDepX = 10.0;
    camDepZ = 0;
    if (cars != NULL) {
        delete cars;
    }
    if (car != NULL) {
        delete car;
    }
    cars = new Cars(1.0, 2.5, 5.0, Pos3D(0, 1.0, 0), 0);
    cars->setCurrentMorceauParcoursIndex(0);
}

/* Scene dessinee                               */

static void scene(void) {
    for (int i = 0; i < nbMorceau; i++) {
        glPushMatrix();
        parcours[i]->modeliser();
        //        Pos3D flouboulou = parcours[i]->getPosition();
        //        glTranslated(flouboulou.x, flouboulou.y, flouboulou.z);
        //        glutSolidCube(0.5);
        glPopMatrix();
    }
    glPushMatrix();
    cars->model();
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
    double norme = sqrt(cars->getDeplaceX() * cars->getDeplaceX() + cars->getDeplaceZ() * cars->getDeplaceZ());
    if (norme != 0) {
        camDepX = cars->getDeplaceX() / norme * 10 + cars->getDeplaceX() / 10;
        camDepZ = cars->getDeplaceZ() / norme * 10 + cars->getDeplaceZ() / 10;
    }
    if (modeCamera != 4) {
        px = pos.x + cars->length / 2;
        pz = pos.z + cars->width / 2;
    }
    if (modeCamera == 1) {
        gluLookAt(px, pos.y + cars->height * 4, pz, px + camDepX * 50, 0, pz + camDepZ * 50, 0.0, 1.0, 0.0);
    }
    if (modeCamera == 2) {
        gluLookAt(px, py, pz, px, 0, pz, camDepX, 0.0, camDepZ);
    }
    if (modeCamera == 3) {
        gluLookAt(px - camDepX, py / 3.0, pz - camDepZ, px + camDepX, 0, pz + camDepZ, 0.0, 1.0, 0.0);
    }
    if (modeCamera == 4) {
        if (camera4Move) {
            gluLookAt(px, py / 3.0 * zoom, pz, px, 0, pz, 0.0, 0.0, -1.0);
        }
        else {
            normeCamera = sqrt(px * px + py * py + pz * pz);
            normeCamera /= 20.0;
            normeCamera /= zoom;
            //            gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / 1, 0, oz / 1, 0.0, 0.0, -1.0);
            gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / normeCamera, 0, oz / normeCamera, 0.0, 0.0, -1.0);
        }
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
    std::chrono::duration<double> diffTime = test - lastFrame;
    double diffTimeDouble = diffTime.count();
    if (keys[KEY_UP]) {
        pz -= 1;
        if (modeCamera == 4 && camera4Move) {
            oz = pz;
        }
    }
    if (keys[KEY_DOWN]) {
        pz += 1;
        if (modeCamera == 4 && camera4Move) {
            oz = pz;
        }
    }
    if (keys[KEY_LEFT]) {
        px -= 1;
        if (modeCamera == 4 && camera4Move) {
            ox = px;
        }
        glutPostRedisplay();
    }
    if (keys[KEY_RIGHT]) {
        px += 1;
        if (modeCamera == 4 && camera4Move) {
            ox = px;
        }
    }
    if (keys[KEY_PAGE_UP]) {
        py -= 1;
    }
    if (keys[KEY_PAGE_DOWN]) {
        py += 1;
    }
    if (keyboardKeys['z']) {
        cars->accelerate(1, diffTimeDouble);
    }
    if (keyboardKeys['s']) {
        cars->accelerate(-1, diffTimeDouble);
    }
    if (!keyboardKeys['z'] && !keyboardKeys['s']) {
        cars->accelerate(0, diffTimeDouble);
    }
    if (keyboardKeys['d']) {
        cars->moveD(diffTimeDouble);
    }
    if (keyboardKeys['q']) {
        cars->moveG(diffTimeDouble);
    }
    Pos3D futurePos = cars->getFuturePosition(diffTimeDouble);
    int indexBefore, indexBefore2, indexAfter, indexAfter2;
    bool presenceCurr, presenceBefore, presenceBefore2, presenceAfter, presenceAfter2;
    int indexCurrent = cars->getCurrentMorceauParcoursIndex();
    indexBefore = indexCurrent - 1;
    if (indexBefore < 0) {
        indexBefore += nbMorceau;
    }
    indexBefore2 = indexBefore - 1;
    if (indexBefore2 < 0) {
        indexBefore2 += nbMorceau;
    }
    indexAfter = (indexCurrent + 1) % nbMorceau;
    indexAfter2 = (indexAfter + 1) % nbMorceau;

    presenceCurr = parcours[indexCurrent]->testPresenceCar(futurePos);
    if (!presenceCurr) {
        presenceAfter = parcours[indexAfter]->testPresenceCar(futurePos);
        presenceBefore = parcours[indexBefore]->testPresenceCar(futurePos);
        presenceBefore2 = parcours[indexBefore2]->testPresenceCar(futurePos);
        presenceAfter2 = parcours[indexAfter2]->testPresenceCar(futurePos);

        if (presenceAfter) {
            cars->setCurrentMorceauParcoursIndex(indexAfter);
        }
        if (presenceBefore) {
            cars->setCurrentMorceauParcoursIndex(indexBefore);
        }
        if (presenceAfter2) {
            cars->setCurrentMorceauParcoursIndex(indexAfter2);
        }
        if (presenceBefore2) {
            cars->setCurrentMorceauParcoursIndex(indexBefore2);
        }
    }
    if (presenceBefore2 || presenceBefore || presenceCurr || presenceAfter || presenceAfter2) {
        cars->move(diffTimeDouble);
    }
    else {
        cars->stop();
    }
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
    if (key == '4') {
        modeCamera = 4;
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

static void mouse(int button, int state, int x, int y) {
    //printf("M  %4d %4d %4d %4d\n", button, state, x, y);
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        camera4Move = true;
        px = ox;
        pz = oz;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        camera4Move = false;
        ox = px;
        oz = pz;
        //        px = ox * normeCamera;
        //        pz = oz * normeCamera;
    }
    if (button == 3 && state == GLUT_DOWN) {
        zoom -= 0.1;
    }
    if (button == 4 && state == GLUT_DOWN) {
        zoom += 0.1;
    }
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
    if (modeCamera == 4 && camera4Move) {
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
    int posLastx = 0;
    int posLastz = 0;
    parcours[0] = new MorceauParcoursLigne(Pos3D(posLastz = 0.0, 0.0, posLastx = 0.0), 16, 254, MorceauParcours::Direction::OUEST);
    parcours[1] = new MorceauParcoursVirage(Pos3D(posLastx += 254.0, 0.0, posLastz += -8.0), 16, 24, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
    parcours[2] = new MorceauParcoursLigne(Pos3D(posLastx += (24.0 - 16.0), 0.0, posLastz += -64.0), 16, 64, MorceauParcours::Direction::NORD);
    parcours[3] = new MorceauParcoursVirage(Pos3D(posLastx += 54.0, 0.0, posLastz), 16, 54, MorceauParcours::Direction::NORD, MorceauParcours::Direction::EST);
    parcours[4] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz += -54.0 * 2 + 16.0), 16, 54, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
    parcours[5] = new MorceauParcoursLigne(Pos3D(posLastx += 54.0 - 16.0, 0.0, posLastz += -64.0), 16, 64, MorceauParcours::Direction::NORD);
    //    parcours[6] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 16, MorceauParcours::Direction::EST, MorceauParcours::Direction::NORD);
    parcours[6] = new MorceauParcoursVirage(Pos3D(posLastx += 66, 0.0, posLastz), 16, 66, MorceauParcours::Direction::NORD, MorceauParcours::Direction::EST);
    parcours[7] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz), 16, 66, MorceauParcours::Direction::EST, MorceauParcours::Direction::SUD);
    parcours[8] = new MorceauParcoursVirage(Pos3D(posLastx += 55 + 66 - 16, 0.0, posLastz), 16, 55, MorceauParcours::Direction::SUD, MorceauParcours::Direction::EST);
    parcours[9] = new MorceauParcoursLigne(Pos3D(posLastx, 0.0, posLastz += 55 - 16), 16, 58, MorceauParcours::Direction::EST);
    parcours[10] = new MorceauParcoursVirage(Pos3D(posLastx += 58, 0.0, posLastz += 28), 16, 28, MorceauParcours::Direction::EST, MorceauParcours::Direction::SUD);
    parcours[11] = new MorceauParcoursLigne(Pos3D(posLastx += 28 - 16, 0.0, posLastz), 16, 127, MorceauParcours::Direction::NORD);
    parcours[12] = new MorceauParcoursVirage(Pos3D(posLastx += -32 + 16, 0.0, posLastz += 127), 16, 32, MorceauParcours::Direction::SUD, MorceauParcours::Direction::OUEST);
    parcours[13] = new MorceauParcoursLigne(Pos3D(posLastx += -58, 0.0, posLastz += 32 - 16), 16, 58, MorceauParcours::Direction::EST);
    parcours[14] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz += -58 + 16), 16, 58, MorceauParcours::Direction::OUEST, MorceauParcours::Direction::NORD);
    parcours[15] = new MorceauParcoursVirage(Pos3D(posLastx += -58 - 36 + 16, 0.0, posLastz), 16, 36, MorceauParcours::Direction::NORD, MorceauParcours::Direction::OUEST);
    parcours[16] = new MorceauParcoursLigne(Pos3D(posLastx += -75, 0.0, posLastz += -36), 16, 75, MorceauParcours::Direction::EST);
    parcours[17] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz += 25), 16, 25, MorceauParcours::Direction::OUEST, MorceauParcours::Direction::SUD);
    parcours[18] = new MorceauParcoursLigne(Pos3D(posLastx += -25, 0.0, posLastz), 16, 120, MorceauParcours::Direction::NORD);
    parcours[19] = new MorceauParcoursVirage(Pos3D(posLastx += -32 + 16, 0.0, posLastz += 120), 16, 32, MorceauParcours::Direction::SUD, MorceauParcours::Direction::OUEST);
    parcours[20] = new MorceauParcoursLigne(Pos3D(posLastx += -320, 0.0, posLastz += 32 - 16), 16, 320, MorceauParcours::Direction::EST);
    parcours[21] = new MorceauParcoursVirage(Pos3D(posLastx, 0.0, posLastz += -43 + 16), 16, 43, MorceauParcours::Direction::OUEST, MorceauParcours::Direction::NORD);
    parcours[22] = new MorceauParcoursLigne(Pos3D(posLastx += -43, 0.0, posLastz += -2), 16, 2, MorceauParcours::Direction::NORD);
    parcours[23] = new MorceauParcoursVirage(Pos3D(posLastx += -7 + 43, 0.0, posLastz), 16, 36, MorceauParcours::Direction::NORD, MorceauParcours::Direction::EST);
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
