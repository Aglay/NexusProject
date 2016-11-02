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
		��ɫ��
	*/
	class Color
	{
	public:
		float r,g,b,a;

	public:
		/** 
			���캯��
			@remark
				��ʼ��Ϊ��ɫ
		*/
		Color( );

		/** 
			���캯��
			@remark
				ͨ��һ��ARGB��dwordֵ��ʼ��
		*/
		Color(dword color);

		/** 
			���캯��
			@remark
				ͨ����ɫ������ʼ��
		*/
		Color(float alpha, float red, float green, float blue);
		
		/** 
			dwordֵ����
			@param
				color ARGB��ʽdword��ɫ
		*/
		dword operator = (const dword color);

		/** 
			��ֵ������
			@return
				����������
		*/
		Color& operator = (const Color& color);

		/** 
			�ж���ɫ���
			@return
				��ɫ�Ƿ����
		*/
		bool operator == (const Color& color);

		/** 
			�ж���ɫ����
			@return
				��ɫ�Ƿ񲻵�
		*/
		bool operator != (const Color& color);

		/** 
			��ɫ
			@return
				�ѷ�ɫ�����ɫ����
		*/
		Color Inverse( );

		/** 
			dword������ȡɫ
			@return
				ARGB��ɫ
		*/
		operator dword( ) const;

		/** 
			�����ɫ��dword��ʽ��ɫ
			@return
				ARGB��ɫ
		*/
		dword ToDWORD( ) const ;

		/** ͨ��dword��ɫ������ɫ
			@param
				color ARGB��ɫ
			@return
				����������
		*/
		Color& SetColor(dword color);

		/**	
			����4������ֵ
			@param
				alpha ͸����,��Χ(0~1)
			@param
				red ��,��Χ(0~1)
			@param
				green ��,��Χ(0~1)
			@param
				blue ��,��Χ(0~1)
			@return
				����������
		*/
		Color& SetColor(float alpha, float red, float green, float blue);

		/**	
			����4������ֵ
			@param
				alpha ͸����,��Χ(0~255)
			@param
				red ��,��Χ(0~255)
			@param
				green ��,��Χ(0~255)
			@param
				blue ��,��Χ(0~255)
			@return
				����������
		*/
		Color& SetColor255(_byte alpha,_byte red,_byte green,_byte blue);

		/** 
			dword������ɫ
			@param
				color ABGR��ʽ��ɫ
			@return
				����������
		*/
		Color& SetColorABGR(dword color);

		/** 
			4����תΪARGB��ʽ
			@param
				alpha ͸����,��Χ(0~1)
			@param
				red ��,��Χ(0~1)
			@param
				green ��,��Χ(0~1)
			@param
				blue ��,��Χ(0~1)
			@return
				ARGB��ʽ��ɫ
		*/
		static dword ToDWORD(float alpha, float red, float green, float blue);

		/** 
			��ɫ��ֵ
			@param
				color1 ��ɫ1
			@param
				color2 ��ɫ2
			@param
				s ��ֵ��Χ(0~1)
			@return
				��ֵ�����ɫ
		*/
		static Color Lerp(const Color& color1,const Color& color2,float s);

		/** 
			��HSB/HSV ת����RGB�ռ�
			@param
				Hue ɫ��(0~1)
			@param
				Saturation ���Ͷ�(0~1) 
			@param
				Brightness ����(0~1)
			@return
				����������
		*/
		Color& SetHSB(float Hue, float Saturation, float Brightness);

		/** 
			��RGBת��ΪHSB/HSV�ռ�
			@param
				Hue ɫ��(0~1)
			@param
				Saturation ���Ͷ�(0~1) 
			@param
				Brightness ����(0~1)
		*/
		void GetHSB(float* Hue, float* Saturation, float* Brightness) const;

		/** 
			RGB32ת���Ҷ�
			@param
				R ��ɫ(0~255)
			@param
				G ��ɫ(0~255)
			@param
				B ��ɫ(0~255)
			@return
				�Ҷ�ɫ(0~255)
		*/
		static _byte RGB32ToGray( _byte R, _byte G, _byte B );

	public:
		/// ��ɫ
		static const Color cBlack;

		/// ��ɫ
		static const Color cRed;

		/// ��ɫ
		static const Color cGreen;

		/// ��ɫ
		static const Color cBlue;

		/// ��ɫ
		static const Color cYellow;

		/// ��ɫ
		static const Color cWhite;
	};

	

}
