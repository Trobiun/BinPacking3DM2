#include "3D/Debug.h"
#include "3D/ArbreBinaire3D.h"

ArbreBinaire3D::ArbreBinaire3D(float coteX, float coteY, float coteZ) {
	espace_libre = DBG_NEW Composant3D(0, coteX, coteY, coteZ);
	sous_arbre_gauche = nullptr;
	sous_arbre_haut = nullptr;
	sous_arbre_droite = nullptr;
	parent = nullptr;
}

ArbreBinaire3D::ArbreBinaire3D(Composant3D* composant, ArbreBinaire3D* p) {
	espace_libre = DBG_NEW Composant3D(0, composant->getCoteX(), composant->getCoteY(), composant->getCoteZ(), composant->getPosition());
	sous_arbre_gauche = nullptr;
	sous_arbre_haut = nullptr;
	sous_arbre_droite = nullptr;
	parent = p;
}

ArbreBinaire3D::~ArbreBinaire3D() {
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
	if (sous_arbre_haut != nullptr) {
		delete sous_arbre_haut;
		sous_arbre_haut = nullptr;
	}
}

/* Setters                                  */

bool ArbreBinaire3D::setEspaceLibre(Composant3D* el) {
	espace_libre = el;
	return true;
}

bool ArbreBinaire3D::setSousArbreGauche(ArbreBinaire3D* ag) {
	sous_arbre_gauche = ag;
	return true;
}

bool ArbreBinaire3D::setSousArbreDroite(ArbreBinaire3D* ad) {
	sous_arbre_droite = ad;
	return true;
}

bool ArbreBinaire3D::setSousArbreHaut(ArbreBinaire3D* ad) {
	sous_arbre_haut = ad;
	return true;
}

bool ArbreBinaire3D::setParent(ArbreBinaire3D* p) {
	parent = p;
	return true;
}

/* Getters                                  */

Composant3D* ArbreBinaire3D::getEspaceLibre() {
	return espace_libre;
}

ArbreBinaire3D* ArbreBinaire3D::getSousArbreGauche() {
	return sous_arbre_gauche;
}

ArbreBinaire3D* ArbreBinaire3D::getSousArbreDroite() {
	return sous_arbre_droite;
}

ArbreBinaire3D* ArbreBinaire3D::getSousArbreHaut() {
	return sous_arbre_haut;
}
ArbreBinaire3D* ArbreBinaire3D::getParent() {
	return parent;
}

ArbreBinaire3D* ArbreBinaire3D::recherchePremierEspaceLibreValide(float coteX, float coteY, float coteZ) {
	Composant3D* racine = espace_libre;
	ArbreBinaire3D* res = nullptr;
	if ((racine->getCoteX() >= coteX && racine->getCoteY() >= coteY && racine->getCoteZ() >= coteZ) || racine->getCoteX() >= coteY && racine->getCoteY() >= coteX && racine->getCoteZ() >= coteZ) {
		return this;
	}
	else {
		if (this->getSousArbreGauche() != nullptr) {
			res = this->getSousArbreGauche()->recherchePremierEspaceLibreValide(coteX, coteY, coteZ);
			if (res != nullptr) {
				return res;
			}
		}
		if (this->getSousArbreDroite() != nullptr) {
			res = this->getSousArbreDroite()->recherchePremierEspaceLibreValide(coteX, coteY, coteZ);
			if (res != nullptr) {
				return res;
			}
		}
		if (this->getSousArbreHaut() != nullptr) {
			res = this->getSousArbreHaut()->recherchePremierEspaceLibreValide(coteX, coteY, coteZ);
			if (res != nullptr) {
				return res;
			}
		}
	}
	return nullptr;
}

