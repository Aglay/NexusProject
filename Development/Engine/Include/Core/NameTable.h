#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Reflection
	*  @{
	*/

	struct NameData
	{
		enum{ NAME_SIZE = 128 };

		dword mHashCode;
		dword mIndex;				// ȫ�ֱ����name�е�����
		NameData* mNext;			// ����
		wchar mName[NAME_SIZE];		// �ж೤�������Name������ÿ������128
	};

	/// ���ƹ���ԭ��
	enum NameBuildType
	{
		NameBuild_Find,		///< ���Ѵ��ڵ�NameTable�в��ң�û���ҵ�����ΪNone
		NameBuild_Add,		///< ���û���ҵ����Զ����
	};

	enum NameConst
	{
		NameConst_None = 0, // ����ַ������ܱ�Name��
	};

	typedef std::vector<NameData*> NameDataArray;


	/** 
		���Ʊ�
	*/
	class NameRef
	{
	public:
		enum{ NAMECONST_RESERVED_COUNT = 1024, NAME_NO_NUMBER = -1 };

		//�����ж�ʹ�����
		/*
			WString -->StrHashNoCase --> HashTable  --> Array --> Index --> App
			
			NameConst <----Constλ��index��ǰ��
			NAMECONST_RESERVED_COUNT
			Dynamic added Name  <- ��̬��ӵ�Nameλ��Const����
		*/
		
		/// Ĭ�Ϲ���
		NameRef( );

		/** 
			�ڲ�����
			@param
				Index ��������
			@param
				Number ���ƺ���
		*/
		NameRef( dword Index, dword Number );

		/** 
			��������
		*/
		NameRef( dword c );

		/** 
			�Զ��������ƹ���
			@param
				name ���б�ʾ������,����Actor_0
			@param
				buildtype ������ʽ
			@param
				Number �����������������
			@param
				SpliteName �Ƿ���Ҫ��������
		*/
		NameRef( const wchar* name, NameBuildType buildtype = NameBuild_Add, dword Number = NAME_NO_NUMBER, bool SpliteName = true);

		/// ����
		NameRef& operator=( const NameRef& Other );


		/// �ж����
		bool operator==( const NameRef& Other ) const
		{
			return mIndex == Other.mIndex && mNumber == Other.mNumber;
		}

		/// �ж�����
		bool operator!=( const NameRef& Other ) const
		{
			return mIndex != Other.mIndex || mNumber != Other.mNumber;
		}

		/// For std::map
		bool operator < ( const NameRef& Other ) const
		{
			return mIndex < Other.mIndex;
		}

		/// ���key
		dword GetIndex( ) const;

		/// ���HashCode
		dword GetHash( ) const;

		/// ��ȡ������
		dword GetNumber( ) const;

		/// ȡԭ�ַ���( Number == 0 )
		const wchar* ToStringFast( ) const ;

		/// ȡԭ�ַ��� �Զ�
		WString ToStringSafe( ) const;

		/// �����Ƿ���Ч
		bool IsValid() const;

		/// ֱ�����������
		static bool AddNameConst( const wchar* name, dword index );

		static void StaticInit( );

		static void StaticExit( );

		/// ������ֱ����
		static bool CheckNameTable( Logger* logger );

		static void Dump( Logger* logger );
		
		friend dword GetTypeHash( const NameRef& A )
		{
			return A.GetIndex() + A.GetNumber();
		}
	private:
		void RefreshDebugView( );
		static dword GenHashIndex( dword hashcode );

	private:
		const wchar* mContent;
		dword mIndex;
		dword mNumber;// ������ΪClass��ObjectIndex
		
		static NameDataArray GNameRefArray;
		static NameData* GNameDataHash[4096];
		static bool		 GNameTableInitialized;
	};

	
	/** @} */
	/** @} */
}