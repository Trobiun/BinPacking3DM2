#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include "Composant.h"
using namespace std;
#ifndef ____CSVREADER____
#define ____CSVREADER____


class CSVReader {
	protected:
		std::string filename;
		std::list <Composant> listComposant;

	public:

		/* Constructeurs                            */

		CSVReader(std::string filename);

		/* Destructeur                              */

		~CSVReader(void);

		/* Setters                                  */

		virtual bool setFilename(std::string filename);
		virtual bool setListComposant(std::list <Composant> listComposant);

		/* Getters                                  */

		std::string getFilename();
		std::list <Composant> getListComposant();

		void lireCSV();
		void ajoutComposant(std::vector <string> row);
};

#endif
