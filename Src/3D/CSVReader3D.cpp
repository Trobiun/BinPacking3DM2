#include "2D/Debug.h"

#include "3D/CSVReader3D.h"


CSVReader3D::CSVReader3D(std::string name) {
	filename = name;
}
CSVReader3D::~CSVReader3D() {
}

bool CSVReader3D::setFilename(std::string name) {
	filename = name;
	return true;
}
bool CSVReader3D::setListComposant(std::vector <Composant3D *> list) {
	listComposant = list;
	return true;
}
bool CSVReader3D::setListConteneur(std::vector <Conteneur3D *> list) {
	listConteneur = list;
	return true;
}

string CSVReader3D::getFilename() {
	return filename;
}
std::vector <Composant3D *> CSVReader3D::getListComposant() {
	return listComposant;
}
std::vector <Conteneur3D *> CSVReader3D::getListConteneur() {
	return listConteneur;
}

void CSVReader3D::lireCSV(int type) {
	std::vector<std::string> row;
	ifstream fichierCSV(filename.c_str() , ios_base::in);
	if (fichierCSV.good())
	{
		cout << "SUCCESS : Le fichier a pu �tre ouvert." << endl;
		string ligne, word;
		int compteurLigne = 0;
		while (getline(fichierCSV, ligne)) {
			if (compteurLigne != 0) {
				row.clear();
				stringstream s(ligne);

				while (getline(s, word, ';')) {
					row.push_back(word);
				}
				if (type == 0) {
					ajoutConteneur(row);
				}
				else {
					ajoutComposant(row);
				}
			}
			compteurLigne++;
		}
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
		
	}
	fichierCSV.close();
}

void CSVReader3D::ajoutComposant(std::vector <string> row) {
	char * verifErreur;
	size_t indiceCourant = 0;
	bool erreur = false;
	int id = 0, face1 = 0, face2 = 0, face3 = 0, face4 = 0, face5 = 0, face6 = 0;
	float coteX = 0.0, coteY = 0.0, coteZ = 0.0;
	while (erreur == false && indiceCourant < row.size()) {
		if (indiceCourant == 0) {
			id = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : ID non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 1) {
			coteX = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : CoteX non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 2) {
			coteY = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : CoteY non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 3) {
			coteZ = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : CoteZ non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
/*		if (indiceCourant == 4) {
			face1 = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : Face1 non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 5) {
			face2 = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : Face2 non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 6) {
			face3 = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : Face3 non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 7) {
			face4 = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : Face4 non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 8) {
			face5 = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : Face5 non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 9) {
			face6 = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : Face6 non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}*/
		indiceCourant++;
	}
	if (erreur == false) {
		printf("AJOUT D'UN COMPOSANT : id = %d, coteX %.2f, coteY %.2f, coteZ %.2f\n", 
			id, coteX, coteY, coteZ);
		listComposant.push_back(DBG_NEW Composant3D(id, coteX, coteY, coteZ));
		//listComposant.back()->setTabOrientation(face1, face2, face3, face4, face5, face6);
	}
}

void CSVReader3D::ajoutConteneur(std::vector <string> row) {
	char * verifErreur;
	size_t indiceCourant = 0;
	bool erreur = false;
	int id = -1, nb = 0;
	float coteX = 0.0, coteY = 0.0, coteZ = 0.0;
	while (erreur == false && indiceCourant < row.size()) {
		/*if (indiceCourant == 0) {
			id = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : ID non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}*/
		if (indiceCourant == 0) {
			coteX = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : CoteX non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 1) {
			coteY = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : CoteY non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 2) {
			coteZ = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : CoteZ non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 3) {
			nb = strtol(row[indiceCourant].c_str(), &verifErreur,10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : Nombre de conteneur non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		
		indiceCourant++;
	}
	if (erreur == false) {
		printf("AJOUT D'UN CONTENEUR : id = %d, coteX %.2f, coteY %.2f, coteZ %.2f, nb = %d \n",
			id, coteX, coteY, coteZ, nb);
		listConteneur.push_back(DBG_NEW Conteneur3D(id, coteX, coteY, coteZ, nb));
	}
}

void CSVReader3D::verifCompoVectorComposant(std::vector <Composant3D *> liste) {
	printf("LISTE DES COMPOSANTS DU FICHIER CSV : \n");
	for (size_t i = 0; i < liste.size(); i++) {
		liste[i]->affichageComposant();
	}
}
void CSVReader3D::verifCompoVectorConteneur(std::vector <Conteneur3D *> liste) {
	printf("LISTE DES CONTENEURS DU FICHIER CSV : \n");
	for (size_t i = 0; i < liste.size(); i++) {
		liste[i]->affichageConteneur();
	}
}