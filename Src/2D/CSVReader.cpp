#include "../../Include/2D/CSVReader.h"


CSVReader::CSVReader(std::string name) {
	filename = name;
}
CSVReader::~CSVReader() {
}

bool CSVReader::setFilename(std::string name) {
	filename = name;
	return true;
}
bool CSVReader::setListComposant(std::list <Composant> list) {
	listComposant = list;
	return true;
}

string CSVReader::getFilename() {
	return filename;
}
std::list <Composant> CSVReader::getListComposant() {
	return listComposant;
}

void CSVReader::lireCSV() {
	std::string nomFichier(filename);
	Composant *compo = new Composant();
	std::vector<std::string> row;
	ifstream fichierCSV(nomFichier.c_str());
	if (fichierCSV)
	{

		string ligne, word;
		while (getline(fichierCSV, ligne)) {
			row.clear();
			stringstream s(ligne);

			while(getline(s, word, ',')) {
				row.push_back(word);
			}
			ajoutComposant(row);
		}
	}
	else
	{
		cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
		
	}
}
void CSVReader::ajoutComposant(std::vector <string> row) {
	int id = stoi(row[0]);
	float largeur = atof(row[1].c_str());
	float longueur = atof(row[2].c_str());
	printf("Valeur id = %d, valeur largeur %.2f, valeur longueur %.2f", id, largeur, longueur);
	//listComposant.push_back(Composant(id, largeur, longueur));
}