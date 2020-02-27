#pragma once
#include "component.h"

/*
	Transform component

	TODO add some comments
	TODO handle fragmantation
	TODO handle deregistration
*/

namespace Component {

	struct Attributes;

	__ImplementSingleton(Component::Transform)

		// constructor
	Transform::Transform()
	{
		__ConstructSingleton
		this->_stringID = Util::StringAtom("transform");
		this->_instanceData.owners.Reserve(MaxNumInstances);
		this->_instanceData.transform.Reserve(MaxNumInstances);
	}

	// deconstructor
	Transform::~Transform()
	{
		this->_instanceMap.Clear();
		this->_instanceData.owners.Clear();
		this->_instanceData.transform.Clear();
		__DestructSingleton
	}

	inline void Transform::OnRegister(const Entities::Entity& entity)
	{
		this->_instanceData.owners.Append(entity);
		this->_instanceData.transform.Append(_identityMatrix);
	}

	void Transform::OnDeregister(const Entities::Entity& e)
	{
		n_assert(this->_instanceMap.Contains(e));

		// Get the instance that is mapped to the entity
		InstanceId freedInstance = this->_instanceMap[e];
		// Get index of last instance that will be swapped
		IndexT lastInstanceIndex = this->_numInstances - 1;
		// Get the entity who owns the last instance
		Entities::Entity lastInstanceOwner = this->_instanceData.owners[lastInstanceIndex];
		// Update instance map
		this->_instanceMap[lastInstanceOwner] = freedInstance;

		this->_instanceData.owners.EraseIndexSwap(freedInstance);
		this->_instanceData.transform.EraseIndexSwap(freedInstance);

		// Erase the deregistered entity from the instance map
		this->_instanceMap.Erase(e);
		// Decrement amount of registered entities
		this->_numInstances--;
	}

	inline void Transform::OnBeginFrame()
	{}

	inline void Transform::OnRender()
	{}

	inline void Transform::OnEndFrame()
	{}

	void Transform::OnMessage(const Message::Message& msg)
	{
	}

	const Entities::Entity Transform::GetOwner(const InstanceId& instance)
	{
		return this->_instanceData.owners[instance];
	}

	Math::matrix44 Transform::GetTransform(const Entities::Entity& entity)
	{
		n_assert(Component::HasComponent<Component::Transform>(entity));
		InstanceId instance = this->_instanceMap[entity];
		return this->_instanceData.transform[instance];
	}

	void Transform::SetTransform(const Entities::Entity& entity, Math::matrix44 transform)
	{
		n_assert(Component::HasComponent<Component::Transform>(entity));
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.transform[instance] = transform;
	}

}