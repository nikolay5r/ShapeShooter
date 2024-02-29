#include "Game.h"
#include "FileNotFoundException.h"
#include "Entity.h"
#include "Utils.h"

#include <sstream>
#include <iostream>

const std::string WINDOW_KEYWORD = "Window";
const std::string FONT_KEYWORD = "Font";
const std::string PLAYER_KEYWORD = "Player";
const std::string ENEMY_KEYWORD = "Enemy";
const std::string BULLET_KEYWORD = "Bullet";

const unsigned SCORE_MULTIPLIER = 100;
const unsigned MAX_ALPHA_VALUE = 255;
const unsigned MAX_COLOR_VALUE = 255;
const float MAX_DEGREES = 360;

const std::string GAME_TITLE = "ShapeShooter";

const size_t BUFFER_SIZE = 1024;

const unsigned SPECIAL_BULLETS_FIRED = 8;

Game::Game(const std::string& configFilePath)
{
	std::ifstream configFile(configFilePath);
	if (!configFile.is_open())
	{
		throw FileNotFoundException("Cannot open configuration file with path: " + configFilePath + ".");
	}
	setupConfigs(configFile);
	configFile.close();

	m_running = true;
	createPlayer();
}

void Game::createPlayer()
{
	auto player = m_entityManager.addEntity(EntityType::PLAYER);

	player->setCollisionComponent(CollisionComponent(playerConfig.collisionRadius));
	player->setInputComponent(InputComponent());

	player->setShapeComponent(
		ShapeComponet(
			playerConfig.shapeRadius,
			playerConfig.shapeVertices,
			sf::Color(playerConfig.fillColorR, playerConfig.fillColorG, playerConfig.fillColorB),
			sf::Color(playerConfig.outlineColorR, playerConfig.outlineColorG, playerConfig.outlineColorB),
			playerConfig.outlineThickness
		)
	);

	player->setTransformComponent(
		TransformComponent(
			sf::Vector2f(m_width / 2.f, m_height / 2.f),
			sf::Vector2f(0.f, 0.f),
			0.f,
			playerConfig.speed
		)
	);

	m_player = player;
}

void Game::setupConfigs(std::ifstream& configFile)
{
	char buffer[BUFFER_SIZE];
	std::stringstream ss;

	while (!configFile.eof())
	{
		configFile.getline(buffer, BUFFER_SIZE);
		ss << buffer;

		std::string keyword;
		ss >> keyword;

		if (ss.eof())
		{
			break;
		}

		if (keyword == WINDOW_KEYWORD)
		{
			setupWindowConfig(ss);
		}
		else if (keyword == FONT_KEYWORD)
		{
			setupFontConfig(ss);
		}
		else if (keyword == PLAYER_KEYWORD)
		{
			setupPlayerConfig(ss);
		}
		else if (keyword == ENEMY_KEYWORD)
		{
			setupEnemyConfig(ss);
		}
		else if (keyword == BULLET_KEYWORD)
		{
			setupBulletConfig(ss);
		}

		ss.clear();
	}
}

void Game::setupWindowConfig(std::stringstream& ss)
{
	unsigned width, height, frames, fullscrenOption;
	ss >> width >> height >> frames >> fullscrenOption;

	m_window.create(sf::VideoMode(width, height), GAME_TITLE);
	m_window.setFramerateLimit(frames);
	
	m_width = width;
	m_height = height;
}

