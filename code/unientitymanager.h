#pragma once
//#include "core/refcounted.h"
#include "core/singleton.h"
#include "game/manager.h"
#include "util/arraystack.h"
#include "util/queue.h"
#include "unientity.h"

namespace Uni {

	const SizeT MaxNumEntities = 256;

	class EntityManager
	{
		__DeclareSingleton(EntityManager)


	public:
		// constructor
		EntityManager();
		// destructor
		~EntityManager();
		// new entity
		Entity NewEntity();
		// delete entity
		void DeleteEntity(const Entity& e);
		// check if entity is alive
		bool IsAlive(const Entity& e) const;
		// get number of alive entities
		SizeT GetNumEntities() const;


	private:
		// Number of entities?
		Util::ArrayStack<Entity, MaxNumEntities * sizeof(Entity)> _entities;
		Util::Queue<Entity> _idQueue;
		SizeT _numEntities;
		Entity _nextEntity;
		


	};
}