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
		�������ɫ
	*/
	class CameraActor : public Actor
	{
		DECLARE_RTTI_CLASS( CameraActor, Actor, ClassFlag_Intrinsic| ClassFlag_Serializable )
	public:
		CameraActor( );

		Camera* GetCamera( ){ return &mCamera; }

		virtual void Serialize( BinarySerializer& Ser );

		virtual void OnObjectTransformed( dword TransformType );
		
		static const Vector3 cCameraFront;

	private:
		friend class CameraControllerComponent;
		Camera mCamera;

		bool mUpFixed;
	};

	typedef TRefPtr<CameraActor> CameraActorPtr;

	/** 
		Actor����������
	*/
	class ActorControllerComponent : public GeometryComponent
	{
		DECLARE_RTTI_CLASS( ActorControllerComponent, GeometryComponent, ClassFlag_Intrinsic )
	public:		
		ActorControllerComponent( );

		virtual void Draw( SceneView* RV );

		void SetInputDriver( IInputDriver* InputDrv ){ mInputDevice = InputDrv; }

	protected:
		IInputDriver* mInputDevice;
	};


	/** 
		Actor��FPS������
		@remark
			ͨ�������������ת��λ��ʵ��FPS��ʽ�ƶ�
	*/
	class FPSActorControllerComponent : public ActorControllerComponent
	{
		DECLARE_RTTI_CLASS( FPSActorControllerComponent, ActorControllerComponent, ClassFlag_Intrinsic )
	public:		

		virtual void Tick( float Elapse );

		/// ˮƽ��ת
		void Yaw( float XDelta );

		/// ����һ����������ռ��ʸ��,���ݶ��������ת�����ƶ�
		void Move( const Vector3& Delta );

		/// ��ֱ����
		void Pitch( float YDelta );

		/// ��һ��ʸ��Ͷ�䵽����ռ�
		Vector3 VectorMapIntoObjectSpace( const Vector3& V );
	};


	/** 
		�۲�Ԥ����ʽ��Actor������
	*/
	class FocusActorControllerComponent : public ActorControllerComponent
	{
		DECLARE_RTTI_CLASS( FocusActorControllerComponent, ActorControllerComponent, ClassFlag_Intrinsic )
	public:		
		FocusActorControllerComponent( );

		virtual void Tick( float Elapse );

		void SetFocusPoint( const Vector3& Value );

		void Phi( float Delta );

		void Theta( float Delta );

		void UpdateObjectTransform( );

		void OnAttach();
	private:
		Vector3 mFocusTarget;
		
		float mPhi;
		float mTheta;
		float mRadius;
	};


	/** @} */
	/** @} */
}