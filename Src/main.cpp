#include <stdlib.h>
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
#include "2D/CSVReader.h"

/* Variables globales                           */

static int wTx = 480; // Resolution horizontale de la fenetre
static int wTy = 480; // Resolution verticale de la fenetre
static int wPx = 50; // Position horizontale de la fenetre
static int wPy = 50; // Position verticale de la fenetre
static float px = 0;
static float py = 0;
static float pz = 30;
static float ox = 0;
static float oy = 0;
static float oz = 0;
static float camDepX = 0;
static float camDepY = 0;
static float camDepZ = 0;
static const float blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
static bool keys[6] = {false};
static bool keyboardKeys[256] = {false};
static int oldMX = -1, oldMY = -1;
static int deplMX = 0, deplMY = 0;
static bool cameraMove = false;
static float zoom = 1;
static double normeCamera = 1.0;

static Algorithm* algo;
static std::list<Conteneur*> conteneurs;
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
}

static void reset() {
    px = 0;
    py = 0;
    pz = 30;
    ox = 0;
    oy = 0;
    oz = 0;
    camDepX = 0;
    camDepZ = 0;
}

/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();
	std::list<Conteneur*>::iterator it;
	for (it = conteneurs.begin(); it != conteneurs.end(); it++) {
		(*it)->model();
	}
	std::list<Composant*>::iterator it2;
	for (it2 = composants.begin(); it2 != composants.end(); it2++) {
		(*it2)->model();
	}
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
    //if (cameraMove) {
    //    gluLookAt(px, py / 3.0 * zoom, pz, px, 0, pz, 0.0, 1.0, 0.0);
    //} else {
        normeCamera = sqrt(px * px + py * py + pz * pz);
        normeCamera /= 20.0;
        normeCamera /= zoom;
        //gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / 1, oy / 1, oz / 1, 0.0, 1.0, 0.0);
        gluLookAt(px / normeCamera, py / normeCamera, pz / normeCamera, ox / normeCamera, oy , oz / normeCamera, 0.0, 1.0, 0.0);
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
		zoom -= 0.001;
    }
    if (keys[KEY_PAGE_DOWN]) {
		zoom += 0.001;
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
	std::list<Conteneur*>::iterator it;
	for (it = conteneurs.begin(); it != conteneurs.end(); it++) {
		delete *it;
	}
	conteneurs.clear();
	std::list<Composant*>::iterator it2;
	for (it2 = composants.begin(); it2 != composants.end(); it2++) {
		delete *it2;
	}
	composants.clear();

	std::list<Composant*>::iterator it3;
	for (it3 = restants.begin(); it3 != restants.end(); it3++) {
		delete *it3;
	}
	restants.clear();
	if (algo != NULL) {
		delete algo;
	}
    printf("Bye\n");
}

/* Fonction principale                          */
static void createConteneurs() {
	Conteneur* conteneur0 = new Conteneur(0, 30, 30);
	Conteneur* conteneur1 = new Conteneur(1, 16, 8);
	Conteneur* conteneur2 = new Conteneur(2, 8, 16);
	Conteneur* conteneur3 = new Conteneur(3, 10, 10);
	conteneurs.push_back(conteneur0);
	//conteneurs.push_back(conteneur1);
	//conteneurs.push_back(conteneur2);
	//conteneurs.push_back(conteneur3);
}

static void verifCompo(std::vector <Composant *> liste) {
	printf("LISTE DES COMPOSANTS DU FICHIER CSV : \n");
	for (size_t i = 0; i < liste.size(); i++) {
		liste[i]->affichageComposant();
	}
}

static void testCSV() {
	//Changer possiblement le nom du fichier/lien en fonction d'où se trouve le fichier CSV
	std::string filename = "test3DBinPacking.csv";
	CSVReader *fichierCSV = new CSVReader(filename);
	fichierCSV->lireCSV();
	std::vector<Composant *> listeDesComposant = fichierCSV->getListComposant();


	std::vector<Composant*>::iterator it;
	Composant* test;
	for (it = listeDesComposant.begin(); it != listeDesComposant.end(); it++) {
		composants.push_back(*it);
	}
	//composants.insert(composants.end(), listeDesComposant.begin(), listeDesComposant.end());


	algo = new Algorithm(composants, conteneurs);
	//std::list<Composant*> reste = algo->calculRangement();
	//restants.insert(restants.begin(), reste.begin(), reste.end());
	verifCompo(listeDesComposant);
}


int main(int argc, char **argv) {
    atexit(clean);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(wTx, wTy);
    glutInitWindowPosition(wPx, wPy);
    glutCreateWindow("Title");
    init();
	createConteneurs();
	std::list<Conteneur*>::iterator it;
	for (it = conteneurs.begin(); it != conteneurs.end(); it++) {
		(*it)->affichageConteneur();
	}
	testCSV();
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
