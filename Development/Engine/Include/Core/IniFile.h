#pragma once


namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Stream
	*  @{
	*/

	
	/**
		Ini�ζ���
	*/
	class IniSection
	{
	public:
		/// �������
		void AddData( const WString& Key, const WString& Data );		

		/// ��ȡ����
		const WString& GetName( ){ return mName; }

		/// ��ȡ����
		bool Read( const WString& Key, WString& Data );

		/// ��ȡ��������
		bool Read( const WString& Key, std::vector<WString>& DataArray );

		/// �������ݵ��ļ�
		void DumpContent( TextFile& TFile );

		/// ������һ������
		bool GetFirstPair( WString& Key, WString& Data );

		/// ������һ������
		bool GetNextPair( WString& Key, WString& Data );

		/// ������һ��Key
		void SetSearchKey( const WString& Key );

		/// ������һ��Key������
		bool GetNextPairData( WString& Data );

	private:
		friend class IniFile;

		IniSection( const WString& Name );
		

		WString mName;

		typedef std::multimap<WString, WString> SettingsMultiMap;

		SettingsMultiMap mSettingsMultiMap;
		SettingsMultiMap::iterator mIterator;
	};


	/** 
		Ini��ʽ�����ļ�,֧�ֶ�д
		@remark
			�����PropertySerilizerʹ�ñ���
	*/
	class IniFile
	{
	public:
		IniFile( );

		IniFile( const IniFile& Other );

		virtual ~IniFile( );

		/** 
			���ڴ�������ini
			@param
				stream ��Դ�ڴ���
			@param
				copymemory �Ƿ񿽱���Դ�ڴ���,����crash
			@return
				�ļ��Ƿ����ȷ
		*/
		bool Parse( DataStream* stream, bool copymemory = false );

		/** 
			���ļ�����ini
			@param
				filename �򿪵��ļ���
			@return
				�ļ��Ƿ����ȷ
		*/
		bool Parse( const wchar_t* filename );

		/** 
			��ȡini����
			@param
				section Ҫ��ȡ�Ķ�
			@param
				key Ҫ��ȡ��key
			@param
				Result ���ص�����
			@return
				������������Ŀ�Ƿ����
		*/
		bool Read( const WString& Section, const WString& Key, WString& Data );
		/** 
			��ȡ�ζ���
			@param
				Section ����
			@return
				�ζ���
		*/
		IniSection* QuerySection( const WString& Section );

		/**
			��Ini����д�뵽������
		*/
		bool Dump( DataStream* Stream );

		/**
			��Ini����д�뵽�ļ�
		*/
		bool Dump( const wchar* FileName );


		/// ���һ����
		IniSection* AddSection( const WString& Section );

		/**
			������һ����
		*/
		IniSection* GetFirstSection( );

		/**
			������һ����
		*/
		IniSection* GetNextSection( );

		/// ���ƿ���
		IniFile& operator = ( const IniFile& Other );

	private:
		bool ParseContent( TextFile& TFile );
		void DumpContent( TextFile& TFile );

	private:		
		typedef std::map<WString, IniSection*> SectionMap;
		SectionMap mSectionMap;
		SectionMap::iterator mIterator;

	};

	/** @} */
	/** @} */
}