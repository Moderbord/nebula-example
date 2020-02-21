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
	}

	// deconstructor
	Transform::~Transform()
	{
		_instanceMap.Clear();
		__DestructSingleton
	}

	inline void Transform::OnRegister()
	{
		this->_instanceData.transform.Append(_identityMatrix);
	}

	inline void Transform::OnReset(InstanceId& instance)
	{
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

	inline void Transform::OnDestroy()
	{
		// TODO more?
		this->~Transform();
	}

	void Transform::OnMessage(const Entities::Entity& entity, const Message::Type& type)
	{
	}

	Math::matrix44 Transform::GetTransform(const Entities::Entity& entity)
	{
		InstanceId instance = this->_instanceMap[entity];
		return this->_instanceData.transform[instance];
	}

	void Transform::SetTransform(const Entities::Entity& entity, Math::matrix44 transform)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.transform[instance] = transform;
	}

}