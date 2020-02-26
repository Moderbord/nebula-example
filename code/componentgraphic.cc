#pragma once
#include "component.h"
#include "messagemanager.h"


/*
	Graphical component

	TODO see component.h
*/
namespace Component {

	struct Attributes;

	__ImplementSingleton(Component::Graphic)

		// constructor
	Graphic::Graphic()
	{
		__ConstructSingleton
		this->stringID = Util::StringAtom("graphic");
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

	inline void Graphic::OnReset(const Entities::Entity& entity, const InstanceId& instance)
	{
		this->_instanceData.owners[instance] = entity;
		Graphics::GraphicsEntityId id = Graphics::CreateEntity();
		this->_instanceData.graphicId[instance] = id;
		this->_instanceData.resourceName[instance] = "mdl:system/placeholder.n3";
		this->_instanceData.tag[instance] = "Examples";
		this->_instanceData.skeleton[instance] = "";
		this->_instanceData.animation[instance] = "";
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

	inline void Graphic::Clear()
	{
		this->_instanceMap.Clear();
	}

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
				this->DeregisterEntity(data->targetId);
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
			this->_instanceData.animation[instance],this->_instanceData.tag[instance]);
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

	void Graphic::PlayAnimated(const Entities::Entity& entity)
	{
		InstanceId instance = this->_instanceMap[entity];
		Characters::CharacterContext::PlayClip(this->_instanceData.graphicId[instance],
			nullptr, 0, 0, Characters::Append, 1.0f, 1, Math::n_rand() * 100.0f, 0.0f, 0.0f,
			Math::n_rand() * 100.0f);
	}

}