void Game::setupFontConfig(std::stringstream& ss)
{
	std::string fontFilePath;
	unsigned size, r, b, g;
	ss >> fontFilePath >> size >> r >> g >> b;

	if (!m_font.loadFromFile(fontFilePath))
	{
		throw FileNotFoundException("Font file not found. Check if file path is correct: " + fontFilePath + ".");
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(size);
	m_text.setFillColor(sf::Color(r, g, b));
}

void Game::setupPlayerConfig(std::stringstream& ss)
{
	ss >> playerConfig.shapeRadius
		>> playerConfig.collisionRadius
		>> playerConfig.speed
		>> playerConfig.fillColorR
		>> playerConfig.fillColorB
		>> playerConfig.fillColorG
		>> playerConfig.outlineColorR
		>> playerConfig.outlineColorB
		>> playerConfig.outlineColorG
		>> playerConfig.outlineThickness
		>> playerConfig.shapeVertices;
}

void Game::setupEnemyConfig(std::stringstream& ss)
{
	ss >> enemyConfig.shapeRadius
		>> enemyConfig.collisionRadius
		>> enemyConfig.minSpeed
		>> enemyConfig.maxSpeed
		>> enemyConfig.outlineColorR
		>> enemyConfig.outlineColorB
		>> enemyConfig.outlineColorG
		>> enemyConfig.outlineThickness
		>> enemyConfig.minShapeVertices
		>> enemyConfig.maxShapeVertices
		>> enemyConfig.smallLifespan
		>> enemyConfig.smallShapeRadius
		>> enemyConfig.smallCollisionRadius
		>> enemyConfig.spawnInterval;
}

void Game::setupBulletConfig(std::stringstream& ss)
{
	ss >> bulletConfig.shapeRadius
		>> bulletConfig.collisionRadius
		>> bulletConfig.speed
		>> bulletConfig.fillColorR
		>> bulletConfig.fillColorB
		>> bulletConfig.fillColorG
		>> bulletConfig.outlineColorR
		>> bulletConfig.outlineColorB
		>> bulletConfig.outlineColorG
		>> bulletConfig.outlineThickness
		>> bulletConfig.shapeVertices
		>> bulletConfig.lifespan
		>> bulletConfig.shootingRate
		>> bulletConfig.special;
}

void Game::createEnemy(float x,
	float y,
	unsigned vertices,
	const sf::Vector2f& velocity,
	float speed)
{
	auto enemy = m_entityManager.addEntity(EntityType::ENEMY);
	enemy->setCollisionComponent(CollisionComponent(enemyConfig.collisionRadius));
	enemy->setShapeComponent(
		ShapeComponet(
			enemyConfig.shapeRadius,
			vertices,
			sf::Color(
				rand() % (MAX_COLOR_VALUE + 1),
				rand() % (MAX_COLOR_VALUE + 1),
				rand() % (MAX_COLOR_VALUE + 1)
			),
			sf::Color(enemyConfig.outlineColorR, enemyConfig.outlineColorG, enemyConfig.outlineColorB),
			enemyConfig.outlineThickness
		)
	);
	enemy->setScoreComponent(ScoreComponent(vertices * SCORE_MULTIPLIER));
	enemy->setTransformComponent(
		TransformComponent(sf::Vector2f(x, y), velocity, 0.f, speed)
	);
}

void Game::spawnEnemySystem()
{
	if (m_currentFrame % enemyConfig.spawnInterval)
	{
		return;
	}

	srand(time(nullptr));
	float speed = Utils::randomFloat(enemyConfig.minSpeed, enemyConfig.maxSpeed);
	unsigned vertices = enemyConfig.minShapeVertices + 
		(rand() % enemyConfig.maxShapeVertices - enemyConfig.minShapeVertices);
	float xPos = Utils::randomFloat(0 + enemyConfig.shapeRadius, m_width - enemyConfig.shapeRadius);
	float yPos = Utils::randomFloat(0 + enemyConfig.shapeRadius, m_height - enemyConfig.shapeRadius);

	while (Utils::isOverlappingWithPlayer(xPos, yPos, *m_player))
	{
		xPos = Utils::randomFloat(0 + enemyConfig.shapeRadius, m_width - enemyConfig.shapeRadius);
		yPos = Utils::randomFloat(0 + enemyConfig.shapeRadius, m_height - enemyConfig.shapeRadius);
	}

	createEnemy(xPos, yPos, vertices, Utils::findVelocity(speed, Utils::randomFloat(0, MAX_DEGREES)), speed);
	m_lastSpawnEnemyFrame = m_currentFrame;
}

void Game::renderScoreText()
{
	std::stringstream ss;
	ss << "Score: " << m_score;

	m_text.setString(ss.str());
	m_text.setPosition(0, 0);
	m_window.draw(m_text);
}

void Game::createSmallEnemies(std::shared_ptr<Entity> entity)
{
	if (entity->getLifespanComponent() || (!entity->getTransformComponent() && !entity->getShapeComponent()))
	{
		return;
	}

	unsigned vertices = entity->getShapeComponent()->shape().getPointCount();
	float degreeToSpawn = MAX_DEGREES / vertices;
	float startDegree = 0;
	for (size_t i = 0; i < vertices; i++, startDegree += degreeToSpawn)
	{
		auto smallEnemy = m_entityManager.addEntity(EntityType::ENEMY);
		smallEnemy->setCollisionComponent(CollisionComponent(enemyConfig.smallCollisionRadius));
		smallEnemy->setShapeComponent(
			ShapeComponet(
				enemyConfig.smallShapeRadius, vertices, entity->getShapeComponent()->shape().getFillColor(),
				entity->getShapeComponent()->shape().getOutlineColor(), enemyConfig.outlineThickness
			)
		);
		smallEnemy->setScoreComponent(ScoreComponent(vertices * SCORE_MULTIPLIER * 2));
		smallEnemy->setTransformComponent(
			TransformComponent(entity->getTransformComponent()->position(),
				Utils::findVelocity(enemyConfig.minSpeed, startDegree),
				0.f,
				enemyConfig.minSpeed)
		);
		smallEnemy->setLifespanComponent(LifespanComponent(enemyConfig.smallLifespan));
	}
}

void Game::renderSystem()
{
	auto entities = m_entityManager.getEntities();

	m_window.clear();

	for (auto& e: entities)
	{
		if (e->getShapeComponent() && e->getTransformComponent())
		{
			auto shape = e->getShapeComponent()->shape();
			shape.setRotation(e->getTransformComponent()->angle());
			e->getTransformComponent()->incrementAngle();
			shape.setPosition(e->getTransformComponent()->position());
			m_window.draw(shape);
		}
	}
	renderScoreText();

	m_window.display();
}

static void setBulletComponents(std::shared_ptr<Entity> bullet,
	const sf::Vector2f& position,
	const BulletConfig& bulletConfig,
	const sf::Vector2f& velocity)
{
	bullet->setCollisionComponent(CollisionComponent(bulletConfig.collisionRadius));
	bullet->setLifespanComponent(LifespanComponent(bulletConfig.lifespan));
	bullet->setShapeComponent(
		ShapeComponet(
			bulletConfig.shapeRadius,
			bulletConfig.shapeVertices,
			sf::Color(bulletConfig.fillColorR, bulletConfig.fillColorG, bulletConfig.fillColorB),
			sf::Color(bulletConfig.outlineColorR, bulletConfig.outlineColorG, bulletConfig.outlineColorB),
			bulletConfig.outlineThickness
		)
	);

	bullet->setTransformComponent(
		TransformComponent(
			position,
			velocity,
			0.f,
			bulletConfig.speed
		)
	);
}

void Game::createBullet(const sf::Vector2f& destination)
{
	if (m_currentFrame - m_lastSpawnBulletFrame < bulletConfig.shootingRate)
	{
		return;
	}

	auto spawnPosition = m_player->getTransformComponent()->position();
	sf::Vector2f direction = Utils::findDirectionVector(spawnPosition, destination);
	Utils::normalize(direction);

	setBulletComponents(
		m_entityManager.addEntity(EntityType::BULLET),
		spawnPosition,
		bulletConfig,
		sf::Vector2f(bulletConfig.speed * direction.x, bulletConfig.speed * direction.y));

	m_lastSpawnBulletFrame = m_currentFrame;
}

void Game::userInputDuringUnpaused() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_player->getInputComponent()->pressUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player->getInputComponent()->pressRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_player->getInputComponent()->pressDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player->getInputComponent()->pressLeft();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		createBullet(sf::Vector2f(sf::Mouse::getPosition(m_window)));
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		createSpecialWeapon();
	}
}

