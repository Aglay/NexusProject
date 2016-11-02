#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Reflection
	*  @{
	*/

	// Work with RTTIObject
	class DataStream;

	/** 
		���������л���
	*/
	class BinarySerializer
	{
	public:
		/** 
			����ʱ��Ϊ���л�������Դ
			@param
				Stream ����Դ
			@param
				IsLoading �Ƿ�Ϊ����
		*/
		BinarySerializer( DataStream* Stream, bool IsLoading ); 

		static void StaticInit( );

		static void StaticExit( );

		/// �Ƿ�Ϊ����ģʽ
		bool IsLoading( ){ return mIsLoading; }

		/// �Ƿ�Ϊ����ģʽ
		bool IsSaving( ){ return !mIsLoading; }

		/// ��ȡ�ļ�ͷ��,�Ƿ�����

		bool IsStreamOK( ){ return mStreamOK; }
		/** 
			���л��ļ�ͷ
			@remark
				Loadingʱ��Version��0
		*/
		void SerializerFileHeader( dword  Version );

		/** 
			дRTTI����ͷ
		*/
		void WriteObject( RTTIObject* Obj );

		/** 
			��ȡһ��RTTI����
		*/
		RTTIObject* ReadObject(  );

		/** 
			ȡ���л����õ���
		*/
		DataStream* GetStream( );

		/** 
			ȡ�ð汾��
		*/
		dword GetVersion(){ return mVersion; }

	public:

		/// ���Constant���������
		template<typename TType>
		friend BinarySerializer& operator<<( BinarySerializer& Ser, const TType& Data )
		{
			Assert ( Ser.IsSaving() );

			Ser.GetStream()->WriteTypes( Data );

			return Ser;
		}

		/// �������ͣ���������̬�����ڴ��Ա��
		template<typename TType>
		friend BinarySerializer& operator<<( BinarySerializer& Ser, TType& Data )
		{
			if ( Ser.IsLoading() )
			{
				Ser.GetStream()->ReadTypes( Data );
			}
			else
			{
				Ser.GetStream()->WriteTypes( Data );
			}

			return Ser;
		}

		/// ��������
		template<typename TType>
		friend BinarySerializer& operator<<( NekoEngine::BinarySerializer& Ser, std::vector<TType>& Data )
		{
			dword Size = 0;

			if ( Ser.IsLoading() )
			{
				// ȡsize
				Ser << Size;
				Data.resize( Size );
			}
			else
			{
				// ��size
				Size = Data.size();
				Ser << Size;
			}

			// ��ȡ����
			for ( dword i = 0;i< Size;i++)
			{
				Ser << Data[i];
			}

			return Ser;
		}

		/// ����ָ������
		template<typename TType>
		friend BinarySerializer& operator<<( NekoEngine::BinarySerializer& Ser, std::vector<TType*>& Data )
		{
			dword Size = 0;

			if ( Ser.IsLoading() )
			{
				// ȡsize
				Ser << Size;
				Data.resize( Size );

				// ��ȡ����
				for ( dword i = 0;i< Size;i++)
				{
					TType* Mem = null;		// ���Լ���������������Ҫ���new
					Ser << Mem;
					Data[i] = Mem;
				}
			}
			else
			{
				// ��size
				Size = Data.size();
				Ser << Size;

				// ��ȡ����
				for ( dword i = 0;i< Size;i++)
				{
					Ser << Data[i];
				}
			}

			return Ser;
		}

		/// �б�ָ������
		template<typename TType>
		friend BinarySerializer& operator<<( NekoEngine::BinarySerializer& Ser, std::list<TType*>& Data )
		{
			if ( Ser.IsLoading() )
			{
				dword Size = 0;
				// ȡsize
				Ser << Size;

				// ��ȡ����
				for ( dword i = 0;i< Size;i++)
				{
					TType* Mem;
					Ser << Mem;
					Data.push_back( Mem );
				}
			}
			else
			{
				// ��size
				Ser << (dword)Data.size();

				// ��ȡ����
				for ( std::list<TType*>::iterator it = Data.begin();
					it != Data.end();
					++it)
				{
					TType* Mem = *it;
					Ser << Mem;
				}
			}

			return Ser;
		}

		/// �б�����
		template<typename TType>
		friend BinarySerializer& operator<<( NekoEngine::BinarySerializer& Ser, std::list<TType>& Data )
		{
			if ( Ser.IsLoading() )
			{
				dword Size = 0;
				// ȡsize
				Ser << Size;

				// ��ȡ����
				for ( dword i = 0;i< Size;i++)
				{
					TType Mem;
					Ser << Mem;
					Data.push_back( Mem );
				}
			}
			else
			{
				// ��size
				Ser << (dword)Data.size();

				// ��ȡ����
				for ( std::list<TType>::iterator it = Data.begin();
					it != Data.end();
					++it)
				{
					TType& Mem = *it;
					Ser << Mem;
				}
			}

			return Ser;
		}


		/// map����
		template<typename TKey, typename TValue >
		friend BinarySerializer& operator<<( NekoEngine::BinarySerializer& Ser, std::map<TKey, TValue>& Data )
		{

			if ( Ser.IsLoading() )
			{
				dword Size = 0;
				Ser << Size;
				for ( dword i = 0;i< Size;i++)
				{
					TKey Key;
					TValue Value;
					Ser << Key << Value;

					Data[ Key ] = Value;
				}
			}
			else
			{
				Ser << (dword)Data.size();

				// ��ȡ����
				for ( std::map<TKey, TValue>::iterator it = Data.begin();
					it != Data.end();
					++it)
				{
					Ser << it->first << it->second;
				}
			}
	

			return Ser;
		}

		/// Hash����
		template<typename TKey, typename TValue >
		friend BinarySerializer& operator<<( NekoEngine::BinarySerializer& Ser, dynamic_hash<TKey, TValue>& Data )
		{

			if ( Ser.IsLoading() )
			{
				dword Size = 0;
				Ser << Size;
				for ( dword i = 0;i< Size;i++)
				{
					TKey Key;
					TValue Value;
					Ser << Key << Value;

					Data.set( Key, Value );
				}
			}
			else
			{
				Ser << (dword)Data.size();

				// ��ȡ����
				for ( dynamic_hash<TKey, TValue>::iterator it( Data );
					it;
					++it)
				{
					Ser << it.get_key( ) << it.get_value();
				}
			}


			return Ser;
		}

		/// �������л�
		template<typename TClass>
		BinarySerializer& SerializeObject( TClass*& Obj )
		{
			if ( IsLoading() ) 
			{ 
				RTTIObject* ReadedObj = ReadObject(  );

				Obj = RTTI_CAST(TClass, ReadedObj );

				// �����Ľ����������ȡ�������޷�ת��
				Assert( ReadedObj != null && Obj != null && "Can not cast to given object type while serialization");

				// �ͷ��Ѿ������Ķ���
				if ( ReadedObj != null && Obj == null )
				{
					delete ReadedObj;
				}
			} 
			else 
			{	
				WriteObject( Obj );
			} 

			if ( Obj != null ) 
				Obj->Serialize( *this ); 

			return *this;
		}
		

	private:
		DataStream* mStream;
		bool mIsLoading;
		dword mVersion;
		bool mStreamOK;
		static Logger* mLogger;
	};

	/** @} */
	/** @} */
}