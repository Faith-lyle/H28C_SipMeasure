//
// Created by luxshare-ict on 2023/3/7.
//

#include "Public_I2C.h"

void I2C_BusInit(I2C_Def *IIC)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //Enable IIC-SCL RCC peripheral clock
    do{
        __IO uint32_t tmpreg = 0x00U;
        SET_BIT(RCC->AHB1ENR, IIC ->SCL .RCC_peripheral);
        /* Delay after an RCC peripheral clock enabling */
        tmpreg = READ_BIT(RCC->AHB1ENR, IIC ->SCL .RCC_peripheral);
        UNUSED(tmpreg);
    } while(0U);

    //Enable IIC-SDA RCC peripheral clock
    do{
        __IO uint32_t tmpreg = 0x00U;
        SET_BIT(RCC->AHB1ENR, IIC ->SDA .RCC_peripheral);
        /* Delay after an RCC peripheral clock enabling */
        tmpreg = READ_BIT(RCC->AHB1ENR, IIC ->SDA .RCC_peripheral);
        UNUSED(tmpreg);
    } while(0U);

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;		/* 设为输出口 */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;	/* IO口最大速度 */

    GPIO_InitStructure.Pin = IIC ->SCL.GPIO_Pin | IIC ->SDA .GPIO_Pin;;
    HAL_GPIO_Init(IIC ->SCL .BusPort, &GPIO_InitStructure);

    /* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */
    I2C_Stop(IIC);
}
void I2C_Bus(I2C_BusDef IIC_Bus, uint8_t value)
{
    HAL_GPIO_WritePin(IIC_Bus.BusPort,IIC_Bus.GPIO_Pin,(GPIO_PinState)value);
}
static void I2C_Delay(uint8_t uiDelay) {
//			delay_us(uiDelay);
    while (uiDelay > 0){
        uiDelay--;
    }
}

void I2C_BusMode(I2C_BusDef IIC_Bus,int32_t GPIO_Mode)
{
    GPIO_InitTypeDef gpioInitTypeDef;
    gpioInitTypeDef.Pin = IIC_Bus.GPIO_Pin;
    gpioInitTypeDef.Mode = GPIO_Mode;
    gpioInitTypeDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(IIC_Bus.BusPort,&gpioInitTypeDef);
}
/**
 * read data for i2c bus
 * @param IIC_Bus
 * @return i2c bis data
 */
uint8_t I2C_BusRead(I2C_BusDef IIC_Bus)
{
    if((IIC_Bus .BusPort ->IDR & IIC_Bus .GPIO_Pin) != 0)return 1;
    else return 0;
}
void I2C_Stop(I2C_Def *IIC)
{
    /* 当SCL高电平时，SDA出现一个上升沿表示I2C总线停止信号 */
    I2C_BusMode(IIC->SDA,OUT);
    I2C_Bus(IIC->SCL,0);
    I2C_Bus(IIC->SCL,1);
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC->SCL,1);
    I2C_Delay(WAIT_TIME);
}
void I2C_Start(I2C_Def *IIC)
{
    /* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
    I2C_BusMode(IIC->SDA,OUT);
    I2C_Bus(IIC->SDA,1);
    I2C_Bus(IIC->SCL,1);
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC->SDA,0);
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC->SCL,0);
    I2C_Delay(WAIT_TIME);
}
uint8_t I2C_WaitAck(I2C_Def *IIC)
{
    uint8_t IIC_SDA_status;
    I2C_BusMode(IIC ->SDA,IN);
    I2C_Bus(IIC ->SDA,1);	/* CPU释放SDA总线 */
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC ->SCL,1);	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
    I2C_Delay(WAIT_TIME);
    if(I2C_BusRead(IIC ->SDA))	/* CPU读取SDA口线状态 */
    {
        IIC_SDA_status = 1;
    }
    else
    {
        IIC_SDA_status = 0;
    }
    I2C_Bus(IIC ->SCL,0);
    I2C_Delay(WAIT_TIME);
    return IIC_SDA_status;

}
void I2C_Ack(I2C_Def *IIC)
{
    I2C_BusMode(IIC ->SDA,OUT);
    I2C_Bus(IIC ->SDA,0);	/* CPU驱动SDA = 0 */
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC ->SCL,1);	/* CPU产生1个时钟 */
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC ->SCL,0);
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC ->SDA,1);	/* CPU释放SDA总线 */
}
void I2C_NAck(I2C_Def *IIC)
{
    I2C_BusMode(IIC ->SDA,OUT);
    I2C_Bus(IIC ->SDA,1);	/* CPU驱动SDA = 1 */
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC ->SCL,1);	/* CPU产生1个时钟 */
    I2C_Delay(WAIT_TIME);
    I2C_Bus(IIC ->SCL,0);
    I2C_Delay(WAIT_TIME);
}

uint8_t I2C_WriteByte(I2C_Def *IIC,uint8_t uiByte)
{
    uint8_t i;

    /* 先发送字节的高位bit7 */
    I2C_BusMode(IIC ->SDA,OUT);
    for (i = 0; i < 8; i++)
    {
        if (uiByte & 0x80)
        {
            I2C_Bus(IIC ->SDA,1);
        }
        else
        {
            I2C_Bus(IIC ->SDA,0);
        }
        I2C_Delay(WAIT_TIME);
        I2C_Bus(IIC ->SCL,1);
        I2C_Delay(WAIT_TIME);
        I2C_Bus(IIC ->SCL,0);
        uiByte <<= 1;
        I2C_Delay(WAIT_TIME);
    }
    return I2C_WaitAck(IIC);
}
uint8_t I2C_ReadByte(I2C_Def *IIC,uint8_t uiAck)
{
    uint8_t i;
    uint8_t value;

    /* 读到第1个bit为数据的bit7 */
    value = 0;
    I2C_BusMode(IIC ->SDA,IN);
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        I2C_Bus(IIC ->SCL,1);
        I2C_Delay(WAIT_TIME);
        if(I2C_BusRead(IIC ->SDA))
        {
            value++;
        }
        I2C_Bus(IIC ->SCL,0);
        I2C_Delay(WAIT_TIME);
    }
    if(uiAck)I2C_Ack(IIC);
    else I2C_NAck(IIC);
    return value;
}
uint8_t I2C_Check_Device(I2C_Def *IIC,uint8_t uiAddr)
{
    uint8_t ucAck=0;
    if (I2C_BusRead(IIC ->SDA) && I2C_BusRead(IIC ->SCL))
    {
        I2C_Start(IIC);		/* 发送启动信号 */

        /* 发送设备地址+读写控制bit（0 = w， 1 = r) bit7 先传 */
        ucAck = I2C_WriteByte(IIC,uiAddr);
        I2C_Stop(IIC);			/* 发送停止信号 */

        return ucAck;
    }
    return 1;	/* I2C总线异常 */
}