#include "unientity.h"

namespace Uni {


class UniComponentInterface {

	typedef unsigned InstanceId;

public:
	UniComponentInterface();
	~UniComponentInterface();

	virtual InstanceId RegisterEntity(UniEntity& e) = 0;


};
}