/*
 * Folgende Libs dem Linker hinzufügen
 * - sfml-system
 * - sfml-window
 * - sfml-graphics
 *
 * SFML-Tutorial: http://www.sfml-dev.org/tutorials/1.5/window-opengl.php
 *
 */

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

// Listendefinitionen
// 0-9 Hauptlisten
#define SZENE				1 // Gesamte Szene
// 10-999 Unterlisten
#define KOORDINATENSYSTEM	10
#define RASEN				20
#define	HAUS				30
	#define WAENDE			310
	#define DACH			320
	#define DACHGIEBEL		330
	#define	DACHFLAECHEN	340 // Ziegelflächen
	#define SCHORNSTEIN		350
	#define GAUBE			360
	#define HAUSTUER		370
	#define FENSTER			380
#define BAEUME				40
	#define KRONE			410
	#define STAMM			420

const GLfloat offset = 80;

// Vertexe des "Ur"-Würfels
const GLfloat v0[3] = { -35, -35, 50 };
const GLfloat v1[3] = { -35, 26.3, 50 };
const GLfloat v2[3] = { 35, 26.3, 50 };
const GLfloat v3[3] = { 35, -35, 50 };
const GLfloat v4[3] = { 35, -35, -50 };
const GLfloat v5[3] = { 35, 26.3, -50 };
const GLfloat v6[3] = { -35, -35, -50 };
const GLfloat v7[3] = { -35, 26.3, -50 };

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

// Vertexe Haustür
const GLfloat v30[3] = { -35.1, -35, -9 };
const GLfloat v31[3] = { -35.1, -8, -9 };
const GLfloat v32[3] = { -35.1, -8, 9 };
const GLfloat v33[3] = { -35.1, -35, 9 };

// Vertexe Fenster
// Links
const GLfloat fensterl[20][3] = { {-35.1, 7, -42},
								 {-35.1, 25, -42},
								 {-35.1, 25, -17},
								 {-35.1, 7, -17},

								 {-35.1, 7, -12.5},
								 {-35.1, 25, -12.5},
								 {-35.1, 25, 12.5},
								 {-35.1, 7, 12.5},

								 {-35.1, 7, 17},
								 {-35.1, 25, 17},
								 {-35.1, 25, 42},
								 {-35.1, 7, 42},

								 {-35.1, -25, -42},
								 {-35.1, -7, -42},
								 {-35.1, -7, -17},
								 {-35.1, -25, -17},

								 {-35.1, -25, 17},
								 {-35.1, -7, 17},
								 {-35.1, -7, 42},
								 {-35.1, -25, 42} };
// Links
const GLfloat fensterr[24][3] = { {35.1, 7, -42},
								 {35.1, 25, -42},
								 {35.1, 25, -17},
								 {35.1, 7, -17},

								 {35.1, 7, -12.5},
								 {35.1, 25, -12.5},
								 {35.1, 25, 12.5},
								 {35.1, 7, 12.5},

								 {35.1, 7, 17},
								 {35.1, 25, 17},
								 {35.1, 25, 42},
								 {35.1, 7, 42},

								 {35.1, -25, -42},
								 {35.1, -7, -42},
								 {35.1, -7, -17},
								 {35.1, -25, -17},

								 {35.1, -25, -12.5},
								 {35.1, -7, -12.5},
								 {35.1, -7, 12.5},
								 {35.1, -25, 12.5},

								 {35.1, -25, 17},
								 {35.1, -7, 17},
								 {35.1, -7, 42},
								 {35.1, -25, 42} };
// Vorne
const GLfloat fensterv[16][4] = { {-30, 7, 50.1},
								  {-30, 25, 50.1},
								  {-5, 25, 50.1},
								  {-5, 7, 50.1},

								  {5, 7, 50.1},
								  {5, 25, 50.1},
								  {30, 25, 50.1},
								  {30, 7, 50.1},

								  {-30, -25, 50.1},
								  {-30, -7, 50.1},
								  {-5, -7, 50.1},
								  {-5, -25, 50.1},

								  {5, -25, 50.1},
								  {5, -7, 50.1},
								  {30, -7, 50.1},
								  {30, -25, 50.1} };
