#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <3D/Composant3D.h>
#include <3D/Conteneur3D.h>
using namespace std;
#ifndef ____CSVREADER3D____
#define ____CSVREADER3D____


class CSVReader3D {
	protected:
		std::string filename;
		std::vector <Composant3D *> listComposant;
		std::vector <Conteneur3D *> listConteneur;

	public:

		/* Constructeurs                            */

		CSVReader3D(std::string filename);

		/* Destructeur                              */

		~CSVReader3D(void);

		/* Setters                                  */

		virtual bool setFilename(std::string filename);
		virtual bool setListComposant(std::vector <Composant3D *> listComposant);
		virtual bool setListConteneur(std::vector <Conteneur3D *> listConteneur);

		/* Getters                                  */

		std::string getFilename();
		std::vector <Composant3D *> getListComposant();
		std::vector <Conteneur3D *> getListConteneur();

		void lireCSV(int type);
		void ajoutComposant(std::vector <string> row);
		void ajoutConteneur(std::vector <string> row);
		void verifCompoVectorComposant(std::vector <Composant3D *> liste);
		void verifCompoVectorConteneur(std::vector <Conteneur3D *> liste);
};

#endif
