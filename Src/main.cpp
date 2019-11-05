#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cstdbool>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables globales                           */

static int wTx = 480; // Resolution horizontale de la fenetre
static int wTy = 480; // Resolution verticale de la fenetre
static int wPx = 50; // Position horizontale de la fenetre
static int wPy = 50; // Position verticale de la fenetre
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
static int oldMX = -1, oldMY = -1;
static int deplMX = 0, deplMY = 0;
static bool cameraMove = true;
static float zoom = 1;
static double normeCamera = 1.0;

#define KEY_LEFT 0
#define KEY_UP 1
#define KEY_RIGHT 2
#define KEY_DOWN 3
#define KEY_PAGE_UP 4
#define KEY_PAGE_DOWN 5

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
    glEnable(GL_TEXTURE_2D);
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
}

/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();
    glutSolidCube(1.0);
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
    if (cameraMove) {
        gluLookAt(px, py / 3.0 * zoom, pz, px, 0, pz, 0.0, 0.0, -1.0);
    } else {
        normeCamera = sqrt(px * px + py * py + pz * pz);
        normeCamera /= 20.0;
        normeCamera /= zoom;
        //            printf("%lf\n", normeCamera);
        //            gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / 1, 0, oz / 1, 0.0, 0.0, -1.0);
        gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / normeCamera, 0, oz / normeCamera, 0.0, 0.0, -1.0);
    }
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

static void reshape(int wx, int wy) {
    printf("R\n");
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = (double) wTx / wTy;
    if (ratio >= 1.0) {
        gluPerspective(80.0, ratio, 1.0, 100.0);
    } else {
        gluPerspective(80.0 / ratio, ratio, 1.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */

/* n'est en file d'attente                      */

static void idle(void) {
    printf("I\n");
    if (keys[KEY_UP]) {
        pz -= 1;
        if (cameraMove) {
            oz = pz;
        }
    }
    if (keys[KEY_DOWN]) {
        pz += 1;
        if (cameraMove) {
            oz = pz;
        }
    }
    if (keys[KEY_LEFT]) {
        px -= 1;
        if (cameraMove) {
            ox = px;
        }
        glutPostRedisplay();
    }
    if (keys[KEY_RIGHT]) {
        px += 1;
        if (cameraMove) {
            ox = px;
        }
    }
    if (keys[KEY_PAGE_UP]) {
        py -= 1;
    }
    if (keys[KEY_PAGE_DOWN]) {
        py += 1;
    }
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */

/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    if (key == 0x1B) {
        exit(0);
    }
    if (key == 13) {
        reset();
    }
    keyboardKeys[key] = true;
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */

/*   - touches de fonction                      */

static void special(int specialKey, int x, int y) {
    printf("S  %4d %4d %4d\n", specialKey, x, y);
    switch (specialKey) {
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

/* Fonction executee lors de l'utilisation      */

/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", button, state, x, y);
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        cameraMove = true;
        px = ox;
        pz = oz;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cameraMove = false;
        ox = px;
        oz = pz;
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
    printf("MM %4d %4d\n", x, y);
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
    oldMX = x;
    oldMY = y;
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
    printf("Bye\n");
}

/* Fonction principale                          */

int main(int argc, char **argv) {
    atexit(clean);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Title");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
    return (0);
}
