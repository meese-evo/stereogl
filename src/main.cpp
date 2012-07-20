/*
 * Folgende Libs dem Linker hinzufügen
 * - sfml-system
 * - sfml-window
 * - GLU
 *
 * SFML-Tutorial: http://www.sfml-dev.org/tutorials/1.5/window-opengl.php
 *
 */

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>

using namespace std;
//using namespace sf;

struct fVektor {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

bool CalcNormal(GLfloat v0, GLfloat v1, GLfloat v2);

int main() {

	sf::WindowSettings Settings;
	Settings.DepthBits = 24; // Request a 24 bits depth buffer
	Settings.StencilBits = 8; // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 2; // Request 2 levels of antialiasing
	sf::Window App(sf::VideoMode(800, 800, 32), "SFML OpenGL", sf::Style::Close,
			Settings);

	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 500.f);

	// Vertexe des Würfels
	const GLfloat v0[3] = { -50, -50, 50 };
	const GLfloat v1[3] = { -50, 50, 50 };
	const GLfloat v2[3] = { 50, 50, 50 };
	const GLfloat v3[3] = { 50, -50, 50 };
	const GLfloat v4[3] = { 50, -50, -50 };
	const GLfloat v5[3] = { 50, 50, -50 };
	const GLfloat v6[3] = { -50, -50, -50 };
	const GLfloat v7[3] = { -50, 50, -50 };

	// Rotation
	float rotx = 0;
	float roty = 0;

	while (App.IsOpened()) {

		sf::Event Event;
		while (App.GetEvent(Event)) {

			switch (Event.Type) {

			// Window closed
			case sf::Event::Closed:
				App.Close();
				break;
				// Escape key pressed
			case sf::Event::KeyPressed:
				if (Event.Key.Code == sf::Key::Escape)
					App.Close();
				// Rotation Left
				if (Event.Key.Code == sf::Key::Left)
					rotx -= 5;
				//Rotation Right
				if (Event.Key.Code == sf::Key::Right)
					rotx += 5;
				//Rotation Up
				if (Event.Key.Code == sf::Key::Up)
					roty -= 5;
				//Rotation Down
				if (Event.Key.Code == sf::Key::Down)
					roty += 5;
				break;

				// Adjust OpenGL viewport on resize event
			case sf::Event::Resized:
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
				break;

			default:
				break;

			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_COLOR_MATERIAL); //Materialfarbgebungsart
		glEnable(GL_LIGHT0); //Lichtquelle 0 EIN
		glEnable(GL_LIGHTING); //OpenGL-Lichteffekte EIN
		glDisable(GL_CULL_FACE); //Seiten nicht ausblenden
		glEnable(GL_NORMALIZE);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);
		glRotatef(rotx, 0.f, 1.f, 0.f);
		glRotatef(roty, 1.f, 0.f, 0.f);
		//		glRotatef(Clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);

		glBegin(GL_QUADS); // Start der Primitiv-Definition

		//Fläche Vorderseite - Grün
		glColor3f(0, 1, 0);
		glNormal3f(0, 0, 1);
		glVertex3fv(v0);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);

		//Fläche Rechts - Rot
		glColor3f(1, 0, 0);
		glVertex3fv(v4);
		glVertex3fv(v5);
		glVertex3fv(v2);
		glVertex3fv(v3);

		//Fläche Rückseite - Blau
		glColor3f(0, 0, 1); // Definition der Farbe
		glVertex3fv(v6);
		glVertex3fv(v7);
		glVertex3fv(v5);
		glVertex3fv(v4);

		//Fläche Links - Hellblau
		glColor3f(0, 1, 1);
		glVertex3fv(v6);
		glVertex3fv(v7);
		glVertex3fv(v1);
		glVertex3fv(v0);

		//Fläche Unten - Lila
		glColor3f(1, 0, 1);
		glVertex3fv(v0);
		glVertex3fv(v6);
		glVertex3fv(v4);
		glVertex3fv(v3);

		//Fläche Oben - Gelb
		glColor3f(1, 1, 0);
		glVertex3fv(v1);
		glVertex3fv(v7);
		glVertex3fv(v5);
		glVertex3fv(v2);

		glEnd();

		App.Display();
	}
	return EXIT_SUCCESS;
}

bool CalcNormal(GLfloat V1, GLfloat V2, GLfloat V3) {
	fVektor V1V2, V1V3, KREUZ;
	GLfloat Betrag;

	// Vorbereitung
	V1V2.x = V2[1] - V1[1]; // Vektoren für Kreuzprodukt-
	V1V2.y = V2[2] - V1[2]; // berechnung ermitteln:
	V1V2.z = V2[3] - V1[3]; // Komponentenweise auf
	V1V3.x = V3[1] - V1[1]; // Vertex V1 zurückführen
	V1V3.y = V3[2] - V1[2]; // => 2 komplanare Vektoren
	V1V3.z = V3[3] - V1[3]; // mit Berührpunkt V1
	// Berechnung des Kreuzprodukts
	KREUZ.x = +((V1V2.y * V1V3.z) - (V1V2.z * V1V3.y));
	KREUZ.y = -((V1V2.x * V1V3.z) - (V1V2.z * V1V3.x));
	KREUZ.z = +((V1V2.x * V1V3.y) - (V1V2.y * V1V3.x));
	// Prüfen des Vektors
	Betrag = sqrt( //Länge des Vektors ermitteln
			pow(KREUZ.x, 2.0) + pow(KREUZ.y, 2.0) + pow(KREUZ.z, 2.0));
	if (Betrag == 0.0)
		//Der Normalenvektor MUSS länger
		return 0;
	//als ein Nullvektor sein!
	// Normalenvektor als Einsvektor abspeichern
//	m_structOGLStatus.vLastNormale.x = KREUZ.x / Betrag;
//	m_structOGLStatus.vLastNormale.y = KREUZ.y / Betrag;
//	m_structOGLStatus.vLastNormale.z = KREUZ.z / Betrag;

	return 1;

}
