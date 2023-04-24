#include "mpu9250.h"
#include "main.h"
#include "i2c.h"                    
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "stdio.h"

//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32¿ª·¢°å
//MPU9250Çý¶¯´úÂë	   
//ÕýµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//´´½¨ÈÕÆÚ:2016/7/19
//°æ±¾£ºV1.1
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖÝÊÐÐÇÒíµç×Ó¿Æ¼¼ÓÐÏÞ¹«Ë¾ 2014-2024
//All rights reserved	
//********************************************************************************
//ÐÞ¸ÄËµÃ÷
//V1.1 20160902
//ÐÞ¸ÄMPU6500_IDÎª: MPU6500_ID1,MPU6500_ID2,ÒòÎª9205¿ÉÄÜÓÐ2ÖÖID!!!								  
////////////////////////////////////////////////////////////////////////////////// 	

//³õÊ¼»¯MPU9250
//·µ»ØÖµ:0,³É¹¦
//    ÆäËû,´íÎó´úÂë
//u8 MPU9250_Init(void)
//{
//    u8 res=0;
//    IIC_Init();     //³õÊ¼»¯IIC×ÜÏß
//    MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//¸´Î»MPU9250
//    delay_ms(100);  //ÑÓÊ±100ms
//    MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//»½ÐÑMPU9250
//    MPU_Set_Gyro_Fsr(3);					        	//ÍÓÂÝÒÇ´«¸ÐÆ÷,¡À2000dps
//	MPU_Set_Accel_Fsr(0);					       	 	//¼ÓËÙ¶È´«¸ÐÆ÷,¡À2g
//    MPU_Set_Rate(50);						       	 	//ÉèÖÃ²ÉÑùÂÊ50Hz
//    MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //¹Ø±ÕËùÓÐÖÐ¶Ï
//	MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2CÖ÷Ä£Ê½¹Ø±Õ
//	MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	//¹Ø±ÕFIFO
//	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);//INTÒý½ÅµÍµçÆ½ÓÐÐ§£¬¿ªÆôbypassÄ£Ê½£¬¿ÉÒÔÖ±½Ó¶ÁÈ¡´ÅÁ¦¼Æ
//    res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);  //¶ÁÈ¡MPU6500µÄID
//    if(res==MPU6500_ID1||res==MPU6500_ID2) 				//Æ÷¼þIDÕýÈ·
//    {
//        MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	//ÉèÖÃCLKSEL,PLL XÖáÎª²Î¿¼
//        MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	//¼ÓËÙ¶ÈÓëÍÓÂÝÒÇ¶¼¹¤×÷
//		MPU_Set_Rate(50);						       			//ÉèÖÃ²ÉÑùÂÊÎª50Hz   
//    }else return 1;
// 
//    res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA);    			//¶ÁÈ¡AK8963 ID   
//    if(res==AK8963_ID)
//    {
//        MPU_Write_Byte(AK8963_ADDR,MAG_CNTL2,0X01);		//¸´Î»AK8963
//		delay_ms(50);
//        MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11);		//ÉèÖÃAK8963Îªµ¥´Î²âÁ¿
//    }else return 1;

//    return 0;
//}
u8 MPU9250_Init(void)
{
    u8 res=0;
    MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);//å¤ä½MPU9250
    HAL_Delay(100);  //å»¶æ—¶100ms
    MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);//å”¤é†’MPU9250
    MPU_Set_Gyro_Fsr(3);					        	//é™€èžºä»ªä¼ æ„Ÿå™¨,Â±2000dps
	  MPU_Set_Accel_Fsr(0);					       	 	//åŠ é€Ÿåº¦ä¼ æ„Ÿå™¨,Â±2g
    MPU_Set_Rate(50);						       	 	//è®¾ç½®é‡‡æ ·çŽ‡50Hz
    MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   //å…³é—­æ‰€æœ‰ä¸­æ–­
	  MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);//I2Cä¸»æ¨¡å¼å…³é—­
	  MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	//å…³é—­FIFO
	  MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);//INTå¼•è„šä½Žç”µå¹³æœ‰æ•ˆï¼Œå¼€å¯bypassæ¨¡å¼ï¼Œå¯ä»¥ç›´æŽ¥è¯»å–ç£åŠ›è®¡
    res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);  //è¯»å–MPU6500çš„ID
    if(res==MPU6500_ID1||res==MPU6500_ID2) //å™¨ä»¶IDæ­£ç¡®
    {
        MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	//è®¾ç½®CLKSEL,PLL Xè½´ä¸ºå‚è€ƒ
        MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	//åŠ é€Ÿåº¦ä¸Žé™€èžºä»ªéƒ½å·¥ä½œ
		    MPU_Set_Rate(50);						       	//è®¾ç½®é‡‡æ ·çŽ‡ä¸º50Hz   
    }else return 1;
 
    res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA);    			//è¯»å–AK8963 ID   
    if(res==AK8963_ID)
    {
        MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11);		//è®¾ç½®AK8963ä¸ºå•æ¬¡æµ‹é‡æ¨¡å¼
    }else return 1;

    return 0;
}


