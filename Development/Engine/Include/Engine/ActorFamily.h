#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup System
	*  @{
	*/


	class CameraController;

	/** 
		��������������
	*/
	class CameraControllerComponent : public GeometryComponent
	{
		DECLARE_RTTI_CLASS( CameraControllerComponent, GeometryComponent, ClassFlag_Intrinsic )
	public:
		CameraControllerComponent( );

		virtual ~CameraControllerComponent( );

		virtual void Draw( SceneView* RV );

		virtual void Tick( float Elapse );

		/** 
			���ÿ���������
		*/
		void SetControllerType( CameraController* Controller, IInputDriver* InputDrv  );

	private:
		CameraController* mController;
	};


	/** @} */
	/** @} */
}
