#pragma once

namespace NekoEngine
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/


	/** 
		ͼԪ�����ж�
	*/
	class Intersection
	{
	public:

		/// �����еĶ��������
		enum ePrimitiveType
		{
			TriangleList,
			TriangleStrip,
		};

		/** 
			���ߴ�ƽ��
			@param
				ray ����
			@param
				plane ƽ��
			@param
				distance ���صĹ����ϵ�ľ���
		*/
		static bool RayVSPlane( const Ray& ray, const Plane& plane, float& distance );

		/** 
			���ߴ�������
			@param
				ray ����
			@param
				triangle ������
			@param
				distance ���صĹ����ϵ�ľ���
		*/
		static bool RayVSTriangle( const Ray& ray, const Triangle& triangle, float& distance );

		/** 
			���ߴ�����
			@param
				ray ����
			@param
				box ����
			@param
				distance ���صĹ����ϵ�ľ���
		*/
		static bool RayVSBox( const Ray& ray, const Box& box, float& distance );

		/** 
			���ߴ���Գư󶨺�
			@param
				ray ����
			@param
				aabb ��Գư󶨺�
			@param
				distance ���صĹ����ϵ�ľ���
		*/
		static bool RayVSAABox( const Ray& ray, const AABB& aabb, float& distance );

		/** 
			���ߴ�ģ��
			@param
				TRay ����
			@param
				Distance ���صĹ����ϵ�ľ���
			@param
				VertexSize һ�������С
			@param
				PType ģ�Ͷ��������
			@param
				PrimitiveCount ���������
			@param
				VertexBuffer ���㻺�壬����n����������
			@param
				IndexBuffer �������壬word����
			@return
				�Ƿ񴩲嵽
		*/
		static bool RayVSMesh(	const Ray& TRay, 
								float& Distance,
								dword VertexSize,
								ePrimitiveType PType,
								dword PrimitiveCount,
								const _byte* VertexBuffer,
								const _byte* Indexbuffer );

		/** 
			��Գư󶨺л��ഩ��
			@param
				box1 ����1
			@param
				box2 ����2
			@return
				�Ƿ񴩲嵽
		*/
		static bool AABoxVSAABox( const AABB& box1, const AABB& box2 );

		/** 
			����
			@param
				sphere1 ��1
			@param
				sphere2 ��2
			@return
				�Ƿ񴩲嵽
		*/
		static bool SphereVSSphere( const Sphere& sphere1, const Sphere& sphere2 );

		/** 
			��̬��Գư󶨺д�ƽ��
			@param
				box ����
			@param
				plane ƽ��
			@return
				�Ƿ񴩲嵽
		*/
		static bool StaticAABoxVSPlane( const AABB& box, const Plane& plane );

		/** 
			��̬��Գư󶨺д�ƽ��
			@param
				box ����
			@param
				plane ƽ��
			@return
				�Ƿ񴩲嵽
		*/
		static bool DynamicAABoxVSPlane( const AABB& box, const Plane& plane, const Vector3& direction, float& distance );

		/** 
			��̬��ƽ��
			@param
				sphere ��
			@param
				plane ƽ��
			@return
				�Ƿ񴩲嵽
		*/
		static bool StaticSphereVSPlane( const Sphere& sphere, const Plane& plane );

		/** 
			��̬��ƽ��
			@param
				sphere ��
			@param
				plane ƽ��
			@return
				�Ƿ񴩲嵽
		*/
		static bool DynamicSphereVSPlane( const Sphere& sphere, const Plane& plane, const Vector3& direction, float& distance );

		/** 
			���δ�ģ��
			@param
				ScreenArea ��Ļ����
			@param
				Cam �����
			@param
				LocalToWorld �������굽�����ת������
			@param
				BackDistance ����
			@param
				VertexSize �����С
			@param
				PType ���������
			@param
				PrimitiveCount ���������
			@param
				VertexBuffer ���㻺��
			@param
				IndexBuffer ��������
			@return
				�Ƿ񴩲嵽
		*/
		static bool RectVSMesh( const FRect& ScreenArea, 
								Camera* Cam, 
								const Matrix4& LocalToWorld, 
								float BackDistance, 
								dword VertexSize, 
								ePrimitiveType PType, 
								dword PrimitiveCount, 
								const _byte* VertexBuffer, 
								const _byte* IndexBuffer );


	private:
		typedef bool (*IterateVertexCallback)( void* UserData, const Vector3& P1, const Vector3& P2, const Vector3& P3 );

		static void IterateMeshVertex( dword VertexSize, ePrimitiveType PrimitiveType, dword PrimitiveCount, const _byte* VertexBuffer, const _byte* IndexBuffer, IterateVertexCallback Func, void* UserData );
	};

	/** @} */
	/** @} */
}
