#include "BMP280.h"
#include "math.h"
#include "stm32g4xx.h"                  // Device header
#include "i2c.h"

BMP280 _bmp280;
BMP280* bmp280=&_bmp280;
 
uint8_t BMP280_ReadID(void)
{
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1,BMP280_ADDRESS,BMP280_CHIPID_REG,I2C_MEMADD_SIZE_8BIT,&data,1,0xffff);
    return data;
}
 
uint8_t BMP280_Read_Byte(uint8_t reg)
{
    uint8_t data;
    HAL_I2C_Mem_Read(&hi2c1,BMP280_ADDRESS,reg,I2C_MEMADD_SIZE_8BIT,&data,1,0xffff);
    return data;
}
 
void BMP280_Write_Byte(uint8_t reg,uint8_t value)
{
    HAL_I2C_Mem_Write(&hi2c1,BMP280_ADDRESS,reg,I2C_MEMADD_SIZE_8BIT,&value,1,0xffff);
}
 
void Bmp_Init(void)
{
    uint8_t Lsb,Msb;
    
    /********************接下来读出矫正参数*********************/
    //温度传感器的矫正值
    Lsb = BMP280_Read_Byte(BMP280_DIG_T1_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_T1_MSB_REG);
    bmp280->T1 = (((uint16_t)Msb)<<8) + Lsb;            //高位加低位
    Lsb = BMP280_Read_Byte(BMP280_DIG_T2_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_T2_MSB_REG);
    bmp280->T2 = (((uint16_t)Msb)<<8) + Lsb;        
    Lsb = BMP280_Read_Byte(BMP280_DIG_T3_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_T3_MSB_REG);
    bmp280->T3 = (((uint16_t)Msb)<<8) + Lsb;        
    
    //大气压传感器的矫正值
    Lsb = BMP280_Read_Byte(BMP280_DIG_P1_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P1_MSB_REG);
    bmp280->P1 = (((uint16_t)Msb)<<8) + Lsb;        
    Lsb = BMP280_Read_Byte(BMP280_DIG_P2_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P2_MSB_REG);
    bmp280->P2 = (((uint16_t)Msb)<<8) + Lsb;    
    Lsb = BMP280_Read_Byte(BMP280_DIG_P3_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P3_MSB_REG);
    bmp280->P3 = (((uint16_t)Msb)<<8) + Lsb;    
    Lsb = BMP280_Read_Byte(BMP280_DIG_P4_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P4_MSB_REG);
    bmp280->P4 = (((uint16_t)Msb)<<8) + Lsb;    
    Lsb = BMP280_Read_Byte(BMP280_DIG_P5_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P5_MSB_REG);
    bmp280->P5 = (((uint16_t)Msb)<<8) + Lsb;    
    Lsb = BMP280_Read_Byte(BMP280_DIG_P6_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P6_MSB_REG);
    bmp280->P6 = (((uint16_t)Msb)<<8) + Lsb;    
    Lsb = BMP280_Read_Byte(BMP280_DIG_P7_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P7_MSB_REG);
    bmp280->P7 = (((uint16_t)Msb)<<8) + Lsb;    
    Lsb = BMP280_Read_Byte(BMP280_DIG_P8_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P8_MSB_REG);
    bmp280->P8 = (((uint16_t)Msb)<<8) + Lsb;    
    Lsb = BMP280_Read_Byte(BMP280_DIG_P9_LSB_REG);
    Msb = BMP280_Read_Byte(BMP280_DIG_P9_MSB_REG);
    bmp280->P9 = (((uint16_t)Msb)<<8) + Lsb;
 
    /******************************************************/
    BMP280_Write_Byte(BMP280_RESET_REG,BMP280_RESET_VALUE);    //往复位寄存器写入给定值
    
    BMP_OVERSAMPLE_MODE            BMP_OVERSAMPLE_MODEStructure;
    BMP_OVERSAMPLE_MODEStructure.P_Osample = BMP280_P_MODE_5;
    BMP_OVERSAMPLE_MODEStructure.T_Osample = BMP280_T_MODE_2;
    BMP_OVERSAMPLE_MODEStructure.WORKMODE  = BMP280_NORMAL_MODE;
    BMP280_Set_TemOversamp(&BMP_OVERSAMPLE_MODEStructure);
    
    BMP_CONFIG                    BMP_CONFIGStructure;
    BMP_CONFIGStructure.T_SB = BMP280_T_SB1;
    BMP_CONFIGStructure.FILTER_COEFFICIENT = BMP280_FILTER_MODE_4;
    BMP_CONFIGStructure.SPI_EN = DISABLE;
    
    BMP280_Set_Standby_FILTER(&BMP_CONFIGStructure);
}
 
