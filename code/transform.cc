#pragma once
#include "component.h"

namespace Component {

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

	// Clears the component from all registered entities
	inline void Transform::Clear()
	{
		this->_instanceMap.Clear();
	}

	inline void Transform::OnActivate()
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
	}

	inline void Transform::OnEndFrame()
	{
	}
}