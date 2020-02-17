#pragma once
#include "util/stringatom.h"
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

	void (*OnBeginFrame)();

	void (*OnRender)();

	void (*OnEndFrame)();

};
}