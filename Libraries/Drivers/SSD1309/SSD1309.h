#ifndef _SSD1309_H
    #define _SSD1309_H
    #include "Sys.h"
    #include "Port.h"	
	
    class SSD1309
    {
        public:
            void SetPinSpi(Pin sclk,Pin sdin,Pin dc,Pin res=P0,Pin cs=P0);
            void DisplayOn();
            void DisplayOff();
            void Init();
            void Clear(char ch=0x00);
            void ShowChar(uint8_t x, uint8_t y, uint8_t chr);
            void ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
            void ShowString(uint8_t x, uint8_t y, char *p,uint8_t interval=0);
            void ShowCHinese(uint8_t x, uint8_t y, char *hz);
			void DrawBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[]);
        protected:
			void SetPos(uint8_t x, uint8_t y);            
			void _wrcmd(uint8_t cmd);//д����
			void _wrdata(uint8_t da);//д����			       
		private:
			uint32_t oled_pow(uint8_t m, uint8_t n);		
			uint16_t SearchhzIndex(uint8_t lo, uint8_t hi); //���Һ��ֱ���λ��
			void ShowCHinese11(uint8_t x, uint8_t y, uint8_t no);     
			void WRByte(uint8_t dat, uint8_t cmd);
		protected:
            //SPI
			OutputPort _cs;
            OutputPort _res;
            OutputPort _dc;
            OutputPort _sclk;
            OutputPort _sdin;
			//8080
			OutputPort _wr;
            OutputPort _rd;            
    };
#endif
