#pragma once
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "unicomponentinterface.h"

namespace Uni {

	class ComponentTransform : public ComponentInterface{


	public:
		ComponentTransform();
		~ComponentTransform();

		InstanceId RegisterEntity(Entity& e);

		void DeregisterEntity(Entity& e);

		InstanceId GetInstanceID(Entity& e);

		void Clear();

		void (*OnBeginFrame)();


	private:

	};




	inline ComponentTransform::ComponentTransform()
	{
		this->stringID = Util::StringAtom("transform");
	}

	inline ComponentTransform::~ComponentTransform()
	{

	}

	inline InstanceId ComponentTransform::RegisterEntity(Entity& e)
	{
		return InstanceId();
	}

	inline void ComponentTransform::DeregisterEntity(Entity& e)
	{
	}

	inline InstanceId ComponentTransform::GetInstanceID(Entity& e)
	{
		return InstanceId();
	}

	inline void ComponentTransform::Clear()
	{
	}

	inline void ComponentTransform::OnBeginFrame()
	{
	}


}

