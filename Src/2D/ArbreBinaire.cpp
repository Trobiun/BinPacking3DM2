#include "2D/Debug.h"
#include "2D/ArbreBinaire.h"

ArbreBinaire::ArbreBinaire(float coteX, float coteY) {
    espace_libre = DBG_NEW Composant(0, coteX, coteY);
    sous_arbre_gauche = nullptr;
    sous_arbre_droite = nullptr;
    parent = nullptr;
}

ArbreBinaire::ArbreBinaire(Composant* composant, ArbreBinaire* p) {
    espace_libre = DBG_NEW Composant(0, composant->getCoteX(), composant->getCoteY(), composant->getPosition());
    sous_arbre_gauche = nullptr;
    sous_arbre_droite = nullptr;
    parent = p;
}

ArbreBinaire::~ArbreBinaire() {
    if (espace_libre != nullptr) {
        delete espace_libre;
        espace_libre = nullptr;
    }
    if (sous_arbre_gauche != nullptr) {
        delete sous_arbre_gauche;
        sous_arbre_gauche = nullptr;
    }
    if (sous_arbre_droite != nullptr) {
        delete sous_arbre_droite;
        sous_arbre_droite = nullptr;
    }
}

/* Setters                                  */

bool ArbreBinaire::setEspaceLibre(Composant * el) {
    espace_libre = el;
    return true;
}

bool ArbreBinaire::setSousArbreGauche(ArbreBinaire * ag) {
    sous_arbre_gauche = ag;
    return true;
}

bool ArbreBinaire::setSousArbreDroite(ArbreBinaire * ad) {
    sous_arbre_droite = ad;
    return true;
}

bool ArbreBinaire::setParent(ArbreBinaire * p) {
    parent = p;
    return true;
}

/* Getters                                  */

Composant * ArbreBinaire::getEspaceLibre() {
    return espace_libre;
}

ArbreBinaire * ArbreBinaire::getSousArbreGauche() {
    return sous_arbre_gauche;
}

ArbreBinaire * ArbreBinaire::getSousArbreDroite() {
    return sous_arbre_droite;
}

ArbreBinaire * ArbreBinaire::getParent() {
    return parent;
}

ArbreBinaire* ArbreBinaire::recherchePremierEspaceLibreValide(float coteX, float coteY) {
    Composant* racine = espace_libre;
    ArbreBinaire* res = nullptr;
    if (racine->getCoteX() >= coteX && racine->getCoteY() >= coteY) {
        return this;
    } else {
        if (this->getSousArbreGauche() != nullptr) {
            res = this->getSousArbreGauche()->recherchePremierEspaceLibreValide(coteX, coteY);
            if (res != nullptr) {
                return res;
            }
        }
        if (this->getSousArbreDroite() != nullptr) {
            res = this->getSousArbreDroite()->recherchePremierEspaceLibreValide(coteX, coteY);
            if (res != nullptr) {
                return res;
            }
        }
    }
    return nullptr;
}

bool ArbreBinaire::creationFils(float coteX, float coteY, int choix) {
    Composant* libre = espace_libre;
    Position2D* pos = libre->getPosition();
    Composant* gauche = DBG_NEW Composant();
    Composant* droite = DBG_NEW Composant();

    switch (choix) {
        case 0:
            decoupeHorizontale(coteX, coteY, libre, pos, gauche, droite);
            break;
        case 1:
            decoupeVerticale(coteX, coteY, libre, pos, gauche, droite);
            break;
        case 2:
            decoupeSelonAire(coteX, coteY, libre, pos, gauche, droite);
            break;
        default:
            return false;
    }
    libre->setCoteX(0);
    libre->setCoteY(0);
    ArbreBinaire* arbreGauche = DBG_NEW ArbreBinaire(gauche, this);
    ArbreBinaire* arbreDroite = DBG_NEW ArbreBinaire(droite, this);
    if (sous_arbre_gauche != nullptr) {
        delete sous_arbre_gauche;
        sous_arbre_gauche = nullptr;
    }
    if (sous_arbre_droite != nullptr) {
        delete sous_arbre_droite;
        sous_arbre_droite = nullptr;
    }
    sous_arbre_droite = arbreDroite;
    sous_arbre_gauche = arbreGauche;
    delete gauche;
    delete droite;
    return true;

}

bool ArbreBinaire::decoupeHorizontale(float coteX, float coteY, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite) {
    float posX = pos->getX();
    float posY = pos->getY();
    float posXnew = posX + coteX;
    float posYnew = posY + coteY;
    gauche->setCoteX(libre->getCoteX());
    gauche->setCoteY(libre->getCoteY() - coteY);
    droite->setCoteX(libre->getCoteX() - coteX);
    droite->setCoteY(coteY);

    gauche->setPosition(posX, posYnew);
    droite->setPosition(posXnew, posY);
    return true;
}

bool ArbreBinaire::decoupeVerticale(float coteX, float coteY, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite) {
    float posX = pos->getX();
    float posY = pos->getY();
	float posXnew = posX + coteX;
	float posYnew = posY + coteY;

    droite->setCoteX(libre->getCoteX() - coteX);
    droite->setCoteY(libre->getCoteY());
    gauche->setCoteX(coteX);
    gauche->setCoteY(libre->getCoteY() - coteY);
    gauche->setPosition(posX, posYnew);
    droite->setPosition(posXnew, posY);
    return true;
}

bool ArbreBinaire::decoupeSelonAire(float coteX, float coteY, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite) {
    float posX = pos->getX();
    float posY = pos->getY();
	float posXnew = posX + coteX;
	float posYnew = posY + coteY;
    float aireGauche = (libre->getCoteX() - coteX) * libre->getCoteY();
    float aireDroite = libre->getCoteX() * (libre->getCoteY() - coteY);

    if (aireGauche > aireDroite) {
		gauche->setCoteX(libre->getCoteX());
		gauche->setCoteY(libre->getCoteY() - coteY);
		droite->setCoteX(libre->getCoteX() - coteX);
		droite->setCoteY(coteY);
    } else {
		droite->setCoteX(libre->getCoteX() - coteX);
		droite->setCoteY(libre->getCoteY());
		gauche->setCoteX(coteX);
		gauche->setCoteY(libre->getCoteY() - coteY);
    }
    gauche->setPosition(posX, posYnew);
    droite->setPosition(posXnew, posY);
    return true;
}

void ArbreBinaire::affichageArbre() {
    printf("ARBRE : Espace Libre = {CoteX = %.2f, CoteY = %.2f, Position = (%.2f,%.2f)}\n"
        , espace_libre->getCoteX(), espace_libre->getCoteY(), espace_libre->getPosition()->getX(), espace_libre->getPosition()->getY());
    if (sous_arbre_gauche != nullptr) {
        printf("SOUS-ARBRE GAUCHE \n");
        sous_arbre_gauche->affichageArbre();
    }
    if (sous_arbre_droite != nullptr) {
        printf("SOUS-ARBRE DROITE \n");
        sous_arbre_droite->affichageArbre();
    }
}

void ArbreBinaire::model() {
    //glPushMatrix();
    espace_libre->model(bleu);
    if (sous_arbre_gauche != nullptr) {
        sous_arbre_gauche->model();
    }
    if (sous_arbre_droite != nullptr) {
        sous_arbre_droite->model();
    }
    //glPopMatrix();
}
