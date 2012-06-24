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

using namespace std;
//using namespace sf;

int main() {

	sf::WindowSettings Settings;
	Settings.DepthBits = 24; // Request a 24 bits depth buffer
	Settings.StencilBits = 8; // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 2; // Request 2 levels of antialiasing
	sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Close,
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

	const sf::Input& Input = App.GetInput();

	sf::Clock Clock;

	while (App.IsOpened()) {

		sf::Event Event;
		while (App.GetEvent(Event)) {
			// Window closed
			if (Event.Type == sf::Event::Closed)
				App.Close();

			// Escape key pressed
			if ((Event.Type == sf::Event::KeyPressed)
					&& (Event.Key.Code == sf::Key::Escape))
				App.Close();

			// Adjust OpenGL viewport on resize event
			if (Event.Type == sf::Event::Resized)
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}

		// Get some input states
		bool LeftButtonDown = Input.IsMouseButtonDown(sf::Mouse::Left);
		unsigned int MouseX = Input.GetMouseX();
		unsigned int MouseY = Input.GetMouseY();

		if (LeftButtonDown == true) {
			cout << "X-Koordinate: " << MouseX << endl;
			cout << "Y-Koordinate: " << MouseY << endl;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);
		glRotatef(Clock.GetElapsedTime() * 50, 1.f, 0.f, 0.f);
		glRotatef(Clock.GetElapsedTime() * 30, 0.f, 1.f, 0.f);
		glRotatef(Clock.GetElapsedTime() * 90, 0.f, 0.f, 1.f);

		glBegin(GL_QUADS);

		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(-50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, -50.f);
		glVertex3f(50.f, -50.f, -50.f);

		glVertex3f(-50.f, -50.f, 50.f);
		glVertex3f(-50.f, 50.f, 50.f);
		glVertex3f(50.f, 50.f, 50.f);
		glVertex3f(50.f, -50.f, 50.f);

		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(-50.f, 50.f, -50.f);
		glVertex3f(-50.f, 50.f, 50.f);
		glVertex3f(-50.f, -50.f, 50.f);

		glVertex3f(50.f, -50.f, -50.f);
		glVertex3f(50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, 50.f);
		glVertex3f(50.f, -50.f, 50.f);

		glVertex3f(-50.f, -50.f, 50.f);
		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(50.f, -50.f, -50.f);
		glVertex3f(50.f, -50.f, 50.f);

		glVertex3f(-50.f, 50.f, 50.f);
		glVertex3f(-50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, -50.f);
		glVertex3f(50.f, 50.f, 50.f);

		glEnd();

		App.Display();
	}
	return EXIT_SUCCESS;

}
