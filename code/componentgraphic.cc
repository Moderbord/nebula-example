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
		this->_instanceData.graphicId.Clear();
		this->_instanceData.resourceName.Clear();
		this->_instanceData.skeleton.Clear();
		this->_instanceData.animation.Clear();
		this->_instanceData.tag.Clear();
		__DestructSingleton
	}

	inline void Graphic::OnRegister()
	{
		Graphics::GraphicsEntityId id = Graphics::CreateEntity();
		this->_instanceData.graphicId.Append(id);
		this->_instanceData.resourceName.Append("mdl:system/placeholder.n3");
		this->_instanceData.tag.Append("Examples");
		this->_instanceData.skeleton.Append("");
		this->_instanceData.animation.Append("");
	}

	inline void Graphic::OnReset(const InstanceId& instance)
	{
		Graphics::GraphicsEntityId id = Graphics::CreateEntity();
		this->_instanceData.graphicId[instance] = id;
		this->_instanceData.resourceName[instance] = "mdl:system/placeholder.n3";
		this->_instanceData.tag[instance] = "Examples";
		this->_instanceData.skeleton[instance] = "";
		this->_instanceData.animation[instance] = "";
	}

	inline void Graphic::OnBeginFrame()
	{
		// Loop through all instances inside component
		auto it = this->_instanceMap.Begin();
		while (true)
		{
			if (it.key != nullptr) // TODO better
			{
				// Get graphicId
				Graphics::GraphicsEntityId graphicId = this->_instanceData.graphicId[*it.val];
				// TODO Need to check if target has transform component first
				// Get transform
				Math::matrix44 transform = Component::Transform::Instance()->GetTransform(*it.key);
				// TODO doesn't sheck if part of current context
				// Update model context
				Models::ModelContext::SetTransform(graphicId, transform);
			}

			if (it == this->_instanceMap.End())
				break;
			it++;
		}
	}

	inline void Graphic::OnRender()
	{
		Math::matrix44 transform = Component::Transform::Instance()->GetTransform(3);
		transform.translate(Math::float4(0, 0, 0.1, 0));
		Component::Transform::Instance()->SetTransform(3, transform);

		//Math::matrix44 transform2 = Component::Transform::Instance()->GetTransform(1);
		//transform2.translate(Math::float4(0, 0, 0.05, 0));
		//Component::Transform::Instance()->SetTransform(ent2, transform2);
	}

	inline void Graphic::OnEndFrame()
	{
	}

	inline void Graphic::Clear()
	{
		this->_instanceMap.Clear();
	}

	void Graphic::OnMessage(const Entities::Entity& entity, const Message::Type& msgType)
	{
		auto it = this->_instanceMap.Begin();
		while (true)
		{
			if (it.key != nullptr && *it.key == entity)
			{
				// Map entity to instance
				InstanceId instance = *it.val;
				switch (msgType)
				{
				case Message::Type::DEREGISTER:
					this->Deconstruct(entity);
					this->DeregisterEntity(entity);
					break;
				case Message::Type::MEMEFY: // test move
					Math::matrix44 transform = Component::Transform::Instance()->GetTransform(entity);
					transform.translate(Math::float4(0, 0, 5, 0));
					Component::Transform::Instance()->SetTransform(entity, transform);
				}
			}

			// Entity not present
			if (it == this->_instanceMap.End())
			{
				break;
			}
			it++;
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

	void Graphic::Deconstruct(const Entities::Entity& entity)
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