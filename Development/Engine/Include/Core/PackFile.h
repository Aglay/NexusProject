#pragma once

namespace NekoEngine
{
	// ��1�ֽڶ���
#pragma pack(push,1)
	struct PackStdHeader
	{
		char	mTag[4];		
		word	mVersion;

		void Init();

		bool Valid( );
	};
	// ����Ӹ�ʽ��̳�PackStdHeadд,�ɴ˿��������¼���
	
	struct NameSet
	{
		dword mSetA, mSetB, mSetC;

		NameSet( ){}

		NameSet( dword A, dword B, dword C );

		NameSet( const wchar* name );

		void GenHash( const wchar* name );

		bool operator == ( const NameSet& other ) const ;
	};

	struct ChunkSet
	{
		NameSet		mName;			// hashcode �洢�ı�ʾ
		_byte		mEncode;
		dword		mOffset;			// ��Ե�һ��Chunk���λ��
		dword		mSize;			// Chunk���ݴ�С
	};

#pragma pack(pop)

	class PackMaster
	{
	public:
		PackMaster( );

		virtual ~PackMaster( );

		bool		Create( const wchar* packfile );

		bool		Create( DataStream* mem );

		void		WriteNameTable( );

		bool		WriteChunk( const wchar* name, DataStream* stream, bool writeNameTable = false );

		bool		WriteChunk( const NameSet& name, DataStream* stream);

		bool		Open( const wchar* packfile );

		bool		Open( DataStream* mem );

		bool		ReadChunkByName( const wchar* name, DataStream* stream );// ��ȡ��packman���ɵ��ļ���name�е�·��һ��Ϊ\ ������/������

		bool		ReadChunk( const NameSet& hashname , DataStream* stream );

		void		Close( );

		bool		ResetChunkIterator( );

		bool		IteratorChunk( WString& name, DataStream* bs );

		bool		CanWrite( );

		bool		CanRead( );

		bool		Valid();

		bool		ChunkExist( const wchar* name );

		bool		ChunkExist( const NameSet& name );

	private:
		bool		ReadChunkRaw( ChunkSet* chunk, DataStream* stream );

		bool		ReadNameTable( );

		bool		ProcessOpen( DataStream* mem, bool autodelete );

		bool		ProcessCreate( DataStream* mem, bool autodelete );
		
		DataStream* mDataSource;
		bool mSourceAutoDelete;

		friend dword GetTypeHash( const NameSet& A )
		{
			return CheckSum::MemCRC( &A, sizeof(NameSet) );
		}

		typedef dynamic_hash<NameSet,ChunkSet> ChunkMap;

		ChunkMap mChunkMap;

		// �����ļ��б�ʱ��ʹ��
		struct ChunkName
		{
			NameSet mNameSet;
			WString mRealName;
			ChunkName( )
			{

			}
			ChunkName( const NameSet& hashname, const WString& realname )
				: mNameSet( hashname )
				, mRealName( realname )
			{

			}
		};

		enum ePackMasterStatus
		{
			PMS_Invalid,
			PMS_WritePack,
			PMS_ReadPack,
		};


		typedef std::list<ChunkName> NameTableList;
		NameTableList mNameTableList;
		NameTableList::iterator mIterator;
		ePackMasterStatus mPackMasterStatus;
	};




}
