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
bool CSVReader::setListComposant(std::vector <Composant> list) {
	listComposant = list;
	return true;
}

string CSVReader::getFilename() {
	return filename;
}
std::vector <Composant> CSVReader::getListComposant() {
	return listComposant;
}

void CSVReader::lireCSV() {
	std::vector<std::string> row;
	ifstream fichierCSV(filename.c_str() , ios_base::in);
	if (fichierCSV.good())
	{
		cout << "SUCCESS : Le fichier a pu être ouvert." << endl;
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
	//Faire les verif pour chacun des champs
	int id = atoi(row[0].c_str());
	float largeur = atof(row[1].c_str());
	float longueur = atof(row[2].c_str());
	printf("AJOUT D'UN COMPOSANT : id = %d, largeur %.2f, longueur %.2f \n", id, largeur, longueur);
	listComposant.push_back(Composant(id, largeur, longueur));
}