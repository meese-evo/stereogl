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

const GLfloat offset = 80;

// Vertexe des "Ur"-Würfels
const GLfloat v0[3] = { -35, -35, 50 };
const GLfloat v1[3] = { -35, 35, 50 };
const GLfloat v2[3] = { 35, 35, 50 };
const GLfloat v3[3] = { 35, -35, 50 };
const GLfloat v4[3] = { 35, -35, -50 };
const GLfloat v5[3] = { 35, 35, -50 };
const GLfloat v6[3] = { -35, -35, -50 };
const GLfloat v7[3] = { -35, 35, -50 };

// Vertexe des Daches
const GLfloat v8[3] = { 0, 70, 60 };
const GLfloat v9[3] = { 43.8, 26.3, 60 };
const GLfloat v10[3] = { 43.8, 26.3, -60 };
const GLfloat v11[3] = { 0, 70, -60 };
const GLfloat v12[3] = { -43.8, 26.3, 60 };
const GLfloat v13[3] = { -43.8, 26.3, -60 };

// Vertexe des Schornsteins
const GLfloat v14[3] = { 7, 50, -29 };
const GLfloat v15[3] = { 7, 78, -29 };
const GLfloat v16[3] = { 17, 78, -29 };
const GLfloat v17[3] = { 17, 50, -29 };
const GLfloat v18[3] = { 17, 50, -39 };
const GLfloat v19[3] = { 17, 78, -39 };
const GLfloat v20[3] = { 7, 50, -39 };
const GLfloat v21[3] = { 7, 78, -39 };

// Vertexe der Gaube
const GLfloat v22[3] = { -26.25, 43.75, 8.75 };
const GLfloat v23[3] = { -8.75, 61.75, 8.75 };
const GLfloat v24[3] = { -26.25, 61.75, 8.75 };
const GLfloat v25[3] = { -26.25, 43.75, -8.75 };
const GLfloat v26[3] = { -8.75, 61.75, -8.75 };
const GLfloat v27[3] = { -26.25, 61.75, -8.75 };
const GLfloat v28[3] = { -26.25, 70, 0 };
const GLfloat v29[3] = { 0, 70, 0 };

struct fVektor {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} normV;

void DrawCube(int i, int width, int height);
void CalcNormal(GLfloat V1[], GLfloat V2[], GLfloat V3[]);

int main() {

	const int width = 1600;
	const int height = 800;

	int i = 0;

	sf::WindowSettings Settings;
	Settings.DepthBits = 24; // Request a 24 bits depth buffer
	Settings.StencilBits = 8; // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 4; // Request 4 levels of antialiasing
	sf::Window App(sf::VideoMode(width, height, 32), "SFML OpenGL",
			sf::Style::Close, Settings);

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

//				// Adjust OpenGL viewport on resize event
//			case sf::Event::Resized:
//				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
//				break;

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

//		// Berechnung des Normalenvektors
//		// Achtung! Die Vertexe dürfen dann kein const sein!
//		CalcNormal(v8, v12, v13);
//		cout << "Norm.-X: " << normV.x << endl;
//		cout << "Norm.-Y: " << normV.y << endl;
//		cout << "Norm.-Z: " << normV.z << endl;
//		cout << endl << endl;

		// i==0 Viewport links
		// i==1 Viewport rechts
		for (i = 0; i < 2; i++) {
			DrawCube(i, width, height);
		}
		App.Display();

	}
	return EXIT_SUCCESS;
}

