#include "2D/Debug.h"

#include <stdio.h>
#include <cmath>
#include <list>
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "2D/Algorithm.h"
#include "3D/Algorithm3D.h"
#include "2D/ArbreBinaire.h"
#include "2D/Conteneur.h"
#include "3D/Conteneur3D.h"
#include "2D/CSVReader.h"
#include "3D/CSVReader3D.h"

/* Variables globales                           */

static int affichage3Dou2D = 1;
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
static bool keys[6] = {false};
static bool keyboardKeys[256] = {false};
static bool opaque = false;
static const GLfloat blanc[] = {1.0F, 1.0F, 1.0F, 1.0F};
static const GLfloat vert[4] = {0.0F, 1.0F, 0.0F, 1.0F};
static const GLfloat light0_position[4] = {0.0, 0.0, 10.0, 1.0};

static float r = 50;
static float anglex = 0.0;
static float angley = 0.0;

static std::list<Conteneur3D*>::iterator posCont3DDispo;
static std::list<Conteneur3D*>::iterator posCont3D;
static std::list<Conteneur*>::iterator posCont2DDispo;
static std::list<Conteneur*>::iterator posCont2D;

static Algorithm* algo;
static Algorithm3D* algo3D;

static std::list<Conteneur*> conteneurs;
static std::list<Conteneur*> conteneursDispo;
static std::list<Conteneur3D*> conteneurs3D;
static std::list<Conteneur3D*> conteneurs3DDispo;
static std::list<Composant*> composants;
static std::list<Composant3D*> composants3D;

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
    //    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
}

static void courantConteneur() {
    if (affichage3Dou2D == 0) {
        Position2D* posCont = (*posCont2D)->getPosition();
        px = (*posCont2D)->getCoteX() / 2 + posCont->getX();
        py = (*posCont2D)->getCoteY() / 2 + posCont->getY();
        pz = 30;
        ox = px;
        oy = py;
        oz = 0;
    } else {
        Position3D* posCont = (*posCont3D)->getPosition();
        px = (*posCont3D)->getCoteX() / 2 + posCont->getX();
        py = (*posCont3D)->getCoteY() / 2 + posCont->getY();
        pz = (*posCont3D)->getCoteZ() / 2 + posCont->getZ();
        ox = px;
        oy = py;
        oz = 0;
    }
    anglex = 0.0;
    angley = 0.0;
}

static void reset() {
    if (affichage3Dou2D == 0) {
        posCont2D = conteneurs.begin();
        Position2D* posCont = ((*posCont2D)->getPosition());
        px = (*posCont2D)->getCoteX() / 2 + posCont->getX();
        py = (*posCont2D)->getCoteY() / 2 + posCont->getY();
        pz = 30;
        ox = px;
        oy = py;
        oz = 0;
    } else {
        posCont3D = conteneurs3D.begin();
        courantConteneur();
    }
}

/* Scene dessinee                               */

static void scene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //move camera a distance r away from the center
    glTranslatef(ox, oy, -oz - r);
    //rotate
    glRotatef(angley, 0, 1, 0);
    glRotatef(anglex, 1, 0, 0);
    //move to center of circle
    glTranslatef(-px, -py, abs(oz - pz));

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
    } else {
        std::list<Conteneur3D*>::iterator it;
        for (it = conteneurs3D.begin(); it != conteneurs3D.end(); it++) {
            (*it)->model(vert, opaque);
        }
    }
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */

