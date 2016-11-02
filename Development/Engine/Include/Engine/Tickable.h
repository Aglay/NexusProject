#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	/** 
		�ɸ��¶���
		@remark
			�����Ϳ��Զ�����
	*/
	class Tickable
	{
	public:
		Tickable( );

		virtual ~Tickable( );

		virtual void Tick( float Elapse ) = 0;

		virtual bool IsTickable( ){ return true; }

		static void StaticTick( float Elapse );

	public:
		typedef std::list<Tickable*> TickableList;
		static TickableList mTickableList;
	};

	/** @} */
	/** @} */
}
