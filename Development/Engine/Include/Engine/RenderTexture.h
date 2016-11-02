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
		���ڱ���������Ļ���,�Ա�ʵ��MipMap
	*/
	class TextureMipMap
	{
	public:
		TextureMipMap( );

		/** 
			����ͼƬ��С��ռ�õ��ڴ�
			@param
				SizeX,SizeY �ߴ��С
			@param
				PixelFormat ���ظ�ʽ
			@return
				ͼƬ��ռ�ô�С
		*/
		static dword CalculateImageBytes( dword SizeX, dword SizeY, ePixelFormat PixelFormat );

		/** 
			���仺��
			@param
				DataSize ����ʹ��CalculateImageBytes�������,DDSѹ����ʽ����
			@param
				MipCount �����ж��ٲ�,������1��
			@return
				����õ��ڴ�
			@remark
				������ɺ�,����ʹ��SetMip����ÿ�����Ϣ
		*/
		_byte* Alloc( dword DataSize, dword MipCount = 1 );

		
		/** 
			��ò�ͬMip�������
			@param
				MipIndex ���(base 0)
			@param
				Bytes ���ر���ռ�õ�Bytes��
			@return
				���㿪ʼ���ڴ�ָ��
		*/
		_byte* GetMip( dword MipIndex, dword& Bytes );

		/** 
			���ò�ͬMip�������
			@param
				MipIndex ���(base 0)
			@param
				Data ������Դ
			@param
				Bytes ����ռ�õ�Bytes��
		*/
		void SetMip( dword MipIndex, _byte* Data, dword Bytes  );

		/// �ͷ��ڴ�
		void Free( );	

		/** 
			��ȡ������
		*/
		dword GetMipCount( ){ return mMipCount; }

	private:		
		_byte*			mData;
		dword			mDataSize;
		dword			mMipCount;

		struct MipLevelData 
		{
			_byte*		mDataRef;
			dword		Size;
		};

		enum{ MAX_MIP_LEVEL = 8 };

		MipLevelData	mMips[MAX_MIP_LEVEL];
	};


	/** 
		��Ⱦ�������
		@remark
			��װRHI����Ⱦ�߳��첽��ʼ������,��Ҫȫ���ֶ�����������
	*/
	class RenderTexture: public RenderResource
	{
	public:
		RenderTexture( );

		virtual ~RenderTexture( );

		/** 
			��Ⱦ�̳߳�ʼ��������
			@remark
				�����ؼ����Լ���Ҫ��ʼ���Ķ���
		*/
		virtual void InitRHI( );

		/** 
			��Ⱦ�߳�ж�ز�����������
			@remark
				�����ؼ����Լ���Ҫж�صĶ���
		*/
		virtual void ReleaseRHI();

		/// ��ʼ����Ⱦ�߳�ж��D3D��Դ
		virtual void BeginReleaseResource( );

		/// �ܷ�ɾ������ʵ��
		bool ReadyForDestory( );

		/// �����Ƿ���Ч
		bool Valid( );

		/// �ύ����������
		void Commit( dword SamplerIndex );

		/// �����ȴ��ͷ����
		void WaitRelease( );

		/// ����������
		dword GetWidth( );

		/// ��������߶�
		dword GetHeight( );

		/// ���RHI������
		RHITextureRef GetTextureRHI(){ return mTextureRHI; }

		/// ���RHI��Ĳ�����״̬
		RHISamplerStateRef GetSamplerStateRHI( ){ return mSamplerStateRHI;}

	protected:
	
		RHITextureRef		mTextureRHI;

		RHISamplerStateRef	mSamplerStateRHI;

	protected:
		void InitSampler( );
		void ReleaseSamplerTexture( );		
		RenderCommandFence	mReleaseFence;	// ��������ͬ����
		
	};



	class TextureResource;
	class RHITexture2D;

	/** 
		��ά����,����һ���ڴ����ݻ���
	*/
	class RenderTexture2D: public RenderTexture
	{
	public:
		RenderTexture2D( );

		virtual ~RenderTexture2D( );

		/** 
			��ʼ��ʼ������
			@param
				SizeX,SizeY �����С
			@param
				PixelFormat ���ظ�ʽ
			@remark
				�ڵ���ǰӦʹ��GetMips���MipMapBuffer
			@par
				���ú�,��ʼ�첽��Ⱦ�̳߳�ʼ��,�����ݷ���GPU
		*/
		void BeginInitResource( dword SizeX, dword SizeY, ePixelFormat PixelFormat );

		virtual void InitRHI( );

		TextureMipMap& GetMips( ){ return mDataSrc;}

	private:
		dword			mSizeX;
		dword			mSizeY;
		ePixelFormat	mPixelFormat;
		TextureMipMap	mDataSrc;// ������Դ		
	};



	/** 
		�հ�����ʵ��
	*/
	class WhiteTexture: public RenderTexture
	{
	public:
		static void StaticInit( );

		static void StaticExit( );

		virtual void InitRHI( );
		
	};

	/// �հ�����
	extern WhiteTexture* GWhiteTexture;

	/** 
		����������	
	*/
	class CheckerTexture: public RenderTexture
	{
	public:
		CheckerTexture(  );

		static void StaticInit( );

		static void StaticExit( );

		virtual void InitRHI( );
	private:
		dword mCheckerSize;
	};

	/// ����������
	extern CheckerTexture* GCheckerTexture;

	/** @} */
	/** @} */
}
