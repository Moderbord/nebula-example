
#include "application/stdneb.h"
#include "unientitymanager.h"

namespace Uni
{
	//__ImplementClass(Uni::UniEntityManager, 'UEMG', Game::Manager)
	__ImplementSingleton(UniEntityManager)

	UniEntityManager::UniEntityManager() : _numEntities(0), _nextEntity(0)
	{
		__ConstructSingleton;
	}


	UniEntityManager::~UniEntityManager()
	{
		__DestructSingleton;
	}

	UniEntity UniEntityManager::NewEntity()
	{
		// If queue isn't empty
		if (!this->_idQueue.IsEmpty())
		{	
			// pop queue and append it to entity ArrayStack
			UniEntity e = this->_idQueue.Dequeue();
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

	void UniEntityManager::DeleteEntity(const UniEntity& e)
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

	bool UniEntityManager::IsAlive(const UniEntity& e) const
	{
		// Find returns 0 if entity doesn't exist
		return this->_entities.Find(e) != 0;
	}

	SizeT UniEntityManager::GetNumEntities() const
	{
		return this->_numEntities;
	}

}