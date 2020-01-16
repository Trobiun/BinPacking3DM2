#include "3D/Debug.h"

#include <stdio.h>
#include <GL/glut.h>

#include "3D/Conteneur3D.h"

Conteneur3D::Conteneur3D(void) : Conteneur3D(0, 0.0, 0.0, 0.0, 0) {

}

Conteneur3D::Conteneur3D(int nid, float nCoteX, float nCoteY, float nCoteZ, int nnb) : id(nid), coteX(nCoteX), coteY(nCoteY), coteZ(nCoteZ), nb(nnb) {
    pos = DBG_NEW Position3D();
    arbre = DBG_NEW ArbreBinaire3D(coteX, coteY, coteZ);
}

Conteneur3D::~Conteneur3D(void) {
    if (pos != nullptr) {
        delete pos;
        pos = nullptr;
    }
    /*if (arbre != nullptr) {
        delete arbre;
        arbre = nullptr;
    }*/
}

/* Getters                                  */

int Conteneur3D::getId(void) {
    return id;
}

float Conteneur3D::getCoteX(void) {
    return coteX;
}

float Conteneur3D::getCoteY(void) {
    return coteY;
}

float Conteneur3D::getCoteZ(void) {
    return coteZ;
}

int Conteneur3D::getNb(void) {
    return nb;
}

bool Conteneur3D::takeCont() {
    if (nb != 0) {
        if (nb != -1) {
            nb = nb - 1;
        }
        return true;
    }
    return false;
}

/*ArbreBinaire* Conteneur3D::getArbre(void) {
    return arbre;
}*/

std::list<Composant3D*> Conteneur3D::getListComposant(void) {
    return composants;
}

void Conteneur3D::model() {
    glPushMatrix();
    glPushMatrix();
    GLfloat blanc[4] = {1.0F, 1.0F, 1.0F, 1.0F};
    glColor4fv(blanc);
    glTranslatef(pos->getX(), pos->getY(), pos->getZ());
    glutSolidSphere(1.0, 8, 8);
    glPopMatrix();
    glTranslatef(pos->getX() + coteX / 2, pos->getY() + coteY / 2, pos->getZ() - coteZ / 2);
    glScalef(coteX, coteY, coteZ);
    GLfloat couleur[4] = {1.0F, 0.0F, 0.0F, 1.0F};
    glColor4fv(couleur);
    glutWireCube(1.0);
    /*if (arbre != NULL) {
        arbre->model();
    }*/
    glPopMatrix();
}

/* Setters                                  */

bool Conteneur3D::setCoteX(float nCoteX) {
    coteX = nCoteX;
    return true;
}

bool Conteneur3D::setCoteY(float nCoteY) {
    coteY = nCoteY;
    return true;
}

bool Conteneur3D::setCoteZ(float nCoteZ) {
    coteZ = nCoteZ;
    return true;
}

bool Conteneur3D::setNb(int nnb) {
    nb = nnb;
    return true;
}

bool Conteneur3D::setPosition(Position3D *position) {
    pos = position;
    return true;
}

Position3D* Conteneur3D::getPosition() {
    return pos;
}

bool Conteneur3D::setPosition(float posX, float posY, float posZ) {
    pos->setX(posX);
    pos->setY(posY);
    pos->setY(posZ);
    return true;
}

bool Conteneur3D::addComposant(Composant3D * comp) {
    comp->setConteneur(id);
    composants.push_back(comp);
    return true;
}

ArbreBinaire3D* Conteneur3D::rechercheLibre(float coteX, float coteY, float coteZ) {
    return arbre->recherchePremierEspaceLibreValide(coteX, coteY, coteZ);
}

void Conteneur3D::affichageConteneur() {
    printf("CONTENEUR : Id = %d, CoteX = %.2f, CoteY = %.2f, CoteZ = %.2f, Position = (%.2f,%.2f, %.2f), Liste des composants = \n"
        , id, coteX, coteY, coteZ, pos->getX(), pos->getY(), pos->getZ());
    if (composants.empty()) {
        printf("Aucun.  \n");
    } else {
        std::list<Composant3D*>::iterator it;
        for (it = composants.begin(); it != composants.end(); it++) {
            (*it)->affichageComposant();
        }
    }
}