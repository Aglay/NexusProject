#pragma once

namespace NekoEngine
{
	/** 
		�����Զ��������
	*/
	class CoreInitializer
	{
	public:
		/// ����ʱ����ʼ������
		CoreInitializer( );

		/// ����ʱ���˳�����
		~CoreInitializer( );

		/// �ֶ���ʼ������
		static void InitGlobalObject( );

		/// �ֶ���������
		static void ExitGlobalObject( );
	};

	/// �ڳ�����ڼ���˺�����Զ���ʼ��
	#define NEKO_CORE_INIT NekoEngine::CoreInitializer nekocoreobj;
}
