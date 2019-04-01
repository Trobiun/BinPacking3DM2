#include <stdio.h>
#include "TG3D.h"

TG3D::TG3D(void) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == i) {
				c[i][j] = 1;
			}
			else {
				c[i][j] = 0;
			}
		}
	}
}

TG3D::TG3D(TG3D *tg) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->c[i][j] = tg->c[i][j];
		}
	}
}

TG3D::~TG3D(void) {
}

void TG3D::print(void) {
	printf("fonction d'affichage qui n'est pas faite la");
}

void TG3D::transformation(CH3D *ch) {
	CH3D aux;
	for (int i = 0; i < 4; i++) {
		aux.c[i] = 0.0;
		for (int j = 0; j < 4; j++)
			aux.c[i] += c[i][j] * ch->c[j];
	}
	for (int i = 0; i < 4; i++)
		ch->c[i] = aux.c[i];
}

void TG3D::transformation(CH3D *ch, CH3D *res) {
	CH3D tempch;
	double temp = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp += this->c[i][j] * ch->c[j];
		}
		tempch.c[i] = temp;
		temp = 0;
	}
	res->x = tempch.x;
	res->y = tempch.y;
	res->z = tempch.z;
	res->w = tempch.w;
}

void TG3D::affectation(TG3D *temp, TG3D *res) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res->c[i][j] = temp->c[i][j];
		}
	}
}

// on multiplie this par tg

void TG3D::composition(TG3D *tg, TG3D *res) {
	TG3D temp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp.c[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				temp.c[i][j] += this->c[i][k] * tg->c[k][j];
			}
		}
	}
	//methode a developper qui prend les valeur de temp et les mets dans res ( a developper )
	affectation(&temp, res);
}