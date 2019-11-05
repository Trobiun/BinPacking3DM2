#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <cstdbool>

#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "2d/rectangle.h"
/* variables globales                           */

static int wtx = 480; // resolution horizontale de la fenetre
static int wty = 480; // resolution verticale de la fenetre
static int wpx = 50; // position horizontale de la fenetre
static int wpy = 50; // position verticale de la fenetre
static float px = 0;
static float py = 30;
static float pz = 0;
static float ox = 0;
static float oy = 0;
static float oz = 0;
static float camdepx = 0;
static float camdepy = 30;
static float camdepz = 0;
static const float blanc[] = {1.0f, 1.0f, 1.0f, 1.0f};
static bool keys[6] = {false};
static bool keyboardkeys[256] = {false};
static int oldmx = -1, oldmy = -1;
static int deplmx = 0, deplmy = 0;
static bool cameramove = true;
static float zoom = 1;
static double normecamera = 1.0;

#define key_left 0
#define key_up 1
#define key_right 2
#define key_down 3
#define key_page_up 4
#define key_page_down 5

/* fonction d'initialisation des parametres     */
/* opengl ne changeant pas au cours de la vie   */

/* du programme                                 */

static void init(void) {
    glclearcolor(0.25f, 0.25f, 0.25f, 1.0f);
    gllightfv(gl_light0, gl_diffuse, blanc);
    glenable(gl_lighting);
    glenable(gl_light0);
    gldepthfunc(gl_less);
    glenable(gl_depth_test);
    glenable(gl_texture_2d);
    glenable(gl_normalize);
}

static void reset() {
    px = 0;
    py = 30;
    pz = 0;
    ox = 0;
    oy = 0;
    oz = 0;
    camdepx = 10.0;
    camdepz = 0;
}

/* scene dessinee                               */

static void scene(void) {
    glpushmatrix();
    glutsolidcube(1.0);
    glpopmatrix();
}

/* fonction executee lors d'un rafraichissement */

/* de la fenetre de dessin                      */

static void display(void) {
    printf("d\n");
    glclear(gl_color_buffer_bit | gl_depth_buffer_bit);
    const glfloat light0_position[] = {0.0, 0.0, 10.0, 1.0};
    glpushmatrix();
    gllightfv(gl_light0, gl_position, light0_position);
    if (cameramove) {
        glulookat(px, py / 3.0 * zoom, pz, px, 0, pz, 0.0, 0.0, -1.0);
    } else {
        normecamera = sqrt(px * px + py * py + pz * pz);
        normecamera /= 20.0;
        normecamera /= zoom;
        //            printf("%lf\n", normecamera);
        //            glulookat(px / normecamera, py / normecamera, pz / normecamera, ox / 1, 0, oz / 1, 0.0, 0.0, -1.0);
        glulookat(px / normecamera, py / normecamera, pz / normecamera, ox / normecamera, 0, oz / normecamera, 0.0, 0.0, -1.0);
    }
    scene();
    glpopmatrix();
    glflush();
    glutswapbuffers();
    int error = glgeterror();
    if (error != gl_no_error)
        printf("attention erreur %d\n", error);
}

/* fonction executee lors d'un changement       */

/* de la taille de la fenetre opengl            */

static void reshape(int wx, int wy) {
    printf("r\n");
    wtx = wx;
    wty = wy;
    glviewport(0, 0, wx, wy);
    glmatrixmode(gl_projection);
    glloadidentity();
    double ratio = (double) wtx / wty;
    if (ratio >= 1.0) {
        gluperspective(80.0, ratio, 1.0, 100.0);
    } else {
        gluperspective(80.0 / ratio, ratio, 1.0, 100.0);
    }
    glmatrixmode(gl_modelview);
    glloadidentity();
}

/* fonction executee lorsqu'aucun evenement     */

/* n'est en file d'attente                      */

static void idle(void) {
    printf("i\n");
    if (keys[key_up]) {
        pz -= 1;
        if (cameramove) {
            oz = pz;
        }
    }
    if (keys[key_down]) {
        pz += 1;
        if (cameramove) {
            oz = pz;
        }
    }
    if (keys[key_left]) {
        px -= 1;
        if (cameramove) {
            ox = px;
        }
        glutpostredisplay();
    }
    if (keys[key_right]) {
        px += 1;
        if (cameramove) {
            ox = px;
        }
    }
    if (keys[key_page_up]) {
        py -= 1;
    }
    if (keys[key_page_down]) {
        py += 1;
    }
    glutpostredisplay();
}

/* fonction executee lors de l'appui            */

/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    if (key == 0x1b) {
        exit(0);
    }
    if (key == 13) {
        reset();
    }
    keyboardkeys[key] = true;
}

/* fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */

/*   - touches de fonction                      */

static void special(int specialkey, int x, int y) {
    printf("s  %4d %4d %4d\n", specialkey, x, y);
    switch (specialkey) {
        case glut_key_left:
            keys[key_left] = false;
            break;
        case glut_key_up:
            keys[key_up] = false;
            break;
        case glut_key_right:
            keys[key_right] = false;
            break;
        case glut_key_down:
            keys[key_down] = false;
            break;
        case glut_key_page_up:
            keys[key_page_up] = false;
            break;
        case glut_key_page_down:
            keys[key_page_down] = false;
            break;
    }
}

/* fonction executee lors de l'utilisation      */

/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    printf("m  %4d %4d %4d %4d\n", button, state, x, y);
    if (button == glut_middle_button && state == glut_down) {
        cameramove = true;
        px = ox;
        pz = oz;
    }
    if (button == glut_left_button && state == glut_down) {
        cameramove = false;
        ox = px;
        oz = pz;
    }
    if (button == 3 && state == glut_down) {
        zoom -= 0.1;
    }
    if (button == 4 && state == glut_down) {
        zoom += 0.1;
    }
}

/* fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* avec un boutton presse                       */

static void mousemotion(int x, int y) {
    printf("mm %4d %4d\n", x, y);
    if (oldmx < 0) {
        oldmx = x;
    }
    if (oldmy < 0) {
        oldmy = y;
    }
    if (x < oldmx) {
        deplmx = -1;
    }
    if (x > oldmx) {
        deplmx = 1;
    }
    int diffx = x - oldmx;
    int diffy = y - oldmy;
    px += diffx % 3;
    pz += diffy % 3;
    oldmx = x;
    oldmy = y;
}

/* fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* sans boutton presse                          */

static void passivemousemotion(int x, int y) {
    printf("pm %4d %4d\n", x, y);
}

/* fonction executee automatiquement            */

/* lors de l'execution de la fonction exit()    */

static void clean(void) {
    printf("bye\n");
}

/* fonction principale                          */

int main(int argc, char **argv) {
    atexit(clean);

    glutinit(&argc, argv);
    glutinitdisplaymode(glut_rgba | glut_depth | glut_double);
    glutinitwindowsize(wtx, wty);
    glutinitwindowposition(wpx, wpy);
    glutcreatewindow("title");
    init();
    glutkeyboardfunc(keyboard);
    glutspecialfunc(special);
    glutmousefunc(mouse);
    glutmotionfunc(mousemotion);
    //glutpassivemotionfunc(passivemousemotion);
    glutreshapefunc(reshape);
    glutidlefunc(idle);
    glutdisplayfunc(display);
    glutmainloop();
    return (0);
}
