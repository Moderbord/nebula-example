#pragma once
#include "component.h"

namespace Component {

	struct Attributes;

	__ImplementSingleton(Component::Graphic)

		// constructor
	Graphic::Graphic()
	{
		__ConstructSingleton
		this->stringID = Util::StringAtom("graphic");
	}

	// deconstructor
	Graphic::~Graphic()
	{
		_instanceMap.Clear();
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

	inline void Graphic::OnReset(InstanceId& instance)
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
			if (it.val != nullptr) // TODO better
			{
				// Get graphicId
				Graphics::GraphicsEntityId graphicId = this->_instanceData.graphicId[*it.val];
				// TODO Need to check if target has transform component first
				// Get transform
				Entities::Entity entity = *it.key;
				Math::matrix44 transform = Component::Transform::Instance()->GetTransform(entity);
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
	}

	inline void Graphic::OnEndFrame()
	{
	}

	inline void Graphic::Clear()
	{
		this->_instanceMap.Clear();
	}

	inline void Graphic::OnDestroy()
	{
		// TODO more?
		this->~Graphic();
	}

	void Graphic::Setup(Entities::Entity& entity)
	{
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

	void Graphic::SetupAnimated(Entities::Entity& entity)
	{
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

	void Graphic::SetResourceName(Entities::Entity& entity, const Util::StringAtom& resource)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.resourceName[instance] = resource;
	}

	void Graphic::SetSkeleton(Entities::Entity& entity, const Util::StringAtom& skeleton)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.skeleton[instance] = skeleton;
	}

	void Graphic::SetAnimation(Entities::Entity& entity, const Util::StringAtom& animation)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.animation[instance] = animation;
	}

	void Graphic::SetTag(Entities::Entity& entity, const Util::StringAtom& tag)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.tag[instance] = tag;
	}

	void Graphic::PlayAnimated(Entities::Entity& entity)
	{
		InstanceId instance = this->_instanceMap[entity];
		Characters::CharacterContext::PlayClip(this->_instanceData.graphicId[instance],
			nullptr, 0, 0, Characters::Append, 1.0f, 1, Math::n_rand() * 100.0f, 0.0f, 0.0f,
			Math::n_rand() * 100.0f);
	}

}