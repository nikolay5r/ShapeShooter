#pragma once
#include "Entity.h"

#include <vector>
#include <unordered_map>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::unordered_map<EntityType, EntityVector, std::hash<int>> EntityMap;

class EntityManager 
{
private:
	size_t m_totalEntities = 0;
	EntityVector m_entities;
	EntityVector m_entitiesToAdd;
	EntityMap m_entitiesByType;

	void removeInactiveEntities();
public:
	std::shared_ptr<Entity> addEntity(EntityType type);
	const EntityVector& getEntities() const;
	const EntityVector& getEntities(EntityType type) const;
	void update();
};
