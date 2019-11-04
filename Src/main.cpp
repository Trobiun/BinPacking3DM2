#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
/* Variables globales                           */

static int wTx = 480; // Resolution horizontale de la fenetre
static int wTy = 480; // Resolution verticale de la fenetre
static int wPx = 50; // Position horizontale de la fenetre
static int wPy = 50; // Position verticale de la fenetre


/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}
/* Scene dessinee                               */

static void scene(void) {
	glPushMatrix();

	glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
	printf("D\n");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	scene();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx, int wy) {
	printf("R\n");
	wTx = wx;
	wTy = wy;
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
	printf("I\n");
	glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
	printf("K  %4c %4d %4d\n", key, x, y);
	switch (key) {
	case 0x1B:
		exit(0);
		break;
	}
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey, int x, int y) {
	printf("S  %4d %4d %4d\n", specialKey, x, y);
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int buton, int state, int x, int y) {
	printf("M  %4d %4d %4d %4d\n", buton, state, x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un boutton presse                       */

static void mouseMotion(int x, int y) {
	printf("MM %4d %4d\n", x, y);
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans boutton presse                          */

static void passiveMouseMotion(int x, int y) {
	printf("PM %4d %4d\n", x, y);
}

/* Fonction executee automatiquement            */
/* lors de l'execution de la fonction exit()    */

static void clean(void) {
	printf("Bye\n");
}
/* Fonction principale                          */

int main(int argc, char** argv) {
	atexit(clean);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(wTx, wTy);
	glutInitWindowPosition(wPx, wPy);
	glutCreateWindow("Title");
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	//glutPassiveMotionFunc(passiveMouseMotion);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutMainLoop();
	return (0);
}
