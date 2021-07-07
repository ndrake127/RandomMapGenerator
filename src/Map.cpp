#include "Map.h"

#include <ctime>
#include <cmath>

Map::Map() : 
	m_MapWidth(800),
	m_MapHeight(600)
{
	m_MapImage.create(m_MapWidth, m_MapHeight);
	m_MapTexture.loadFromImage(m_MapImage);
	m_MapSprite.setTexture(m_MapTexture);

	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetSeed(std::time(nullptr));
}

void Map::draw(sf::RenderWindow& window) {
	window.draw(m_MapSprite);
}

void Map::update() {
	m_MapTexture.loadFromImage(m_MapImage);
	m_MapSprite.setTexture(m_MapTexture);
}

void Map::GenerateNoise() {
	for (unsigned int y = 0; y < m_MapHeight; y++) {
		for (unsigned int x = 0; x < m_MapWidth; x++) {
			unsigned char val = (std::round((noise.GetNoise((float)x, (float)y) + 1.0f) / 2.0f)) * 255;
			m_MapImage.setPixel(x, y, sf::Color(val, val, val));
		}
	}

	update();
}