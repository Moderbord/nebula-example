#pragma once
#include "util/stringatom.h"
#include "util/queue.h"
#include "entity.h"

#define p_RegisterComponent(COMPONENT) \
	Manager::ComponentManager::Instance()->RegisterComponent(COMPONENT);


namespace Component {

	typedef unsigned InstanceId;
	const static int MaxNumInstances = 256;

class ComponentInterface
{

public:
	ComponentInterface();
	~ComponentInterface();

	InstanceId RegisterEntity(Entities::Entity& e);

	void DeregisterEntity(Entities::Entity& e);

	bool IsRegistered(Entities::Entity& e);

	InstanceId GetInstanceID(Entities::Entity& e);

	const Util::StringAtom GetStringID() const;

	virtual void Clear() = 0;

	virtual void OnActivate() = 0;

	virtual void OnReset(InstanceId& id) = 0;

	virtual void OnBeginFrame() = 0;

	virtual void OnRender() = 0;

	virtual void OnEndFrame() = 0;

	Util::StringAtom stringID;

protected:
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
InstanceId Register(Entities::Entity& e)
{
	return COMPONENT::Instance()->RegisterEntity(e);
}

}