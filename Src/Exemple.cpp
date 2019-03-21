/* Lumieres et materiaux                         */
/*                                               */
/* Auteur: Nicolas JANEY                         */
/* nicolas.janey@univ-fcomte.fr                  */
/* Fevrier 2019                                  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables et constantes globales              */

static double px = 0.0;
static double py = 0.0;
static double pz = 10.0;

static float rxs = 0.0;
static float rys = 0.0;
static float rzs = 0.0;

static int n = 100;
static int n1 = 72;
static int n2 = 360;

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float cyan[] = { 0.0F,1.0F,0.0F,1.0F };
static const float magenta[] = { 1.0F,0.0F,1.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };
static const float noir[] = { 0.0F,0.0F,0.0F,1.0F };
static const float grisMoyen[] = { 0.5F,0.5F,0.5F,1.0F };

static int affichage = 1;
static int scene = 0;
static int animation = 0;
static int culling = 0;

/* Fonction d'initialisation des parametres      */
/* OpenGL ne changeant pas au cours de la vie    */
/* du programme                                  */

static void init(void) {
	glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, noir);
}

/* Modelisation geometrique d'un parallelogramme */
/* (quadrilatere dont les cotes opposes          */
/* sont paralleles)                              */
/* px, py et pz    : La position du sommet       */
/*                   de reference                */
/* tx1, ty1 et tz1 : Les dimensions du cote 1    */
/* tx2, ty2 et tz2 : Les dimensions du cote 2    */
/* n1 et n2        : Les nombres de facettes     */
/*                   selon les cotes 1 et 2      */

static void mySolidParallelogram(double px, double py, double pz,
	double tx1, double ty1, double tz1,
	double tx2, double ty2, double tz2,
	int n1, int n2) {
	double dx1 = tx1 / n1;
	double dy1 = ty1 / n1;
	double dz1 = tz1 / n1;
	double dx2 = tx2 / n2;
	double dy2 = ty2 / n2;
	double dz2 = tz2 / n2;
	double ds = 1.0 / n1;
	double dt = 1.0 / n2;
	for (int i1 = 0; i1 < n1; i1++) {
		glBegin(GL_QUAD_STRIP);
		double x = px + i1 * dx1;
		double y = py + i1 * dy1;
		double z = pz + i1 * dz1;
		double s = i1 * ds;
		double t = 0.0;
		for (int i2 = 0; i2 <= n2; i2++) {
			glTexCoord2d(s, t);
			glVertex3d(x, y, z);
			glTexCoord2d(s + ds, t);
			glVertex3d(x + dx1, y + dy1, z + dz1);
			x += dx2;
			y += dy2;
			z += dz2;
			t += dt;
		}
		glEnd();
	}
}

/* Modelisation geometrique d'un cube            */
/* ct : la taille du cube                        */
/* n  : le nombre de facettes generees           */
/*      selon chaque axe pour le dessin          */
/*      de chacune des faces                     */

static void mySolidCube(double ct, int n) {
	double c = ct / 2.0F;
	glNormal3f(0.0F, 0.0F, -1.0F);
	mySolidParallelogram(-c, -c, -c, 0.0, ct, 0.0, ct, 0.0, 0.0, n, n);
	glNormal3f(0.0F, -1.0F, 0.0F);
	mySolidParallelogram(-c, -c, -c, ct, 0.0, 0.0, 0.0, 0.0, ct, n, n);
	glNormal3f(-1.0F, 0.0F, 0.0F);
	mySolidParallelogram(-c, -c, -c, 0.0, 0.0, ct, 0.0, ct, 0.0, n, n);
	glNormal3f(0.0F, 0.0F, 1.0F);
	mySolidParallelogram(c, c, c, -ct, 0.0, 0.0, 0.0, -ct, 0.0, n, n);
	glNormal3f(0.0F, 1.0F, 0.0F);
	mySolidParallelogram(c, c, c, 0.0, 0.0, -ct, -ct, 0.0, 0.0, n, n);
	glNormal3f(1.0F, 0.0F, 0.0F);
	mySolidParallelogram(c, c, c, 0.0, -ct, 0.0, 0.0, 0.0, -ct, n, n);
}

