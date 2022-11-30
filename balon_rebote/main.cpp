// balon_rebote.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "Balon.cpp"

Balon* ball;
GLfloat balonx = 10, balony = 115, balonz = 0;
double t = 0.0;

void init();
void display();
void caidaLibre(float);
void rebote(float);
void animacion();
void mostrarTexto(int, int, char*, int);
void teclado(unsigned char, int, int);

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	// dibujar campo
	glColor3f(0.3, 0.3, 1);
	/*glBegin(GL_QUADS);
	glVertex3i(24, 0, 0);
	glVertex3i(24, 100, 0);
	glVertex3i(174, 100, 0);
	glVertex3i(174, 0, 0);
	glEnd();*/

	//dibujar balon

	ball->setUbicacion(balonx, balony, balonz);
	ball->dibujar();

	glutSwapBuffers();
}

void init() {

	glClearColor(1, 1, 1, 1);
	glLoadIdentity();
	glOrtho(0, 199, 0, 149, -1, 100);

	ball = new Balon(10, 32, 32);

}

void caidaLibre(float t) {
	//calcular caida libre
	//std::cout << "caidaLibre( t = " << t << ", y = " << y << " )" << std::endl;
	float yn = 0.5 * 9.81 * pow(t, 2);
	//restar de la posicion actual
	balony -= yn;
	if (balony <= 15) {
		ball->setEstado(ball->EDO_SUELO);
		std::cout << "golpe en el suelo" << std::endl;
		balony = 15;
	}
	ball->setUbicacion(balonx, balony, balonz);
	ball->dibujar();
}

void rebote(float t) {
	if (balonx <= 199) {
		balony = 149 * exp(-0.1 * t) * fabs(sin((2 * 3.14159 / 20) * t));
	}
	else {
		balony = 15;
		std::cout << "rebote terminado" << std::endl;
	}
}

void animacion() {
	
	switch (ball->getEstado())
	{
	case ball->EDO_INICIAL:
		break;
	case ball->EDO_CAYENDO:
		//std::cout << "t = " << t << ", y = " << y << std::endl;
		caidaLibre(t);
		t += 0.01;
		glutPostRedisplay();
		break;
	case ball->EDO_SUELO:
		ball->setEstado(ball->EDO_SUBIENDO);
		t = 0;
		break;
	case ball->EDO_SUBIENDO:
		rebote(t);
		balonx += 0.5;
		t += 0.1;
		//std::cout << x << "," << y << std::endl;
		glutPostRedisplay();
		break;
	default:
		break;
	}
	
}

/*
* Muestra una cadena de texto en la posicion indicada
*/
void mostrarTexto(int x, int y, char* cadena, int cadenaSize) {
	glRasterPos2i(x, y);
	for (int i = 0; i < cadenaSize; i++)
	{
		//std::cout << cadena[i];
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cadena[i]);
	}
}

/*funcion de teclado*/
void teclado(unsigned char key, int xi, int yi) {
	switch (key)
	{
	case 'B':
	case 'b':
		if (ball->getEstado() == ball->EDO_INICIAL)
		{
			ball->setEstado(ball->EDO_CAYENDO);
			std::cout << "tecla \'b\' presionada, cayendo" << std::endl;
		}
		break;
	case 'R':// las letras R y r funcionan igual,
	case 'r':// provocando la repeticion de la animacion
		balonx = 10;
		balony = 175;
		t = 0;
		ball->setEstado(ball->EDO_INICIAL);
		ball->setUbicacion(balonx, balony, balonz);
		ball->dibujar();
		break;
	case 27: // salir presionando escape
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
    std::cout << "Hello World!\n";

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(150, 50);
	glutCreateWindow("Computacion Grafica. Semestre 2023-1. Marin Roldan Ivan");

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(teclado);
	glutIdleFunc(animacion);


	glutMainLoop();

	return 0;

}
