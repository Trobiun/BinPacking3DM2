#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <3D/Composant3D.h>
using namespace std;
#ifndef ____CSVREADER3D____
#define ____CSVREADER3D____


class CSVReader3D {
	protected:
		std::string filename;
		std::vector <Composant3D *> listComposant;

	public:

		/* Constructeurs                            */

		CSVReader3D(std::string filename);

		/* Destructeur                              */

		~CSVReader3D(void);

		/* Setters                                  */

		virtual bool setFilename(std::string filename);
		virtual bool setListComposant(std::vector <Composant3D *> listComposant);

		/* Getters                                  */

		std::string getFilename();
		std::vector <Composant3D *> getListComposant();

		void lireCSV();
		void ajoutComposant(std::vector <string> row);
		void verifCompoVector(std::vector <Composant3D *> liste);
};

#endif
