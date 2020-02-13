#include "core/singleton.h"
#include "game/manager.h"
#include "util/arraystack.h"
#include "util/queue.h"
#include "unientity.h"

namespace Uni {

	const SizeT MaxNumEntities = 256;

	class UniComponentManager/* : public Game::Manager*/
	{
		//__DeclareClass(UniEntityManager)
		__DeclareSingleton(UniComponentManager)


	public:
		// constructor
		UniComponentManager();
		// destructor
		~UniComponentManager();
		// new entity
		void RegisterEntity(const UniEntity& e);
		// delete entity
		void DeleteEntity(const UniEntity& e);

	private:
		//// Number of entities?
		//Util::ArrayStack<UniEntity, MaxNumEntities * sizeof(UniEntity)> _entities;
		//Util::Queue<UniEntity> _idQueue;
		//SizeT _numEntities;
		//UniEntity _nextEntity;



	};
}