void Game::calculatePlayerVelocity()
{
	auto cShape = m_player->getShapeComponent();
	auto cInput = m_player->getInputComponent();
	auto cTransform = m_player->getTransformComponent();

	if (cShape && cInput && cTransform)
	{
		float distX = cInput->right() && cShape->shape().getRadius() + cTransform->position().x < m_width ?
			cTransform->position().x + playerConfig.speed :
			cInput->left() && cTransform->position().x - cShape->shape().getRadius() > 0 ?
				cTransform->position().x - playerConfig.speed :
				cTransform->position().x;
		float distY = cInput->down() && cShape->shape().getRadius() + cTransform->position().y < m_height ?
			cTransform->position().y + playerConfig.speed :
			cInput->up() && cTransform->position().y - cShape->shape().getRadius() > 0 ?
				cTransform->position().y - playerConfig.speed :
				cTransform->position().y;

		sf::Vector2f direction = Utils::findDirectionVector(
			cTransform->position(),
			sf::Vector2f(distX, distY)
		);
		Utils::normalize(direction);

		cTransform->setVelocity(
			sf::Vector2f(direction.x * playerConfig.speed, direction.y * playerConfig.speed)
		);
		cInput->reset();
	}
}

void Game::movementSystem()
{
	calculatePlayerVelocity();

	auto entities = m_entityManager.getEntities();
	for (auto& e : entities)
	{
		auto cShape = e->getShapeComponent();
		auto cTransform = e->getTransformComponent();
		if (cShape && cTransform)
		{
			if (e->type() == EntityType::ENEMY)
			{
				sf::Vector2f futurePosition = cTransform->position() + cTransform->velocity();
				sf::Vector2f currentVelocity = cTransform->velocity();
				if (futurePosition.x + cShape->shape().getRadius() >= m_width ||
					futurePosition.x - cShape->shape().getRadius() < 0)
				{
					cTransform->setVelocity(sf::Vector2f(-currentVelocity.x, currentVelocity.y));
				}
				if (futurePosition.y + cShape->shape().getRadius() >= m_height ||
					futurePosition.y - cShape->shape().getRadius() < 0)
				{
					cTransform->setVelocity(sf::Vector2f(currentVelocity.x, -currentVelocity.y));
				}
			}

			cTransform->setPosition(cTransform->position() + cTransform->velocity());
		}
	}
}

