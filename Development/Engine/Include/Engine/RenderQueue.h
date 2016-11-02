#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/


	class GeometryComponent;

	/** 
		��Ⱦ���з���
	*/
	enum eRenderQueueGroup
	{
		RQF_Background = 0,		///< ����
		RQF_SkiesEarly = 5,		///< �������
		RQF_Default= 50,		///< Ĭ��
		RQF_SkiesLater = 95,	///< �������
		RQF_Overlay = 100,		///< ����
	};

	/** 
		��Ⱦ���з���
	*/
	class RenderQueueGroup
	{
	public:
		/** 
			���캯��
			@param
				GroupID ����ID
		*/
		RenderQueueGroup( dword GroupID );

		/** 
			���һ���ɻ��ƶ���
		*/
		void Add( GeometryComponent* Component );

		/** 
			����������ڵĶ���
		*/
		void Draw( SceneView* RV );

		/** 
			������ڶ���
		*/
		void Clear();

		/** 
			��ȡ��ID
		*/
		dword GetGroupID( ){ return mGroupID; }

	private:
		typedef std::vector<GeometryComponent*> RenderList;

		void DrawRenderList( SceneView* RV, RenderList& RList );
		
		dword		mGroupID;

		RenderList	mOpaqueRenderList;
		RenderList	mTransparentRenderList;
		RenderList	mSolidRenderList;
	};

	/** 
		��Ⱦ����
	*/
	class RenderQueue
	{
	public:
		RenderQueue( );

		~RenderQueue( );

		/** 
			���һ���ɻ��ƶ���
		*/
		void Add( GeometryComponent* Comp );

		/** 
			������ڶ���
		*/
		void Clear( );

		/** 
			���ƶ���
		*/
		void Draw( SceneView* RV );

	private:
		RenderQueueGroup* GetRenderGroup( dword GroupID );
		
	private:
		typedef std::map<dword, RenderQueueGroup*> RenderGroupMap;
		RenderGroupMap mRenderGroupMap;
		typedef std::vector<RenderQueueGroup*> RenderGroupArray;
		RenderGroupArray mRenderGroupArray;

		bool mNeedUpdateGroupOrder;

	};

	/** @} */
	/** @} */
}