bool ArbreBinaire3D::creationFils(float coteX, float coteY, float coteZ, int choix) {
	Composant3D* libre = espace_libre;
	Position3D* pos = libre->getPosition();
	Composant3D* gauche = DBG_NEW Composant3D();
	Composant3D* droite = DBG_NEW Composant3D();
	Composant3D* haut = DBG_NEW Composant3D();

	switch (choix) {
	case 0:
		decoupeHorizontale(coteX, coteY, coteZ, libre, pos, gauche, droite, haut);
		break;
	case 1:
		decoupeVerticale(coteX, coteY, coteZ, libre, pos, gauche, droite, haut);
		break;
	case 2:
		decoupeSelonAire(coteX, coteY, coteZ, libre, pos, gauche, droite, haut);
		break;
	default:
		return false;
	}
	libre->setCoteX(0);
	libre->setCoteY(0);
	libre->setCoteZ(0);
	ArbreBinaire3D* arbreGauche = DBG_NEW ArbreBinaire3D(gauche, this);
	ArbreBinaire3D* arbreDroite = DBG_NEW ArbreBinaire3D(droite, this);
	ArbreBinaire3D* arbreHaut = DBG_NEW ArbreBinaire3D(droite, this);

	if (sous_arbre_gauche != nullptr) {
		delete sous_arbre_gauche;
		sous_arbre_gauche = nullptr;
	}
	if (sous_arbre_haut != nullptr) {
		delete sous_arbre_haut;
		sous_arbre_haut = nullptr;
	}
	if (sous_arbre_droite != nullptr) {
		delete sous_arbre_droite;
		sous_arbre_droite = nullptr;
	}
	sous_arbre_droite = arbreDroite;
	sous_arbre_gauche = arbreGauche;
	sous_arbre_gauche = arbreHaut;

	delete gauche;
	delete droite;
	delete haut;
	return true;

}

bool ArbreBinaire3D::decoupeHorizontale(float coteX, float coteY, float coteZ, Composant3D* libre, Position3D* pos, Composant3D* gauche, Composant3D* droite, Composant3D* haut) {
	float posZ = pos->getZ();
	float posX = pos->getX();
	float posY = pos->getY();
	float posXnew = posX + coteX;
	float posYnew = posY + coteY;
	gauche->setCoteX(libre->getCoteX());
	gauche->setCoteY(libre->getCoteY() - coteY);
	droite->setCoteX(libre->getCoteX() - coteX);
	droite->setCoteY(coteY);
	haut->setPosition(posX, posY, posZ + coteZ);
	gauche->setPosition(posX, posYnew, posY);
	droite->setPosition(posXnew, posY, posY);
	return true;
}

bool ArbreBinaire3D::decoupeVerticale(float coteX, float coteY, float coteZ, Composant3D* libre, Position3D* pos, Composant3D* gauche, Composant3D* droite, Composant3D* haut) {
	float posX = pos->getX();
	float posY = pos->getY();
	float posXnew = posX + coteX;
	float posYnew = posY + coteY;

	droite->setCoteX(libre->getCoteX() - coteX);
	droite->setCoteY(libre->getCoteY());
	gauche->setCoteX(coteX);
	gauche->setCoteY(libre->getCoteY() - coteY);
	gauche->setPosition(posX, posYnew, 0);
	droite->setPosition(posXnew, posY, 0);
	return true;
}

bool ArbreBinaire3D::decoupeSelonAire(float coteX, float coteY, float coteZ, Composant3D* libre, Position3D* pos, Composant3D* gauche, Composant3D* droite, Composant3D* haut) {
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
	}
	else {
		droite->setCoteX(libre->getCoteX() - coteX);
		droite->setCoteY(libre->getCoteY());
		gauche->setCoteX(coteX);
		gauche->setCoteY(libre->getCoteY() - coteY);
	}
	gauche->setPosition(posX, posYnew, 0);
	droite->setPosition(posXnew, posY, 0);
	return true;
}

/*void ArbreBinaire3D::affichageArbre() {
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
}*/

void ArbreBinaire3D::model() {
	//glPushMatrix();
	espace_libre->model(bleu);
	if (sous_arbre_gauche != nullptr) {
		sous_arbre_gauche->model();
	}
	if (sous_arbre_droite != nullptr) {
		sous_arbre_droite->model();
	}
	if (sous_arbre_haut != nullptr) {
		sous_arbre_haut->model();
	}
	//glPopMatrix();
}
