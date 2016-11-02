#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/


#ifdef USE_R_HAND_COORDSYS
	const float CameraCoordFix = 1.0f;
	const Vector3 CameraStartPos = Vector3(10,50,50);
#else
	const Vector3 CameraStartPos = Vector3(10,-50,50);
	const float CameraCoordFix = -1.0f;
#endif

	class BinarySerializer;

	/** 
		�������װ��
		@remark
			ͨ�����л�������
	*/
	class Camera
	{
	public:
		Camera( );

		/** 
			���� �� ����
			@param
				Value ����
		*/
		void SetUp( const Vector3& Value );

		/** 
			���� ����
			@param
				Value 3D�ռ��
		*/
		void SetLook( const Vector3& Value );

		/** 
			���� �����λ��
			@param
				Value 3D�ռ��
		*/
		void SetPosition( const Vector3& Value );

		/** 
			��ȡͶ�����
			@return
				����
		*/
		const Matrix4& GetProjectMatrix( ) const{ return mProjectMatrix; }

		/** 
			��ȡ�۲����
			@return
				����
		*/
		const Matrix4& GetViewMatrix( ) const;

		/** 
			��ȡ������
			@return
				����
		*/
		const Vector3& GetUp( ) const { return mUp; }

		/** 
			��ȡ�۲��
			@return
				3D�ռ��
		*/
		const Vector3& GetLook( ) const { return mLook; }

		/** 
			��ȡ�����λ��
			@return
				3D�ռ��
		*/
		const Vector3& GetPosition( ) const{ return mPosition;}

		/// ���л�
		virtual void Serialize( BinarySerializer& Ser );

		/** 
			��ȡ�����λ�ó���
			@remark
				ViewDir = Pos - Look
			@return
				3D�ռ��
		*/
		Vector3 GetViewDir( );

		/** 
			����Ͷ��͹۲���󹹽���׶����
			@return
				��׶
		*/
		Frustum CreateFrustum( )  const;

		/** 
			������� X ��ת
			@param
				radian ����
		*/
		void Yaw(float radian);

		/** 
			������� Y ��ת
			@param
				radian ����
		*/
		void Pitch(float radian);

		/** 
			������� Z ��ת
			@param
				radian ����
		*/
		void Roll(float radian);

		/** 
			������������ĺ����ƶ�
			@param
				units 3D��λ
		*/
		void Strafe(float units);

		/** 
			������������Ĵ�ֱ�ƶ�
			@param
				units 3D��λ
		*/
		void Fly(float units);

		/** 
			���������Ϸ���Ĵ�ֱ�ƶ�
			@param
				units 3D��λ
		*/
		void FlyStaticUp(float units);

		/** 
			���벻�䣬ת�������λ��	
			@param
				look ���㣬3D�ռ��
		*/
		void LookAt( const Vector3& look );

		/** 
			���������������ǰ���ƶ�
			@param
				units 3D��λ
		*/
		void Zoom(float units);

		/** 
			������� �Ϸ��� ת�����ҷ���
			@param
				radian ����
		*/
		void Phi( float radian );

		/** 
			������� �ҷ��� ת��ǰ�󷭹�
			@param
				radian ����
		*/
		void Theta( float radian );

		/** 
			������۲췽��İ뾶����
			@param
				units 3D��λ
		*/
		void Radius( float units );

		/** 
			�������������
			@remark
				������������Ϸ��򣬹۲췽������Ը��¹۲����Ͷ�����
			@param
				vp �ӿ�
		*/
		void Update( const Viewport& vp );

		/// ���������л�����
		friend BinarySerializer& operator <<( NekoEngine::BinarySerializer& Ser, Camera& Data )
		{
			Data.Serialize( Ser );

			return Ser;
		}

	private:
		void UpdateViewMatrix( ) const;

	private:
		Vector3		mLook;
		Vector3		mPosition;
		Vector3		mUp;

		Matrix4		mProjectMatrix;

		mutable Matrix4	mViewMatrix;
		mutable bool	mViewMatrixDirty;		
	};

}
