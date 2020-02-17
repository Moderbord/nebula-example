#pragma once
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "componentinterface.h"

namespace Component {

	class ComponentTransform : public ComponentInterface{


	public:
		ComponentTransform();
		~ComponentTransform();

		InstanceId RegisterEntity(Entities::Entity& e);

		void DeregisterEntity(Entities::Entity& e);

		InstanceId GetInstanceID(Entities::Entity& e);

		void Clear();

	private:

	};




	inline ComponentTransform::ComponentTransform()
	{
		this->stringID = Util::StringAtom("transform");
	}

	inline ComponentTransform::~ComponentTransform()
	{

	}

	inline InstanceId ComponentTransform::RegisterEntity(Entities::Entity& e)
	{
		return InstanceId();
	}

	inline void ComponentTransform::DeregisterEntity(Entities::Entity& e)
	{
	}

	inline InstanceId ComponentTransform::GetInstanceID(Entities::Entity& e)
	{
		return InstanceId();
	}

	inline void ComponentTransform::Clear()
	{
	}

}