// Hinten
const GLfloat fensterh[16][4] = { {-30, 7, -50.1},
								  {-30, 25, -50.1},
								  {-5, 25, -50.1},
								  {-5, 7, -50.1},

								  {5, 7, -50.1},
								  {5, 25, -50.1},
								  {30, 25, -50.1},
								  {30, 7, -50.1},

								  {-30, -25, -50.1},
								  {-30, -7, -50.1},
								  {-5, -7, -50.1},
								  {-5, -25, -50.1},

								  {5, -25, -50.1},
								  {5, -7, -50.1},
								  {30, -7, -50.1},
								  {30, -25, -50.1} };

const GLfloat fensterg[6][3] = { {0, 65, 50.1},
								 {28.8, 36.3, 50.1},
								 {-28.8, 36.3, 50.1},

								 {0, 65, -50.1},
								 {28.8, 36.3, -50.1},
								 {-28.8, 36.3, -50.1} };

const GLfloat fenstergf[12][3] = { {-0.5, 63, 50.2},
								   {-0.5, 37.3, 50.2},
								   {-26.3, 37.3, 50.2},

								   {0.5, 63, 50.2},
								   {0.5, 37.3, 50.2},
								   {26.3, 37.3, 50.2},

								   {-0.5, 63, -50.2},
								   {-0.5, 37.3, -50.2},
								   {-26.3, 37.3, -50.2},

								   {0.5, 63, -50.2},
								   {0.5, 37.3, -50.2},
								   {26.3, 37.3, -50.2} };

const GLfloat rasen[4][3] = { {85,-35,-85},
							  {-85,-35,-85},
							  {-85,-35,85},
							  {85,-35,85} };

const GLfloat drempel[8][3] = { {-0.5, 63, 50.2},
								{-0.5, 37.3, 50.2},
								{-26.3, 37.3, 50.2},

								{0.5, 63, 50.2},
								{0.5, 37.3, 50.2},
								{26.3, 37.3, 50.2} };

struct fVektor {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} normV;

void CalcNormal(GLfloat V1[], GLfloat V2[], GLfloat V3[]);

