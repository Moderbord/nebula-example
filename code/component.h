#pragma once
#include "core/singleton.h"
#include "util/hashtable.h"
#include "util/stringatom.h"
#include "util/arraystack.h"
#include "util/array.h"
#include "componentinterface.h"
#include "entity.h"

namespace Component {
	//------------------------------------------------------------------------------
	/**
		Transform component
	*/
	class Transform : public ComponentInterface
	{
		__DeclareSingleton(Component::Transform)
		const Math::matrix44 _identityMatrix = Math::matrix44::translation(Math::point(0, 0, 0));

	public:
		Transform();
		~Transform();

		void OnRegister();
		void OnReset(InstanceId& instance);
		void OnBeginFrame();
		void OnRender();
		void OnEndFrame();
		void Clear();
		void OnDestroy();

		struct Attributes{
			Util::ArrayStack<Math::matrix44, MaxNumInstances> transform;
		};

		Math::matrix44 GetTransform(Entities::Entity& entity);
		void SetTransform(Entities::Entity& entity, Math::matrix44 transform);

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

		void OnRegister();
		void OnReset(InstanceId& instance);
		void OnBeginFrame();
		void OnRender();
		void OnEndFrame();
		void Clear();
		void OnDestroy();

		struct Attributes {
			Util::ArrayStack<Graphics::GraphicsEntityId, MaxNumInstances> graphicId;
			Util::ArrayStack<Util::StringAtom, MaxNumInstances> resourceName;
			Util::ArrayStack<Util::StringAtom, MaxNumInstances> skeleton;
			Util::ArrayStack<Util::StringAtom, MaxNumInstances> animation;
			Util::ArrayStack<Util::StringAtom, MaxNumInstances> tag;
		};

		void Setup(Entities::Entity& entity);
		void SetupAnimated(Entities::Entity& entity);

		void SetResourceName(Entities::Entity& entity, const Util::StringAtom& resource);
		void SetSkeleton(Entities::Entity& entity, const Util::StringAtom& skeleton);
		void SetAnimation(Entities::Entity& entity, const Util::StringAtom& animation);
		void SetTag(Entities::Entity& entity, const Util::StringAtom& tag);

		void PlayAnimated(Entities::Entity& entity);

	private:
		// Contains the data for each entity in an array
		Attributes _instanceData;
	};
}

