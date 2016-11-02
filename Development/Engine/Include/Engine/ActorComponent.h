#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	class Actor;

	/** 
		�������
	*/
	class ActorComponent : public RTTIObject
	{
	DECLARE_RTTI_CLASS( ActorComponent, RTTIObject, ClassFlag_Intrinsic )

	public:
		ActorComponent( );

		virtual void Tick( float Elapse );

		/// �ҽӵ�Actorʱ
		virtual void OnAttach( ){}

		/// ��Actor�Ͽ�ʱ
		virtual void OnDetach( ){}

		/// �Ƿ�ɻ���
		virtual bool IsDrawable( ) { return false; }

		/// ��ȡ������Actor
		Actor* GetOwner( ){ return mOwner; }

	protected:
		friend class Actor;
		Actor*			mOwner;

	private:
		friend class Actor;
		dword			mIndex;
	};

	class SceneView;


	/** 
		�ɻ������
		@remark
			�Զ���ӵ������б�
	*/
	class GeometryComponent : public ActorComponent
	{
	DECLARE_RTTI_ABSTRACT( GeometryComponent, ActorComponent, ClassFlag_Intrinsic )

	public:
		
		GeometryComponent( );

		/// ��Ҫʵ�ֵĻ��ƹ���
		virtual void Draw( SceneView* RV ) = 0;

		virtual bool IsDrawable( ) { return true; }

		/// ��Ҫʵ��: �Ƿ���͸����,��������˳��
		virtual bool IsTransparent( ){ return false; }

		/// ��Ҫʵ��: �Ƿ���Ҫд�����.ƽ��ʱ����false
		virtual bool IsEnableDepthWrite( ){ return true; }

		/// �����������·��
		virtual float GetViewDepthSquared( Camera* C ){ return Math::cMaxFloat; }

		/// ��ȡ��Ⱦ����
		dword GetRenderQueueGroup( ){ return mRenderQueueGroup; }

		/// ������Ⱦ����
		void SetRenderQueueGroup( dword GroupID ){ mRenderQueueGroup = GroupID; }

		dword		mPickID;

	private:
		dword	mRenderQueueGroup;
	};

	
	/** 
		������������ߵ����,�ṩ������Rootʹ��
	*/
	class GridAxisComponent : public GeometryComponent
	{
		DECLARE_RTTI_CLASS( GridAxisComponent, GeometryComponent, ClassFlag_Intrinsic )
	public:
		virtual void Draw( SceneView* RV );
	};

	class SkeletonInstance;
	class Canvas;
	struct BoneContent;

	/** 
		����RT�ĵ�һ��View�л���֡����Ϣ	
	*/
	class ActorHelperComponent : public GeometryComponent
	{
		DECLARE_RTTI_CLASS( ActorHelperComponent, GeometryComponent, ClassFlag_Intrinsic )
	public:
		ActorHelperComponent( );

		static void StaticInitProperty( );

		virtual void Draw( SceneView* RV );

		Color mBoundingBoxColor;
		Color mBoneStartColor;
		Color mBoneEndColor;

		bool mShowBoundingBox;
		bool mShowSkeleton;

	private:
		void DrawSkeleton( SkeletonInstance* Skeleton, Canvas* Painter );

		void DrawSkeleton( SkeletonInstance* Skeleton, Canvas* Painter, BoneContent* Bone );

	};


	/** @} */
	/** @} */
}
