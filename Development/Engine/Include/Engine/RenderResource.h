#pragma once


namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/


	/** 
		��Ⱦ��Դ����
	*/
	class RenderResource
	{
	public:

		/** 
			@return
				ȫ�ֳ�ʼ�������Դ�б�
		*/
		static TLinkedList<RenderResource*>*& GetResourceList();

		RenderResource():
			mInitialized(false)
		{}

		virtual ~RenderResource(){}

		/** 
			��ʼ����̬��Դ,ʹ��Dynamic��־��������Դ
		*/
		virtual void InitDynamicRHI() {}

		/** 
			ж�ض�̬��Դ
		*/
		virtual void ReleaseDynamicRHI() {}

		/** 
			��ʼ��Managed��Դ
		*/
		virtual void InitRHI() {}

		/** 
			ж��Managed��Դ
		*/
		virtual void ReleaseRHI() {}

		/** 
			����Դ������Ⱦ�߳̿�ʼ�첽��ʼ��
		*/
		virtual void BeginInitResource( );

		/** 
			����Դ������Ⱦ�߳̿�ʼ�첽ж��
		*/
		virtual void BeginReleaseResource( );

		/** 
			��������Դ����
		*/
		void operator=(const RenderResource& OtherResource) {}

		/** 
			��Դ�Ƿ��ʼ�����
		*/
		bool IsInitialized() const { return mInitialized; }

	protected:
		/// �ֶ���ʼ����Դ
		void Init();

		/// �ֶ�ж����Դ
		void Release();

		void UpdateRHI();
	private:

		TLinkedList<RenderResource*> mResourceLink;

		bool mInitialized;
	};

	/** @} */
	/** @} */
}