//ÉèÖÃMPU9250ÍÓÂÝÒÇ´«¸ÐÆ÷ÂúÁ¿³Ì·¶Î§
//fsr:0,¡À250dps;1,¡À500dps;2,¡À1000dps;3,¡À2000dps
//·µ»ØÖµ:0,ÉèÖÃ³É¹¦
//    ÆäËû,ÉèÖÃÊ§°Ü 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,(fsr<<3)|3);//ÉèÖÃÍÓÂÝÒÇÂúÁ¿³Ì·¶Î§  
}
//ÉèÖÃMPU9250¼ÓËÙ¶È´«¸ÐÆ÷ÂúÁ¿³Ì·¶Î§
//fsr:0,¡À2g;1,¡À4g;2,¡À8g;3,¡À16g
//·µ»ØÖµ:0,ÉèÖÃ³É¹¦
//    ÆäËû,ÉèÖÃÊ§°Ü 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//ÉèÖÃ¼ÓËÙ¶È´«¸ÐÆ÷ÂúÁ¿³Ì·¶Î§  
}

//ÉèÖÃMPU9250µÄÊý×ÖµÍÍ¨ÂË²¨Æ÷
//lpf:Êý×ÖµÍÍ¨ÂË²¨ÆµÂÊ(Hz)
//·µ»ØÖµ:0,ÉèÖÃ³É¹¦
//    ÆäËû,ÉèÖÃÊ§°Ü 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data);//ÉèÖÃÊý×ÖµÍÍ¨ÂË²¨Æ÷  
}

//ÉèÖÃMPU9250µÄ²ÉÑùÂÊ(¼Ù¶¨Fs=1KHz)
//rate:4~1000(Hz)
//·µ»ØÖµ:0,ÉèÖÃ³É¹¦
//    ÆäËû,ÉèÖÃÊ§°Ü 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	//ÉèÖÃÊý×ÖµÍÍ¨ÂË²¨Æ÷
 	return MPU_Set_LPF(rate/2);	//×Ô¶¯ÉèÖÃLPFÎª²ÉÑùÂÊµÄÒ»°ë
}

//µÃµ½ÎÂ¶ÈÖµ
//·µ»ØÖµ:ÎÂ¶ÈÖµ(À©´óÁË100±¶)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return temp*100;;
}
//µÃµ½ÍÓÂÝÒÇÖµ(Ô­Ê¼Öµ)
//gx,gy,gz:ÍÓÂÝÒÇx,y,zÖáµÄÔ­Ê¼¶ÁÊý(´ø·ûºÅ)
//·µ»ØÖµ:0,³É¹¦
//    ÆäËû,´íÎó´úÂë
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res; 
	res=MPU_Read_Len(MPU9250_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//µÃµ½¼ÓËÙ¶ÈÖµ(Ô­Ê¼Öµ)
//gx,gy,gz:ÍÓÂÝÒÇx,y,zÖáµÄÔ­Ê¼¶ÁÊý(´ø·ûºÅ)
//·µ»ØÖµ:0,³É¹¦
//    ÆäËû,´íÎó´úÂë
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}

