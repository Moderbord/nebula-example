#pragma once
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "util/arraystack.h"
#include "util/array.h"
#include "componentinterface.h"
#include "entity.h"

namespace Component {

	// Transform component
	class Transform : public ComponentInterface{



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
			Util::ArrayStack<unsigned, sizeof(unsigned) * MaxNumInstances> x;
			Util::ArrayStack<unsigned, sizeof(unsigned)* MaxNumInstances> y;
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
		this->_instanceData.x.Append(0);
		this->_instanceData.y.Append(0);
	}

	inline void Transform::OnReset(InstanceId& instance)
	{
		this->_instanceData.x[instance] = 0;
		this->_instanceData.y[instance] = 0;
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

