#pragma once
#include "application/stdneb.h"
#include "messagemanager.h"

/*
	Message manager

	TODO some functionality, see header file
*/
namespace Message
{
	__ImplementClass(Message::MessageManager, 'MMGR', Core::RefCounted)
	__ImplementSingleton(Message::MessageManager)

	MessageManager::MessageManager()
	{
		__ConstructSingleton;
	}

	MessageManager::~MessageManager()
	{
		__DestructSingleton;
	}
}