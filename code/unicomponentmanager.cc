#pragma once
#include "application/stdneb.h"
#include "componentmanager.h"

namespace Manager
{
	__ImplementClass(Manager::ComponentManager, 'CMGR', Core::RefCounted)
	__ImplementSingleton(Manager::ComponentManager)

	ComponentManager::ComponentManager()
	{
		__ConstructSingleton;
	}

	ComponentManager::~ComponentManager()
	{
		__DestructSingleton;
	}

	void ComponentManager::RegisterComponent(Component::ComponentInterface* component)
	{
		this->_components.Append(component);
		this->_componentTable.Add(component->stringID, component);
	}

	void ComponentManager::UnregisterComponent(Component::ComponentInterface* component)
	{
		// Component array
		IndexT index = this->_components.FindIndex(component);
		if (index != InvalidIndex)
		{
			this->_components.EraseIndex(index);
		}
		// Component table
		auto it = this->_componentTable.Begin();
		while (true)
		{
			if (*it.val == component)
			{
				this->_componentTable.Erase(*it.key);
				break;
			}

			if (it == this->_componentTable.End())
				break;

			it++;
		}
	}

	bool ComponentManager::HasComponent(Component::ComponentInterface* component)
	{
		IndexT index = this->_components.FindIndex(component);
		return index != InvalidIndex;
	}

	bool ComponentManager::HasComponentByStringID(Util::StringAtom& stringID)
	{
		auto it = this->_componentTable.Begin();
		while (true)
		{
			if (*it.key == stringID)
			{
				return true;
			}

			if (it == this->_componentTable.End())
				return false;

			it++;
		}
	}

	Component::ComponentInterface* ComponentManager::GetComponent(Util::StringAtom& stringID)
	{
		auto it = this->_componentTable.Begin();
		while (true)
		{
			if (*it.key == stringID)
			{
				return *it.val;
			}

			if (it == this->_componentTable.End())
				return NULL;

			it++;
		}
	}


}