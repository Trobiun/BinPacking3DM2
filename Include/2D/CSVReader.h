#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Composant.h"
using namespace std;
#ifndef ____CSVREADER____
#define ____CSVREADER____


class CSVReader {
	protected:
		std::string filename;
		std::vector <Composant *> listComposant;

	public:

		/* Constructeurs                            */

		CSVReader(std::string filename);

		/* Destructeur                              */

		~CSVReader(void);

		/* Setters                                  */

		virtual bool setFilename(std::string filename);
		virtual bool setListComposant(std::vector <Composant *> listComposant);

		/* Getters                                  */

		std::string getFilename();
		std::vector <Composant *> getListComposant();

		void lireCSV();
		void ajoutComposant(std::vector <string> row);
};

#endif
