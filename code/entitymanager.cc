#pragma once
#include "application/stdneb.h"
#include "entitymanager.h"


/*
	Entity manager. Handles creation, deletion and recycling of entity Id's

	TODO not much
*/
namespace Manager
{
	__ImplementClass(Manager::EntityManager, 'EMGR', Core::RefCounted)
	__ImplementSingleton(EntityManager)

	EntityManager::EntityManager() : _numEntities(0), _nextEntity(0)
	{
		__ConstructSingleton;
		this->_entities.Reserve(MaxNumEntities);
	}


	EntityManager::~EntityManager()
	{
		this->_entities.Clear();
		__DestructSingleton;
	}

	Entities::Entity EntityManager::NewEntity()
	{
		// If queue isn't empty
		if (!this->_idQueue.IsEmpty())
		{	
			// pop queue and append it to entity Array
			Entities::Entity e = this->_idQueue.Dequeue();
			this->_entities.Append(e);
			this->_numEntities++;
			return e;
		}

		// Increment
		++this->_nextEntity;
		// While id is occupied
		while (IsAlive(this->_nextEntity))
		{
			// increment
			++this->_nextEntity;
		}
		// append
		this->_entities.Append(this->_nextEntity);
		this->_numEntities++;
		// return ID of created entity
		return this->_nextEntity;
	}

	void EntityManager::DeleteEntity(const Entities::Entity& e)
	{	
		// Get index from Array
		IndexT index = this->_entities.FindIndex(e);
		// check if invalid index
		if (index != InvalidIndex)
		{
			// Remove entity 
			this->_entities.EraseIndexSwap(index);
			this->_numEntities--;
			// Add removed entity id to queue
			this->_idQueue.Enqueue(e);
		}
	}

	bool EntityManager::IsAlive(const Entities::Entity& e) const
	{
		if (e > this->_numEntities)
			return false;
		// TODO check queue instead
		// Returns 0 if entity doesn't exist
		return this->_entities.Find(e) != 0;
	}

	SizeT EntityManager::GetNumEntities() const
	{
		return this->_numEntities;
	}

}