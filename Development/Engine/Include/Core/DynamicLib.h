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
		��̬���ӿ��ȡ��
	*/
	class DynamicLib
	{
	public:
		DynamicLib( );

		/** 
			�Ӵ��̶�ȡ��̬���ӿ�
		*/
		bool		Load(const wchar* libname);

		/** 
			ж�ؼ��صĶ�̬���ӿ�
		*/
		void		Unload();

		/** 
			ȡ��һ��Symbol�ľ��	
		*/
		void*		GetSymbol(const wchar* name);

		/** 
			ȡ��һ��Symbol�ľ��
		*/
		void*		GetSymbol(const char* name);

		/** 
			��DLL����һ��ʵ��
			@param
				dllname dll·��
			@param
				entryname �����Ĵ���������
			@param
				userdata ����ʱ�õ�������
			@return
				���ش����õ���
		*/
		template <typename T>
		T CreateInstance( const wchar* dllname, const wchar* entryname, void* userdata = null )
		{
			typedef T	(*CreateFunc)( void* u );

			if ( !Load(dllname) )
				return null;

			CreateFunc func = (CreateFunc)GetSymbol( entryname );
			if ( func == null )
				return null;

			return func( userdata );
		}

	private:
		handle mInstance;
	};
}