//设置BMP过采样因子 MODE 
//BMP280_SLEEP_MODE||BMP280_FORCED_MODE||BMP280_NORMAL_MODE
void BMP280_Set_TemOversamp(BMP_OVERSAMPLE_MODE * Oversample_Mode)
{
    uint8_t Regtmp;
    Regtmp = ((Oversample_Mode->T_Osample)<<5)|
             ((Oversample_Mode->P_Osample)<<2)|
             ((Oversample_Mode)->WORKMODE);
    
    BMP280_Write_Byte(BMP280_CTRLMEAS_REG,Regtmp);
}
 
 
//设置保持时间和滤波器分频因子
void BMP280_Set_Standby_FILTER(BMP_CONFIG * BMP_Config)
{
    uint8_t Regtmp;
    Regtmp = ((BMP_Config->T_SB)<<5)|
             ((BMP_Config->FILTER_COEFFICIENT)<<2)|
             ((BMP_Config->SPI_EN));
    
    BMP280_Write_Byte(BMP280_CONFIG_REG,Regtmp);
}
 
//获取BMP当前状态
//status_flag = BMP280_MEASURING ||
//                 BMP280_IM_UPDATE
uint8_t  BMP280_GetStatus(uint8_t status_flag)
{
    uint8_t flag;
    flag = BMP280_Read_Byte(BMP280_STATUS_REG);
    if(flag&status_flag)    return SET;
    else return RESET;
}
 
//大气压值-Pa
uint32_t BMP280_Get_Pressure(void)
{
    uint8_t temp[3];
    long signed Bit32;
    //double pressure;
    HAL_I2C_Mem_Read(&hi2c1,BMP280_ADDRESS,BMP280_PRESSURE_MSB_REG,I2C_MEMADD_SIZE_8BIT,temp,3,0xffff);
    Bit32 = ((long)(temp[0] << 12))|((long)(temp[1] << 4))|(temp[2]>>4);    //寄存器的值组合起来
    return Bit32 ;
}
 
/*******************主要部分*********************/
/****************获取传感器精确值****************/
//大气压值-Pa
double BMP280_Get_Pressure_f(void)
{
    return bmp280_compensate_P_int64(BMP280_Get_Pressure())/256.0;
}
 
//温度值-℃
double BMP280_Get_Temperature(void)
{
    uint8_t temp[3];
    long signed Bit32;
    double temperature;
    HAL_I2C_Mem_Read(&hi2c1,BMP280_ADDRESS,BMP280_TEMPERATURE_MSB_REG,I2C_MEMADD_SIZE_8BIT,temp,3,0xffff);
    Bit32 = ((long)(temp[0] << 12))|((long)(temp[1] << 4))|(temp[2]>>4);    //寄存器的值组合起来
    temperature = bmp280_compensate_T_int32(Bit32)/100.0;
    return temperature;
}
 
/**************************传感器值转定点值*************************************/
 
BMP280_S32_t t_fine;            //用于计算补偿
// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC. 
// t_fine carries fine temperature as global value
BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T)
{
    BMP280_S32_t var1, var2, T;
    var1 = ((((adc_T>>3) - ((BMP280_S32_t)dig_T1<<1))) * ((BMP280_S32_t)dig_T2)) >> 11;
    var2 = (((((adc_T>>4) - ((BMP280_S32_t)dig_T1)) * ((adc_T>>4) - ((BMP280_S32_t)dig_T1))) >> 12) * 
    ((BMP280_S32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}
 
// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
BMP280_U32_t bmp280_compensate_P_int64(BMP280_S32_t adc_P)
{
    BMP280_S64_t var1, var2, p;
    var1 = ((BMP280_S64_t)t_fine) - 128000;
    var2 = var1 * var1 * (BMP280_S64_t)dig_P6;
    var2 = var2 + ((var1*(BMP280_S64_t)dig_P5)<<17);
    var2 = var2 + (((BMP280_S64_t)dig_P4)<<35);
    var1 = ((var1 * var1 * (BMP280_S64_t)dig_P3)>>8) + ((var1 * (BMP280_S64_t)dig_P2)<<12);
    var1 = (((((BMP280_S64_t)1)<<47)+var1))*((BMP280_S64_t)dig_P1)>>33;
    if (var1 == 0)
    {
    return 0; // avoid exception caused by division by zero
    }
    p = 1048576-adc_P;
    p = (((p<<31)-var2)*3125)/var1;
    var1 = (((BMP280_S64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
    var2 = (((BMP280_S64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((BMP280_S64_t)dig_P7)<<4);
    return (BMP280_U32_t)p;
}

double BMP280_Altitide(void)
{
  double P,T;
  P=BMP280_Get_Pressure_f();
  T=BMP280_Get_Temperature();
	if(P>0)
	{
		return((pow((101325.0/P),1/5.257)-1.0)*(T+273.15))/0.0065;
		//*Altitide=44330*(1.0-pow((P/101325.0),1/5.255));
	}
  else
    return 0;
}
