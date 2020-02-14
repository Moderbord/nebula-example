
#include "application/stdneb.h"
#include "unicomponentmanager.h"

namespace Uni
{
	//__ImplementClass(Uni::UniComponentManager, 'UCMG', Game::Manager)
	__ImplementSingleton(UniComponentManager)

	UniComponentManager::UniComponentManager()
	{
		__ConstructSingleton;
	}

	UniComponentManager::~UniComponentManager()
	{
		__DestructSingleton;
	}

	void UniComponentManager::RegisterEntity(const UniEntity& e)
	{
		// TODO
	}

	void UniComponentManager::DeleteEntity(const UniEntity& e)
	{
		// TODO
	}

}