#ifndef CSVOUTPUTWRITER3D_H
#define CSVOUTPUTWRITER3D_H

#include <iostream>
#include <fstream>
#include "3D/Conteneur3D.h"
#include "3D/Composant3D.h"
#include "3D/Position3D.h"

class CSVOutputWriter3D {
private:
    std::string filename;
    std::ofstream file;

public:
    CSVOutputWriter3D();
    virtual ~CSVOutputWriter3D();

    void writeCSV(std::list<Conteneur3D*> conteneurs, std::list<Conteneur3D*> resteConteneurs, std::list<Composant3D*> resteComposants);
    
    void writeCSVConteneurHeader();
    void writeCSVConteneurHeaderRestant();
    void writeCSVConteneur(Conteneur3D* conteneur);
    void writeCSVConteneurRestant(Conteneur3D* conteneur);
    
    void writeCSVComposantHeader();
    void writeCSVComposantHeaderRestant();
    void writeCSVComposant(Composant3D* composant);
    void writeCSVComposantRestant(Composant3D* composant);
    
    void writeCSVPosition(Position3D* position);

private:

};

#endif /* CSVOUTPUTWRITER3D_H */

