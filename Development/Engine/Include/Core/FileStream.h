#pragma once


namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Stream
	*  @{
	*/


	/// �ļ�����ģʽ
	enum eFileAccessMode
	{ 
		FAM_Invalid,		///< �Ƿ�����ģʽ
		FAM_Read,			///< ����ʽ
		FAM_Write,			///< д��ʽ
	};

	/** 
		�ļ���
	*/
	class  FileStream : public DataStream
	{
	public:
		FileStream( );

		virtual ~FileStream( );

		/** 
			����ʱ���ļ�
			@param
				filename �򿪵��ļ���
			@param
				accessmode ����ģʽ
			@param
				openalways ʼ�մ򿪷�ʽ
			@remark
				ע��ʹ��Vaild�����ж��ļ��Ƿ�ɹ���
		*/
		FileStream( const wchar* filename, eFileAccessMode accessmode, bool openalways = false );

		/** 
			������д�뵽�ļ�
			@param
				input ��������
			@param
				numberOfBytes д���ֽ���
			@return
				�Ƿ�ɹ�д��
		*/
		virtual bool	WriteBuffer( const void* input, dword numberOfBytes );

		/** 
			д����
			@param
				s Դ�����ڴ���
			@return
				�Ƿ�ɹ���ȡ,�ֽ�������ʱ��Ϊ��ȡʧ��
		*/
		bool			WriteBuffer( DataStream* s );


		/** 
			���ļ����뻺��
			@param
				output ���ջ���
			@param
				numberOfBytes �����ֽ���
			@return
				�Ƿ�ɹ���ȡ,�ֽ�������ʱ��Ϊ��ȡʧ��
		*/
		virtual bool	ReadBuffer( void* output, dword numberOfBytesToRead );

		/** 
			�鿴�ļ����ж����ֽڿ��Զ�ȡ
			@return
				�ֽ���
			@remark
				���ڶ�ȡʱ����
		*/
		virtual dword	GetRemainBytes( ) const;

		/** 
			�鿴�ļ�ָ��λ��
		*/
		virtual dword	GetPosition() const;

		/** 
			��λָ��
			@param
				offset �ļ�ƫ��,������
			@param
				mso ��������
		*/
		virtual bool	Seek( int offset, eMemoerySeekOrigin mso );

		/** 
			�����ļ�����
			@param
				len �ļ�����
			@remark
				����дģʽ����

		*/
		virtual void	SetLength( dword len );

		/** 
			��λ�ļ�ָ��
		*/
		virtual void	Reset( );

		/** 
			FileStream�в��ɷ��仺��
		*/
		virtual char*	AllocBuffer( dword size );

		/** 
			FileStream���ɻ�û����ַ
		*/
		virtual char*	GetBuffer( );

		/** 
			ȡ���ļ���С
		*/
		virtual dword	GetSize( ) const;

		/** 
			�ֶ����ļ�
			@param
				filename �򿪵��ļ���
			@param
				accessmode ����ģʽ
			@param
				openalways ʼ�մ򿪷�ʽ
			@return
				���Ƿ�ɹ�
		*/
		bool			Open( const wchar* filename, eFileAccessMode accessmode, bool openalways = false );

		/** 
			�ر��ļ�
		*/
		void			Close( );

		/** 
			ȡ�ļ����
		*/
		handle			GetHandle( ){ return mFile;}

		/** 
			�ļ��Ƿ������������
		*/
		virtual bool	IsValid( );

		/** 
			ȡ�õ�ǰ�ļ�����ģʽ
		*/
		eFileAccessMode GetMode( ){ return mFileAccessMode; }
		
	protected:
		handle	mFile;
		eFileAccessMode mFileAccessMode;
	};

	/** @} */
	/** @} */
}