void Game::userInputSystem()
{
	if (!m_player->getInputComponent())
	{
		return;
	}

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			m_window.close();
			m_running = false;
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				m_paused = !m_paused;
				std::cout << "Game paused: " << m_paused << std::endl;
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
				m_running = false;
			}
		}	
	}

	if (!m_paused)
	{
		userInputDuringUnpaused();
	}
}

void Game::collisionSystem()
{
	auto bullets = m_entityManager.getEntities(EntityType::BULLET);
	auto enemies = m_entityManager.getEntities(EntityType::ENEMY);

	for (auto& enemy : enemies)
	{
		if (enemy->getCollisionComponent() &&
			enemy->getTransformComponent())
		{
			for (auto& bullet : bullets)
			{
				if (bullet->getCollisionComponent() &&
					bullet->getTransformComponent())
				{
					if (Utils::areColided(*bullet, *enemy))
					{
						createSmallEnemies(enemy);
						enemy->destroy();
						bullet->destroy();
						m_score += enemy->getScoreComponent()->score();
					}
				}
			}

			if (Utils::areColided(*m_player, *enemy) && enemy->isActive())
			{
				createSmallEnemies(enemy);
				enemy->destroy();
				m_score = 0;
			}
		}
	}
}

void Game::createSpecialWeapon()
{
	if (m_currentFrame - m_lastUseOfSpecialFrame < bulletConfig.special ||
		!m_player->getTransformComponent())
	{
		return;
	}

	float startAngle = 0.f;
	float decrease = MAX_DEGREES / SPECIAL_BULLETS_FIRED;

	for (size_t i = 0; i < SPECIAL_BULLETS_FIRED; i++, startAngle += decrease)
	{
		setBulletComponents(
			m_entityManager.addEntity(EntityType::BULLET),
			m_player->getTransformComponent()->position(),
			bulletConfig,
			Utils::findVelocity(bulletConfig.speed, startAngle)
		);
	}

	m_lastUseOfSpecialFrame = m_currentFrame;
}

void Game::lifespanSystem()
{
	auto entities = m_entityManager.getEntities();
	for (auto& e: entities)
	{
		auto cLifespan = e->getLifespanComponent();
		auto cShape = e->getShapeComponent();
		if (cShape && cLifespan)
		{
			float percentage = cLifespan->remaining() / (cLifespan->total() * 1.f);
			if (percentage <= 0.1)
			{
				e->destroy();
				continue;
			}

			float newAlphaValue = MAX_ALPHA_VALUE * percentage;

			cShape->setAlphaValue(
				newAlphaValue
			);
			cLifespan->decrease();
		}
	}
}

void Game::run()
{
	while (m_running)
	{
		m_entityManager.update();

		sf::Event event;
		
		renderSystem();
		userInputSystem();

		if (!m_paused)
		{
			spawnEnemySystem();
			movementSystem();
			collisionSystem();
			lifespanSystem();

			m_currentFrame++;
		}

	}
}