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

string CSVReader::getFilename() {
	return filename;
}
std::vector <Composant *> CSVReader::getListComposant() {
	return listComposant;
}

void CSVReader::lireCSV() {
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
				ajoutComposant(row);
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
	float largeur = 0.0, longueur = 0.0;
	while (erreur == false && indiceCourant < row.size()) {
		if (indiceCourant == 0) {
			id = strtol(row[indiceCourant].c_str(), &verifErreur, 10);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : ID non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 1) {
			largeur = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : largeur non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		if (indiceCourant == 2) {
			longueur = strtod(row[indiceCourant].c_str(), &verifErreur);
			if (*verifErreur != '\0') {
				printf("ERREUR LORS DE L'AJOUT D'UN COMPOSANT : longueur non valide, le composant %s n'est pas ajout�. \n", row[0].c_str());
				erreur = true;
			}
		}
		
		indiceCourant++;
	}
	if (erreur == false) {
		printf("AJOUT D'UN COMPOSANT : id = %d, largeur %.2f, longueur %.2f \n", id, largeur, longueur);
		listComposant.push_back(DBG_NEW Composant(id, largeur, longueur));
	}
}