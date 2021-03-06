#pragma once
#include "core/singleton.h"
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "util/arraystack.h"
#include "util/array.h"
#include "componentinterface.h"
#include "entity.h"

/*
	Header file for all components

	TODO handle fragmantation
*/
namespace Component {
	//------------------------------------------------------------------------------
	/**
		Transform component
	*/
	class Transform : public ComponentInterface
	{
		__DeclareSingleton(Component::Transform)
		const Math::matrix44 _identityMatrix;

	public:
		Transform();
		~Transform();

		void OnRegister(const Entities::Entity& entity);
		void OnDeregister(const Entities::Entity& e);
		void OnReset(const Entities::Entity& entity, const InstanceId& instance);
		void OnBeginFrame();
		void OnRender();
		void OnEndFrame();
		void OnMessage(const Message::Message& msg);

		struct Attributes{
			Util::Array<Entities::Entity> owners;
			Util::Array<Math::matrix44> transform;
		};

		const Entities::Entity GetOwner(const InstanceId& instance);

		Math::matrix44 GetTransform(const Entities::Entity& entity);
		void SetTransform(const Entities::Entity& entity, const Math::matrix44 transform);

	private:
		// Contains the data for each entity in an array
		Attributes _instanceData;
	};

	//------------------------------------------------------------------------------
	/**
		Graphic component
	*/
	class Graphic : public ComponentInterface
	{
		__DeclareSingleton(Component::Graphic)

	public:
		Graphic();
		~Graphic();

		void OnRegister(const Entities::Entity& entity);
		//template<typename T>
		void OnDeregister(const Entities::Entity& e);
		void OnReset(const Entities::Entity& entity, const InstanceId& instance);
		void OnBeginFrame();
		void OnRender();
		void OnEndFrame();
		void OnMessage(const Message::Message& msg);

		struct Attributes {
			Util::Array<Entities::Entity> owners;
			Util::Array<Graphics::GraphicsEntityId> graphicId;
			Util::Array<Util::StringAtom> resourceName;
			Util::Array<Util::StringAtom> skeleton;
			Util::Array<Util::StringAtom> animation;
			Util::Array<Util::StringAtom> tag;
		};

		const Entities::Entity GetOwner(const InstanceId& instance);

		void SetResourceName(const Entities::Entity& entity, const Util::StringAtom& resource);
		void SetSkeleton(const Entities::Entity& entity, const Util::StringAtom& skeleton);
		void SetAnimation(const Entities::Entity& entity, const Util::StringAtom& animation);
		void SetTag(const Entities::Entity& entity, const Util::StringAtom& tag);

		void Setup(const Entities::Entity& entity);
		void SetupAnimated(const Entities::Entity& entity);
		void Remove(const Entities::Entity& entity);
		void PlayAnimated(const Entities::Entity& entity);

	private:
		// Contains the data for each entity in an array
		Attributes _instanceData;
	};
}

