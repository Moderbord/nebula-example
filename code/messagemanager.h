#pragma once
#include "core/singleton.h"
#include "core/refcounted.h"
#include "componentmanager.h"
#include "message.h"

/*
	MessageHandler receives and dispatches messages 


	TODO add message groups and possibility for entities (components?)
	TODO subscription to message groups
	TODO send to all entities/components
	TODO send to message group
	TODO delayed messages
*/

namespace Message
{
	class MessageManager : public Core::RefCounted
	{
		__DeclareClass(Message::MessageManager)
		__DeclareSingleton(Message::MessageManager)

	public:
		// constructor
		MessageManager();
		// destructor
		~MessageManager();

	private:
	};
		
	inline void Send(const Entities::Entity& entity, const Type& type)
	{
		Manager::ComponentManager::Instance()->RelayMessage(entity, type);
	}

}