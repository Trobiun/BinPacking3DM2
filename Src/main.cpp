#include "2D/Debug.h"

#include <stdio.h>
#include <cmath>
#include <list>
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "2D/Algorithm.h"
#include "2D/ArbreBinaire.h"
#include "2D/Conteneur.h"
#include "3D/Conteneur3D.h"
#include "2D/CSVReader.h"

/* Variables globales                           */

static int affichage3Dou2D = 0;
static int wTx = 480; // Resolution horizontale de la fenetre
static int wTy = 480; // Resolution verticale de la fenetre
static int wPx = 50; // Position horizontale de la fenetre
static int wPy = 50; // Position verticale de la fenetre
static float px = 25;
static float py = 25;
static float pz = 30;
static float ox = 25;
static float oy = 25;
static float oz = 0;
static float camDepX = 0;
static float camDepY = 0;
static float camDepZ = 0;
static bool keys[6] = {false};
static bool keyboardKeys[256] = {false};
static int oldMX = -1, oldMY = -1;
static int deplMX = 0, deplMY = 0;
static bool cameraMove = false;
static float zoom = 3.0;
static double normeCamera = 1.0;
static const GLfloat blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
static const GLfloat vert[4] = {0.0F, 1.0F, 0.0F, 1.0F};
static const GLfloat light0_position[4] = {0.0, 0.0, 10.0, 1.0};

static Algorithm* algo;
static std::list<Conteneur*> conteneurs;
static std::list<Conteneur3D*> conteneurs3D;
static std::list<Composant*> composants;
static std::list<Composant*> restants;

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
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
}

static void reset() {
    px = 25;
    py = 25;
    pz = 30;
    ox = 25;
    oy = 25;
    oz = 0;
    camDepX = 0;
    camDepZ = 0;
}

/* Scene dessinee                               */

static void scene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	if (affichage3Dou2D == 0) {
		std::list<Conteneur*>::iterator it;
		std::list<Composant *> compo;
		for (it = conteneurs.begin(); it != conteneurs.end(); it++) {
			std::list<Composant*>::iterator it2;
			compo = (*it)->getListComposant();
			for (it2 = compo.begin(); it2 != compo.end(); it2++) {
				(*it2)->model(vert);
			}
			(*it)->model();
		}
	}
	else {
		std::list<Conteneur3D*>::iterator it;
		std::list<Composant3D *> compo;
		for (it = conteneurs3D.begin(); it != conteneurs3D.end(); it++) {
			std::list<Composant3D*>::iterator it2;
			compo = (*it)->getListComposant();
			for (it2 = compo.begin(); it2 != compo.end(); it2++) {
				(*it2)->model(vert);
			}
			(*it)->model();
		}
	}
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */

/* de la fenetre de dessin                      */

