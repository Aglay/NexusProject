#pragma once

namespace NekoEngine
{
	#pragma warning( disable:4291 )

	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/


	/** 
		��Ⱦָ��
	*/
	class RenderCommand
	{
	public:
		
		/** 
			ʹ�÷���������һ����Ⱦָ��
			@param
				Size ��Ҫ����Ĵ�С
			@param
				Allocation ������
			@remark
				����:new(ringbuffer::alloc_context(GRenderThread.mRenderCommandBuffer,sizeof(TypeName))) TypeName Params;
		*/		
		void* operator new(size_t Size,const ringbuffer::alloc_context& Allocation)
		{
			return Allocation.get_alloc();
		}

		virtual ~RenderCommand() {}

		/** 
			��Ⱦ�߳�ִ��ָ��
		*/
		virtual dword Execute() = 0;

		/** 
			ָ������
		*/
		virtual const char* DescribeCommand() = 0;
	};

	/** 
		��Ⱦָ��ͬ����
	*/
	class RenderCommandFence
	{
	public:
		RenderCommandFence():
			NumPendingFences(0)
		{}

		/** 
			���һ��ͬ��������Ⱦ�߳�
			һ�����������Լ�һ
			����Ⱦ�߳�ִ��������ָ���,���������Լ�һ
		*/
		void BeginFence();


		/** 
			�ȴ���Ⱦͬ��ָ�ִ��
			@param
				NumFencesLeft ָ���ȴ�ʣ�¶���ָ���ֹͣ
			@remark
				��������һֱ����ֱ��ǰ��ָ��ȫ����ִ�����
		*/
		void Wait( dword NumFencesLeft=0 ) const;

		/** 
			��û�ʣ�¶���ָ��
		*/
		dword GetNumPendingFences() const { return NumPendingFences; }

	private:
		volatile dword NumPendingFences;
	};

	/** 
		��Ⱦ�߳�
	*/
	class RenderThread
	{
	public:
		RenderThread( );

		/** 
			ˢ���߳������е���Ⱦָ��
		*/
		float Flush();

		/** 
			������Ⱦ�߳�
		*/
		void Start( );

		/** 
			ֹͣ��Ⱦ�߳�
		*/
		void Stop( );

		/**
			֪ͨ�߳̿�ʼ����
		*/
		void NotifyNewTask( );

		/// �Ƿ���
		bool IsEnable( ){ return mEnable; }

	public:
		/// ��״���������̼߳����񽻻�
		ringbuffer	mRenderCommandBuffer;

		bool		mEnable;

		Thread		mRenderThread;

		EventObject mRenderEvent;
	};

	extern RenderThread GRenderThread;


	#define ENQUEUE_RENDER_COMMAND(TypeName,Params) \
	{ \
		if(GRenderThread.mEnable) \
		{ \
			new(ringbuffer::alloc_context(GRenderThread.mRenderCommandBuffer,sizeof(TypeName))) TypeName Params; \
			GRenderThread.NotifyNewTask();\
		} \
		else \
		{ \
			TypeName Command Params; \
			Command.Execute(); \
		} \
	}

	/**
	 * Declares a rendering command type with 0 parameters.
	 */
	#define ENQUEUE_UNIQUE_RENDER_COMMAND(TypeName,Code) \
		class TypeName : public RenderCommand \
		{ \
		public: \
			virtual dword Execute() \
			{ \
				Code; \
				return sizeof(*this); \
			} \
			virtual const char* DescribeCommand() \
			{ \
				return #TypeName; \
			} \
		}; \
		ENQUEUE_RENDER_COMMAND(TypeName,);



	#define ENQUEUE_UNIQUE_RENDER_COMMAND_ONEPARAMETER(TypeName,ParamType1,ParamName1,ParamValue1,Code) \
	class TypeName : public RenderCommand \
	{ \
	public: \
		typedef ParamType1 _ParamType1; \
		TypeName(const _ParamType1& In##ParamName1): \
		  ParamName1(In##ParamName1) \
		{} \
		virtual dword Execute() \
		{ \
			Code; \
			return sizeof(*this); \
		} \
		virtual const char* DescribeCommand() \
		{ \
		return #TypeName; \
		} \
	private: \
		ParamType1 ParamName1; \
	}; \
	ENQUEUE_RENDER_COMMAND(TypeName,(ParamValue1));

/**
 * Declares a rendering command type with 2 parameters.
 */
#define ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(TypeName,ParamType1,ParamName1,ParamValue1,ParamType2,ParamName2,ParamValue2,Code) \
	class TypeName : public RenderCommand \
	{ \
	public: \
		typedef ParamType1 _ParamType1; \
		typedef ParamType2 _ParamType2; \
		TypeName(const _ParamType1& In##ParamName1,const _ParamType2& In##ParamName2): \
		  ParamName1(In##ParamName1), \
		  ParamName2(In##ParamName2) \
		{} \
		virtual dword Execute() \
		{ \
			Code; \
			return sizeof(*this); \
		} \
		virtual const char* DescribeCommand() \
		{ \
		return #TypeName; \
		} \
	private: \
		ParamType1 ParamName1; \
		ParamType2 ParamName2; \
	}; \
	ENQUEUE_RENDER_COMMAND(TypeName,(ParamValue1,ParamValue2));

	/** @} */
	/** @} */
}
