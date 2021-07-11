#include "Map.h"

#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>

Map::Map() : 
	m_MapWidth(800),
	m_MapHeight(600)
{
	m_IslandGraph = std::vector<std::vector<int> >(m_MapWidth, std::vector<int>(m_MapHeight, -1));

	m_MapImage.create(m_MapWidth, m_MapHeight);
	m_MapTexture.loadFromImage(m_MapImage);
	m_MapSprite.setTexture(m_MapTexture);

	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	noise.SetSeed(std::time(nullptr));

	m_IslandColor = sf::Color(37, 116, 54);
	m_OceanColor = sf::Color(49, 73, 184);
}

void Map::draw(sf::RenderWindow& window) {
	window.draw(m_MapSprite);
}

void Map::update() {
	m_MapTexture.loadFromImage(m_MapImage);
	m_MapSprite.setTexture(m_MapTexture);
}

void Map::RecursiveIslandAssignment(unsigned int x, unsigned int y) {
	if (m_IslandGraph[x][y] == -1 && m_MapImage.getPixel(x, y) == sf::Color::White) {
		// Assigment
		m_IslandGraph[x][y] = m_IslandCount;

		// Recursive calls
		if (x >= 1)				  RecursiveIslandAssignment(x - 1, y);
		if (x <= m_MapWidth - 2)  RecursiveIslandAssignment(x + 1, y);
		if (y >= 1)				  RecursiveIslandAssignment(x, y - 1);
		if (y <= m_MapHeight - 2) RecursiveIslandAssignment(x, y + 1);
	}
	else {
		// Base case
		return;
	}
}

void Map::Generate() {
	GenerateNoise();
	ApplyThreshold();
	AssignIslandGroups();
	TrimEdgeIslands();
	RandomIslandPrune();
	ColorIslands();

	update();
}

void Map::GenerateNoise() {
	for (unsigned int y = 0; y < m_MapHeight; y++) {
		for (unsigned int x = 0; x < m_MapWidth; x++) {
			unsigned char val = (noise.GetNoise((float)x, (float)y) + 1.0f) / 2.0f * 255.0f;
			m_MapImage.setPixel(x, y, sf::Color(val, val, val));
		}
	}
}

void Map::ApplyThreshold() {
	float threshold = 0.6f;

	for (unsigned int y = 0; y < m_MapHeight; y++) {
		for (unsigned int x = 0; x < m_MapWidth; x++) {
			sf::Color val = (m_MapImage.getPixel(x, y).r > threshold * 255.0f) ? sf::Color::White : sf::Color::Black;
			m_MapImage.setPixel(x, y, val);
		}
	}
}

// This function steps through every pixel in the map. If it encounters a white pixel that has not been assigned to an island group, then
// it will temporarily recursively assign all white neighbors to a number unique to that cluster of white pixels. When no white pixels are left,
// it will continue the original iteration where it began the recursive search and ignore the pixels at just assigned.
void Map::AssignIslandGroups() {
	for (unsigned int y = 0; y < m_MapHeight; y++) {
		for (unsigned int x = 0; x < m_MapWidth; x++) {
			if (m_IslandGraph[x][y] == -1 && m_MapImage.getPixel(x, y) == sf::Color::White) {
				// new island found, begin recursive assignment
				RecursiveIslandAssignment(x, y);
				m_IslandList.push_back(m_IslandCount);
				m_IslandCount++;
			}
		}
	}
}

void Map::TrimEdgeIslands() {
	for (unsigned int x = 0; x < m_MapWidth; x++) {
		m_IslandList.erase(std::remove(m_IslandList.begin(), m_IslandList.end(), m_IslandGraph[x][0]), m_IslandList.end());
		m_IslandList.erase(std::remove(m_IslandList.begin(), m_IslandList.end(), m_IslandGraph[x][m_MapHeight-1]), m_IslandList.end());
	}
	for (unsigned int y = 1; y < m_MapHeight-1; y++) {
		m_IslandList.erase(std::remove(m_IslandList.begin(), m_IslandList.end(), m_IslandGraph[0][y]), m_IslandList.end());
		m_IslandList.erase(std::remove(m_IslandList.begin(), m_IslandList.end(), m_IslandGraph[m_MapWidth-1][y]), m_IslandList.end());
	}

	for (auto i : m_IslandList) {
		std::cout << i << ' ';
	}

	for (unsigned int y = 0; y < m_MapHeight; y++) {
		for (unsigned int x = 0; x < m_MapWidth; x++) {
			if (m_IslandGraph[x][y] != -1 && std::find(m_IslandList.begin(), m_IslandList.end(), m_IslandGraph[x][y]) == m_IslandList.end()) {
				m_IslandGraph[x][y] = -1;
				m_MapImage.setPixel(x, y, sf::Color::Black);
			}
		}
	}
}

void Map::RandomIslandPrune() {
	unsigned int finalIslandCount = 8;
	finalIslandCount = (finalIslandCount <= m_IslandCount) ? finalIslandCount : m_IslandCount;
	std::vector<int> preservedIslands(finalIslandCount, -1);

	std::vector<int> islandList = m_IslandList;
	std::shuffle(islandList.begin(), islandList.end(), std::default_random_engine(std::time(nullptr)));

	for (unsigned int i = 0; i < finalIslandCount; i++) {
		preservedIslands[i] = islandList[i];
		std::cout << preservedIslands[i] << '\n';
	}

	for (unsigned int y = 0; y < m_MapHeight; y++) {
		for (unsigned int x = 0; x < m_MapWidth; x++) {
			if (m_IslandGraph[x][y] != -1 && std::find(preservedIslands.begin(), preservedIslands.end(), m_IslandGraph[x][y]) == preservedIslands.end()) {
				m_IslandGraph[x][y] = -1;
				m_MapImage.setPixel(x, y, sf::Color::Black);
			}
		}
	}
}

void Map::ColorIslands() {
	for (unsigned int y = 0; y < m_MapHeight; y++) {
		for (unsigned int x = 0; x < m_MapWidth; x++) {
			if (m_IslandGraph[x][y] != -1) {
				m_MapImage.setPixel(x, y, m_IslandColor);
			}
			else {
				m_MapImage.setPixel(x, y, m_OceanColor);
			}
		}
	}
}