//µÃµ½´ÅÁ¦¼ÆÖµ(Ô­Ê¼Öµ)
//mx,my,mz:´ÅÁ¦¼Æx,y,zÖáµÄÔ­Ê¼¶ÁÊý(´ø·ûºÅ)
//·µ»ØÖµ:0,³É¹¦
//    ÆäËû,´íÎó´úÂë
u8 MPU_Get_Magnetometer(short *mx,short *my,short *mz)
{
    u8 buf[6],res;  
 	res=MPU_Read_Len(AK8963_ADDR,MAG_XOUT_L,6,buf);
	if(res==0)
	{
		*mx=((u16)buf[1]<<8)|buf[0];  
		*my=((u16)buf[3]<<8)|buf[2];  
		*mz=((u16)buf[5]<<8)|buf[4];
	} 	 
	MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11); //AK8963Ã¿´Î¶ÁÍêÒÔºó¶¼ÐèÒªÖØÐÂÉèÖÃÎªµ¥´Î²âÁ¿Ä£Ê½
    return res;;
}

//IICÁ¬ÐøÐ´
//addr:Æ÷¼þµØÖ· 
//reg:¼Ä´æÆ÷µØÖ·
//len:Ð´Èë³¤¶È
//buf:Êý¾ÝÇø
//·µ»ØÖµ:0,Õý³£
//    ÆäËû,´íÎó´úÂë
//u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
//{
//    u8 i;
//    IIC_Start();
//    IIC_Send_Byte((addr<<1)|0); //·¢ËÍÆ÷¼þµØÖ·+Ð´ÃüÁî
//    if(IIC_Wait_Ack())          //µÈ´ýÓ¦´ð
//    {
//        IIC_Stop();
//        return 1;
//    }
//    IIC_Send_Byte(reg);         //Ð´¼Ä´æÆ÷µØÖ·
//    IIC_Wait_Ack();             //µÈ´ýÓ¦´ð
//    for(i=0;i<len;i++)
//    {
//        IIC_Send_Byte(buf[i]);  //·¢ËÍÊý¾Ý
//        if(IIC_Wait_Ack())      //µÈ´ýACK
//        {
//            IIC_Stop();
//            return 1;
//        }
//    }
//    IIC_Stop();
//    return 0;
//} 

////IICÁ¬Ðø¶Á
////addr:Æ÷¼þµØÖ·
////reg:Òª¶ÁÈ¡µÄ¼Ä´æÆ÷µØÖ·
////len:Òª¶ÁÈ¡µÄ³¤¶È
////buf:¶ÁÈ¡µ½µÄÊý¾Ý´æ´¢Çø
////·µ»ØÖµ:0,Õý³£
////    ÆäËû,´íÎó´úÂë
//u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
//{ 
//    IIC_Start();
//    IIC_Send_Byte((addr<<1)|0); //·¢ËÍÆ÷¼þµØÖ·+Ð´ÃüÁî
//    if(IIC_Wait_Ack())          //µÈ´ýÓ¦´ð
//    {
//        IIC_Stop();
//        return 1;
//    }
//    IIC_Send_Byte(reg);         //Ð´¼Ä´æÆ÷µØÖ·
//    IIC_Wait_Ack();             //µÈ´ýÓ¦´ð
//	IIC_Start();                
//    IIC_Send_Byte((addr<<1)|1); //·¢ËÍÆ÷¼þµØÖ·+¶ÁÃüÁî
//    IIC_Wait_Ack();             //µÈ´ýÓ¦´ð
//    while(len)
//    {
//        if(len==1)*buf=IIC_Read_Byte(0);//¶ÁÊý¾Ý,·¢ËÍnACK 
//		else *buf=IIC_Read_Byte(1);		//¶ÁÊý¾Ý,·¢ËÍACK  
//		len--;
//		buf++;  
//    }
//    IIC_Stop();                 //²úÉúÒ»¸öÍ£Ö¹Ìõ¼þ
//    return 0;       
//}

