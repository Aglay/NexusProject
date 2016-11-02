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
		����ʰȡ��
	*/
	class WorldPick
	{
	public:
		/**
			���캯��
			@param
				World ��Ҫʰȡ������	
		*/
		WorldPick( GameWorld* World );

		/**
			ʰȡ
			@param
				PickRay ����
			@param
				SortResult ���մӽ���Զ��˳������
			@return
				�Ƿ�ʰȡ��
		*/
		bool Pick( const Ray& PickRay, bool SortResult = false );

		/** 
			��һ��6������׶����ʰȡ
		*/
		bool Pick( const PlaneBoundedVolume& BoundedVolume );


		/**
			���ʰȡ���
			@param
				Index ����
			@return
				ʰȡ���Ľ��
		*/
		Actor* GetActor( dword Index );

		/// ��ȡʰȡ����
		dword GetCount( );

		/// ��ȡʰȡ����ľ���
		float GetDistance( dword Index );

		struct PickResult 
		{
			Actor*	mActor;
			float	mDistance;
		};

	private:
		void PickActor( const Ray& PickRay, Actor* A );

		void PickActor( const PlaneBoundedVolume& BoundedVolume, Actor* A );

	private:

		typedef std::vector<PickResult> PickResultArray;

		PickResultArray mPickResult;

		GameWorld* mWorld;
		
	};

	/** @} */
	/** @} */
}
