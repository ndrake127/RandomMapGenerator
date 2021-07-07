#include <SFML/Graphics.hpp>
#include "Map.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Nick's Random Map Generator");
	Map map;
	map.GenerateNoise();

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