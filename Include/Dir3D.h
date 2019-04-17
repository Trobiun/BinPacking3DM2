/* Mathematiques de l'informatique graphique    */
/* Direction en 3D                              */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Mars 2019                                    */

#ifndef ____DIR3D____
#define ____DIR3D____

class Pos3D;

#include "CH3D.h"

class Dir3D : public CH3D {
public:
    /* Constructeurs                            */
    Dir3D(void);
    Dir3D(double x, double y, double z);
    Dir3D(Dir3D *c);
    Dir3D(Pos3D *pi, Pos3D *pf);

    /* Destructeur                              */
    ~Dir3D(void);

    /* Methode de calcul de la norme            */
    double norme(void);

    /* Methode de normalisation                 */
    void normalisation(void);

    /* Methode de calcul du produit scalaire    */
    /* de this et d'une direction               */
    double produitScalaire(Dir3D *d);

    /* Methode statique de calcul               */
    /* du produit scalaire de deux directions   */
    static double produitScalaire(Dir3D *d1, Dir3D *d2);

    /* Methode de calcul du produit vectoriel   */
    /* de this par une direction                */
    /* avec stockage du resultat dans this      */
    void produitVectoriel(Dir3D *d);

    /* Methode statique de calcul               */
    /* du produit vectoriel de deux directions  */
    /* Retour d'un objet Dir3D                  */
    /* cree dans la methode                     */
    static Dir3D *produitVectoriel(Dir3D *d1, Dir3D *d2);

    static double angle(Dir3D *d1, Dir3D *d2);

    static Pos3D intersection(Dir3D *d1, Dir3D *d2);
};

#endif
