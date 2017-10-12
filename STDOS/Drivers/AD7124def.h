#ifndef _AD7124DEF_8_H
    #define _AD7124DEF_8_H

    /************************ AD7124 COMMS寄存器读写控制 *************************************/
    #define AD7124_WR				0x00
    #define AD7124_RD				0x40

    /* AD7124 Register Map */
    #define AD7124_COMM_REG      0x00
    #define AD7124_STATUS_REG    0x00
    #define AD7124_ADC_CTRL_REG  0x01
    #define AD7124_DATA_REG      0x02
    #define AD7124_IO_CTRL1_REG  0x03
    #define AD7124_IO_CTRL2_REG  0x04
    #define AD7124_ID_REG        0x05
    #define AD7124_ERR_REG       0x06
    #define AD7124_ERREN_REG     0x07
    #define AD7124_CH0_MAP_REG   0x09
    #define AD7124_CH1_MAP_REG   0x0A
    #define AD7124_CH2_MAP_REG   0x0B
    #define AD7124_CH3_MAP_REG   0x0C
    #define AD7124_CH4_MAP_REG   0x0D
    #define AD7124_CH5_MAP_REG   0x0E
    #define AD7124_CH6_MAP_REG   0x0F
    #define AD7124_CH7_MAP_REG   0x10
    #define AD7124_CH8_MAP_REG   0x11
    #define AD7124_CH9_MAP_REG   0x12
    #define AD7124_CH10_MAP_REG  0x13
    #define AD7124_CH11_MAP_REG  0x14
    #define AD7124_CH12_MAP_REG  0x15
    #define AD7124_CH13_MAP_REG  0x16
    #define AD7124_CH14_MAP_REG  0x17
    #define AD7124_CH15_MAP_REG  0x18
    #define AD7124_CFG0_REG      0x19
    #define AD7124_CFG1_REG      0x1A
    #define AD7124_CFG2_REG      0x1B
    #define AD7124_CFG3_REG      0x1C
    #define AD7124_CFG4_REG      0x1D
    #define AD7124_CFG5_REG      0x1E
    #define AD7124_CFG6_REG      0x1F
    #define AD7124_CFG7_REG      0x20
    #define AD7124_FILT0_REG     0x21
    #define AD7124_FILT1_REG     0x22
    #define AD7124_FILT2_REG     0x23
    #define AD7124_FILT3_REG     0x24
    #define AD7124_FILT4_REG     0x25
    #define AD7124_FILT5_REG     0x26
    #define AD7124_FILT6_REG     0x27
    #define AD7124_FILT7_REG     0x28
    #define AD7124_OFFS0_REG     0x29
    #define AD7124_OFFS1_REG     0x2A
    #define AD7124_OFFS2_REG     0x2B
    #define AD7124_OFFS3_REG     0x2C
    #define AD7124_OFFS4_REG     0x2D
    #define AD7124_OFFS5_REG     0x2E
    #define AD7124_OFFS6_REG     0x2F
    #define AD7124_OFFS7_REG     0x30
    #define AD7124_GAIN0_REG     0x31
    #define AD7124_GAIN1_REG     0x32
    #define AD7124_GAIN2_REG     0x33
    #define AD7124_GAIN3_REG     0x34
    #define AD7124_GAIN4_REG     0x35
    #define AD7124_GAIN5_REG     0x36
    #define AD7124_GAIN6_REG     0x37
    #define AD7124_GAIN7_REG     0x38

    /* AD7124 Register Bytes */
    #define AD7124_COMM_REG_BYTES    	 1
    #define AD7124_STATUS_REG_BYTES    1
    #define AD7124_ADC_CTRL_REG_BYTES  2
    #define AD7124_DATA_REG_BYTES      3
    #define AD7124_IO_CTRL1_REG_BYTES  3
    #define AD7124_IO_CTRL2_REG_BYTES  2
    #define AD7124_ID_REG_BYTES        1
    #define AD7124_ERR_REG_BYTES       3
    #define AD7124_ERREN_REG_BYTES     3
    #define AD7124_CH0_MAP_REG_BYTES   2
    #define AD7124_CH1_MAP_REG_BYTES   2
    #define AD7124_CH2_MAP_REG_BYTES   2
    #define AD7124_CH3_MAP_REG_BYTES   2
    #define AD7124_CH4_MAP_REG_BYTES   2
    #define AD7124_CH5_MAP_REG_BYTES   2
    #define AD7124_CH6_MAP_REG_BYTES   2
    #define AD7124_CH7_MAP_REG_BYTES   2
    #define AD7124_CH8_MAP_REG_BYTES   2
    #define AD7124_CH9_MAP_REG_BYTES   2
    #define AD7124_CH10_MAP_REG_BYTES  2
    #define AD7124_CH11_MAP_REG_BYTES  2
    #define AD7124_CH12_MAP_REG_BYTES  2
    #define AD7124_CH13_MAP_REG_BYTES  2
    #define AD7124_CH14_MAP_REG_BYTES  2
    #define AD7124_CH15_MAP_REG_BYTES  2
    #define AD7124_CFG0_REG_BYTES      2
    #define AD7124_CFG1_REG_BYTES      2
    #define AD7124_CFG2_REG_BYTES      2
    #define AD7124_CFG3_REG_BYTES      2
    #define AD7124_CFG4_REG_BYTES      2
    #define AD7124_CFG5_REG_BYTES      2
    #define AD7124_CFG6_REG_BYTES      2
    #define AD7124_CFG7_REG_BYTES      2
    #define AD7124_FILT0_REG_BYTES     3
    #define AD7124_FILT1_REG_BYTES     3
    #define AD7124_FILT2_REG_BYTES     3
    #define AD7124_FILT3_REG_BYTES     3
    #define AD7124_FILT4_REG_BYTES     3
    #define AD7124_FILT5_REG_BYTES     3
    #define AD7124_FILT6_REG_BYTES     3
    #define AD7124_FILT7_REG_BYTES     3
    #define AD7124_OFFS0_REG_BYTES     3
    #define AD7124_OFFS1_REG_BYTES     3
    #define AD7124_OFFS2_REG_BYTES     3
    #define AD7124_OFFS3_REG_BYTES     3
    #define AD7124_OFFS4_REG_BYTES     3
    #define AD7124_OFFS5_REG_BYTES     3
    #define AD7124_OFFS6_REG_BYTES     3
    #define AD7124_OFFS7_REG_BYTES     3
    #define AD7124_GAIN0_REG_BYTES     3
    #define AD7124_GAIN1_REG_BYTES     3
    #define AD7124_GAIN2_REG_BYTES     3
    #define AD7124_GAIN3_REG_BYTES     3
    #define AD7124_GAIN4_REG_BYTES     3
    #define AD7124_GAIN5_REG_BYTES     3
    #define AD7124_GAIN6_REG_BYTES     3
    #define AD7124_GAIN7_REG_BYTES     3

    /* Communication Register bits */
    #define AD7124_COMM_REG_WEN    (0 << 7)
    #define AD7124_COMM_REG_WR     (0 << 6)
    #define AD7124_COMM_REG_RD     (1 << 6)
    #define AD7124_COMM_REG_RA(x)  ((x) & 0x3F)

    /* Status Register bits */
    #define AD7124_STATUS_REG_RDY          (1 << 7)
    #define AD7124_STATUS_REG_ERROR_FLAG   (1 << 6)
    #define AD7124_STATUS_REG_POR_FLAG     (1 << 4)
    #define AD7124_STATUS_REG_CH_ACTIVE(x) ((x) & 0xF)

    /* ADC_Control Register bits */
    #define AD7124_ADC_CTRL_REG_DOUT_RDY_DEL   (1 << 12)
    #define AD7124_ADC_CTRL_REG_CONT_READ      (1 << 11)
    #define AD7124_ADC_CTRL_REG_DATA_STATUS    (1 << 10)
    #define AD7124_ADC_CTRL_REG_CS_EN          (1 << 9)
    #define AD7124_ADC_CTRL_REG_REF_EN         (1 << 8)
    #define AD7124_ADC_CTRL_REG_POWER_MODE(x)  (((x) & 0x3) << 6)
    #define AD7124_ADC_CTRL_REG_MODE(x)        (((x) & 0xF) << 2)
    #define AD7124_ADC_CTRL_REG_CLK_SEL(x))    (((x) & 0x3) << 0)

    /* IO_Control_1 Register bits */
    #define AD7124_IO_CTRL1_REG_GPIO_DAT2     (1 << 23)
    #define AD7124_IO_CTRL1_REG_GPIO_DAT1     (1 << 22)
    #define AD7124_IO_CTRL1_REG_GPIO_CTRL2    (1 << 19)
    #define AD7124_IO_CTRL1_REG_GPIO_CTRL1    (1 << 18)
    #define AD7124_IO_CTRL1_REG_PDSW          (1 << 15)
    #define AD7124_IO_CTRL1_REG_IOUT1(x)      (((x) & 0x7) << 11)
    #define AD7124_IO_CTRL1_REG_IOUT0(x)      (((x) & 0x7) << 8)
    #define AD7124_IO_CTRL1_REG_IOUT_CH1(x)   (((x) & 0xF) << 4)
    #define AD7124_IO_CTRL1_REG_IOUT_CH0(x)   (((x) & 0xF) << 0)

    /*IO_Control_1 AD7124-8 specific bits */
    #define AD7124_8_IO_CTRL1_REG_GPIO_DAT4     (1 << 23)
    #define AD7124_8_IO_CTRL1_REG_GPIO_DAT3     (1 << 22)
    #define AD7124_8_IO_CTRL1_REG_GPIO_DAT2     (1 << 21)
    #define AD7124_8_IO_CTRL1_REG_GPIO_DAT1     (1 << 20)
    #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL4    (1 << 19)
    #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL3    (1 << 18)
    #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL2    (1 << 17)
    #define AD7124_8_IO_CTRL1_REG_GPIO_CTRL1    (1 << 16)

    /* IO_Control_2 Register bits */
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS7   (1 << 15)
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS6   (1 << 14)
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS5   (1 << 11)
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS4   (1 << 10)
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS3   (1 << 5)
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS2   (1 << 4)
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS1   (1 << 1)
    #define AD7124_IO_CTRL2_REG_GPIO_VBIAS0   (1 << 0)

    /*IO_Control_2 AD7124-8 specific bits */
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS15  (1 << 15)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS14  (1 << 14)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS13  (1 << 13)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS12  (1 << 12)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS11  (1 << 11)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS10  (1 << 10)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS9   (1 << 9)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS8   (1 << 8)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS7   (1 << 7)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS6   (1 << 6)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS5   (1 << 5)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS4   (1 << 4)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS3   (1 << 3)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS2   (1 << 2)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS1   (1 << 1)
    #define AD7124_8_IO_CTRL2_REG_GPIO_VBIAS0   (1 << 0)

    /* ID Register bits */
    #define AD7124_ID_REG_DEVICE_ID(x)   (((x) & 0xF) << 4)
    #define AD7124_ID_REG_SILICON_REV(x) (((x) & 0xF) << 0)

    /* Error Register bits */
    #define AD7124_ERR_REG_LDO_CAP_ERR        (1 << 19)
    #define AD7124_ERR_REG_ADC_CAL_ERR        (1 << 18)
    #define AD7124_ERR_REG_ADC_CONV_ERR       (1 << 17)
    #define AD7124_ERR_REG_ADC_SAT_ERR        (1 << 16)
    #define AD7124_ERR_REG_AINP_OV_ERR        (1 << 15)
    #define AD7124_ERR_REG_AINP_UV_ERR        (1 << 14)
    #define AD7124_ERR_REG_AINM_OV_ERR        (1 << 13)
    #define AD7124_ERR_REG_AINM_UV_ERR        (1 << 12)
    #define AD7124_ERR_REG_REF_DET_ERR        (1 << 11)
    #define AD7124_ERR_REG_DLDO_PSM_ERR       (1 << 9)
    #define AD7124_ERR_REG_ALDO_PSM_ERR       (1 << 7)
    #define AD7124_ERR_REG_SPI_IGNORE_ERR     (1 << 6)
    #define AD7124_ERR_REG_SPI_SLCK_CNT_ERR   (1 << 5)
    #define AD7124_ERR_REG_SPI_READ_ERR       (1 << 4)
    #define AD7124_ERR_REG_SPI_WRITE_ERR      (1 << 3)
    #define AD7124_ERR_REG_SPI_CRC_ERR        (1 << 2)
    #define AD7124_ERR_REG_MM_CRC_ERR         (1 << 1)

    /* Error_En Register bits */
    #define AD7124_ERREN_REG_MCLK_CNT_EN           (1 << 22)
    #define AD7124_ERREN_REG_LDO_CAP_CHK_TEST_EN   (1 << 21)
    #define AD7124_ERREN_REG_LDO_CAP_CHK(x)        (((x) & 0x3) << 19)
    #define AD7124_ERREN_REG_ADC_CAL_ERR_EN        (1 << 18)
    #define AD7124_ERREN_REG_ADC_CONV_ERR_EN       (1 << 17)
    #define AD7124_ERREN_REG_ADC_SAT_ERR_EN        (1 << 16)
    #define AD7124_ERREN_REG_AINP_OV_ERR_EN        (1 << 15)
    #define AD7124_ERREN_REG_AINP_UV_ERR_EN        (1 << 14)
    #define AD7124_ERREN_REG_AINM_OV_ERR_EN        (1 << 13)
    #define AD7124_ERREN_REG_AINM_UV_ERR_EN        (1 << 12)
    #define AD7124_ERREN_REG_REF_DET_ERR_EN        (1 << 11)
    #define AD7124_ERREN_REG_DLDO_PSM_TRIP_TEST_EN (1 << 10)
    #define AD7124_ERREN_REG_DLDO_PSM_ERR_ERR      (1 << 9)
    #define AD7124_ERREN_REG_ALDO_PSM_TRIP_TEST_EN (1 << 8)
    #define AD7124_ERREN_REG_ALDO_PSM_ERR_EN       (1 << 7)
    #define AD7124_ERREN_REG_SPI_IGNORE_ERR_EN     (1 << 6)
    #define AD7124_ERREN_REG_SPI_SCLK_CNT_ERR_EN   (1 << 5)
    #define AD7124_ERREN_REG_SPI_READ_ERR_EN       (1 << 4)
    #define AD7124_ERREN_REG_SPI_WRITE_ERR_EN      (1 << 3)
    #define AD7124_ERREN_REG_SPI_CRC_ERR_EN        (1 << 2)
    #define AD7124_ERREN_REG_MM_CRC_ERR_EN         (1 << 1)

    /* Channel Registers 0-15 bits */
    #define AD7124_CH_MAP_REG_CH_ENABLE    (1 << 15)
    #define AD7124_CH_MAP_REG_SETUP(x)     (((x) & 0x7) << 12)
    #define AD7124_CH_MAP_REG_AINP(x)      (((x) & 0x1F) << 5)    
    #define AD7124_CH_MAP_REG_AINM(x)      (((x) & 0x1F) << 0)

    /* Configuration Registers 0-7 bits */
    #define AD7124_CFG_REG_BIPOLAR     (1 << 11)
    #define AD7124_CFG_REG_BURNOUT(x)  (((x) & 0x3) << 9)
    #define AD7124_CFG_REG_REF_BUFP    (1 << 8)
    #define AD7124_CFG_REG_REF_BUFM    (1 << 7)
    #define AD7124_CFG_REG_AIN_BUFP    (1 << 6)
    #define AD7124_CFG_REG_AINN_BUFM   (1 << 5)
    #define AD7124_CFG_REG_REF_SEL(x)  ((x) & 0x3) << 3
    #define AD7124_CFG_REG_PGA(x)      (((x) & 0x7) << 0)

    /* Filter Register 0-7 bits */
    #define AD7124_FILT_REG_FILTER(x)         (((x) & 0x7) << 21)
    #define AD7124_FILT_REG_REJ60             (1 << 20)
    #define AD7124_FILT_REG_POST_FILTER(x)    (((x) & 0x7) << 17)
    #define AD7124_FILT_REG_SINGLE_CYCLE      (1 << 16)
    #define AD7124_FILT_REG_FS(x)             (((x) & 0x7FF) << 0)    



    //ADC_CONTROL			内部参考电压使能	低功率	连续转换模式	内部时钟不输出
    //IO_CONTROL_1		无数字输出 	数字输出禁用	PDSW关	IOUT1关闭	IOUT0关闭	IOUT1_CH=0	IOUT0_CH=0
    //IO_CONTROL_2		无偏置电压
    //CONFIG0					单极性	Burnout关	基准电压缓冲禁用	模拟输入缓冲禁用	基准电压REF1	PGA=16
    //CONFIG1					单极性	Burnout关	基准电压缓冲禁用	模拟输入缓冲禁用	基准电压REF2	PGA=16
    //CONFIG2					单极性	Burnout关	基准电压缓冲禁用	模拟输入缓冲禁用	基准电压内部	PGA=128
    //CONFIG3					单极性	Burnout关	基准电压缓冲禁用	模拟输入缓冲禁用	基准电压内部	PGA=1
    //CONFIG4					双极性	Burnout关	基准电压缓冲禁用	模拟输入缓冲禁用	基准电压内部	PGA=1
    #define AD7124_ADC_CTRL_REG_DATA	AD7124_ADC_CTRL_REG_REF_EN | AD7124_ADC_CTRL_REG_POWER_MODE(1)//| AD7124_ADC_CTRL_REG_MODE(1)
    #define AD7124_IO_CTRL1_REG_DATA	0
    #define AD7124_IO_CTRL2_REG_DATA	0
    #define AD7124_CFG0_REG_DATA	AD7124_CFG_REG_REF_SEL(0)|AD7124_CFG_REG_PGA(4)
    #define AD7124_CFG1_REG_DATA	AD7124_CFG_REG_REF_SEL(1)|AD7124_CFG_REG_PGA(4)
    #define AD7124_CFG2_REG_DATA	AD7124_CFG_REG_REF_SEL(2)|AD7124_CFG_REG_PGA(7)
    #define AD7124_CFG3_REG_DATA	AD7124_CFG_REG_REF_SEL(2)|AD7124_CFG_REG_PGA(0)
    #define AD7124_CFG4_REG_DATA	AD7124_CFG_REG_REF_SEL(2)|AD7124_CFG_REG_PGA(0)
    //FILTER0
    //FILTER1
    //FILTER2
    //FILTER3
    //FILTER4
    /*
    #define AD7124_FILT_REG_FILTER(x)         (((x) & 0x7) << 21)
    #define AD7124_FILT_REG_REJ60             (1 << 20)
    #define AD7124_FILT_REG_POST_FILTER(x)    (((x) & 0x7) << 17)
    #define AD7124_FILT_REG_SINGLE_CYCLE      (1 << 16)
    #define AD7124_FILT_REG_FS(x)             (((x) & 0x7FF) << 0)
     */
    #define AD7124_FILT0_REG_DATA		AD7124_FILT_REG_FS(100)
    #define AD7124_FILT1_REG_DATA		AD7124_FILT_REG_FS(100)
    #define AD7124_FILT2_REG_DATA		AD7124_FILT_REG_FS(100)
    #define AD7124_FILT3_REG_DATA		AD7124_FILT_REG_FS(100)
    #define AD7124_FILT4_REG_DATA		AD7124_FILT_REG_FS(100)

    //IO_CTRL_1_TEMP1				无数字输出 	数字输出禁用	PDSW关	IOUT1关闭			IOUT0=500uA	IOUT1_CH=0		IOUT0_CH=AIN0
    //IO_CTRL_1_TEMP1_RES		无数字输出 	数字输出禁用	PDSW关	IOUT1=1000uA	IOUT0关闭		IOUT1_CH=AIN1	IOUT0_CH=0
    //IO_CTRL_1_TEMP2				无数字输出 	数字输出禁用	PDSW关	IOUT1关闭			IOUT0=500uA	IOUT1_CH=0		IOUT0_CH=AIN4
    //IO_CTRL_1_TEMP2_RES		无数字输出 	数字输出禁用	PDSW关	IOUT1=1000uA	IOUT0关闭		IOUT1_CH=AIN7	IOUT0_CH=0
    #define AD7124_IO_CTRL1_REG_DATA_TEMP1			AD7124_IO_CTRL1_REG_IOUT1(0) | AD7124_IO_CTRL1_REG_IOUT0(4) | AD7124_IO_CTRL1_REG_IOUT_CH1(0) | AD7124_IO_CTRL1_REG_IOUT_CH0(0)
    #define AD7124_IO_CTRL1_REG_DATA_TEMP1_RES	AD7124_IO_CTRL1_REG_IOUT1(6) | AD7124_IO_CTRL1_REG_IOUT0(0) | AD7124_IO_CTRL1_REG_IOUT_CH1(1) | AD7124_IO_CTRL1_REG_IOUT_CH0(0)
    #define AD7124_IO_CTRL1_REG_DATA_TEMP2			AD7124_IO_CTRL1_REG_IOUT1(0) | AD7124_IO_CTRL1_REG_IOUT0(4) | AD7124_IO_CTRL1_REG_IOUT_CH1(0) | AD7124_IO_CTRL1_REG_IOUT_CH0(4)
    #define AD7124_IO_CTRL1_REG_DATA_TEMP2_RES	AD7124_IO_CTRL1_REG_IOUT1(6) | AD7124_IO_CTRL1_REG_IOUT0(0) | AD7124_IO_CTRL1_REG_IOUT_CH1(7) | AD7124_IO_CTRL1_REG_IOUT_CH0(0)

    //IO_CTRL_1_TEMP1_TEST	无数字输出 	数字输出禁用	PDSW关	IOUT1=500uA		IOUT0=500uA	IOUT1_CH=AIN1		IOUT0_CH=AIN0
    #define AD7124_IO_CTRL1_REG_DATA_TEMP1_TEST	AD7124_IO_CTRL1_REG_IOUT1(4) | AD7124_IO_CTRL1_REG_IOUT0(4) | AD7124_IO_CTRL1_REG_IOUT_CH1(1) | AD7124_IO_CTRL1_REG_IOUT_CH0(0)

    //温度1						CH0		ENABLE	CONFIG0		AINP[AIN2]		AINM[AIN3]
    //温度1线路电阻		CH1		ENABLE	CONFIG2		AINP[AIN3]		AINM[AVSS]
    //温度2						CH2		ENABLE	CONFIG1		AINP[AIN5]		AINM[AIN6]
    //温度2线路电阻		CH3		ENABLE	CONFIG2		AINP[AIN6]		AINM[AVSS]
    //流量A						CH4		ENABLE	CONFIG3		AINP[AIN8]		AINM[AVSS]
    //流量B						CH5		ENABLE	CONFIG3		AINP[AIN9]		AINM[AVSS]
    //TC1047					CH6		ENABLE	CONFIG3		AINP[AIN10]		AINM[AVSS]
    //AD内部温度			CH7		ENABLE	CONFIG4		AINP[温度]		AINM[AVSS]
    #define AD7124_CH0_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(0) | AD7124_CH_MAP_REG_AINP(2) | AD7124_CH_MAP_REG_AINM(3)
    #define AD7124_CH1_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(2) | AD7124_CH_MAP_REG_AINP(3) | AD7124_CH_MAP_REG_AINM(17)
    #define AD7124_CH2_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(1) | AD7124_CH_MAP_REG_AINP(5) | AD7124_CH_MAP_REG_AINM(6)
    #define AD7124_CH3_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(2) | AD7124_CH_MAP_REG_AINP(6) | AD7124_CH_MAP_REG_AINM(17)
    #define AD7124_CH4_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(3) | AD7124_CH_MAP_REG_AINP(8) | AD7124_CH_MAP_REG_AINM(17)
    #define AD7124_CH5_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(3) | AD7124_CH_MAP_REG_AINP(9) | AD7124_CH_MAP_REG_AINM(17)
    #define AD7124_CH6_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(3) | AD7124_CH_MAP_REG_AINP(10)| AD7124_CH_MAP_REG_AINM(17)
    #define AD7124_CH7_MAP_REG_DATA		AD7124_CH_MAP_REG_CH_ENABLE | AD7124_CH_MAP_REG_SETUP(4) | AD7124_CH_MAP_REG_AINP(16)| AD7124_CH_MAP_REG_AINM(17)


    #define AD7124_TEMP1_CH_CFG()					AD7124_Write_Reg(AD7124_CH0_MAP_REG,	AD7124_CH0_MAP_REG_BYTES, 	AD7124_CH0_MAP_REG_DATA);
    #define AD7124_TEMP1_IO_CFG()					AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA_TEMP1);
    #define AD7124_TEMP1_RES_CH_CFG()			AD7124_Write_Reg(AD7124_CH1_MAP_REG,	AD7124_CH1_MAP_REG_BYTES, 	AD7124_CH1_MAP_REG_DATA);
    #define AD7124_TEMP1_RES_IO_CFG()			AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA_TEMP1_RES);
    #define AD7124_TEMP2_CH_CFG()					AD7124_Write_Reg(AD7124_CH2_MAP_REG,	AD7124_CH2_MAP_REG_BYTES, 	AD7124_CH2_MAP_REG_DATA);
    #define AD7124_TEMP2_IO_CFG()					AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA_TEMP2);
    #define AD7124_TEMP2_RES_CH_CFG()			AD7124_Write_Reg(AD7124_CH3_MAP_REG,	AD7124_CH3_MAP_REG_BYTES, 	AD7124_CH3_MAP_REG_DATA);
    #define AD7124_TEMP2_RES_IO_CFG()			AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA_TEMP2_RES);
    #define AD7124_FLOWA_CH_CFG()					AD7124_Write_Reg(AD7124_CH4_MAP_REG,	AD7124_CH4_MAP_REG_BYTES, 	AD7124_CH4_MAP_REG_DATA);
    #define AD7124_FLOWA_IO_CFG()					AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA);
    #define AD7124_FLOWB_CH_CFG()					AD7124_Write_Reg(AD7124_CH5_MAP_REG,	AD7124_CH5_MAP_REG_BYTES, 	AD7124_CH5_MAP_REG_DATA);
    #define AD7124_FLOWB_IO_CFG()					AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA);
    #define AD7124_BRDTEMP_CH_CFG()				AD7124_Write_Reg(AD7124_CH6_MAP_REG,	AD7124_CH6_MAP_REG_BYTES, 	AD7124_CH6_MAP_REG_DATA);
    #define AD7124_BRDTEMP_IO_CFG()				AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA);
    #define AD7124_ADTEMP_CH_CFG()				AD7124_Write_Reg(AD7124_CH7_MAP_REG,	AD7124_CH7_MAP_REG_BYTES, 	AD7124_CH7_MAP_REG_DATA);
    #define AD7124_ADTEMP_IO_CFG()				AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	AD7124_IO_CTRL1_REG_DATA);

    #define AD7124_TEMP1_CH_CFG_CLR()				AD7124_Write_Reg(AD7124_CH0_MAP_REG,	AD7124_CH0_MAP_REG_BYTES, 	0);
    #define AD7124_TEMP1_IO_CFG_CLR()				AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	0);
    #define AD7124_TEMP1_RES_CH_CFG_CLR()		AD7124_Write_Reg(AD7124_CH1_MAP_REG,	AD7124_CH1_MAP_REG_BYTES, 	0);
    #define AD7124_TEMP1_RES_IO_CFG_CLR()		AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	0);
    #define AD7124_TEMP2_CH_CFG_CLR()				AD7124_Write_Reg(AD7124_CH2_MAP_REG,	AD7124_CH2_MAP_REG_BYTES, 	0);
    #define AD7124_TEMP2_IO_CFG_CLR()				AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	0);
    #define AD7124_TEMP2_RES_CH_CFG_CLR()		AD7124_Write_Reg(AD7124_CH3_MAP_REG,	AD7124_CH3_MAP_REG_BYTES, 	0);
    #define AD7124_TEMP2_RES_IO_CFG_CLR()		AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES, 	0);
    #define AD7124_FLOWA_CH_CFG_CLR()				AD7124_Write_Reg(AD7124_CH4_MAP_REG,	AD7124_CH4_MAP_REG_BYTES,   0);
    #define AD7124_FLOWA_IO_CFG_CLR()				AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES,  0);
    #define AD7124_FLOWB_CH_CFG_CLR()				AD7124_Write_Reg(AD7124_CH5_MAP_REG,	AD7124_CH5_MAP_REG_BYTES, 	0);
    #define AD7124_FLOWB_IO_CFG_CLR()				AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES,  0);
    #define AD7124_BRDTEMP_CH_CFG_CLR()			AD7124_Write_Reg(AD7124_CH6_MAP_REG,	AD7124_CH6_MAP_REG_BYTES,   0);
    #define AD7124_BRDTEMP_IO_CFG_CLR()			AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES,  0);
    #define AD7124_ADTEMP_CH_CFG_CLR()			AD7124_Write_Reg(AD7124_CH7_MAP_REG,	AD7124_CH7_MAP_REG_BYTES,   0);
    #define AD7124_ADTEMP_IO_CFG_CLR()			AD7124_Write_Reg(AD7124_IO_CTRL1_REG, AD7124_IO_CTRL1_REG_BYTES,  0);

#endif
