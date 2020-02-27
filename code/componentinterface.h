#pragma once
#include "util/stringatom.h"
#include "util/queue.h"
#include "entity.h"
#include "message.h"

#define p_RegisterComponent(COMPONENT) \
	Manager::ComponentManager::Instance()->RegisterComponent(&COMPONENT);
/*
	Header for component interface

	TODO add some const
*/

namespace Component {

	typedef unsigned InstanceId;
	const static int MaxNumInstances = 256;

	class ComponentInterface
	{

	public:
		ComponentInterface();
		~ComponentInterface();

		virtual void OnRegister(const Entities::Entity& e) = 0;

		virtual void OnDeregister(const Entities::Entity& e) = 0;

		virtual void OnBeginFrame() = 0;

		virtual void OnRender() = 0;

		virtual void OnEndFrame() = 0;

		virtual void OnMessage(const Message::Message& msg) = 0;

		virtual const Entities::Entity GetOwner(const InstanceId& id) = 0;

		InstanceId RegisterEntity(const Entities::Entity& e);

		bool IsRegistered(const Entities::Entity& e);

		InstanceId GetInstanceID(const Entities::Entity& e);

		const Util::StringAtom GetStringID() const;

		void Clear();

	protected:
		// string atom Id
		Util::StringAtom _stringID;
		// tracks number of instances the component has
		SizeT _numInstances;
		// keeps track of the highest ID which will be assigned to an instance
		InstanceId _nextInstanceID;
		// queue of free instance ID's that can be used
		Util::Queue<Entities::Entity> _instanceQueue;
		// maps component instance to owner entity
		Util::HashTable<Entities::Entity, InstanceId, MaxNumInstances, 1> _instanceMap;

	};

	template<typename COMPONENT>
	InstanceId Register(const Entities::Entity& e)
	{
		return COMPONENT::Instance()->RegisterEntity(e);
	}

	template<typename COMPONENT>
	void Deregister(const Entities::Entity& e)
	{
		return COMPONENT::Instance()->DeregisterEntity(e);
	}

	template<typename COMPONENT>
	bool HasComponent(const Entities::Entity& e)
	{
		return COMPONENT::Instance()->IsRegistered(e);
	}

	template<typename COMPONENT>
	InstanceId GetInstanceID(Entities::Entity& e)
	{
		return COMPONENT::Instance()->GetInstanceID(e);
	}

}