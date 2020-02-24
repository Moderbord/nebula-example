#pragma once
#include "core/refcounted.h"
#include "core/singleton.h"
#include "game/manager.h"
#include "util/arraystack.h"
#include "util/queue.h"
#include "entity.h"

/*
	Header file for entity manager
*/
namespace Manager {

	const SizeT MaxNumEntities = 256;

	class EntityManager : public Core::RefCounted
	{
		__DeclareClass(Manager::EntityManager)
		__DeclareSingleton(Manager::EntityManager)


	public:
		// constructor
		EntityManager();
		// destructor
		~EntityManager();
		// new entity
		Entities::Entity NewEntity();
		// delete entity
		void DeleteEntity(const Entities::Entity& e);
		// check if entity is alive
		bool IsAlive(const Entities::Entity& e) const;
		// get number of alive entities
		SizeT GetNumEntities() const;


	private:
		// Number of entities?
		Util::Array<Entities::Entity> _entities;
		Util::Queue<Entities::Entity> _idQueue;
		SizeT _numEntities;
		Entities::Entity _nextEntity;
	};
}