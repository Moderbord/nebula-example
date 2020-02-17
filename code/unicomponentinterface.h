#pragma once
#include "unientity.h"
#include "util/stringatom.h"

namespace Uni {

	typedef unsigned InstanceId;


class ComponentInterface
{

public:
	ComponentInterface();
	~ComponentInterface();

	virtual InstanceId RegisterEntity(Entity& e) = 0;

	virtual void DeregisterEntity(Entity& e) = 0;

	virtual InstanceId GetInstanceID(Entity& e) = 0;

	virtual void Clear() = 0;

	Util::StringAtom stringID;

	const Util::StringAtom GetStringID() const;

	void (*OnBeginFrame)();

	void (*OnRender)();

	void (*OnEndFrame)();

};
}