// Fkt. zum Zeichnen des Würfels
void DrawCube(int i, int width, int height) {

	struct Viewport {
		int x;
		int y;
		int w;
		int h;
	};

	float giebel = v8[2] - v0[2];

	Viewport view0 = { 0, 0, width / 2 - 1, height - 1 };
	Viewport view1 = { width / 2, 0, width / 2 - 1, height - 1 };

	if (i == 0) {
		glViewport(view0.x, view0.y, view0.w, view0.h); // linker Viewport
	} else if (i == 1) {
		glViewport(view1.x, view1.y, view1.w, view1.h); // rechter Viewport
	}

	// Dach und Seitenwände zeichnen
	glBegin(GL_QUADS);
		// Fläche Vorderseite - Grün
		glColor3f(0, 1, 0); // Definition der Farbe
		glNormal3f(0, 0, 1); // Normalenvektor für die Beleuchtung
		glVertex3fv(v0);
		glVertex3fv(v1);
		glVertex3fv(v2);
		glVertex3fv(v3);
		// Fläche Rechts - Rot
		glColor3f(1, 0, 0);
		glNormal3f(1, 0, 0);
		glVertex3fv(v4);
		glVertex3fv(v5);
		glVertex3fv(v2);
		glVertex3fv(v3);
		// Fläche Rückseite - Blau
		glColor3f(0, 0, 1);
		glNormal3f(0, 0, -1);
		glVertex3fv(v6);
		glVertex3fv(v7);
		glVertex3fv(v5);
		glVertex3fv(v4);
		// Fläche Links - Hellblau
		glColor3f(0, 1, 1);
		glNormal3f(-1, 0, 0);
		glVertex3fv(v6);
		glVertex3fv(v7);
		glVertex3fv(v1);
		glVertex3fv(v0);
		// Fläche Unten - Lila
		glColor3f(1, 0, 1);
		glNormal3f(0, -1, 0);
		glVertex3fv(v0);
		glVertex3fv(v6);
		glVertex3fv(v4);
		glVertex3fv(v3);
//		// Fläche Oben - Gelb
//		glColor3f(1, 1, 0);
//		glNormal3f(0, 1, 0);
//		glVertex3fv(v1);
//		glVertex3fv(v7);
//		glVertex3fv(v5);
//		glVertex3fv(v2);
		// Fläche Dach rechts - Gelb
		glColor3f(1, 1, 0);
		glNormal3f(0.706298, 0.707914 , 0);
		glVertex3fv(v8);
		glVertex3fv(v9);
		glVertex3fv(v10);
		glVertex3fv(v11);
		// Fläche Dach links - Gelb
		glColor3f(1, 1, 0);
		glNormal3f(-0.706298, 0.707914 , 0);
		glVertex3fv(v8);
		glVertex3fv(v12);
		glVertex3fv(v13);
		glVertex3fv(v11);
	glEnd();

	// Giebel zeichnen
	glBegin(GL_TRIANGLES);
		// Fläche Vorderseite - Grün
		glColor3f(0, 1, 0);
		glNormal3f(0, 0, 1);
		glVertex3f(v12[0], v12[1], v12[2]-giebel);
		glVertex3f(v9[0], v9[1], v9[2]-giebel);
		glVertex3f(v8[0], v8[1], v8[2]-giebel);
		// Fläche Rückseite - Blau
		glColor3f(0, 0, 1);
		glNormal3f(0, 0, -1);
		glVertex3f(v13[0], v13[1], v13[2]+giebel);
		glVertex3f(v10[0], v10[1], v10[2]+giebel);
		glVertex3f(v11[0], v11[1], v11[2]+giebel);
	glEnd();

	// Schornstein
	glBegin(GL_QUADS);
		// Fläche Vorderseite - Grün
		glColor3f(0, 1, 0); // Definition der Farbe
		glNormal3f(0, 0, 1); // Normalenvektor für die Beleuchtung
		glVertex3fv(v14);
		glVertex3fv(v15);
		glVertex3fv(v16);
		glVertex3fv(v17);
		// Fläche Rechts - Rot
		glColor3f(1, 0, 0);
		glNormal3f(1, 0, 0);
		glVertex3fv(v18);
		glVertex3fv(v19);
		glVertex3fv(v16);
		glVertex3fv(v17);
		// Fläche Rückseite - Blau
		glColor3f(0, 0, 1);
		glNormal3f(0, 0, -1);
		glVertex3fv(v20);
		glVertex3fv(v21);
		glVertex3fv(v19);
		glVertex3fv(v18);
		// Fläche Links - Hellblau
		glColor3f(0, 1, 1);
		glNormal3f(-1, 0, 0);
		glVertex3fv(v20);
		glVertex3fv(v21);
		glVertex3fv(v15);
		glVertex3fv(v14);
		// Fläche Unten - Lila
		glColor3f(1, 0, 1);
		glNormal3f(0, -1, 0);
		glVertex3fv(v14);
		glVertex3fv(v20);
		glVertex3fv(v18);
		glVertex3fv(v17);
		// Fläche Oben - Gelb
		glColor3f(1, 1, 0);
		glNormal3f(0, 1, 0);
		glVertex3f(v15[0], v15[1]-3, v15[2]);
		glVertex3f(v21[0], v21[1]-3, v21[2]);
		glVertex3f(v19[0], v19[1]-3, v19[2]);
		glVertex3f(v16[0], v16[1]-3, v16[2]);
	glEnd();

	// Seitenwände, Giebel der Gaube zeichnen
	glBegin(GL_TRIANGLES);
		// Fläche Vorderseite - Grün
		glColor3f(0, 1, 0);
		glNormal3f(0, 0, 1);
		glVertex3fv(v22);
		glVertex3fv(v23);
		glVertex3fv(v24);
		// Fläche Rückseite - Blau
		glColor3f(0, 0, 1);
		glNormal3f(0, 0, -1);
		glVertex3fv(v25);
		glVertex3fv(v26);
		glVertex3fv(v27);
		// Giebel - Hellblau
		glColor3f(0, 1, 1);
		glNormal3f(-1, 0, 0);
		glVertex3fv(v27);
		glVertex3fv(v24);
		glVertex3fv(v28);
	glEnd();

	// Front und Dach der Gaube zeichnen
	glBegin(GL_QUADS);
		// Frontfläche Giebel - Hellblau
		glColor3f(0, 1, 1);
		glNormal3f(-1, 0, 0);
		glVertex3fv(v22);
		glVertex3fv(v24);
		glVertex3fv(v27);
		glVertex3fv(v25);
		// Fläche Dach rechts - Gelb
		glColor3f(1, 1, 0);
		glNormal3f(0.706298, 0.707914 , 0);
		glVertex3f(v28[0]-5, v28[1], v28[2]);
		glVertex3fv(v29);
		glVertex3f(v23[0]-5, v23[1]-5, v23[2]+5.5);
		glVertex3f(v24[0]-5, v24[1]-5, v24[2]+5.5);
		// Fläche Dach links - Gelb
		glColor3f(1, 1, 0);
		glNormal3f(-0.706298, 0.707914 , 0);
		glVertex3f(v28[0]-5, v28[1], v28[2]);
		glVertex3fv(v29);
		glVertex3f(v26[0]-5, v26[1]-5, v26[2]-5.5);
		glVertex3f(v27[0]-5, v27[1]-5, v27[2]-5.5);
	glEnd();


//		// Schornsteinrohr - Zylinder
//		// http://wiki.delphigl.com/index.php/glRotate
//		// http://www.codeworx.org/opengl_tut18.php
//		glTranslatef(v15[1]-3, 20.0, -34);// Center The Cylinder
//		glRotatef(90, v15[1]-3, 20.0, -34);
//		GLUquadricObj *quadratic;// Storage For Our Quadratic Objects
//		quadratic=gluNewQuadric();// Create A Pointer To The Quadric Object ( NEW )
//		gluQuadricNormals(quadratic, GLU_SMOOTH);// Create Smooth Normals ( NEW )
//		gluQuadricTexture(quadratic, GL_TRUE);// Create Texture Coords ( NEW )
//		gluCylinder(quadratic,10.0f,10.0f,50.0f,32,32);// Draw Our Cylinder
}

