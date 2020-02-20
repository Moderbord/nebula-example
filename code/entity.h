#pragma once

#define p_NewEntity() \
	Manager::EntityManager::Instance()->NewEntity();

namespace Entities
{
	// All entities are represented by their ID alone
	typedef unsigned Entity;
}