#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/

	class RenderFont;

	/** 
		������
	*/
	class Canvas
	{
	public:
		/// ����Ԫ������
		enum eElementType
		{
			ET_Line,		///< ��
			ET_Triangle,	///< ������
			ET_MAX,
		};

		/** 
			����
			@param
				vp ����һ���ӿ�
			@remark
				CanvasĬ��������һ��2D���󣬻���2DͼԪʱ������ѹ�����
		*/
		Canvas( const Viewport& vp );

		virtual ~Canvas( );

		/** 
			����һ��ƽ������
		*/
		void DrawLine2D( const Vector2& P1, const Vector2& P2, const Color& C );

		/** 
			����һ�����ľ���
		*/
		void DrawRect2D( const Vector2& P1, const Vector2& P2, const Color& C );

		/** 
			����һ��3D����
		*/
		void DrawLine( const Vector3& P1, const Vector3& P2, const Color& C );

		/** 
			����һ��3D����,ͨ��Ӳ����C1��C2��ɫ���ֵ
			@param
				P1 ����1
			@param
				P2 ����2
			@param
				C1 ��ɫ1
			@param
				C2 ��ɫ2
		*/
		void DrawLine( const Vector3& P1, const Vector3& P2, const Color& C1, const Color& C2 );

		/** 
			����һ��������
			@param
				Pos ���Ͻ�
			@param
				Size ��С
			@param
				UV ͼƬ�����������Ͻ�
			@param
				SizeUV ͼƬ���������Сƫ��
			@param
				C ��ɫ
			@param
				InTexture ����
			@param
				Mode ���ģʽ
		*/
		void DrawTile(	const Vector2& Pos, 
						const Vector2& Size, 
						const Vector2& UV, 
						const Vector2& SizeUV, 
						const Color& C, 
						RenderTexture* InTexture, 
						eBlendMode Mode = BLEND_Opaque );

		/** 
			����һ���ַ���
			@param
				Font �������
			@param
				Pos �ַ������Ͻ�
			@param
				C ��ɫ
			@param
				Text �ַ���
		*/
		void DrawString( RenderFont* Font, const Vector2& Pos, const Color& C, const wchar* Text );


		/** 
			ѹ��һ���µı任����
			@remark
				���������ˢ��֮ǰ�Ļ���
		*/
		void PushTransform( const Matrix4& mat );
		
		/** 
			����֮ǰ�ľ���
			@remark
				���������ˢ��֮ǰ�Ļ���
		*/
		void PopTransform( );

		/** 
			ȡͼԪ���Ƶ������任
		*/
		const Matrix4& GetFullTransform( );

		/** 
			�������е������ύ����Ⱦ�߳�
			@remark
				�߼��б���ʹ��Flush��Ӧ��Pop����
		*/
		void Flush( );
		
	private:

		BatchedElements* GetBatcher( eElementType ElementType, RenderTexture* InTexture = null, eBlendMode BlendMode = BLEND_MAX);
		
		typedef std::vector<Matrix4> TransformStack;

		TransformStack mTransformStack;

		float mViewportWidth;
		float mViewportHeight;

		// ����������ж�
		BatchedElements* mBatchedElements;
		RenderTexture* mTexture;
		eElementType mElementType;
		eBlendMode mBlendMode;
	};

	/** @} */
	/** @} */
}
