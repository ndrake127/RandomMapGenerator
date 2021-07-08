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

	void Generate();

private:
	// call these from Generate()
	void GenerateNoise();
	void ApplyThreshold();
	void AssignIslandGroups();
	void TrimEdgeIslands();
	void RandomIslandPrune();

	// dont call these from Generate(), let other functions do it for you
	void RecursiveIslandAssignment(unsigned int x, unsigned int y);

	const unsigned int m_MapWidth;
	const unsigned int m_MapHeight;

	FastNoiseLite noise;

	sf::Sprite m_MapSprite;
	sf::Texture m_MapTexture;

	sf::Image m_MapImage;
	std::vector<std::vector<int> > m_IslandGraph;
	std::vector<int> m_IslandList;
	unsigned int m_IslandCount = 0;
};

