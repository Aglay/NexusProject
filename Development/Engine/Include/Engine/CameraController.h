#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/

	class IInputDriver;

	/** 
		�����������������
	*/
	class CameraController
	{
	public:
		CameraController( );

		/** 
			�ҽ�һ�������豸
		*/
		void AttachInputDevice( IInputDriver* driver );

		/** 
			�ҽ�һ�������
		*/
		void AttachCamera( Camera* camera );

		/** 
			�����߼�
		*/
		virtual void Tick( float elapse ) = 0;

	protected:
		Camera* mCamera;
		IInputDriver* mInputDev;
	};

	/** 
		��������ο�����
	*/
	class ArcBallCameraController : public CameraController
	{
	public:
		virtual void Tick( float elapse  );
	};


	/** 
		��һ�˳ƿ�����
	*/
	class FPSCameraController : public CameraController
	{
	public:
		virtual void Tick( float elapse );
	};


	/** 
		���������������
	*/
	class FocusCameraController : public CameraController
	{
	public:
		FocusCameraController( );

		virtual void Tick( float elapse );

		bool mZooming;
		float mSavedMouseY;
		Vector3 mSavedPos;
	};



	/** @} */
	/** @} */
}