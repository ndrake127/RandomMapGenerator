#include <SFML/Graphics.hpp>
#include "Map.h"

int main() {
	unsigned int width = 1280;
	unsigned int height = 720;

	sf::RenderWindow window(sf::VideoMode(width, height), "Nick's Random Map Generator");


	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		Map map(width, height);
		map.Generate();
		window.clear();
		map.draw(window);
		window.display();

		sf::sleep(sf::seconds(2));
	}

	return 1;
}