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
		// Set transform?
		//Models::ModelContext::SetTransform
		Visibility::ObservableContext::Setup(graphicId, Visibility::VisibilityEntityType::Model);

	}

	void Graphic::SetupAnimated(Entities::Entity& entity)
	{

	}

	void Graphic::SetResourceName(Entities::Entity& entity, Util::StringAtom& resource)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.resourceName[instance] = resource;
	}

	void Graphic::SetSkeleton(Entities::Entity& entity, Util::StringAtom& skeleton)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.skeleton[instance] = skeleton;
	}

	void Graphic::SetAnimation(Entities::Entity& entity, Util::StringAtom& animation)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.animation[instance] = animation;
	}

	void Graphic::SetTag(Entities::Entity& entity, Util::StringAtom& tag)
	{
		InstanceId instance = this->_instanceMap[entity];
		this->_instanceData.tag[instance] = tag;
	}

}