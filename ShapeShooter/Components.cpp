#include "Components.h"

//-------------TransformComponent-------------

TransformComponent::TransformComponent(
	const sf::Vector2f& position,
	const sf::Vector2f& velocity,
	float angle,
	float speed
) 
	: m_position(position), m_velocity(velocity),
	m_angle(angle), m_speed(speed)
{
}

void TransformComponent::setPosition(const sf::Vector2f& position) 
{
	m_position = position;
}

void TransformComponent::setVelocity(const sf::Vector2f& velocity) 
{
	m_velocity = velocity;
}

void TransformComponent::incrementAngle()
{
	m_angle += 1.f;
	if (m_angle >= 360.f)
	{
		m_angle -= 360.f;
	}
}

const sf::Vector2f& TransformComponent::position() const
{
	return m_position;
}

const sf::Vector2f& TransformComponent::velocity() const
{
	return m_velocity;
}

float TransformComponent::angle() const
{
	return m_angle;
}

float TransformComponent::speed() const
{
	return m_speed;
}

//-------------TransformComponent-------------

//---------------InputComponent---------------

bool InputComponent::up() const
{
	return m_up;
}

bool InputComponent::right() const
{
	return m_right;
}

bool InputComponent::down() const
{
	return m_down;
}

bool InputComponent::left() const
{
	return m_left;
}

void InputComponent::pressUp() 
{
	m_up = true;
}

void InputComponent::pressRight() 
{
	m_right = true;
}

void InputComponent::pressDown() 
{
	m_down = true;
}

void InputComponent::pressLeft()
{
	m_left = true;
}

void InputComponent::unpressUp()
{
	m_up = false;
}

void InputComponent::unpressRight()
{
	m_right = false;
}

void InputComponent::unpressDown()
{
	m_down = false;
}

void InputComponent::unpressLeft()
{
	m_left = false;
}

void InputComponent::reset()
{
	m_up = m_right = m_down = m_left = false;
}

//---------------InputComponent---------------

//---------------ShapeComponent---------------

ShapeComponet::ShapeComponet(float radius,
	unsigned pointsCount,
	const sf::Color& color,
	const sf::Color& outline,
	float thickness)
{
	m_shape = sf::CircleShape(radius, pointsCount);
	m_shape.setFillColor(color);
	m_shape.setOrigin(radius, radius);
	m_shape.setOutlineColor(outline);
	m_shape.setOutlineThickness(thickness);
}

void ShapeComponet::setAlphaValue(sf::Uint8 alpha)
{
	const sf::Color& color = m_shape.getFillColor();
	const sf::Color& outline = m_shape.getOutlineColor();

	m_shape.setFillColor(
		{
			color.r,
			color.b,
			color.g,
			alpha
		}
	);
	m_shape.setOutlineColor(
		{
			outline.r,
			outline.b,
			outline.g,
			alpha
		}
	);
}

const sf::CircleShape& ShapeComponet::shape() const
{
	return m_shape;
}

//---------------ShapeComponent---------------

//-------------LifeSpanComponent--------------


LifespanComponent::LifespanComponent(unsigned totalLifeSpanInFrames)
	: m_remaining(totalLifeSpanInFrames), m_total(totalLifeSpanInFrames)
{	
}

void LifespanComponent::decrease()
{
	if (m_remaining)
	{
		m_remaining--;
	}
}

unsigned LifespanComponent::remaining() const
{
	return m_remaining;
}

unsigned LifespanComponent::total() const
{
	return m_total;
}

//-------------LifeSpanComponent--------------

//-------------CollisionComponent-------------

CollisionComponent::CollisionComponent(float collisionRadius)
	: m_radius(collisionRadius)
{
}

float CollisionComponent::radius() const
{
	return m_radius;
}

//-------------CollisionComponent-------------

//---------------ScoreComponent---------------

ScoreComponent::ScoreComponent(size_t score)
	: m_score(score)
{
}

size_t ScoreComponent::score() const
{
	return m_score;
}

//---------------ScoreComponent---------------