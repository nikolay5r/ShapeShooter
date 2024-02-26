#pragma once
#include "Entity.h"

#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager 
{
private:
	size_t m_totalEntities = 0;
	EntityVector m_entities;
	EntityVector m_entitiesToAdd;
	EntityMap m_entitiesByType;

	void removeInactiveEntities();
public:
	std::shared_ptr<Entity> addEntity(const std::string& tag);
	const EntityVector& getEntities() const;
	const EntityVector& getEntities(const std::string& tag) const;
	void update();
};