static void display(void) {
    //printf("D\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    //if (cameraMove) {
    //    gluLookAt(px, py / 3.0 * zoom, pz, px, 0, pz, 0.0, 1.0, 0.0);
    //} else {
    normeCamera = sqrt(px * px + py * py + pz * pz);
    normeCamera /= 20.0;
    normeCamera /= zoom;
    //gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / 1, oy / 1, oz / 1, 0.0, 1.0, 0.0);
    gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / normeCamera, oy / normeCamera, oz / normeCamera, 0.0, 1.0, 0.0);
    //}
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
    //printf("R\n");
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
    //printf("I\n");
    if (keys[KEY_UP]) {
        py -= 0.25;
    }
    if (keys[KEY_DOWN]) {
        py += 0.25;
    }
    if (keys[KEY_LEFT]) {
        px -= 0.25;
    }
    if (keys[KEY_RIGHT]) {
        px += 0.25;
    }
    if (keys[KEY_PAGE_UP]) {
        zoom -= 0.05;
    }
    if (keys[KEY_PAGE_DOWN]) {
        zoom += 0.05;
    }
    if (keyboardKeys['z']) {
        py += 0.05;
        oy = py;
    }
    if (keyboardKeys['s']) {
        py -= 0.05;
        oy = py;
    }
    if (keyboardKeys['q']) {
        px -= 0.05;
        ox = px;
    }
    if (keyboardKeys['d']) {
        px += 0.05;
        ox = px;
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

static void keyboardUp(unsigned char key, int x, int y) {
    keyboardKeys[key] = false;
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */

/*   - touches de fonction                      */

static void specialUp(int specialKey, int x, int y) {
    //printf("S  %4d %4d %4d\n", specialKey, x, y);
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

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */

/*   - touches de fonction                      */

static void special(int specialKey, int x, int y) {
    //printf("S  %4d %4d %4d\n", specialKey, x, y);
    switch (specialKey) {
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
    printf("Clean\n");
    std::list<Conteneur*>::iterator it;
    for (it = conteneurs.begin(); it != conteneurs.end(); it++) {
        //delete *it;
    }
    //conteneurs.clear();
    std::list<Composant*>::iterator it2;
    for (it2 = composants.begin(); it2 != composants.end(); it2++) {
        //delete *it2;
    }
    //composants.clear();

    std::list<Composant*>::iterator it3;
    for (it3 = restants.begin(); it3 != restants.end(); it3++) {
        //delete *it3;
    }
    //restants.clear();
    if (algo != NULL) {
        delete algo;
    }
#ifdef _WIN32
	int test = _CrtDumpMemoryLeaks();
	printf("Bye %i\n",test);
#endif
}

/* Fonction principale                          */
static void createConteneur2D() {
    Conteneur* conteneur0 = DBG_NEW Conteneur(0, 60.0F, 50.0F);
    conteneurs.push_back(conteneur0);
}

static void createConteneur3D() {
	Conteneur3D* conteneur0 = DBG_NEW Conteneur3D(0, 50.0F, 50.0F, 50.0F);
	conteneurs3D.push_back(conteneur0);
}

static void verifCompoVector(std::vector <Composant *> liste) {
    printf("LISTE DES COMPOSANTS DU FICHIER CSV : \n");
    for (size_t i = 0; i < liste.size(); i++) {
        liste[i]->affichageComposant();
    }
}

static void verifCompoList(std::list <Composant*> liste, int type) {
    if (type == -1) {
        printf("LISTE DES COMPOSANTS DE LA LISTE RESTE: \n");
    } else {
        printf("LISTE DES COMPOSANTS DE LA LISTE CONTENEUR %d: \n", type);
    }
    std::list<Composant*>::iterator comp = liste.begin();
    while (comp != liste.end()) {
        (*comp)->affichageComposant();
        comp++;
    }
}

static void testCSV() {
    //Changer possiblement le nom du fichier/lien en fonction d'o� se trouve le fichier CSV
    std::string filename = "test3DBinPacking.csv";
    CSVReader *fichierCSV = DBG_NEW CSVReader(filename);
    fichierCSV->lireCSV();
    std::vector<Composant *> listeDesComposant = fichierCSV->getListComposant();

    std::vector<Composant*>::iterator it;
    for (it = listeDesComposant.begin(); it != listeDesComposant.end(); it++) {
        composants.push_back(*it);
    }
    //listeDesComposant.clear();
    //composants.insert(composants.end(), listeDesComposant.begin(), listeDesComposant.end());

    algo = DBG_NEW Algorithm(composants, conteneurs);
    std::list<Composant*> reste = algo->calculRangement();

    restants.insert(restants.begin(), reste.begin(), reste.end());
    verifCompoVector(listeDesComposant);
    verifCompoList(restants, -1);
    verifCompoList((*conteneurs.begin())->getListComposant(), 1);
    if (fichierCSV != NULL) {
        delete fichierCSV;
    }
}

int main(int argc, char **argv) {
    atexit(clean);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("3DBinPacking");
    init();
	if (affichage3Dou2D == 0) {
		createConteneur2D();
		std::list<Conteneur*>::iterator it;
		for (it = conteneurs.begin(); it != conteneurs.end(); it++) {
			(*it)->affichageConteneur();
		}
		testCSV();
	}
	else {
		createConteneur3D();
		Composant3D* comp1 = DBG_NEW Composant3D(0, 10.0F, 10.0F, 10.0F, 0, 10, 0);
		Composant3D* comp2 = DBG_NEW Composant3D(1, 10.0F, 10.0F, 20.0F, 0, 0, 0);
		std::list<Conteneur3D*>::iterator it;
		for (it = conteneurs3D.begin(); it != conteneurs3D.end(); it++) {
			(*it)->addComposant(comp1);
			(*it)->addComposant(comp2);
		}
	}
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    //glutMouseFunc(mouse);
    //glutMotionFunc(mouseMotion);
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMainLoop();
    return (0);
}
