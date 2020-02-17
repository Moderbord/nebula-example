#pragma once
#include "application/stdneb.h"
#include "unientitymanager.h"

namespace Uni
{
	//__ImplementClass(Uni::EntityManager, 'UEMG', Game::Manager)
	__ImplementSingleton(EntityManager)

	EntityManager::EntityManager() : _numEntities(0), _nextEntity(0)
	{
		__ConstructSingleton;
	}


	EntityManager::~EntityManager()
	{
		__DestructSingleton;
	}

	Entity EntityManager::NewEntity()
	{
		// If queue isn't empty
		if (!this->_idQueue.IsEmpty())
		{	
			// pop queue and append it to entity ArrayStack
			Entity e = this->_idQueue.Dequeue();
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

	void EntityManager::DeleteEntity(const Entity& e)
	{	
		// Get index from ArrayStack
		IndexT index = this->_entities.FindIndex(e);
		// check if invalid index
		if (index != -1)
		{
			// Remove entity 
			this->_entities.EraseIndexSwap(index);
			this->_numEntities--;
			// Add removed entity id to queue
			this->_idQueue.Enqueue(e);
		}
	}

	bool EntityManager::IsAlive(const Entity& e) const
	{
		// Returns 0 if entity doesn't exist
		return this->_entities.Find(e) != 0;
	}

	SizeT EntityManager::GetNumEntities() const
	{
		return this->_numEntities;
	}

}