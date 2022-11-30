#include <GL/glut.h>

class Balon {
private:
	GLUquadric* quadric;
	GLdouble radio;
	GLint paralelos;
	GLint meridianos;
	GLfloat posx, posy, posz;
	int estado;
public:
	enum estado {
		EDO_INICIAL,
		EDO_CAYENDO,
		EDO_SUELO,
		EDO_SUBIENDO
	};

	Balon(GLdouble r, GLint parals, GLint merids) {
		radio = r;
		paralelos = parals;
		meridianos = merids;
		quadric = gluNewQuadric();
		setEstado(EDO_INICIAL);
		setUbicacion(0, 0, 0);
	}

	void dibujar() {
		glPushMatrix();
		glTranslatef(posx, posy, posz);
		gluSphere(quadric, radio, paralelos, meridianos);
		glPopMatrix();
	}

	void setUbicacion(GLfloat x, GLfloat y, GLfloat z) {
		posx = x;
		posy = y;
		posz = z;
	}

	void setEstado(int e) {
		switch (e)
		{
		case EDO_INICIAL:
		case EDO_CAYENDO:
		case EDO_SUELO:
		case EDO_SUBIENDO:
			estado = e;
			break;
		default:
			estado = EDO_INICIAL;
			break;
		}
	}

	int getEstado() {
		return estado;
	}
};