#pragma once
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "util/arraystack.h"
#include "util/array.h"
#include "componentinterface.h"
#include "entity.h"

namespace Component {

	// Transform component
	class Transform : public ComponentInterface{

		const static int MaxNumInstances = 256;

	public:
		Transform();
		~Transform();

		InstanceId RegisterEntity(Entities::Entity& e);

		void DeregisterEntity(Entities::Entity& e);

		bool IsRegistered(Entities::Entity& e);

		InstanceId GetInstanceID(Entities::Entity& e);

		void InitInstanceData(InstanceId& instance);

		void ResetInstanceData(InstanceId& instance);

		void Clear();

		void OnBeginFrame();
		void OnRender();
		void OnEndFrame();

		struct Attributes{
			Util::ArrayStack<unsigned, sizeof(unsigned) * MaxNumInstances> x;
			Util::ArrayStack<unsigned, sizeof(unsigned)* MaxNumInstances> y;
		};


	private:

		// Contains the data for each entity in an array
		Attributes _instanceData;

		// maps component instance to owner entity
		Util::HashTable<Entities::Entity, InstanceId, MaxNumInstances, 1> _instanceMap;

	};

	// constructor
	inline Transform::Transform()
	{
		this->stringID = Util::StringAtom("transform");
	}

	// deconstructor
	inline Transform::~Transform()
	{
		_instanceMap.Clear();
	}

	// Register and entity to the component
	inline InstanceId Transform::RegisterEntity(Entities::Entity& e)
	{
		// check if entity already isn't registered
		IndexT index = this->_instanceMap.FindIndex(e);
		n_assert(index == InvalidIndex);

		// If queue isn't empty
		if (!this->_instanceQueue.IsEmpty())
		{
			InstanceId id = this->_instanceQueue.Dequeue();
			this->_instanceMap.Add(e, id);
			this->_numInstances++;
			// reset target instance data
			ResetInstanceData(id);
			return id;
		}

		// TODO may go out of maximum allowed entries
		// assign and increment
		InstanceId id = this->_nextInstanceID++;
		// add to map
		this->_instanceMap.Add(e, id);
		// increment num instances
		this->_numInstances++;
		InitInstanceData(id);
		return id;
	}

	// De-register and entity from the component
	inline void Transform::DeregisterEntity(Entities::Entity& e)
	{
		// check if entity is registered
		auto it = this->_instanceMap.Begin();
		while (true)
		{
			if (*it.key == e)
			{
				// TODO this will leave an unused "gap" in memory until new entity fills it
				this->_instanceMap.Erase(e);
				this->_numInstances--;
				// queue free instance
				this->_instanceQueue.Enqueue(*it.val);
				break;
			}
			if (it == this->_instanceMap.End())
			{
				break;
			}
			it++;
		}
	}

	inline bool Transform::IsRegistered(Entities::Entity& e)
	{
		return this->_instanceMap.Contains(e);
	}

	// Retreives a component instance owned by an entity
	inline InstanceId Transform::GetInstanceID(Entities::Entity& e)
	{
		IndexT index = this->_instanceMap.FindIndex(e);
		n_assert(index != InvalidIndex);
		return this->_instanceMap[e];
	}

	inline void Transform::InitInstanceData(InstanceId& instance)
	{
		this->_instanceData.x.Append(0);
		this->_instanceData.y.Append(0);
	}

	inline void Transform::ResetInstanceData(InstanceId& instance)
	{
		this->_instanceData.x[instance] = 0;
		this->_instanceData.y[instance] = 0;
	}

	// Clears the component from all registered entities
	inline void Transform::Clear()
	{
		this->_instanceMap.Clear();
	}

	inline void Transform::OnBeginFrame()
	{
	}

	inline void Transform::OnRender()
	{
	}

	inline void Transform::OnEndFrame()
	{
	}

}

