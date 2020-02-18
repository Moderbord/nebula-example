#pragma once
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "util/arraystack.h"
#include "util/array.h"
#include "componentinterface.h"
#include "entity.h"

namespace Component {
	//------------------------------------------------------------------------------
	/**
		Transform component
	*/
	class Transform : public ComponentInterface{

		const Math::matrix44 _identityMatrix = Math::matrix44::translation(Math::point(0, 0, 0));

	public:
		Transform();
		~Transform();

		void Clear();
		void OnActivate();
		void OnReset(InstanceId& instance);
		void OnBeginFrame();
		void OnRender();
		void OnEndFrame();

		struct Attributes{
			Util::ArrayStack<Math::matrix44, MaxNumInstances> transform;
		};


	private:
		// Contains the data for each entity in an array
		Attributes _instanceData;
	};

	// constructor
	inline Transform::Transform()
	{
		this->stringID = Util::StringAtom("transform");
	}

	// deconstructor
	inline Transform::~Transform()
	{
		_instanceMap.Clear();
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

