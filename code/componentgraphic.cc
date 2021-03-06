#pragma once
#include "component.h"
#include "messagemanager.h"


/*
	Graphical component

	TODO see component.h
*/
namespace Component {

	__ImplementSingleton(Component::Graphic)

		// constructor
	Graphic::Graphic()
	{
		__ConstructSingleton
		this->_stringID = Util::StringAtom("graphic");
		// Reserve memory
		this->_instanceData.owners.Reserve(MaxNumInstances);
		this->_instanceData.graphicId.Reserve(MaxNumInstances);
		this->_instanceData.resourceName.Reserve(MaxNumInstances);
		this->_instanceData.skeleton.Reserve(MaxNumInstances);
		this->_instanceData.animation.Reserve(MaxNumInstances);
		this->_instanceData.tag.Reserve(MaxNumInstances);
	}

	// deconstructor
	Graphic::~Graphic()
	{
		_instanceMap.Clear();
		this->_instanceData.owners.Clear();
		this->_instanceData.graphicId.Clear();
		this->_instanceData.resourceName.Clear();
		this->_instanceData.skeleton.Clear();
		this->_instanceData.animation.Clear();
		this->_instanceData.tag.Clear();
		__DestructSingleton
	}

	inline void Graphic::OnRegister(const Entities::Entity& entity)
	{
		this->_instanceData.owners.Append(entity);
		Graphics::GraphicsEntityId id = Graphics::CreateEntity();
		this->_instanceData.graphicId.Append(id);
		this->_instanceData.resourceName.Append("mdl:system/placeholder.n3");
		this->_instanceData.tag.Append("Examples");
		this->_instanceData.skeleton.Append("");
		this->_instanceData.animation.Append("");
	}

	//template<typename T>
	void Graphic::OnDeregister(const Entities::Entity& e)
	{
		n_assert(this->_instanceMap.Contains(e));

		// Get the instance that is mapped to the entity
		InstanceId freedInstance = this->_instanceMap[e];
		// Get index of last instance that will be swapped
		IndexT lastInstanceIndex = this->_numInstances - 1;
		// Get the entity who owns the last instance
		Entities::Entity lastInstanceOwner = this->_instanceData.owners[lastInstanceIndex];
		// Update instance map
		this->_instanceMap[lastInstanceOwner] = freedInstance;
		// swap all data
		this->_instanceData.owners.EraseIndexSwap(freedInstance);
		this->_instanceData.graphicId.EraseIndexSwap(freedInstance);
		this->_instanceData.resourceName.EraseIndexSwap(freedInstance);
		this->_instanceData.skeleton.EraseIndexSwap(freedInstance);
		this->_instanceData.animation.EraseIndexSwap(freedInstance);
		this->_instanceData.tag.EraseIndexSwap(freedInstance);

		//for (Util::Array<T> data : this->_instanceData)
		//{
		//	data.EraseIndexSwap(freedInstance);
		//}

		// Erase the deregistered entity from the instance map
		this->_instanceMap.Erase(e);
		// Decrement amount of registered entities
		this->_numInstances--;

		//this->_instanceQueue.Enqueue(freedInstance);
	}

	inline void Graphic::OnBeginFrame()
	{
		// Loop through all entities in component
		for (Entities::Entity entity : this->_instanceData.owners)
		{
			// check that entity exist in map
			n_assert(this->_instanceMap.Contains(entity))
			// Get instance of data
			InstanceId instance = this->_instanceMap[entity];
			// graphical id
			Graphics::GraphicsEntityId graphicId = this->_instanceData.graphicId[instance];
			// transform
			Math::matrix44 transform = Component::Transform::Instance()->GetTransform(entity);
			// Update model context
			Models::ModelContext::SetTransform(graphicId, transform);
		}
	}

	inline void Graphic::OnRender()
	{
		// movespead instead
		Math::matrix44 transform = Component::Transform::Instance()->GetTransform(3);
		transform.translate(Math::float4(0, 0, 0.1, 0));
		Component::Transform::Instance()->SetTransform(3, transform);
	}

	inline void Graphic::OnEndFrame()
	{}

