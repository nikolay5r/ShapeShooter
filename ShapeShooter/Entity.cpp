#include "Entity.h"

Entity::Entity(EntityType type, size_t id)
	: m_type(type), m_id(id)
{
}

const std::shared_ptr<const TransformComponent>& Entity::getTransformComponent() const
{
	return c_transform;
}

const std::shared_ptr<const LifespanComponent>& Entity::getLifespanComponent() const
{
	return c_lifeSpan;
}

const std::shared_ptr<const ScoreComponent>& Entity::getScoreComponent() const
{
	return c_score;
}

const std::shared_ptr<const InputComponent>& Entity::getInputComponent() const
{
	return c_input;
}

const std::shared_ptr<const ShapeComponet>& Entity::getShapeComponent() const
{
	return c_shape;
}

const std::shared_ptr<const CollisionComponent>& Entity::getCollisionComponent() const
{
	return c_collision;
}

const std::shared_ptr<TransformComponent>& Entity::getTransformComponent()
{
	return c_transform;
}

const std::shared_ptr<LifespanComponent>& Entity::getLifespanComponent()
{
	return c_lifeSpan;
}

const std::shared_ptr<ScoreComponent>& Entity::getScoreComponent()
{
	return c_score;
}

const std::shared_ptr<InputComponent>& Entity::getInputComponent()
{
	return c_input;
}

const std::shared_ptr<ShapeComponet>& Entity::getShapeComponent()
{
	return c_shape;
}

const std::shared_ptr<CollisionComponent>& Entity::getCollisionComponent()
{
	return c_collision;
}

void Entity::setTransformComponent(const TransformComponent& transformComponent)
{
	if (!c_transform)
	{
		c_transform = std::make_shared<TransformComponent>(transformComponent);
	}
}

void Entity::setLifespanComponent(const LifespanComponent& lifeSpanComponent)
{
	if (!c_lifeSpan)
	{
		c_lifeSpan = std::make_shared<LifespanComponent>(lifeSpanComponent);
	}
}

void Entity::setScoreComponent(const ScoreComponent& scoreComponent)
{
	if (!c_score)
	{
		c_score = std::make_shared<ScoreComponent>(scoreComponent);
	}
}

void Entity::setInputComponent(const InputComponent& inputComponent)
{
	if (!c_input)
	{
		c_input = std::make_shared<InputComponent>(inputComponent);
	}
}

void Entity::setShapeComponent(const ShapeComponet& shapeComponent)
{
	if (!c_shape)
	{
		c_shape = std::make_shared<ShapeComponet>(shapeComponent);
	}
}

void Entity::setCollisionComponent(const CollisionComponent& collisionComponent)
{
	if (!c_collision)
	{
		c_collision = std::make_shared<CollisionComponent>(collisionComponent);
	}
}

bool Entity::isActive() const 
{
	return m_isActive;
}

void Entity::destroy() 
{
	m_isActive = false;
}

EntityType Entity::type() const
{
	return m_type;
}

size_t Entity::id() const
{
	return m_id;
}