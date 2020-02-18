#pragma once
#include "componentinterface.h"

namespace Component
{

ComponentInterface::ComponentInterface()
	: _nextInstanceID(0), _numInstances(0)
{

}

ComponentInterface::~ComponentInterface()
{

}

InstanceId ComponentInterface::RegisterEntity(Entities::Entity& e)
{
	// check if entity already isn't registered
	n_assert(!this->_instanceMap.Contains(e));

	// If queue isn't empty
	if (!this->_instanceQueue.IsEmpty())
	{
		InstanceId id = this->_instanceQueue.Dequeue();
		this->_instanceMap.Add(e, id);
		this->_numInstances++;
		// reset target instance data
		this->OnReset(id);
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
	this->OnActivate();
	return id;
}

void ComponentInterface::DeregisterEntity(Entities::Entity& e)
{
	// check if entity is registered
	auto it = this->_instanceMap.Begin();
	while (true)
	{
		if (*it.key == e)
		{
			// TODO this will leave an unused "gap" in memory until new entity fills it
			this->_instanceMap.Erase(e);
			this->_numInstances--;
			// queue free instance
			this->_instanceQueue.Enqueue(*it.val);
			break;
		}
		if (it == this->_instanceMap.End())
		{
			break;
		}
		it++;
	}
}

bool ComponentInterface::IsRegistered(Entities::Entity& e)
{
	return this->_instanceMap.Contains(e);
}

InstanceId ComponentInterface::GetInstanceID(Entities::Entity& e)
{
	n_assert(this->_instanceMap.Contains(e));
	return this->_instanceMap[e];
}

const Util::StringAtom
ComponentInterface::GetStringID() const
{
	return this->stringID;
}

}