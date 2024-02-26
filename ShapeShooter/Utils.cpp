#include "Utils.h"

#include <math.h>
#include <random>

const unsigned MIN_DISTANCE_BETWEEN_PLAYER_AND_ENEMY = 50;

const float HALF_MAX_DEGREES = 180.f;
const float PI = 3.14f;

sf::Vector2f& Utils::normalize(sf::Vector2f& vec) {
	float dist = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (dist != 0)
	{
		vec.x = vec.x / dist;
		vec.y = vec.y / dist;
	}
	return vec;
}

float Utils::randomFloat(float min, float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

bool Utils::isOverlappingWithPlayer(float x, float y, const Entity& player)
{
	auto playerPosition = player.getTransformComponent()->position();
	float playerX = playerPosition.x;
	float playerY = playerPosition.y;
	float playerR = player.getCollisionComponent()->radius();

	return x < playerX + MIN_DISTANCE_BETWEEN_PLAYER_AND_ENEMY + playerR &&
		x > playerX - MIN_DISTANCE_BETWEEN_PLAYER_AND_ENEMY - playerR &&
		y < playerY + MIN_DISTANCE_BETWEEN_PLAYER_AND_ENEMY + playerR &&
		y > playerY - MIN_DISTANCE_BETWEEN_PLAYER_AND_ENEMY - playerR;

}

sf::Vector2f Utils::findDirectionVector(const sf::Vector2f& current,
	const sf::Vector2f& destination)
{
	return (destination - current);
}

sf::Vector2f Utils::findVelocity(float speed, float angle)
{
	return { cos(angle * PI / HALF_MAX_DEGREES) * speed, sin(angle * PI / HALF_MAX_DEGREES) * speed };
}

bool Utils::areColided(const Entity& lhsEntity, const Entity& rhsEntity)
{
	auto& lhsPosition = lhsEntity.getTransformComponent()->position();
	auto& rhsPosition = rhsEntity.getTransformComponent()->position();
	float destination = sqrt(
		(lhsPosition.x - rhsPosition.x) * (lhsPosition.x - rhsPosition.x) +
		(lhsPosition.y - rhsPosition.y) * (lhsPosition.y - rhsPosition.y)
	);
	float combinedCollisionRadius = 
		lhsEntity.getCollisionComponent()->radius() + rhsEntity.getCollisionComponent()->radius();

	return combinedCollisionRadius >= destination;
}