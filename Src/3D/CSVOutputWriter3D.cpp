#include "3D/CSVOutputWriter3D.h"

CSVOutputWriter3D::CSVOutputWriter3D() {
    filename = "resultat.csv";
    file.open(filename);
}

CSVOutputWriter3D::~CSVOutputWriter3D() {
    file.close();
}

void CSVOutputWriter3D::writeCSV(std::list<Conteneur3D*> conteneurs, std::list<Conteneur3D*> conteneursDispo, std::list<Composant3D*> resteComposants) {
    file << "Liste des conteneurs remplis;;;;;;" << endl;
    std::list<Conteneur3D*>::const_iterator it;
    std::list<Composant3D*>::const_iterator itComp;
    for (it = conteneurs.cbegin(); it != conteneurs.cend(); it++) {
        writeCSVConteneurHeader();
        writeCSVConteneur(*it);
        file << endl;
    }
    file << "Liste des conteneurs restants;;;;;;" << endl;
    writeCSVConteneurHeaderRestant();
    for (it = conteneursDispo.cbegin(); it != conteneursDispo.cend(); it++) {
        if ((*it)->getNb() != 0) {
            writeCSVConteneurRestant(*it);
        }
    }
    file << endl;
    file << "Liste des composants restants;;;;;;" << endl;
    writeCSVComposantHeaderRestant();
    for (itComp = resteComposants.cbegin(); itComp != resteComposants.cend(); itComp++) {
        writeCSVComposantRestant(*itComp);
    }
    file << endl;
}

void CSVOutputWriter3D::writeCSVConteneurHeader() {
    file << "idConteneur;CoteX;CoteY;CoteZ;;;" << endl;
}

void CSVOutputWriter3D::writeCSVConteneurHeaderRestant() {
    file << "Nombre restants;CoteX;CoteY;CoteZ;;;" << endl;
}

void CSVOutputWriter3D::writeCSVConteneur(Conteneur3D* conteneur) {
    file << conteneur->getId() << ";"
        << conteneur->getCoteX() << ";" << conteneur->getCoteY() << ";" << conteneur->getCoteZ() << ";"
        << ";;" << endl;
    std::list<Composant3D*> listComposants = conteneur->getListComposant();
    std::list<Composant3D*>::const_iterator it;
    writeCSVComposantHeader();
    for (it = listComposants.cbegin(); it != listComposants.cend(); it++) {
        writeCSVComposant(*it);
    }
}

void CSVOutputWriter3D::writeCSVConteneurRestant(Conteneur3D* conteneur) {
    file << conteneur->getNb() << ";"
        << conteneur->getCoteX() << ";" << conteneur->getCoteY() << ";" << conteneur->getCoteZ() << ";"
        << ";;" << endl;
}

void CSVOutputWriter3D::writeCSVComposantHeader() {
    file << "IdComposant;CoteX;CoteY;CoteZ;PosX;PosY;PosZ" << endl;
}

void CSVOutputWriter3D::writeCSVComposantHeaderRestant() {
    file << "IdComposant;CoteX;CoteY;CoteZ;;;" << endl;
}

void CSVOutputWriter3D::writeCSVComposant(Composant3D* composant) {
    file << composant->getId() << ";"
        << composant->getCoteX() << ";" << composant->getCoteY() << ";" << composant->getCoteZ() << ";";
    writeCSVPosition(composant->getPosition());
    file << endl;
}

void CSVOutputWriter3D::writeCSVComposantRestant(Composant3D* composant) {
    file << composant->getId() << ";"
        << composant->getCoteX() << ";" << composant->getCoteY() << ";" << composant->getCoteZ() << ";";
    file << endl;
}

void CSVOutputWriter3D::writeCSVPosition(Position3D* position) {
    file << position->getX() << ";" << position->getY() << ";" << position->getZ() << ";";
}