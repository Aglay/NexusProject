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
		���������
	*/
	class ProxyStream : public DataStream
	{
	public:
		ProxyStream( );

		/** 
			�趨������
			@param
				m ��Ҫ�������
			@param
				numberOfBytes ���ߴ�
		*/
		ProxyStream( DataStream* m, dword numberOfBytes );

		virtual bool	WriteBuffer( const void* input, dword numberOfBytes );

		virtual bool	ReadBuffer( void* output, dword numberOfBytesToRead );

		virtual char*	GetBuffer( );

		virtual dword	GetRemainBytes( ) const;

		virtual dword	GetPosition() const;

		virtual bool	Seek( int offset, eMemoerySeekOrigin mso );

		virtual void	SetLength( dword offset );

		virtual void	Reset( );

		virtual dword	GetSize( ) const;


	protected:
		DataStream* mHost;
		dword mMaxSize;
		dword mInitPosition;
	};

	/** @} */
	/** @} */
}