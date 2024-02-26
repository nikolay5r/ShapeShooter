#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"

class Utils
{
public:
	static sf::Vector2f& normalize(sf::Vector2f& vec);
	static sf::Vector2f findDirectionVector(const sf::Vector2f& current,
		const sf::Vector2f& destination);
	static sf::Vector2f findVelocity(float speed, float angle);
	static float randomFloat(float min, float max);
	static bool isOverlappingWithPlayer(float x, float y, const Entity& player);
	static bool areColided(const Entity& lhsEntity, const Entity& rhsEntity);
};

