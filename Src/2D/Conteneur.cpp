#include "2D/Debug.h"

#include <stdio.h>
#include <GL/glut.h>

#include "2D/Conteneur.h"
#include "2D/ArbreBinaire.h"

Conteneur::Conteneur(void) : Conteneur(0, 0.0, 0.0, 0) {

}

Conteneur::Conteneur(int nid, float nCoteX, float nCoteY, int nnb) : id(nid), coteX(nCoteX), coteY(nCoteY), nb(nnb) {
    pos = DBG_NEW Position2D();
    arbre = DBG_NEW ArbreBinaire(coteX, coteY);
}

Conteneur::~Conteneur(void) {
    if (pos != nullptr) {
        delete pos;
        pos = nullptr;
    }
    if (arbre != nullptr) {
        delete arbre;
        arbre = nullptr;
    }
}

/* Getters                                  */

int Conteneur::getId(void) {
    return id;
}

float Conteneur::getCoteX(void) {
    return coteX;
}

float Conteneur::getCoteY(void) {
    return coteY;
}
float Conteneur::getNb(void) {
	return nb;
}

ArbreBinaire* Conteneur::getArbre(void) {
    return arbre;
}

std::list<Composant*> Conteneur::getListComposant(void) {
    return composants;
}

void Conteneur::model() {
    glPushMatrix();
    glTranslatef(pos->getX() + coteX / 2, pos->getY() + coteY / 2, 0.0);
    glScalef(coteX, coteY, 0.0);
    GLfloat couleur[4] = {1.0F, 0.0F, 0.0F, 1.0F};
    glColor4fv(couleur);
    glutWireCube(1.0);
    if (arbre != NULL) {
        arbre->model();
    }
    glPopMatrix();
}

/* Setters                                  */

bool Conteneur::setCoteX(float nCoteX) {
    coteX = nCoteX;
    return true;
}

bool Conteneur::setCoteY(float nCoteY) {
    coteY = nCoteY;
    return true;
}

bool Conteneur::setNb(int nnb) {
	nb = nnb;
	return true;
}

bool Conteneur::setPosition(Position2D *position) {
    pos = position;
    return true;
}

bool Conteneur::setPosition(float posX, float posY) {
    pos->setX(posX);
    pos->setY(posY);
    return true;
}

Position2D* Conteneur::getPosition() {
	return pos;
}

bool Conteneur::addComposant(Composant * comp) {
    comp->setConteneur(id);
    composants.push_back(comp);
    return true;
}

ArbreBinaire* Conteneur::rechercheLibre(float coteX, float coteY) {
    return arbre->recherchePremierEspaceLibreValide(coteX, coteY);
}

void Conteneur::affichageConteneur() {
    printf("CONTENEUR : Id = %d, CoteX = %.2f, CoteY = %.2f, Position = (%.2f,%.2f), Liste des composants = \n"
        , id, coteX, coteY, pos->getX(), pos->getY());
    if (composants.empty()) {
        printf("Aucun.  \n");
    } else {
        std::list<Composant*>::iterator it;
        for (it = composants.begin(); it != composants.end(); it++) {
            (*it)->affichageComposant();
        }
    }
}