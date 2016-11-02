#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Model
	*  @{
	*/

	class SkeletonInstance;

	/** 
		��������������
	*/
	class SkeletonAnimController
	{
	public:
		/**
			���캯��
			@param
				AnimResource ����������Դ
			@param
				Skeleton ����
			@remark
				��Դ��������
		*/
		SkeletonAnimController(SkeletonAnimResource* AnimResource, SkeletonInstance* Skeleton);

		/// ���ݶ������¹���
		void	Update( float elapse );

		/// ��������
		float	GetDuration( );

		/// ��ȡ��������λ��
		float	GetCurrent( );

		/// ���ö�������λ��
		void	SetCurrent( float current, bool autoupdate = true );

		/// ��ö��������ٶ�
		float	GetSpeed( );

		/// ���ö��������ٶ�,Ĭ��Ϊ1
		void	SetSpeed( float speed );

		/// ��ȡ�����Ƿ����ѭ��
		bool	GetLoop( );

		/// ���ö����Ƿ����ѭ��
		void	SetLoop( bool circle );

	private:
		void	SetBlendOption( bool affecttransform, bool fixroot );

		void	InitDeltaTransform( );

		Matrix4 GetDeltaTransform( );


		void	Update(float last,float current,float weight = 1.0f);

		SkeletonAnimResource*			mAnimationLoader;
		SkeletonInstance*				mSkeleton;

		float					mCurrent;
		float					mSpeed;
		bool					mCircle;
		bool					mAffectTransform;
		bool					mFixRoot;

		Vector3					mLastTranslation;
		Quaternion				mLastRotation;

		Vector3					mAccumTranslation;
		Quaternion				mAccumRotation;
		Vector3					mDeltaTranslation;
		Quaternion				mDeltaRotation;
	};
}
