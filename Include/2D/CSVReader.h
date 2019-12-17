#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Composant.h"
#include "Conteneur.h"
using namespace std;
#ifndef ____CSVREADER____
#define ____CSVREADER____


class CSVReader {
	protected:
		std::string filename;
		std::vector <Composant *> listComposant;
		std::vector <Conteneur *> listConteneur;

	public:

		/* Constructeurs                            */

		CSVReader(std::string filename);

		/* Destructeur                              */

		~CSVReader(void);

		/* Setters                                  */

		virtual bool setFilename(std::string filename);
		virtual bool setListComposant(std::vector <Composant *> listComposant);
		virtual bool setListConteneur(std::vector <Conteneur *> listConteneur);

		/* Getters                                  */

		std::string getFilename();
		std::vector <Composant *> getListComposant();
		std::vector <Conteneur *> getListConteneur();

		void lireCSV(int type);
		void ajoutComposant(std::vector <string> row);
		void ajoutConteneur(std::vector <string> row);
		void verifCompoVectorComposant(std::vector <Composant *> liste);
		void verifCompoVectorConteneur(std::vector <Conteneur *> liste);
};

#endif
