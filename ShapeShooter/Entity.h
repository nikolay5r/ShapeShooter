#pragma once
#include "Components.h"

#include <string>
#include <memory>

class EntityManager;

enum EntityType {
	PLAYER,
	ENEMY,
	BULLET
};

class Entity
{
private:
	bool m_isActive = true;
	size_t m_id;
	EntityType m_type;

	std::shared_ptr<TransformComponent> c_transform;
	std::shared_ptr<LifespanComponent> c_lifeSpan;
	std::shared_ptr<ScoreComponent> c_score;
	std::shared_ptr<InputComponent> c_input;
	std::shared_ptr<ShapeComponet> c_shape;
	std::shared_ptr<CollisionComponent> c_collision;

	Entity(EntityType type, size_t id);
public:

	const std::shared_ptr<const TransformComponent>& getTransformComponent() const;
	const std::shared_ptr<const LifespanComponent>& getLifespanComponent() const;
	const std::shared_ptr<const ScoreComponent>& getScoreComponent() const;
	const std::shared_ptr<const InputComponent>& getInputComponent() const;
	const std::shared_ptr<const ShapeComponet>& getShapeComponent() const;
	const std::shared_ptr<const CollisionComponent>& getCollisionComponent() const;

	const std::shared_ptr<TransformComponent>& getTransformComponent();
	const std::shared_ptr<LifespanComponent>& getLifespanComponent();
	const std::shared_ptr<ScoreComponent>& getScoreComponent();
	const std::shared_ptr<InputComponent>& getInputComponent();
	const std::shared_ptr<ShapeComponet>& getShapeComponent();
	const std::shared_ptr<CollisionComponent>& getCollisionComponent();

	void setTransformComponent(const TransformComponent& transformComponent);
	void setLifespanComponent(const LifespanComponent& lifeSpanComponent);
	void setScoreComponent(const ScoreComponent& scoreComponent);
	void setInputComponent(const InputComponent& inputComponent);
	void setShapeComponent(const ShapeComponet& shapeComponent);
	void setCollisionComponent(const CollisionComponent& collisionComponent);

	bool isActive() const;
	EntityType type() const;
	size_t id() const;
	void destroy();

	friend class EntityManager;
};