// Fkt. aus Markt&Technik "Jetzt lerne ich OpenGL"
// Fkt. zur Berechnung des Normalenvektors
void CalcNormal(GLfloat V1[], GLfloat V2[], GLfloat V3[]) {
	fVektor V1V2, V1V3, KREUZ;
	GLfloat Betrag;

	// Vorbereitung
	V1V2.x = V2[0] - V1[0]; // Vektoren für Kreuzprodukt-
	V1V2.y = V2[1] - V1[1]; // berechnung ermitteln:
	V1V2.z = V2[2] - V1[2]; // Komponentenweise auf
	V1V3.x = V3[0] - V1[0]; // Vertex V1 zurückführen
	V1V3.y = V3[1] - V1[1]; // => 2 komplanare Vektoren
	V1V3.z = V3[2] - V1[2]; // mit Berührpunkt V1
	// Berechnung des Kreuzprodukts
	KREUZ.x = +((V1V2.y * V1V3.z) - (V1V2.z * V1V3.y));
	KREUZ.y = ((-1) * ((V1V2.x * V1V3.z)) - (V1V2.z * V1V3.x));
	KREUZ.z = +((V1V2.x * V1V3.y) - (V1V2.y * V1V3.x));
	// Prüfen des Vektors
	Betrag = sqrt( //Länge des Vektors ermitteln
			pow(KREUZ.x, 2.0) + pow(KREUZ.y, 2.0) + pow(KREUZ.z, 2.0));
	// Normalenvektor als Einsvektor abspeichern
	normV.x = KREUZ.x / Betrag;
	normV.y = KREUZ.y / Betrag;
	normV.z = KREUZ.z / Betrag;
}
