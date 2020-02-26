#pragma once
#include "componentinterface.h"


/*
	Component interface which all components derive from

	TODO change the way to search for entities and their component values?
*/
namespace Component
{

ComponentInterface::ComponentInterface()
	: _nextInstanceID(0), _numInstances(0)
{

}

ComponentInterface::~ComponentInterface()
{

}

InstanceId ComponentInterface::RegisterEntity(const Entities::Entity& e)
{
	// check if entity already isn't registered
	n_assert(!this->_instanceMap.Contains(e));

	// If queue isn't empty
	if (!this->_instanceQueue.IsEmpty())
	{
		// pull from queue
		InstanceId id = this->_instanceQueue.Dequeue();
		// map entity with queued instance
		this->_instanceMap.Add(e, id);
		this->_numInstances++;
		// reset queued instance data
		this->OnReset(e, id);
		return id;
	}

	// TODO may go out of maximum allowed entries
	// assign and increment
	InstanceId id = this->_nextInstanceID++;
	// add to map
	this->_instanceMap.Add(e, id);
	// increment num instances
	this->_numInstances++;
	// initiates components variabels
	this->OnRegister(e);
	return id;
}

void ComponentInterface::DeregisterEntity(const Entities::Entity& e)
{
	n_assert(this->_instanceMap.Contains(e));
	// TODO this will leave an unused "gap" in memory until new entity fills it
	this->_instanceQueue.Enqueue(this->_instanceMap[e]);
	this->_instanceMap.Erase(e);
	this->_numInstances--;
}

bool ComponentInterface::IsRegistered(const Entities::Entity& e)
{
	return this->_instanceMap.Contains(e);
}

InstanceId ComponentInterface::GetInstanceID(const Entities::Entity& e)
{
	n_assert(this->_instanceMap.Contains(e));
	return this->_instanceMap[e];
}

const Entities::Entity ComponentInterface::GetOwner(const InstanceId& id)
{
	auto it = this->_instanceMap.Begin();
	while (true)
	{
		if (it.key != nullptr && *it.val == id)
		{
			return *it.key;
		}

		if (it == this->_instanceMap.End())
			n_error("No entity found for instance");
		it++;
	}
}

const Util::StringAtom
ComponentInterface::GetStringID() const
{
	return this->stringID;
}

}