/* de la fenetre de dessin                      */

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    gluLookAt(px, py, pz, ox, oy, oz, 0.0, 1.0, 0.0);

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
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = (double) wTx / wTy;
    if (ratio >= 1.0) {
        gluPerspective(80.0, ratio, 1.0, 1000.0);
    } else {
        gluPerspective(80.0 / ratio, ratio, 1.0, 1000.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */

/* n'est en file d'attente                      */

static void idle(void) {
    if (keys[KEY_UP]) {
        if (anglex < 90) {
            anglex++;
        }
    }
    if (keys[KEY_DOWN]) {
        if (anglex > -90) {
            anglex--;
        }
    }
    if (keys[KEY_LEFT]) {
        angley++;
    }
    if (keys[KEY_RIGHT]) {
        angley--;
    }
    if (keys[KEY_PAGE_UP]) {
        r--;
    }
    if (keys[KEY_PAGE_DOWN]) {
        r++;
    }
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */

/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    //printf("S  %4d %4d %4d\n", key, x, y);
    if (key == 0x1B) {
        exit(0);
    }
    if (key == 13) {
        reset();
    }

    if (key == 39 || key == 52) {
        if (affichage3Dou2D == 0) {
            if (posCont2D == conteneurs.begin()) {
                posCont2D = conteneurs.end();
            }
            posCont2D--;

        } else {
            if (posCont3D == conteneurs3D.begin()) {
                posCont3D = conteneurs3D.end();
            }
            posCont3D--;
        }
        courantConteneur();
    }

    if (key == 40 || key == 53) {
        courantConteneur();
    }

    if (key == 45 || key == 54) {
        if (affichage3Dou2D == 0) {
            posCont2D++;
            if (++posCont2D == conteneurs.end()) {
                posCont2D = conteneurs.begin();
            }
        } else {
            posCont3D++;
            if (posCont3D == conteneurs3D.end()) {
                posCont3D = conteneurs3D.begin();
            }
        }
        courantConteneur();
    }
    if (key == 32) {
        opaque = !opaque;
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
    // printf("S  %4d %4d %4d\n", specialKey, x, y);
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
    // printf("M  %4d %4d %4d %4d\n", button, state, x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* avec un boutton presse                       */

static void mouseMotion(int x, int y) {
    //printf("MM %4d %4d\n", x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */

/* sans boutton presse                          */

static void passiveMouseMotion(int x, int y) {
    // printf("PM %4d %4d\n", x, y);
}

/* Fonction executee automatiquement            */

/* lors de l'execution de la fonction exit()    */

static void clean(void) {
    // printf("Clean\n");
    if (affichage3Dou2D == 0) {
        delete algo;
        std::list<Conteneur*>::iterator it;
        for (it = conteneursDispo.begin(); it != conteneursDispo.end(); it++) {
            delete* it;
        }

    } else {
        delete algo3D;
    }
    if (algo != NULL) {
    }
    if (algo3D != NULL) {
    }
#ifdef _WIN32
    int test = _CrtDumpMemoryLeaks();
    // printf("Bye %i\n", test);
#endif
}

/* Fonction principale                          */

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

static void verifCompoList3D(std::list <Composant3D*> liste, int type) {
    if (type == -1) {
        printf("LISTE DES COMPOSANTS 3D DE LA LISTE RESTE: \n");
    } else {
        printf("LISTE DES COMPOSANTS 3D DE LA LISTE CONTENEUR %d: \n", type);
    }
    std::list<Composant3D*>::iterator comp = liste.begin();
    while (comp != liste.end()) {
        (*comp)->affichageComposant();
        comp++;
    }
}

static bool addCont3D(int idCont) {
    bool newCont = false;
    bool breakage = false;

    std::list<Conteneur3D*>::iterator contDisp = conteneurs3DDispo.begin();

    for (contDisp; contDisp != conteneurs3DDispo.end(); contDisp++) {
        if ((*contDisp)->getNb() != 0) {
            std::list < Composant3D*>::iterator comp = composants3D.begin();
            for (comp; comp != composants3D.end(); comp++) {
                if (((*comp)->getCoteX() <= (*contDisp)->getCoteX() && (*comp)->getCoteY() <= (*contDisp)->getCoteY() && (*comp)->getCoteZ() <= (*contDisp)->getCoteZ())
                    || ((*comp)->getCoteX() <= (*contDisp)->getCoteY() && (*comp)->getCoteY() <= (*contDisp)->getCoteX() && (*comp)->getCoteZ() <= (*contDisp)->getCoteZ())) {
                    newCont = true;
                    (*contDisp)->takeCont();
                    conteneurs3D.push_back(new Conteneur3D(idCont, (*contDisp)->getCoteX(), (*contDisp)->getCoteY(), (*contDisp)->getCoteZ(), 0));
                    breakage = true;
                    break;
                }
            }
            if (breakage) {
                break;
            }
        }
    }
    if (!newCont) {
        return false;
    }
    return true;
}

static bool addCont(int idCont) {
    bool newCont = false;
    bool breakage = false;

    std::list<Conteneur*>::iterator contDisp = conteneursDispo.begin();

    for (contDisp; contDisp != conteneursDispo.end(); contDisp++) {

        if ((*contDisp)->getNb() != 0) {
            std::list < Composant*>::iterator comp = composants.begin();
            for (comp; comp != composants.end(); comp++) {
                if (((*comp)->getCoteX() * (*comp)->getCoteY()) < ((*contDisp)->getCoteX() * (*contDisp)->getCoteY())) {
                    newCont = true;
                    (*contDisp)->takeCont();
                    conteneurs.push_back(new Conteneur(idCont, (*contDisp)->getCoteX(), (*contDisp)->getCoteY(), 0));
                    breakage = true;
                    break;
                }
            }
            if (breakage) {
                break;
            }
        }
    }
    if (!newCont) {
        return false;
    }
    return true;
}

static void lectureCSVConteneur(std::string filename) {
    if (affichage3Dou2D == 0) {
        CSVReader *fichierCSV = DBG_NEW CSVReader(filename);
        fichierCSV->lireCSV(0);
        fichierCSV->verifCompoVectorConteneur(fichierCSV->getListConteneur());
        std::vector<Conteneur *> listeDesConteneurs = fichierCSV->getListConteneur();
        std::vector<Conteneur*>::iterator it;
        for (it = listeDesConteneurs.begin(); it != listeDesConteneurs.end(); it++) {
            conteneursDispo.push_back(*it);
        }
        if (fichierCSV != NULL) {
            delete fichierCSV;
        }
        posCont2DDispo = conteneursDispo.begin();

    } else {
        CSVReader3D *fichierCSV = DBG_NEW CSVReader3D(filename);
        fichierCSV->lireCSV(0);
        fichierCSV->verifCompoVectorConteneur(fichierCSV->getListConteneur());
        std::vector<Conteneur3D *> listeDesConteneurs = fichierCSV->getListConteneur();
        std::vector<Conteneur3D*>::iterator it;
        for (it = listeDesConteneurs.begin(); it != listeDesConteneurs.end(); it++) {
            conteneurs3DDispo.push_back(*it);
        }
        if (fichierCSV != NULL) {
            delete fichierCSV;
        }
        posCont3DDispo = conteneurs3DDispo.begin();
    }
}

static void lectureCSVComposant(std::string filename) {
    if (affichage3Dou2D == 0) {
        CSVReader *fichierCSV = DBG_NEW CSVReader(filename);
        fichierCSV->lireCSV(1);
        std::vector<Composant *> listeDesComposant = fichierCSV->getListComposant();
        std::vector<Composant*>::iterator it;
        for (it = listeDesComposant.begin(); it != listeDesComposant.end(); it++) {
            composants.push_back(*it);
        }
        if (fichierCSV != NULL) {
            delete fichierCSV;
        }
        algo = DBG_NEW Algorithm(composants, conteneurs, conteneursDispo);
        int idCont = 0;
        bool nofin = true;
        nofin = addCont(idCont);
        idCont++;
        algo->setListeConteneur(conteneurs);
        std::list<Composant*> composants = algo->calculRangement();
        algo->setListeComposant(composants);

        while (!(composants.empty()) && nofin) {

            nofin = addCont(idCont);
            idCont++;
            algo->setListeConteneur(conteneurs);
            composants = algo->calculRangement();
            algo->setListeComposant(composants);
        }
        posCont2D = conteneurs.begin();

        verifCompoVector(listeDesComposant);
        verifCompoList(composants, -1);
        verifCompoList((*posCont2D)->getListComposant(), 1);
        posCont2D = conteneurs.begin();


    } else {
        CSVReader3D *fichierCSV = DBG_NEW CSVReader3D(filename);
        fichierCSV->lireCSV(1);
        fichierCSV->verifCompoVectorComposant(fichierCSV->getListComposant());
        std::vector<Composant3D *> listeDesComposant = fichierCSV->getListComposant();
        std::vector<Composant3D*>::iterator it;
        for (it = listeDesComposant.begin(); it != listeDesComposant.end(); it++) {
            composants3D.push_back(*it);
        }
        if (fichierCSV != NULL) {
            delete fichierCSV;
        }
        algo3D = DBG_NEW Algorithm3D(composants3D, conteneurs3D, conteneurs3DDispo);
        int idCont = 0;
        bool nofin = true;
        nofin = addCont3D(idCont);
        idCont++;
        algo3D->setListeConteneur(conteneurs3D);
        composants3D = algo3D->calculRangement();
        algo3D->setListeComposant(composants3D);

        while (!(composants3D.empty()) && nofin) {

            nofin = addCont3D(idCont);
            idCont++;
            if (nofin) {
                algo3D->setListeConteneur(conteneurs3D);
                composants3D = algo3D->calculRangement();
                algo3D->setListeComposant(composants3D);
            }
        }
        posCont3D = conteneurs3D.begin();
        //verifCompoVector(composants3D);
        verifCompoList3D(composants3D, -1);
        while (posCont3D != conteneurs3D.end()) {
            verifCompoList3D((*posCont3D)->getListComposant(), 1);
            posCont3D++;
        }
        posCont3D = conteneurs3D.begin();
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
        lectureCSVConteneur("test2DBinPackingConteneur.csv");
        lectureCSVComposant("test2DBinPackingComposant.csv");
    } else {
        lectureCSVConteneur("test3DBinPackingConteneur.csv");
        lectureCSVComposant("test3DBinPackingComposant.csv");
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
