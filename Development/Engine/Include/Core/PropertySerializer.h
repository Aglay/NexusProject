#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Reflection
	*  @{
	*/


	class TextFile;
	class IniFile;
	class IniSection;

	class PropertySerializer;

	/** 
		�������л�����
	*/
	class PropertySerializerErrorCatcher
	{
	public:
		PropertySerializerErrorCatcher( PropertySerializer& Ser );

		virtual ~PropertySerializerErrorCatcher( );

		/** 
			д��һ������
		*/
		void WriteError( const WString& Section, const WString& Key );

		/// �Ƿ��д���
		bool HasError( ){ return mErrorArray.size() > 0; }

		/// ��������
		dword GetErrorCount( ){return mErrorArray.size(); }

		/// ��������
		bool GetErrorDesc( dword Index, WString& ErrorSec, WString& ErrorKey );

	private:
		PropertySerializer& mSer;

		struct ErrorDesc 
		{
			WString mSection;
			WString mKey;
			ErrorDesc( const WString& Sec, const WString& Key )
				: mSection( Sec )
				, mKey( Key )
			{

			}
		};

		typedef std::vector<ErrorDesc> ErrorArray;
		ErrorArray mErrorArray;
	};


	/** 
		INI��ʽ�������л�
	*/
	class PropertySerializer
	{
	public:
		PropertySerializer( const wchar* FileName, bool IsLoading );

		virtual ~PropertySerializer( );

		/// ���л�Ini�Ķ�
		bool SerializeSection( const WString& Name );

		/// ��ȡ��ǰ���л��Ķ�
		const WString& GetSection( );

		/// ��ǰ�Ƿ�Ϊ��ȡ״̬
		bool IsLoading( );

		/// ��ǰ�Ƿ�Ϊ����״̬
		bool IsSaving( );

		/// ��ȡ�������
		PropertySerializerErrorCatcher* GetErrorObject( );

		/// ����Key
		friend PropertySerializer& operator<<( PropertySerializer& Ser, const wchar_t* Key )
		{
			// ��Ϊkey
			Ser.mKey = Key;

			return Ser;
		}

		/// ʹ��value_����ƥ�����ͣ�ע����������ȷ��
		template<typename TType>
		friend PropertySerializer& operator<<( PropertySerializer& Ser, const TType& Data )
		{
			PropertySerializerErrorCatcher* ErrorObj = Ser.GetErrorObject();

			if ( Ser.mSectionData == null )
			{
				if ( ErrorObj != NULL )
					ErrorObj->WriteError( L"Section not found", Ser.mKey );

				return Ser;
			}

			assert( Ser.IsSaving() );

			if ( Ser.IsSaving() )
			{
				Ser.mSectionData->AddData( mKey, value_tostringW(Data) );
			}

			return Ser;
		}

		/// ʹ��value_����ƥ�����ͣ�ע����������ȷ��
		template<typename TType>
		friend PropertySerializer& operator<<( PropertySerializer& Ser, TType& Data )
		{				
			PropertySerializerErrorCatcher* ErrorObj = Ser.GetErrorObject();

			if ( Ser.mSectionData == null )
			{
				if ( ErrorObj != NULL )
					ErrorObj->WriteError( L"Section not found", Ser.mKey );

				return Ser;
			}
			if ( Ser.IsSaving() )
			{
				Ser.mSectionData->AddData( Ser.mKey, value_tostringW( Data ).c_str() );
			}
			else
			{				
				WString Result;
				if ( Ser.mSectionData->Read( Ser.mKey, Result ) )
				{
					value_parse( Result.c_str(), Data );
				}
				else 
				{

					if ( ErrorObj != NULL )
						ErrorObj->WriteError( Ser.mSectionData->GetName(), Ser.mKey );
				}

			}

			return Ser;
		}
		

		/// ʹ��value_����ƥ�����ͣ�ע����������ȷ��
		template<typename TType>
		friend PropertySerializer& operator<<( PropertySerializer& Ser, std::vector<TType>& DataArray )
		{				
			PropertySerializerErrorCatcher* ErrorObj = Ser.GetErrorObject();

			if ( Ser.mSectionData == null )
			{
				if ( ErrorObj != NULL )
					ErrorObj->WriteError( L"Section not found", Ser.mKey );

				return Ser;
			}
			if ( Ser.IsSaving() )
			{
				for ( dword i = 0;i< DataArray.size();i++)
				{
					Ser.mSectionData->AddData( Ser.mKey, value_tostringW( DataArray[i] ).c_str() );
				}
			}
			else
			{	

				Ser.mSectionData->SetSearchKey( Ser.mKey );

				WString Result;
				while( Ser.mSectionData->GetNextPairData( Result ) )
				{
					TType Data;
					value_parse( Result.c_str(), Data );

					DataArray.push_back( Data );
				}
			}

			return Ser;
		}

	public:
		IniFile*		mIniFile;

		WString			mKey;

		IniSection*		mSectionData;

		WString*		mSaveFileName;

		typedef std::list<PropertySerializerErrorCatcher*> ErrorObjectStack;
		ErrorObjectStack mErrorObjectStack;
	};

	//void GameEngine::SerializeConfig( PropertySerializer& Ser )
	//{
	//	Ser.SerializeSection(L"Option" )
	//		<< L"UseThreadRendering" << mUseThreadRendering
	//		<< L"UseThreadStreaming" << mUseThreadStreaming
	//		<< L"UseShaderCache" << mUseShaderCache
	//		<< L"ShowGrid"		<< mShowGrid;


	//	Ser.SerializeSection( L"Debug" ) 
	//		<< L"CameraPosition";
	//}

	/** @} */
	/** @} */
}