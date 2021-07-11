#include <SFML/Graphics.hpp>
#include "Map.h"

int main() {
	unsigned int width = 1200;
	unsigned int height = 600;

	sf::RenderWindow window(sf::VideoMode(width, height), "Nick's Random Map Generator");
	Map map(width, height);
	map.Generate();

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		map.draw(window);
		window.display();
	}

	return 1;
}