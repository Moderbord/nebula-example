#pragma once
#include "core/singleton.h"
#include "game/manager.h"
#include "util/arraystack.h"
#include "util/queue.h"
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "unientity.h"
#include "unicomponentinterface.h"

namespace Uni {

	const SizeT MaxNumComponents = 256;

	class ComponentManager
	{
		__DeclareSingleton(ComponentManager)


	public:
		// constructor
		ComponentManager();
		// destructor
		~ComponentManager();
		// new component
		void RegisterComponent(ComponentInterface* component);
		// delete component
		void UnregisterComponent(ComponentInterface* component);

		bool HasComponent(ComponentInterface* component);

		bool HasComponentByStringID(Util::StringAtom& stringID);

		ComponentInterface* GetComponent(Util::StringAtom& stringID);

	private:

		Util::HashTable<Util::StringAtom, ComponentInterface*> _componentTable;
		Util::Array<ComponentInterface*> _components;

	};
}