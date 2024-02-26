#pragma once
#include "SFML\Graphics.hpp"
#include <string>

//-------------TransformComponent-------------

class TransformComponent
{
private:
	sf::Vector2f m_position = { 0.f, 0.f };
	sf::Vector2f m_velocity = { 0.f, 0.f };
	float m_angle = 0.f;
	float m_speed = 0.f;

public:
	TransformComponent() = default;
	TransformComponent(const sf::Vector2f& position,
		const sf::Vector2f& velocity,
		float angle,
		float speed);

	void setPosition(const sf::Vector2f& position);
	void setVelocity(const sf::Vector2f& velocity);
	void incrementAngle();

	const sf::Vector2f& position() const;
	const sf::Vector2f& velocity() const;
	float angle() const;
	float speed() const;
};

//-------------TransformComponent-------------

//---------------InputComponent---------------

class InputComponent
{
private:
	bool m_up = false;
	bool m_right = false;
	bool m_down = false;
	bool m_left = false;

public:
	InputComponent() = default;

	bool up() const;
	bool right() const;
	bool down() const;
	bool left() const;

	void pressUp();
	void pressRight();
	void pressDown();
	void pressLeft();

	void unpressUp();
	void unpressRight();
	void unpressDown();
	void unpressLeft();

	void reset();
};

//---------------InputComponent---------------

//---------------ShapeComponent---------------

class ShapeComponet {
private:
	sf::CircleShape m_shape;
public:
	ShapeComponet(float radius, unsigned pointsCount, const sf::Color& color,
		const sf::Color& outline, float thickness);
	
	void setAlphaValue(sf::Uint8 alpha);
	const sf::CircleShape& shape() const;
};

//---------------ShapeComponent---------------

//-------------LifeSpanComponent--------------

class LifespanComponent {
private:
	unsigned m_remaining = 0;
	unsigned m_total = 0;
public:
	LifespanComponent(unsigned totalLifeSpanInFrames);

	void decrease();

	unsigned remaining() const;
	unsigned total() const;
};

//-------------LifeSpanComponent--------------

//-------------CollisionComponent-------------

class CollisionComponent {
private:
	float m_radius = 0;
public:
	CollisionComponent(float collisionRadius);

	float radius() const;
};

//-------------CollisionComponent-------------

//---------------ScoreComponent---------------

class ScoreComponent {
private:
	size_t m_score = 0;
public:
	ScoreComponent(size_t score);

	size_t score() const;
};

//---------------ScoreComponent---------------
