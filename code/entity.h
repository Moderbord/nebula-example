#pragma once

#define p_NewEntity() \
	Manager::EntityManager::Instance()->NewEntity();

/*
	Entity
*/
namespace Entities
{
	// All entities are represented by their ID alone
	typedef unsigned Entity;
}