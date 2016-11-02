#pragma once

namespace NekoEngine
{
	/** \addtogroup Engine
	*  @{
	*/
	/** \addtogroup Render
	*  @{
	*/


	/** 
		֡�ʼ�����
	*/
	class FrameSpeedUnit
	{
	public:
		FrameSpeedUnit( );

		/** 
			����
		*/
		void Tick( );

		/** 
			��õ�ǰ��֡��
		*/
		int GetFramePerSecond( );

	private:
		int				mDisplayNumber;
		int				mAccumulator;
		float			mFPSTimer;
	};

	/** 
		��Ⱦ����
	*/
	class RenderHelper
	{
	public:
		/** 
			���Ƶ���������
			@param
				Cam �����
			@param
				VP �ӿ�
			@param
				����Χ
			@param
				���Ӵ�С
		*/

		enum eVectorFontType
		{
			XFont,
			YFont,
			ZFont,
		};

		/** 
			���������ἰ����
			@param
				Cam �����
			@param
				CV ����,������
			@param
				VP �ӿ�
			@param
				Range ����Χ,3D��λ
			@param
				Size ���С
		*/
		static void DrawAxisGrid( Camera* Cam, Canvas* CV, const Viewport& VP , float Range = 100.0f, float Size = 10.0f );

		/** 
			������������ο�
			@param
				Cam �����
			@param
				CV ����,������
			@param
				VP �ӿ�
			@param
				XRatio ��Ļ����ƫ��,������½�
			@param
				YRatio ��Ļ����ƫ��,������½�
			@param
				AxisScale ������
		*/
		static void DrawAxisDirection( Camera* Cam, Canvas* CV, const Viewport& VP, float XRatio = 0.05f, float YRatio = 0.1f, float AxisScale = 30.0f );

		/** 
			����ƽ��ʸ��XYZ����
			@param
				CV ����,������
			@param
				BasePointSCR ���ƻ�������,��Ļ����ϵ
			@param
				VFT XYZ��ָʾ
			@param
				Scale �������ص�λ
		*/
		static void DrawVectorFont( Canvas* CV, const Vector2& BasePointSCR, eVectorFontType VFT, float Scale );
	};

	/** @} */
	/** @} */
}
