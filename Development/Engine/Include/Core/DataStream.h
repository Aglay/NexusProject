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
		�ڴ涨λ����
	*/
	enum eMemoerySeekOrigin
	{
		MSO_Begin,			///< ������ʼ��λ
		MSO_Current,		///< �ӵ�ǰָ��λ�ö�λ
		MSO_End,			///< ����β��ʼ��λ
	};

	/** 
		�ڴ������
		@remark
			������Ҫ��������ʵ��
	*/
	class DataStream
	{
	public:
		DataStream( );

		virtual ~DataStream( );

		/** 
			д����
			@param
				input ��������
			@param
				numberOfBytes д���ֽ���
			@return
				�Ƿ�ɹ�д��
		*/
		virtual bool	WriteBuffer( const void* input, dword numberOfBytes );

		/** 
			������
			@param
				output ���ջ���
			@param
				numberOfBytes �����ֽ���
			@return
				�Ƿ�ɹ���ȡ,�ֽ�������ʱ��Ϊ��ȡʧ��
		*/
		virtual bool	ReadBuffer( void* output, dword numberOfBytesToRead );

		/** 
			������
			@param
				s Դ�����ڴ���
			@param
				numberOfBytes �����ֽ���
			@param
				extendbufferalloc ����ķ����ֽ���
			@return
				�Ƿ�ɹ���ȡ,�ֽ�������ʱ��Ϊ��ȡʧ��
		*/
		bool			ReadBuffer( DataStream* s, dword numberOfBytes , dword extendbufferalloc = 0);

		/** 
			д����
			@param
				s Դ�����ڴ���
			@return
				�Ƿ�ɹ���ȡ,�ֽ�������ʱ��Ϊ��ȡʧ��
		*/
		bool			WriteBuffer( DataStream* s );

		/** 
			�鿴�����ж����ֽڿ��Զ�ȡ
			@return
				�ֽ���
			@remark
				���ڶ�ȡʱ����
		*/
		virtual dword	GetRemainBytes( )	const; 

		/** 
			�鿴��ָ��λ��
		*/
		virtual dword	GetPosition()	const;	

		/** 
			��λָ��
			@param
				offset �ļ�ƫ��,������
			@param
				mso ��������
		*/
		virtual bool	Seek( int offset, eMemoerySeekOrigin mso );		// ����ʽ����

		/** 
			�����ֽ���
			@remark
				���ڶ���ʽ�¿���
		*/
		virtual bool	IgnoreBytes( dword numberOfBytes );

		/** 
			����������
			@param
				len ����
			@remark
				����дģʽ����

		*/
		virtual void	SetLength( dword len );

		/** 
			��λ��ָ��
		*/
		virtual void	Reset( );

		/** 
			ȡ�û����ַ
		*/
		virtual char*	GetBuffer( ) = 0;

		/** 
			ȡ������С
		*/
		virtual dword	GetSize( ) const;

		/** 
			�����ڲ��洢�ռ�
		*/
		virtual char*	AllocBuffer( dword size );

		/** 
			�ͷ��ڲ��洢�ռ�
		*/
		virtual void	ReleaseBuffer( );

		/** 
			���Ƿ����
		*/
		virtual bool	IsValid( );

		/// ģ��д����
		template<typename T>
		bool	WriteTypes( const T& v )		{	return WriteBuffer( &v, sizeof(T) );}

		/// д��Ansi�ַ���
		bool	WriteTypes( const AString& v )  { return WriteANSIString( v.c_str()); }

		/// д��Unicode�ַ���
		bool	WriteTypes( const WString& v )  { return WriteUNICODEString( v.c_str()); }

		/// д��Ansi�ַ���
		bool	WriteTypes( const char* v )  { return WriteANSIString( v ); }

		/// д��Unicode�ַ���
		bool	WriteTypes( const wchar* v )  { return WriteUNICODEString( v ); }


		/// ģ�������
		template<typename T>
		bool	ReadTypes( T& Ret )		{	return ReadBuffer( &Ret, sizeof(T)  );}

		/// ����Ansi�ַ���
		template<> 
		bool ReadTypes( AString& Ret )				{ return ReadString<AString, char>( Ret ); }

		/// ����Unicode�ַ���
		template<>
		bool ReadTypes( WString& Ret)				{ return ReadString<WString, wchar>( Ret ); }

		/// ����Ansi�ַ���,���Դ���,Ĭ��ֵΪ��
		AString ReadANSIString( );

		/// ����Unicode�ַ���,���Դ���,Ĭ��ֵΪ��
		WString ReadUNICODEString( );

		/** 
			����Unicode�ַ���
			@remark
				���ڶ�ģʽ����
		*/
		bool	IgnoreUNICODEString( );

		/** 
			����Ansi�ַ���
			@remark
				���ڶ�ģʽ����
		*/
		bool	IgnoreANSIString( );

		/// д��Unicode�ַ���
		bool	WriteUNICODEString( const WString& str );

		/// д��Unicode�ַ���
		bool	WriteUNICODEString( const wchar* str );

		/// д��Ansi�ַ���
		bool	WriteANSIString( const AString& str );

		/// д��Ansi�ַ���
		bool	WriteANSIString( const char* str );

	private:
		template<typename T, typename T2>
		bool		ReadString( T& Str );		
		template<typename T> 
		bool	WriteString( const T* str, dword len );

	protected:
		dword		mDataSize;		// ����ʵ�ʴ�С
		dword		mPointer;		// �� λ��
		dword		mAllocedSize;	// �Ѿ�������ڴ��С
	};

	/** @} */
	/** @} */
}