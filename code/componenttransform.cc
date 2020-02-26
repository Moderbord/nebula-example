#pragma once
#include "component.h"

/*
	Transform component

	TODO add some comments
	TODO add some const
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
		this->stringID = Util::StringAtom("transform");
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

	inline void Transform::OnReset(const Entities::Entity& entity, const InstanceId& instance)
	{
		this->_instanceData.owners[instance] = entity;
		this->_instanceData.transform[instance] = _identityMatrix;
	}

	inline void Transform::OnBeginFrame()
	{

	}

	inline void Transform::OnRender()
	{
		// TODO stuff
	}

	inline void Transform::OnEndFrame()
	{
	}

	inline void Transform::Clear()
	{
		this->_instanceMap.Clear();
	}

	void Transform::OnMessage(const Message::Message& msg)
	{
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