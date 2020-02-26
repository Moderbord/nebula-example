#define __DeclareMessage(HASH) \
	static constexpr uint ID = HASH;

struct MyMsg
{
	__DeclareMessage('MyMs');
	int a = 0;
	float foo = 20.0f;
};

//class Message
//{
//public:
//	template<typename T>
//	explicit Message(T* data) :
//		type(T::ID),
//		data(data)
//	{
//		// for serialization
//		//static_assert(std::is_trivially_copyable<T>());
//	}
//
//	Message() = delete;
//
//	const uint type;
//	const void* data;
//};

//MyMsg m;
//m.a = 10;
//m.foo = 60.0f;
//Message msg = Message(&m);
//
//
//if (msg.type == MyMsg::ID)
//{
//	MyMsg* data = (MyMsg*)msg.data;
//
//}