int main() {

	const int width = 1600;
	const int height = 800;

	int i = 0;
	int m;

	struct Viewport {
		int x;
		int y;
		int w;
		int h;
	};

	Viewport view0 = { 0, 0, width / 2 - 1, height - 1 };
	Viewport view1 = { width / 2, 0, width / 2 - 1, height - 1 };

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

	GLfloat giebel = v8[2] - v0[2];

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
		glEnable(GL_TEXTURE_2D);
		glLoadIdentity();
//		glTranslatef(0.f, 0.f, -200.f);
//		glRotatef(rotx, 0.f, 1.f, 0.f);
//		glRotatef(roty, 1.f, 0.f, 0.f);

		// Bilder laden und Mipmap erstellen
	    GLuint Texture = 0;
		sf::Image Image;
		if (!Image.LoadFromFile("textures/roof.jpg"))
			return EXIT_FAILURE;
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, Image.GetWidth(), Image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, Image.GetPixelsPtr());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// Seitenwände zeichnen
		glNewList((GLuint) WAENDE, GL_COMPILE);
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
			glEnd();
		glEndList();

		// Dach zeichnen
		glNewList((GLint) DACHFLAECHEN, GL_COMPILE);
					glBegin(GL_QUADS);
						// Fläche Dach rechts - Gelb
						glColor3f(1, 1, 1);
						glNormal3f(0.706298, 0.707914 , 0);
						glTexCoord2f(0, 0); glVertex3fv(v8);
						glTexCoord2f(0, 1); glVertex3fv(v9);
						glTexCoord2f(1, 1); glVertex3fv(v10);
						glTexCoord2f(1, 0); glVertex3fv(v11);
						// Fläche Dach links - Gelb
						glColor3f(1, 1, 1);
						glNormal3f(-0.706298, 0.707914 , 0);
						glTexCoord2f(0, 0); glVertex3fv(v8);
						glTexCoord2f(0, 1); glVertex3fv(v12);
						glTexCoord2f(1, 1); glVertex3fv(v13);
						glTexCoord2f(1, 0); glVertex3fv(v11);
					glEnd();
		glEndList();

		// Dachgiebel zeichnen
		glNewList((GLuint) DACHGIEBEL, GL_COMPILE);
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
				// Fensterrahmen vorne
				glColor3f(0.373, 0.114, 0.055);
				glNormal3f(0, 0, 1);
				for(m=0; m<3; m++) {
						glVertex3f(fensterg[m][0], fensterg[m][1], fensterg[m][2]);
				}
				// Fensterrahmen hinten
				glColor3f(0.373, 0.114, 0.055);
				glNormal3f(0, 0, -1);
				for(m=3; m<6; m++) {
						glVertex3f(fensterg[m][0], fensterg[m][1], fensterg[m][2]);
				}
				glNormal3f(0, 0, 1);
				glColor3f(0.471, 0.776, 0.992);
				for(m=0; m<6; m++) {
					glVertex3f(fenstergf[m][0], fenstergf[m][1], fenstergf[m][2]);
					m = m+1;
					glVertex3f(fenstergf[m][0], fenstergf[m][1], fenstergf[m][2]);
					m = m+1;
					glVertex3f(fenstergf[m][0], fenstergf[m][1], fenstergf[m][2]);
				}
				glNormal3f(0, 0, -1);
				glColor3f(0.471, 0.776, 0.992);
				for(m=6; m<12; m++) {
					glVertex3f(fenstergf[m][0], fenstergf[m][1], fenstergf[m][2]);
					m = m+1;
					glVertex3f(fenstergf[m][0], fenstergf[m][1], fenstergf[m][2]);
					m = m+1;
					glVertex3f(fenstergf[m][0], fenstergf[m][1], fenstergf[m][2]);
				}
			glEnd();
		glEndList();

		// Schornstein
		glNewList((GLint) SCHORNSTEIN, GL_COMPILE);
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
		glEndList();

		// Gaube
		glNewList((GLint) GAUBE, GL_COMPILE);
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
			// Front, Fenster und Dach der Gaube zeichnen
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
				// Fensterrahmen
				glColor3f(0.373, 0.114, 0.055);
				glNormal3f(-1, 0, 0);
				glVertex3f(v22[0]-0.1, v22[1]+2, v22[2]-2);
				glVertex3f(v25[0]-0.1, v25[1]+2, v25[2]+2);
				glVertex3f(v27[0]-0.1, v27[1]-2, v27[2]+2);
				glVertex3f(v24[0]-0.1, v24[1]-2, v24[2]-2);
				// Fenster
				glColor3f(0.471, 0.776, 0.992);
				glNormal3f(-1, 0, 0);
				glVertex3f(v22[0]-0.2, v22[1]+2.5, v22[2]-2.5);
				glVertex3f(v25[0]-0.2, v25[1]+2.5, v25[2]+2.5);
				glVertex3f(v27[0]-0.2, v27[1]-2.5, v27[2]+2.5);
				glVertex3f(v24[0]-0.2, v24[1]-2.5, v24[2]-2.5);
			glEnd();
		glEndList();

		// Haustür mit Fenster
		glNewList((GLint) HAUSTUER, GL_COMPILE);
			glBegin(GL_QUADS);
				// Tür
				glColor3f(0.373, 0.114, 0.055);
				glNormal3f(-1, 0, 0);
				glVertex3fv(v30);
				glVertex3fv(v31);
				glVertex3fv(v32);
				glVertex3fv(v33);
				// Fenster der Haustür
				glColor3f(0.471, 0.776, 0.992);
				glNormal3f(-1, 0, 0);
				glVertex3f(v30[0]-0.1, v30[1]+4, v30[2]+4);
				glVertex3f(v31[0]-0.1, v31[1]-4, v31[2]+4);
				glVertex3f(v32[0]-0.1, v32[1]-4, v32[2]-4);
				glVertex3f(v33[0]-0.1, v33[1]+4, v33[2]-4);
			glEnd();
		glEndList();

		//Fenster und Fensterrahmen
		glNewList((GLint) FENSTER, GL_COMPILE);
			glBegin(GL_QUADS);
				//Fensterrahmen
				glColor3f(0.373, 0.114, 0.055);
				// links
				glNormal3f(-1, 0, 0);
				for(m=0; m<20; m++) {
						glVertex3f(fensterl[m][0], fensterl[m][1], fensterl[m][2]);
				}
				// rechts
				glNormal3f(1, 0, 0);
				for(m=0; m<24; m++) {
						glVertex3f(fensterr[m][0], fensterr[m][1], fensterr[m][2]);
				}
				// vorne
				glNormal3f(0, 0, 1);
				for(m=0; m<16; m++) {
						glVertex3f(fensterv[m][0], fensterv[m][1], fensterv[m][2]);
				}
				// hinten
				glNormal3f(0, 0, -1);
				for(m=0; m<16; m++) {
						glVertex3f(fensterh[m][0], fensterh[m][1], fensterh[m][2]);
				}
				//Fensterscheiben
				glColor3f(0.471, 0.776, 0.992);
				// links
				glNormal3f(-1, 0, 0);
				for(m=0; m<20; m++) {
					glVertex3f(fensterl[m][0]-0.1, fensterl[m][1]+1, fensterl[m][2]+1);
					m = m+1;
					glVertex3f(fensterl[m][0]-0.1, fensterl[m][1]-1, fensterl[m][2]+1);
					m = m+1;
					glVertex3f(fensterl[m][0]-0.1, fensterl[m][1]-1, fensterl[m][2]-1);
					m = m+1;
					glVertex3f(fensterl[m][0]-0.1, fensterl[m][1]+1, fensterl[m][2]-1);
				}
				// rechts
				glNormal3f(1, 0, 0);
				for(m=0; m<24; m++) {
					glVertex3f(fensterr[m][0]+0.1, fensterr[m][1]+1, fensterr[m][2]+1);
					m = m+1;
					glVertex3f(fensterr[m][0]+0.1, fensterr[m][1]-1, fensterr[m][2]+1);
					m = m+1;
					glVertex3f(fensterr[m][0]+0.1, fensterr[m][1]-1, fensterr[m][2]-1);
					m = m+1;
					glVertex3f(fensterr[m][0]+0.1, fensterr[m][1]+1, fensterr[m][2]-1);
				}
				//vorne
				glNormal3f(0, 0, 1);
				for(m=0; m<16; m++) {
					glVertex3f(fensterv[m][0]+1, fensterv[m][1]+1, fensterv[m][2]+0.1);
					m = m+1;
					glVertex3f(fensterv[m][0]+1, fensterv[m][1]-1, fensterv[m][2]+0.1);
					m = m+1;
					glVertex3f(fensterv[m][0]-1, fensterv[m][1]-1, fensterv[m][2]+0.1);
					m = m+1;
					glVertex3f(fensterv[m][0]-1, fensterv[m][1]+1, fensterv[m][2]+0.1);
				}
				//hinten
				glNormal3f(0, 0, -1);
				for(m=0; m<16; m++) {
					glVertex3f(fensterh[m][0]+1, fensterh[m][1]+1, fensterh[m][2]-0.1);
					m = m+1;
					glVertex3f(fensterh[m][0]+1, fensterh[m][1]-1, fensterh[m][2]-0.1);
					m = m+1;
					glVertex3f(fensterh[m][0]-1, fensterh[m][1]-1, fensterh[m][2]-0.1);
					m = m+1;
					glVertex3f(fensterh[m][0]-1, fensterh[m][1]+1, fensterh[m][2]-0.1);
				}
			glEnd();
		glEndList();

		glNewList((GLint) HAUS, GL_COMPILE);
				glCallList((GLint) WAENDE);
				glCallList((GLint) DACHFLAECHEN);
				glCallList((GLint) DACHGIEBEL);
				glCallList((GLint) SCHORNSTEIN);
				glCallList((GLint) GAUBE);
				glCallList((GLint) HAUSTUER);
				glCallList((GLint) FENSTER);
		glEndList();

		// Kugel
		// http://wiki.delphigl.com/index.php/glRotate
		// http://www.codeworx.org/opengl_tut18.php
		GLUquadricObj *sphere;// Storage For Our Quadratic Objects
		GLUquadricObj *cylinder;
		sphere=gluNewQuadric();// Create A Pointer To The Quadric Object
		cylinder=gluNewQuadric();

		int n;

		glNewList(KRONE, GL_COMPILE);
			gluQuadricNormals(sphere, GLU_SMOOTH);// Create Smooth Normals
			gluQuadricTexture(sphere, GL_TRUE);// Create Texture Coords
			glColor3f(0, 1, 0);
			for(n=0; n<2; n++){
				if(n==0){
					glTranslated(-78, 0, -40);
					gluSphere(sphere,15,40,40);// Kugel zeichnen
					glTranslated(+78, 0, +40);
				}
				else if(n==1){
					glTranslated(-65, -10, -20);
					gluSphere(sphere,10,40,40);
					glTranslated(+65, +10, +20);
				}
			}
		glEndList();

		glNewList(STAMM, GL_COMPILE);
			gluQuadricNormals(sphere, GLU_SMOOTH);// Create Smooth Normals
			gluQuadricTexture(sphere, GL_TRUE);// Create Texture Coords
			glColor3f(0.373, 0.114, 0.055);
			for(n=0; n<2; n++){
				if(n==0){
					glTranslated(-78,0,-40);
					glRotated(90, 1, 0, 0);
					gluCylinder(cylinder,4,4,35,20,20);// Draw Our Cylinder
					glRotated(-90, 1, 0, 0);
					glTranslated(+78, 0, +40);
				}
				else if(n==1){
					glTranslated(-65, -10, -20);
					glRotated(90, 1, 0, 0);
					gluCylinder(cylinder,3,3,25,20,20);// Draw Our Cylinder
					glRotated(-90, 1, 0, 0);
					glTranslated(+65, +10, +20);
				}
			}
		glEndList();

		glNewList((GLint) BAEUME, GL_COMPILE);
			glCallList((GLint) KRONE);
			glCallList((GLint) STAMM);
		glEndList();

		glNewList((GLint) RASEN, GL_COMPILE);
			glBegin(GL_QUADS);
				glColor3f(0, 1, 0);
				glNormal3f(0, 1, 0);
				glVertex3fv(rasen[0]);
				glVertex3fv(rasen[1]);
				glVertex3fv(rasen[2]);
				glVertex3fv(rasen[3]);
			glEnd();
		glEndList();

		glNewList((GLint) SZENE, GL_COMPILE);
			glCallList((GLint) HAUS);
			glCallList((GLint) BAEUME);
			glCallList((GLint) RASEN);
		glEndList();

		for(i=0; i<2; i++){
			if (i == 0) {
					glLoadIdentity();
					glTranslatef(0.f, 0.f, -200.f);
					glRotatef(rotx, 0.f, 1.f, 0.f);
					glRotatef(roty, 1.f, 0.f, 0.f);
					glViewport(view0.x, view0.y, view0.w, view0.h); // linker Viewport
				}
			else if (i == 1) {
					glLoadIdentity();
					glTranslatef(0.f, 0.f, -200.f);
					glRotatef(rotx, 0.f, 1.f, 0.f);
					glRotatef(roty, 1.f, 0.f, 0.f);
					glViewport(view1.x, view1.y, view1.w, view1.h); // rechter Viewport
				}
			glCallList((GLint) SZENE);
		}

		App.Display();

	}
	return EXIT_SUCCESS;
}

// Fkt. aus Markt&Technik "Jetzt lerne ich OpenGL"
// Fkt. zur Berechnung des Normalenvektors
// Folgend der Fkt. Aufruf. Bei Bedarf in Main einzufügen:
//		// Berechnung des Normalenvektors
//		// Achtung! Die Vertexe dürfen dann kein const sein!
//		CalcNormal(v8, v12, v13);
//		cout << "Norm.-X: " << normV.x << endl;
//		cout << "Norm.-Y: " << normV.y << endl;
//		cout << "Norm.-Z: " << normV.z << endl;
//		cout << endl << endl;
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
