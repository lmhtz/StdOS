/*
*********************************************************************************************************
*
*	ģ������ : �ַ�������\��ֵת��
*	�ļ����� : bsp_user_lib.h
*	��    �� : V1.1
*	˵    �� : ͷ�ļ�
*
*********************************************************************************************************
*/

#ifndef __BSP_USER_LIB_H
#define __BSP_USER_LIB_H
#ifdef __cplusplus
extern "C"  {
#endif
int str_len(char *_str);
void str_cpy(char *_tar, char *_src);
int str_cmp(char * s1, char * s2);
void mem_set(char *_tar, char _data, int _len);

void int_to_str(int _iNumber, char *_pBuf, unsigned char _len);
int str_to_int(char *_pStr);

uint16_t BEBufToUint16(uint8_t *_pBuf);
uint16_t LEBufToUint16(uint8_t *_pBuf);

uint16_t CRC16_Modbus(uint8_t *_pBuf, uint16_t _usLen) ;
int32_t  CaculTwoPoint(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x);
#ifdef __cplusplus
}
#endif
#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/