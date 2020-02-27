#pragma once
#include "application/stdneb.h"
#include "componentmanager.h"


/*
	Component manager

	TODO add some const
	TODO add some comments
*/
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
		this->_componentTable.Add(component->GetStringID(), component);
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
			if (it.key != nullptr && *it.val == component)
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

	bool ComponentManager::HasComponentByStringID(const Util::StringAtom& stringID)
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

	void ComponentManager::OnBeginFrame()
	{
		for (Component::ComponentInterface* component : this->_components)
		{
			component->OnBeginFrame();
		}
	}

	void ComponentManager::OnRender()
	{
		for (Component::ComponentInterface* component : this->_components)
		{
			component->OnRender();
		}
	}

	void ComponentManager::OnEndFrame()
	{
		for (Component::ComponentInterface* component : this->_components)
		{
			component->OnEndFrame();
		}
	}

	Component::ComponentInterface* ComponentManager::GetComponent(const Util::StringAtom& stringID)
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

	/*
		Called from a component when deleting a whole entity
	*/
	void ComponentManager::DeleteEntity(const Entities::Entity& entity)
	{
		// Iterate through components
		for (Component::ComponentInterface* component : this->_components)
		{	
			// Check if entity is registered
			if (component->IsRegistered(entity))
				component->OnDeregister(entity);
		}
	}

	//void ComponentManager::HandleMessage(const Entities::Entity& entity, const Message::Type& type) const
	//{
	//	for (Component::ComponentInterface* component : this->_components)
	//	{
	//		component->OnMessage(entity, type);
	//	}
	//}



}