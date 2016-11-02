#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Platform
	*  @{
	*/


	/** 
		�������װ
	*/
	class Clipboard
	{
	public:
		
		/// �����ַ�����������
		static bool Copy( const wchar* string );

		/// �Ӽ�����ȡ���ַ���
		static bool Paste( WString& string );
	};

};