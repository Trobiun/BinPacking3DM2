#include "2D/ArbreBinaire.h"

ArbreBinaire::ArbreBinaire(float cLargeur, float cLongueur) {
	espace_libre = new Composant(0, cLargeur, cLongueur);
	sous_arbre_gauche = nullptr;
	sous_arbre_droite = nullptr;
	parent = nullptr;
}

ArbreBinaire::ArbreBinaire(Composant* composant, ArbreBinaire* p) {
	espace_libre = new Composant(0, composant->getLargeur(), composant->getLongueur(),composant->getPosition());
	sous_arbre_gauche = nullptr;
	sous_arbre_droite = nullptr;
	parent = p;
}

ArbreBinaire::~ArbreBinaire() {
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

ArbreBinaire* ArbreBinaire::recherchePremierEspaceLibreValide(float largeur, float longueur) {
	Composant* racine = espace_libre;
	ArbreBinaire* res = nullptr;
	if (racine->getLargeur() >= largeur && racine->getLongueur() >= longueur) {
		return this;
	}
	else {
		if (this->getSousArbreGauche() != nullptr) {
			 res = this->getSousArbreGauche()->recherchePremierEspaceLibreValide(largeur, longueur);
			if (res != nullptr) {
				return res;
			}
		}
		if (this->getSousArbreDroite() != nullptr) {
			res = this->getSousArbreDroite()->recherchePremierEspaceLibreValide( largeur, longueur);
			if (res != nullptr) {
				return res;
			}
		}
	}
	return nullptr;
}

bool ArbreBinaire::creationFils(float largeur, float longueur, int choix) {
	Composant* libre = espace_libre;
	Position2D* pos = libre->getPosition();
	Composant* gauche = new Composant();
	Composant* droite = new Composant();

	switch (choix)
	{
	case 0:
		decoupeHorizontale(largeur, longueur, libre, pos, gauche, droite);
		break;
	case 1:
		decoupeVerticale(largeur, longueur, libre, pos, gauche, droite);
		break;
	case 2:
		decoupeSelonAire(largeur, longueur, libre, pos, gauche, droite);
		break;
	default:
		return false;
	}
	libre->setLargeur(0);
	libre->setLongueur(0);
	ArbreBinaire* arbreGauche = new ArbreBinaire(gauche, this);
	ArbreBinaire* arbreDroite = new ArbreBinaire(droite, this);
	sous_arbre_droite = arbreDroite;
	sous_arbre_gauche = arbreGauche;
	return true;

}

bool ArbreBinaire::decoupeHorizontale(float largeur, float longueur, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite) {
	float posX = pos->getX();
	float posY = pos->getY();
	float posXnew = posY + longueur;
	float posYnew = posX + largeur;
	gauche->setLargeur(libre->getLargeur() - largeur);
	gauche->setLongueur(libre->getLongueur());	
	gauche->setLargeur(libre->getLargeur());
	gauche->setLongueur(libre->getLongueur() - longueur);
	gauche->setPosition(new Position2D(posX, posYnew));
	droite->setPosition(new Position2D(posXnew, posY));
	return true;
}

bool ArbreBinaire::decoupeVerticale(float largeur, float longueur, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite) {
	float posX = pos->getX();
	float posY = pos->getY();
	float posXnew = posY + longueur;
	float posYnew = posX + largeur;
	gauche->setLargeur (libre->getLargeur() - largeur);
	gauche->setLongueur(libre->getLongueur() - longueur);
	gauche->setLargeur(libre->getLargeur());
	gauche->setLongueur(libre->getLongueur() - longueur);
	gauche->setPosition(new Position2D(posX, posYnew));
	droite->setPosition(new Position2D(posXnew, posY));
	return true;
}

bool ArbreBinaire::decoupeSelonAire(float largeur, float longueur, Composant* libre, Position2D* pos, Composant* gauche, Composant* droite) {
	float posX = pos->getX();
	float posY = pos->getY();
	float posXnew = posY + longueur;
	float posYnew = posX + largeur;
	float gaucheLargeur = (libre->getLongueur() - longueur) * (libre->getLargeur() - largeur);
	float droiteLargeur = (libre->getLongueur() - longueur) * libre->getLargeur();
	float gaucheLongueur = (libre->getLongueur() - longueur) * (libre->getLargeur() - largeur);
	float droiteLongueur = (libre->getLongueur() - longueur) * libre->getLargeur();
	if (((gaucheLargeur > gaucheLongueur) && (gaucheLargeur> droiteLongueur)) || ((droiteLargeur > gaucheLongueur) && (droiteLargeur > droiteLongueur))) {
		gauche->setLargeur(libre->getLargeur() - largeur);
		gauche->setLongueur(libre->getLongueur());
		gauche->setLargeur(libre->getLargeur());
		gauche->setLongueur(libre->getLongueur() - longueur);
		gauche->setPosition(new Position2D(posX, posYnew));
		droite->setPosition(new Position2D(posXnew, posY));
	}
	else {
		gauche->setLargeur(libre->getLargeur() - largeur);
		gauche->setLongueur(libre->getLongueur() - longueur);
		gauche->setLargeur(libre->getLargeur());
		gauche->setLongueur(libre->getLongueur() - longueur);
		gauche->setPosition(new Position2D(posX, posYnew));
		droite->setPosition(new Position2D(posXnew, posY));
	}
	return true;
}

void ArbreBinaire::affichageArbre() {
	printf("ARBRE : Espace Libre = {Largeur = %.2f, Longueur = %.2f, Position = (%.2f,%.2f)}\n"
		,espace_libre->getLargeur(), espace_libre->getLongueur(), espace_libre->getPosition()->getX(), espace_libre->getPosition()->getY());
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
    GLfloat bleu[] = {0.0F,0.0F,1.0F,1.0F};
    printf("");
    espace_libre->affichageComposant();
    espace_libre->model(bleu);
    if (sous_arbre_gauche != nullptr) {
		sous_arbre_gauche->model();
	}
	if (sous_arbre_droite != nullptr) {
		sous_arbre_droite->model();
	}
    //glPopMatrix();
}