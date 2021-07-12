#include <SFML/Graphics.hpp>
#include "Map.h"

int main() {
	unsigned int width = 1280;
	unsigned int height = 720;

	sf::RenderWindow window(sf::VideoMode(width, height), "Nick's Random Map Generator");

	Map map(width, height);
	map.Generate();

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					map.Delete();
					map.Generate();
				}
			}
		}

		window.clear();
		map.draw(window);
		window.display();
	}

	return 1;
}