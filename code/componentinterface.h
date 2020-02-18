#pragma once
#include "util/stringatom.h"
#include "util/queue.h"
#include "entity.h"

namespace Component {

	typedef unsigned InstanceId;


class ComponentInterface
{

public:
	ComponentInterface();
	~ComponentInterface();

	virtual InstanceId RegisterEntity(Entities::Entity& e) = 0;

	virtual void DeregisterEntity(Entities::Entity& e) = 0;

	virtual InstanceId GetInstanceID(Entities::Entity& e) = 0;

	virtual void Clear() = 0;

	Util::StringAtom stringID;

	const Util::StringAtom GetStringID() const;

	virtual void OnBeginFrame() = 0;

	virtual void OnRender() = 0;

	virtual void OnEndFrame() = 0;

protected:

	Util::Queue<Entities::Entity> _instanceQueue;
	SizeT _numInstances;
	InstanceId _nextInstanceID;
	

};
}