/* Scene dessinee 2                              */

static void configurationMaterielCube(void) {
}

static void scene2() {
	glPushMatrix();
	configurationMaterielCube();
	mySolidCube(7.0, n);
	glPopMatrix();
}

/* Scene dessinee 1                              */

static void configurationMaterielTore1(void) {
}

static void configurationMaterielTore2(void) {
}

static void configurationMaterielTore3(void) {
}

static void scene1() {
	glPushMatrix();
	configurationMaterielTore1();
	glutSolidTorus(1.0, 5.0, n1, n2);
	glRotatef(90.0F, 1.0F, 0.0F, 0.0F);
	configurationMaterielTore2();
	glutSolidTorus(1.0, 5.0, n1, n2);
	glRotatef(90.0F, 0.0F, 1.0F, 0.0F);
	configurationMaterielTore3();
	glutSolidTorus(1.0, 5.0, n1, n2);
	glPopMatrix();
}

/* Fonction de configuration des lumieres        */

static void configurationLumieres(void) {
}

/* Fonction executee lors d'un rafraichissement  */
/* de la fenetre de dessin                       */

static void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, (affichage) ? GL_FILL : GL_LINE);
	if (culling) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}
	glPushAttrib(GL_LIGHTING_BIT);
	glPushMatrix();
	gluLookAt(px, py, pz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	configurationLumieres();
	glRotatef(rxs, 1.0F, 0.0F, 0.0F);
	glRotatef(rys, 0.0F, 1.0F, 0.0F);
	glRotatef(rzs, 0.0F, 0.0F, 1.0F);
	switch (scene) {
	case 0:
		scene1();
		break;
	case 1:
		scene2();
		break;
	}
	glPopMatrix();
	glPopAttrib();
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Erreur OpenGL: %d\n", error);
}

/* Fonction executee lors d'un changement        */
/* de la taille de la fenetre OpenGL             */
/* -> Ajustement de la camera de visualisation   */

static void reshape(int tx, int ty) {
	glViewport(0, 0, tx, ty);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = (double)tx / ty;
	if (ratio >= 1.0)
		gluPerspective(80.0, ratio, 1.0, 20.0);
	else
		gluPerspective(80.0 / ratio, ratio, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Fonction executee lors de la frappe           */
/* d'une touche speciale du clavier              */

static void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		py += 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		py -= 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		px -= 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		px += 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_UP:
		pz -= 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		pz += 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F1:
		px = 0.0;
		py = 0.0;
		pz = 10.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F2:
		rxs = 0.0;
		rys = 0.0;
		rzs = 0.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F3:
		rxs = 10.0;
		rys = 60.0;
		rzs = 110.0;
		glutPostRedisplay();
		break;
	}
}

/* Fonction executee en tache de fond            */

static void idle1(void) {
	rxs += 0.7F;
	rys += 0.5F;
	rzs += 0.3F;
	glutPostRedisplay();
}

/* Fonction executee lors de la frappe           */
/* d'une touche du clavier                       */

static void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		animation = (animation + 1) % 2;
		switch (animation) {
		case 0:
			glutIdleFunc(NULL);
			break;
		case 1:
			glutIdleFunc(idle1);
			break;
		}
		break;
	case 'c':
		culling = !culling;
		glutPostRedisplay();
		break;
	case 0x20:
		affichage = !affichage;
		glutPostRedisplay();
		break;
	case 's':
		scene = (scene + 1) % 2;
		glutPostRedisplay();
		break;
	case 0x1B:
		exit(0);
		break;
	}
}

/* Fonction principale                           */

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(360, 360);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Lumieres et matériel");
	//glColorMaterial(GL_FRONT, GL_)
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return(0);
}
