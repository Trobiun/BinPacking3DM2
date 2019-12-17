#include "2D/Debug.h"

#include "2D/CSVReader.h"


CSVReader::CSVReader(std::string name) {
	filename = name;
}
CSVReader::~CSVReader() {
}

bool CSVReader::setFilename(std::string name) {
	filename = name;
	return true;
}
bool CSVReader::setListComposant(std::vector <Composant *> list) {
	listComposant = list;
	return true;
}
bool CSVReader::setListConteneur(std::vector <Conteneur *> list) {
	listConteneur = list;
	return true;
}

string CSVReader::getFilename() {
	return filename;
}
std::vector <Composant *> CSVReader::getListComposant() {
	return listComposant;
}
std::vector <Conteneur *> CSVReader::getListConteneur() {
	return listConteneur;
}

void CSVReader::lireCSV(int type) {
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
void CSVReader::ajoutComposant(std::vector <string> row) {
	char * verifErreur;
	size_t indiceCourant = 0;
	bool erreur = false;
	int id = 0;
	float coteX = 0.0, coteY = 0.0;
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
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : coteX non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 2) {
			coteY = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : coteY non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		
		indiceCourant++;
	}
	if (erreur == false) {
		printf("AJOUT D'UN COMPOSANT : id = %d, coteX %.2f, coteY %.2f \n", id, coteX, coteY);
		listComposant.push_back(DBG_NEW Composant(id, coteX, coteY));
	}
}

void CSVReader::ajoutConteneur(std::vector <string> row) {
	char * verifErreur;
	size_t indiceCourant = 0;
	bool erreur = false;
	int id = 0;
	float coteX = 0.0, coteY = 0.0;
	while (erreur == false && indiceCourant < row.size()) {
		if (indiceCourant == 0) {
			id = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : ID non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 1) {
			coteX = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : coteX non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 2) {
			coteY = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN CONTENEUR : coteY non valide, le conteneur %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}

		indiceCourant++;
	}
	if (erreur == false) {
		printf("AJOUT D'UN CONTENEUR : id = %d, coteX %.2f, coteY %.2f \n", id, coteX, coteY);
		listConteneur.push_back(DBG_NEW Conteneur(id, coteX, coteY));
	}
}

void CSVReader::verifCompoVectorComposant(std::vector <Composant *> liste) {
	printf("LISTE DES COMPOSANTS DU FICHIER CSV : \n");
	for (size_t i = 0; i < liste.size(); i++) {
		liste[i]->affichageComposant();
	}
}
void CSVReader::verifCompoVectorConteneur(std::vector <Conteneur *> liste) {
	printf("LISTE DES CONTENEURS DU FICHIER CSV : \n");
	for (size_t i = 0; i < liste.size(); i++) {
		liste[i]->affichageConteneur();
	}
}