#include "EntityManager.h"

void EntityManager::removeInactiveEntities()
{
	for (size_t i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->m_isActive)
		{
			m_entities.erase(m_entities.begin() + i);
		}
	}

	for (auto& entry : m_entitiesByType)
	{
		for (size_t i = 0; i < entry.second.size(); i++)
		{
			if (!entry.second[i]->m_isActive)
			{
				entry.second.erase(entry.second.begin() + i);
			}
		}
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(EntityType type)
{
	m_entitiesToAdd.push_back(std::shared_ptr<Entity>(new Entity(type, m_totalEntities)));
	return m_entitiesToAdd.back();
}

const EntityVector& EntityManager::getEntities() const
{
	return m_entities;
}

const EntityVector& EntityManager::getEntities(EntityType type) const
{
	auto it = m_entitiesByType.find(type);
	if (it != m_entitiesByType.end()) {
		return it->second;
	}

	return EntityVector();
}

void EntityManager::update()
{
	for (auto e: m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entitiesByType[e->m_type].push_back(e);
	}

	m_entitiesToAdd.clear();

	removeInactiveEntities();
}