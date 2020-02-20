#pragma once
#include "core/singleton.h"
#include "core/refcounted.h"
#include "util/arraystack.h"
#include "util/queue.h"
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "entity.h"
#include "component.h"

namespace Manager {

	const SizeT MaxNumComponents = 256;

	class ComponentManager : public Core::RefCounted
	{
		__DeclareClass(Manager::ComponentManager)
		__DeclareSingleton(Manager::ComponentManager)

	public:
		// constructor
		ComponentManager();
		// destructor
		~ComponentManager();
		// new component
		void RegisterComponent(Component::ComponentInterface* component);
		// delete component
		void UnregisterComponent(Component::ComponentInterface* component);

		bool HasComponent(Component::ComponentInterface* component);

		bool HasComponentByStringID(Util::StringAtom& stringID);

		Component::ComponentInterface* GetComponent(Util::StringAtom& stringID);

	private:

		Util::HashTable<Util::StringAtom, Component::ComponentInterface*> _componentTable;
		Util::Array<Component::ComponentInterface*> _components;

	};

}