	void Graphic::OnMessage(const Message::Message& msg)
	{
		switch (msg.type)
			{
			case 'dReg':
			{
				Message::Deregister* data = (Message::Deregister*)msg.data;
				// remove from visual context (nebula stuff)
				this->Remove(data->targetId);
				// deregister from component
				this->OnDeregister(data->targetId);
				break;
			}
			case 'sMov': // test move
			{
				Message::SendMove* data = (Message::SendMove*)msg.data;
				// get transform
				Math::matrix44 transform = Component::Transform::Instance()->GetTransform(data->targetId);
				// do transformation
				transform.translate(data->vec);
				// set new transform
				Component::Transform::Instance()->SetTransform(data->targetId, transform);
				break;
			}
			}
	}

	const Entities::Entity Graphic::GetOwner(const InstanceId& instance)
	{
		return this->_instanceData.owners[instance];
	}

	void Graphic::SetResourceName(const Entities::Entity& entity, const Util::StringAtom& resource)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.resourceName[instance] = resource;
	}

	void Graphic::SetSkeleton(const Entities::Entity& entity, const Util::StringAtom& skeleton)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.skeleton[instance] = skeleton;
	}

	void Graphic::SetAnimation(const Entities::Entity& entity, const Util::StringAtom& animation)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.animation[instance] = animation;
	}

	void Graphic::SetTag(const Entities::Entity& entity, const Util::StringAtom& tag)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.tag[instance] = tag;
	}

	void Graphic::Setup(const Entities::Entity& entity)
	{
		n_assert(this->_instanceMap.Contains(entity));
		// Get component instance and associated graphicId
		InstanceId instance = this->_instanceMap[entity];
		Graphics::GraphicsEntityId graphicId = this->_instanceData.graphicId[instance];
		// Register to Model and Observable contexts
		Graphics::RegisterEntity<Models::ModelContext, Visibility::ObservableContext>(graphicId);
		// Register in ModelContext
		Models::ModelContext::Setup(graphicId, this->_instanceData.resourceName[instance], this->_instanceData.tag[instance]);
		// Add to observable context
		Visibility::ObservableContext::Setup(graphicId, Visibility::VisibilityEntityType::Model);

	}

	void Graphic::SetupAnimated(const Entities::Entity& entity)
	{
		n_assert(this->_instanceMap.Contains(entity));
		// Get component instance and associated graphicId
		InstanceId instance = this->_instanceMap[entity];
		Graphics::GraphicsEntityId graphicId = this->_instanceData.graphicId[instance];
		// Register to Model and Observable contexts
		Graphics::RegisterEntity<Models::ModelContext, Visibility::ObservableContext, Characters::CharacterContext>(graphicId);
		// Register in ModelContext
		Models::ModelContext::Setup(graphicId, this->_instanceData.resourceName[instance], this->_instanceData.tag[instance]);
		// Add to observable context
		Visibility::ObservableContext::Setup(graphicId, Visibility::VisibilityEntityType::Model);
		// Setup skeleton and animation
		Characters::CharacterContext::Setup(graphicId, this->_instanceData.skeleton[instance],
			this->_instanceData.animation[instance], this->_instanceData.tag[instance]);
	}

	void Graphic::Remove(const Entities::Entity& entity)
	{
		n_assert(this->_instanceMap.Contains(entity));
		// Get component instance and associated graphicId
		InstanceId instance = this->_instanceMap[entity];
		Graphics::GraphicsEntityId graphicId = this->_instanceData.graphicId[instance];
		// Deregister from contexts
		Graphics::DeregisterEntity<Models::ModelContext, Visibility::ObservableContext>(graphicId);
		// check if animated 
		if (Characters::CharacterContext::IsEntityRegistered(graphicId))
			Characters::CharacterContext::DeregisterEntity(graphicId);
	}

	void Graphic::PlayAnimated(const Entities::Entity& entity)
	{
		InstanceId instance = this->_instanceMap[entity];
		Characters::CharacterContext::PlayClip(this->_instanceData.graphicId[instance],
			nullptr, 0, 0, Characters::Append, 1.0f, 1, Math::n_rand() * 100.0f, 0.0f, 0.0f,
			Math::n_rand() * 100.0f);
	}

}