#pragma once


namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Model
	*  @{
	*/



	/** 
		���㹤��
		����ģ�Ͷ���,��������ʽ����
	*/
	class MeshVertexFactory : public RTTIObject
							, public VertexFactory
	{
		DECLARE_RTTI_CLASS( MeshVertexFactory, RTTIObject, ClassFlag_Intrinsic| ClassFlag_Serializable )

	public:
		MeshVertexFactory( );

		~MeshVertexFactory( );

		/// ��ȡ��������
		virtual DataStream*		GetVertexStream( ){ return mVertexStream; }

		/// ��ȡ��������
		virtual DataStream*		GetIndexStream( ){ return mIndexStream; }

		/// ��ȡ��������
		virtual dword				GetVertexCount( ){ return mVertexCount; }

		/// ��ȡ��ʽ
		virtual VertexFormat*		GetFormatData( ){ return mFormatData; }

		/// ��ȡ��������
		virtual dword				GetIndexCount( ){ return mIndexCount; }

		/// ��ȡ�󶨺�
		AABB GetStaticBoundingBox( );

	public:
		virtual void Serialize( BinarySerializer& Ser );

		void InitData(	const WString& Name, 
					dword VertexCount, 
					HeapStream* VertexStream,
					dword IndexCount,
					HeapStream* IndexStream,
					dword MaterialIndex );
	private:
		friend class MeshResource;
		WString				mName;
		dword				mMaterialIndex;

		dword				mVertexCount;
		dword				mIndexCount;

		HeapStream*			mIndexStream;
		HeapStream*			mVertexStream;
		VertexFormat*		mFormatData;
		AABB				mCachedAABB;
	};

	/** 
		ͨ��ģ����Դ
	*/
	class MeshResource : public ManagedObject
	{
		DECLARE_RTTI_CLASS( MeshResource, ManagedObject, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		MeshResource( );

		virtual ~MeshResource( );

		
		///	�����ģ�͵Ķ��㹤��
		dword AddVertexFactory( MeshVertexFactory* Factory );

		/// ��������
		dword GetVertexFactoryCount( );

		/// ��ȡ����
		MeshVertexFactory* GetVertexFactory( dword Index );
		
		/// ��ȡ����,ģ��
		template<typename TClass>
		TClass* GetVertexFactory( dword Index )
		{
			return RTTI_CAST(TClass, GetVertexFactory( Index ) );
		}

		/// ��ȡ�����ʽ
		VertexFormat& GetVertexFormat( ){ return mVertexFormat;}

		/// ��ȡ�󶨺�
		AABB GetBoundingBox( );

	public:
		virtual void Serialize( BinarySerializer& Ser );

	protected:
		virtual void PostLoad( );

		virtual bool IsManualResourceReady();

		virtual void BeginDispose( );

		virtual bool CanDestroyNow( );

	private:
		void InitializeVertexFactory( );
		
	protected:
		friend class VertexFactory;
		typedef std::vector<MeshVertexFactory*> VertexFactoryList;
		VertexFormat			mVertexFormat;

		VertexFactoryList		mVertexFactoryList;			
		RenderCommandFence		mReadyFence;
		RenderCommandFence		mReleaseFence;
		AsyncTaskFence		mStreamingFence;
	};

}
