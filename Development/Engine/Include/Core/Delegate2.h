#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Reflection
	*  @{
	*/

	/** 
		���������
	*/
	template<typename TSender, typename TArg> 
	class delegate2_handler 
	{ 
	public: 
		virtual void operator()( TSender sender, TArg args ) = 0;
		virtual delegate2_handler* clone( ) = 0;
	};

	/** 
		����̬�������
	*/
	template<typename functype, typename TSender, typename TArg> 
	class delegate2_statichandler : public delegate2_handler<typename TSender, typename TArg>
	{ 
	public: 
		delegate2_statichandler(){} 
		delegate2_statichandler(functype &func) 
			: m_func(func) 
		{ 
		}

		virtual void operator()(TSender sender, TArg args) 
		{ 
			m_func( sender, args ); 
		}

		virtual delegate2_handler* clone( )
		{
			return new delegate2_statichandler<functype>(m_func);
		}

	protected: 
		functype    m_func; 
	};

	/** 
		�����Ա�������
	*/
	template<typename callee, typename functype, typename TSender, typename TArg> 
	class delegate2_memberhander : public delegate2_handler <typename TSender, typename TArg>
	{ 
	public: 
		delegate2_memberhander(){} 
		delegate2_memberhander(callee* obj, functype func) 
			: m_callee(obj) 
			, m_func(func) 
		{ 
		}

		virtual void operator()(TSender sender, TArg args) 
		{ 
			(m_callee->*m_func)(sender, args); 
		}

		virtual delegate2_handler* clone( )
		{
			return new delegate2_memberhander<callee, functype, TSender, TArg>(m_callee, m_func);
		}

	protected: 
		functype    m_func; 
		callee*    m_callee; 
	};

	/** 
		�򵥴���2��
		@remark
			֧��C/C++ ����,��̬����,���Ա������Ϊ�ص�
		@param
			TSender �ص���sender����
		@param
			TArg �ص���Arg����
	*/
	template<typename TSender, typename TArg> 
	class delegate2 
	{ 
	public: 
		/** 
			���캯��
		*/
		delegate2() 
			: m_handler(0) 
		{ 
		}

		/** 
			�������캯��
		*/
		delegate2( const delegate2& other )
			: m_handler(0) 
		{
			assign( other );
		}

		/** 
			��ֵ����
		*/
		delegate2& operator = ( const delegate2& other)
		{
			return assign( other );
		}

		/** 
			��һ��C������̬��Ա����
			@param
				func ��Ҫ�󶨵ĺ���
			@remark
				����: xx.bind( class::staticfunc );
		*/
		template<typename functype> 
		delegate2<TSender, TArg>& bind( functype func ) 
		{ 
			m_handler = new delegate2_statichandler<functype, TSender, TArg>(func);

			return *this;
		}

		/** 
			��һ��C++���Ա����
			@param
				obj ����ʵ��
			@param
				func ��Ҫ�󶨵ĺ���
			@remark
				����: xx.bind( classptr, &class::memberfunc );
		*/
		template<typename callee, typename functype> 
		delegate2<TSender, TArg>& bind( callee* obj, functype func ) 
		{ 
			m_handler = new delegate2_memberhander<callee, functype, TSender, TArg>(obj, func); 

			return *this;
		}

		/** 
			��ֵ
		*/
		delegate2& assign( const delegate2& other )
		{
			clear();

			if ( other.m_handler )
				m_handler = other.m_handler->clone();

			return *this;
		}

		/** 
			ȡ����
		*/
		void clear( )
		{
			if ( m_handler )
				delete m_handler;
		}

		virtual ~delegate2() 
		{ 
			clear();
		}

		/** 
			���Ƿ���Ч
		*/
		bool valid( )
		{
			return m_handler != 0;
		}

		/** 
			���ð󶨵ĺ���
		*/
		void invoke(TSender sender, TArg args)
		{
			if (!m_handler)
				return;

			(*m_handler)(sender, args); 
		}


	private: 
		delegate2_handler<TSender, TArg>     *m_handler; 
	};

	/** @} */
	/** @} */
}


//class MyClass
//{
//public:
//	void foo(int sender, MemoryStream* args)
//	{
//		Console::WriteLine( args.ReadUNICODEString().c_str() );
//	}
//};
//
//
//
//int wmain( )
//{
//	ByteStream s;
//	s.WriteUNICODEString( L"hello");
//
//	MyClass b;
//	delegate2<int, MemoryStream*> a( &b, &MyClass::foo );
//	a.invoke( 0, s );
//}