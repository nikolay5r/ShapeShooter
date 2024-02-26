#pragma once
#include "SFML\Graphics.hpp"
#include "EntityManager.h"

#include <fstream>
#include <sstream>

struct PlayerConfig
{
	float shapeRadius;
	float collisionRadius;
	float speed;
	unsigned fillColorR;
	unsigned fillColorB;
	unsigned fillColorG;
	unsigned outlineColorR;
	unsigned outlineColorB;
	unsigned outlineColorG;
	float outlineThickness;
	unsigned shapeVertices;
};

struct EnemyConfig
{
	float shapeRadius;
	float collisionRadius;
	float minSpeed;
	float maxSpeed;
	unsigned outlineColorR;
	unsigned outlineColorB;
	unsigned outlineColorG;
	float outlineThickness;
	unsigned minShapeVertices;
	unsigned maxShapeVertices;
	unsigned smallLifespan;
	float smallShapeRadius;
	float smallCollisionRadius;
	unsigned spawnInterval;
};

struct BulletConfig
{
	float shapeRadius;
	float collisionRadius;
	float speed;
	unsigned fillColorR;
	unsigned fillColorB;
	unsigned fillColorG;
	unsigned outlineColorR;
	unsigned outlineColorB;
	unsigned outlineColorG;
	float outlineThickness;
	unsigned shapeVertices;
	unsigned lifespan;
	unsigned shootingRate;
	unsigned special;
};

class Game
{
	EntityManager m_entityManager;
	sf::RenderWindow m_window;
	unsigned m_width;
	unsigned m_height;
	sf::Font m_font;
	sf::Text m_text;
	size_t m_currentFrame = 0;
	size_t m_lastSpawnEnemyFrame = 0;
	size_t m_lastSpawnBulletFrame = 0;
	size_t m_lastUseOfSpecialFrame = 0;
	size_t m_score = 0;
	bool m_paused = false;
	bool m_running;
	std::shared_ptr<Entity> m_player;

	PlayerConfig playerConfig;
	EnemyConfig enemyConfig;
	BulletConfig bulletConfig;

	void createPlayer();
	void createEnemy(float x,
		float y,
		unsigned vertices,
		const sf::Vector2f& velocity,
		float speed);
	void createBullet(const sf::Vector2f& destination);
	void createSmallEnemies(std::shared_ptr<Entity> entity);
	void createSpecialWeapon();

	void renderScoreText();
	void userInputDuringUnpaused();
	void calculatePlayerVelocity();

	void setupConfigs(std::ifstream& configFile);
	void setupWindowConfig(std::stringstream& ss);
	void setupFontConfig(std::stringstream& ss);
	void setupPlayerConfig(std::stringstream& ss);
	void setupEnemyConfig(std::stringstream& ss);
	void setupBulletConfig(std::stringstream& ss);

	void collisionSystem();
	void lifespanSystem();
	void spawnEnemySystem();
	void movementSystem();
	void userInputSystem();
	void renderSystem();

public:
	Game(const std::string& configFilePath);

	void run();
};

