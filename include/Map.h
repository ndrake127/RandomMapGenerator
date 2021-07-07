#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "FastNoiseLite.h"

class Map
{
private:
	struct Pixel {
		unsigned char channel[3];
	};

public:
	Map();

	void draw(sf::RenderWindow& window);
	void update();

	void GenerateNoise();

private:
	const unsigned int m_MapWidth;
	const unsigned int m_MapHeight;

	FastNoiseLite noise;

	sf::Sprite m_MapSprite;
	sf::Texture m_MapTexture;
	sf::Image m_MapImage;
};

