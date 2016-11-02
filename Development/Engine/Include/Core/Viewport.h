#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/


	class Camera;

	/** 
		�ӿ�
	*/
	class Viewport
	{
	public:
		dword					X,Y, Width,Height;
		float					NearZ, FarZ;

		Viewport( );

		/** 
			���ռ��еĵ㣬����������趨��Ͷ�䵽��Ļ
		*/
		Vector3 Project( const Vector3& objVec, const Camera& cam ) const;

		/** 
			���ռ�λ���еĵ�Ͷ�䵽��Ļ
		*/
		static Vector3 Project(	const Vector3& objVec,
								const Matrix4& view,
								const Matrix4& proj,
								const Viewport& viewport);
		
		/// ����Ļ�㣬��Ͷ��������
		static Vector3 UnProject(const Vector2& screenVec,const Viewport& viewport,const Matrix4& proj,const Matrix4& InvView);

		/// ����Ļ��һ���㣬Ͷ�䵽�����У���Ϊһ������ʹ��
		static Ray UnProjectRay(const Vector2& screenVec,const Viewport& viewport,const Matrix4& proj,const Matrix4& InvView);
	};

	/** @} */
	/** @} */

}