////IICÐ´Ò»¸ö×Ö½Ú 
////devaddr:Æ÷¼þIICµØÖ·
////reg:¼Ä´æÆ÷µØÖ·
////data:Êý¾Ý
////·µ»ØÖµ:0,Õý³£
////    ÆäËû,´íÎó´úÂë
//u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data)
//{
//    IIC_Start();
//    IIC_Send_Byte((addr<<1)|0); //·¢ËÍÆ÷¼þµØÖ·+Ð´ÃüÁî
//    if(IIC_Wait_Ack())          //µÈ´ýÓ¦´ð
//    {
//        IIC_Stop();
//        return 1;
//    }
//    IIC_Send_Byte(reg);         //Ð´¼Ä´æÆ÷µØÖ·
//    IIC_Wait_Ack();             //µÈ´ýÓ¦´ð
//    IIC_Send_Byte(data);        //·¢ËÍÊý¾Ý
//    if(IIC_Wait_Ack())          //µÈ´ýACK
//    {
//        IIC_Stop();
//        return 1;
//    }
//    IIC_Stop();
//    return 0;
//}

////IIC¶ÁÒ»¸ö×Ö½Ú 
////reg:¼Ä´æÆ÷µØÖ· 
////·µ»ØÖµ:¶Áµ½µÄÊý¾Ý
//u8 MPU_Read_Byte(u8 addr,u8 reg)
//{
//    u8 res;
//    IIC_Start();
//    IIC_Send_Byte((addr<<1)|0); //·¢ËÍÆ÷¼þµØÖ·+Ð´ÃüÁî
//    IIC_Wait_Ack();             //µÈ´ýÓ¦´ð
//    IIC_Send_Byte(reg);         //Ð´¼Ä´æÆ÷µØÖ·
//    IIC_Wait_Ack();             //µÈ´ýÓ¦´ð
//	IIC_Start();                
//    IIC_Send_Byte((addr<<1)|1); //·¢ËÍÆ÷¼þµØÖ·+¶ÁÃüÁî
//    IIC_Wait_Ack();             //µÈ´ýÓ¦´ð
//    res=IIC_Read_Byte(0);		//¶ÁÊý¾Ý,·¢ËÍnACK  
//    IIC_Stop();                 //²úÉúÒ»¸öÍ£Ö¹Ìõ¼þ
//    return res;  
//}
//IICè¿žç»­å†™
//addr:å™¨ä»¶åœ°å€ 
//reg:å¯„å­˜å™¨åœ°å€
//len:å†™å…¥é•¿åº¦
//buf:æ•°æ®åŒº
//è¿”å›žå€¼:0,æ­£å¸¸
//    å…¶ä»–,é”™è¯¯ä»£ç 
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
     HAL_I2C_Mem_Write(&hi2c1, (addr<<1), reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xfff);
     return 0;
} 

//IICè¿žç»­è¯»
//addr:å™¨ä»¶åœ°å€
//reg:è¦è¯»å–çš„å¯„å­˜å™¨åœ°å€
//len:è¦è¯»å–çš„é•¿åº¦
//buf:è¯»å–åˆ°çš„æ•°æ®å­˜å‚¨åŒº
//è¿”å›žå€¼:0,æ­£å¸¸
//    å…¶ä»–,é”™è¯¯ä»£ç 
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
//    while(hi2c1.State != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Read(&hi2c1, (addr<<1), reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xfff);
//    HAL_I2C_Mem_Read_DMA(&hi2c1, (addr<<1), reg, I2C_MEMADD_SIZE_8BIT, buf, len);
    return 0;       
}

//IICå†™ä¸€ä¸ªå­—èŠ‚ 
//devaddr:å™¨ä»¶IICåœ°å€
//reg:å¯„å­˜å™¨åœ°å€
//data:æ•°æ®
//è¿”å›žå€¼:0,æ­£å¸¸
//    å…¶ä»–,é”™è¯¯ä»£ç 
u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data)
{
    HAL_I2C_Mem_Write(&hi2c1, (addr<<1), reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xfff);
    return 0;
}

//IICè¯»ä¸€ä¸ªå­—èŠ‚ 
//reg:å¯„å­˜å™¨åœ°å€ 
//è¿”å›žå€¼:è¯»åˆ°çš„æ•°æ®
u8 MPU_Read_Byte(u8 addr,u8 reg)
{
    u8 res;
    HAL_I2C_Mem_Read(&hi2c1, (addr<<1), reg, I2C_MEMADD_SIZE_8BIT, &res, 1, 0xfff);
    return res;  
}

