#pragma once
#include "core/singleton.h"
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
	class Transform : public ComponentInterface
	{
		__DeclareSingleton(Component::Transform)
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
}

