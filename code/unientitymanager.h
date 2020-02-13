//#include "core/refcounted.h"
#include "core/singleton.h"
#include "game/manager.h"
#include "util/arraystack.h"
#include "util/queue.h"

namespace Uni {

	typedef unsigned UniEntity;

	const SizeT MaxNumEntities = 256;

	class UniEntityManager/* : public Game::Manager*/
	{
		//__DeclareClass(UniEntityManager)
		__DeclareSingleton(UniEntityManager)


	public:
		// constructor
		UniEntityManager();
		// destructor
		~UniEntityManager();
		// new entity
		UniEntity NewEntity();
		// delete entity
		void DeleteEntity(const UniEntity& e);
		// check if entity is alive
		bool IsAlive(const UniEntity& e) const;
		// get number of alive entities
		SizeT GetNumEntities() const;


	private:
		// Number of entities?
		Util::ArrayStack<UniEntity, MaxNumEntities * sizeof(UniEntity)> _entities;
		Util::Queue<UniEntity> _idQueue;
		SizeT _numEntities;
		UniEntity _nextEntity;
		


	};
}