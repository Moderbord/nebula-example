#pragma once
#include "componentinterface.h"


/*
	Component interface which all components derive from

	TODO change the way to search for entities and their component values?
*/
namespace Component
{

	struct Attributes {
		Util::Array<Entities::Entity> owners;
	};
	Attributes _instanceData;

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

bool ComponentInterface::IsRegistered(const Entities::Entity& e)
{
	return this->_instanceMap.Contains(e);
}

InstanceId ComponentInterface::GetInstanceID(const Entities::Entity& e)
{
	n_assert(this->_instanceMap.Contains(e));
	return this->_instanceMap[e];
}

const Util::StringAtom
ComponentInterface::GetStringID() const
{
	return this->_stringID;
}

void ComponentInterface::Clear()
{
	this->_instanceMap.Clear();
}

}