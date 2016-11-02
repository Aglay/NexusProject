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
		������Դ
		@remark
			ӵ�����һ��ջ���
	*/
	class TextureResource :	public ManagedObject
	{
		DECLARE_RTTI_CLASS( TextureResource, ManagedObject, ClassFlag_Intrinsic )

	public:
		TextureResource( );

		virtual ~TextureResource( );

		/** 
			������
		*/
		dword GetWidth( ){ return mRenderTexture->GetWidth(); }

		/** 
			����߶�
		*/
		dword GetHeight( ){ return mRenderTexture->GetHeight(); }

		/** 
			�����Ⱦ������
		*/
		RenderTexture* GetRenderTexture( );
		
		virtual void Serialize( BinarySerializer& Ser );

	private:
		virtual bool CanDestroyNow();

		/// ������ɾ���ύ����Ⱦ�߳�
		virtual void BeginDispose( );

		/// ��������Ƿ���غ�
		virtual bool IsManualResourceReady();

		/// ��Ϸ�߳�
		virtual void PostLoad( );

		

	private:
		friend class RenderTexture2D;
		AsyncTaskFence			mStreamingFence;
		RenderCommandFence		mReadyFence;
		RenderTexture2D*		mRenderTexture;
		DDSTextureParameter		mDDSParamter;
	};

	typedef TRefPtr<TextureResource> TextureResourcePtr;

	/** @} */
	/** @} */
}
