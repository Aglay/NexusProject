#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	/** 
		��Դ����
	*/
	enum eResourceType
	{
		RFT_Unknown = 0,
		RFT_SkeletonAnimation,	///< SA ��������
		RFT_SkeletonMesh,		///< SK ����ģ��
		RFT_StaticMesh,			///< SM ��̬ģ��
		RFT_Texture,			///< TX ����
		RFT_MaterialInstance,	///< MI ����ʵ��
		RFT_Material,			///< MT ��������
		RFT_ShaderFile,			///< SF Shader�ļ�
		RFT_MaxResourceType,
	};

	/** 
		��Դ��������
		@remark
			��Դ���ǽ����·���еķָ���תΪ.����Դ��
			���Ҫ����Դ���в���Я����
	*/
	class ResourceLocation
	{
	public:
		/**
			�޸���Դ������
			@param
				ResourceName ԭ��Դ��
			@param
				OutResourceName �����Դ��
			@param
				Type ��Դ����
			@return
				��Դ�����Ƿ�����������
		*/
		static bool ModifyType( const WString& ResourceName, WString& OutResourceName, eResourceType Type );

		/**
			����Դ������Ϊƽ̨·��
			@param
				ResourceName ��Դ��
			@return
				ƽ̨½��
		*/
		static WString Resovle(const WString& ResourceName );

		/**
			��ƽ̨·��ת��Ϊ��Դ��
			@param
				FileName ����·��
			@return
				��Դ��
		*/
		static WString Build( const WString& FileName );

		/**
			������Դ������Դ����
			@param
				ResourceName ��Դ��
			@return
				��Դ����
		*/
		static eResourceType ParseType( const WString& ResourceName );

		/**
			��ȡ��Դ���͵���չ��
			@param
				Type ��Դ����
			@return
				��չ��,����: .SA
		*/
		static WString GetExtension( eResourceType Type );
	};


	/** 
		��Դ���Զ����
	*/
	template<typename TClass>
	class ResourcePtrMarker
	{
	public:
		ResourcePtrMarker( )
			: mIsDirty( false )
		{

		}

		virtual ~ResourcePtrMarker( ){}


		void operator = ( const TClass& Resource )
		{
			mResource = Resource;
			mIsDirty = true;
		}

		/** 
			��Դ�Ƿ���Ч
		*/
		bool Valid( )
		{
			return mResource.Valid( );
		}

		/** 
			��Դ�Ƿ�Ϊ��
		*/
		bool Empty( )
		{
			return mResource.Empty( );
		}

		/** 
			��Դ�Ƿ�׼����, �����Դ������,������,û��׼����
		*/
		bool IsResourceReady( )
		{
#ifdef _DEBUG			

			if ( mIsDirty )
				return false;

			if ( !mResource.Valid() )
				return false;

			return mResource->IsResourceReady( );
#else
			return !mIsDirty && mResource.Valid() && mResource->IsResourceReady( );
#endif

			
		}

		/** 
			��Դ�Ƿ���
		*/
		bool IsDirty( )
		{
			return mIsDirty;
		}

		/** 
			��Դ�Ƿ���Ը���
		*/
		bool CheckReadyToUpdate( )
		{
			return mIsDirty && mResource.Valid() && mResource->IsResourceReady( );
		}

		/** 
			�������־
		*/
		void ClearFlag( )
		{
			mIsDirty = false;
		}

		TClass& GetResource( )
		{
			return mResource;
		}

		const TClass& GetResource( ) const
		{
			return mResource;
		}

	private:
		TClass	mResource;
		bool	mIsDirty;
	};

	/** @} */
	/** @} */
}
