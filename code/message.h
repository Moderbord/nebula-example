#pragma once
#include "math/matrix44.h"
#include "entity.h"

#define p_DeclareMessage(HASH) \
	static constexpr uint ID = HASH;

namespace Message
{

	struct SendTransform
	{
		p_DeclareMessage('sTrf');
		Math::matrix44 mat; // gives identity matrix
		Entities::Entity targetId;
	};

	struct SendMove
	{
		p_DeclareMessage('sMov');
		Math::float4 vec = Math::float4(0, 0, 0, 0);
		Entities::Entity targetId;
	};

	struct Deregister
	{
		p_DeclareMessage('dReg');
		Entities::Entity targetId;
	};

	class Message
	{
	public:
		template<typename T>
		explicit Message(T* data) :
			type(T::ID),
			data(data)
		{
			// for serialization
			//static_assert(std::is_trivially_copyable<T>());
		}

		Message() = delete;

		const uint type;
		const void* data;
	};

	template<typename COMPONENT>
	void Component(const Message& msg)
	{
		COMPONENT::Instance()->OnMessage(msg);
	}

	template<typename MANAGER>
	void Manager(const Message& msg)
	{
		MANAGER::Instance()->OnMessage(msg);
	}


}