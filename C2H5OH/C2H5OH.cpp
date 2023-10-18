#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Title");

	Event ev;
	while (window.isOpen()) {
		while (window.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				window.close();
			}
		}

		window.clear(Color(45, 75, 118, 255));
		window.display();
	}
}