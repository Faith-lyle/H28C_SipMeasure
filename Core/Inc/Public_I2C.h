//
// Created by luxshare-ict on 2023/3/7.
//

#ifndef H28C_SIPMEASURE_PUBLIC_I2C_H
#define H28C_SIPMEASURE_PUBLIC_I2C_H
#include "main.h"

typedef struct _I2C_BusDef
{
    uint32_t RCC_peripheral;
    GPIO_TypeDef *BusPort;
    uint16_t GPIO_Pin;
}I2C_BusDef;

typedef struct _I2C_Def
{
    I2C_BusDef SDA;
    I2C_BusDef SCL;
}I2C_Def;


#define WAIT_TIME 50
#ifndef IN
#define IN       GPIO_MODE_INPUT
#endif
#ifndef OUT
#define OUT      GPIO_MODE_OUTPUT_PP
#endif
#ifndef I2C_WR
#define I2C_WR         0
#endif
#ifndef I2C_RD
#define I2C_RD         1
#endif

#ifndef FAILED
#define FAILED         1
#endif

#ifndef PASSED
#define PASSED         0
#endif

void I2C_BusInit(I2C_Def *IIC);
void I2C_Bus(I2C_BusDef IIC_Bus,uint8_t value);
void I2C_Stop(I2C_Def *IIC);
void I2C_BusMode(I2C_BusDef IIC_Bus,int32_t GPIO_Mode);
uint8_t I2C_BusRead(I2C_BusDef IIC_Bus);
void I2C_Stop(I2C_Def *IIC);
void I2C_Start(I2C_Def *IIC);
uint8_t I2C_WaitAck(I2C_Def *IIC);
void I2C_Ack(I2C_Def *IIC);
void I2C_NAck(I2C_Def *IIC);
uint8_t I2C_WriteByte(I2C_Def *IIC,uint8_t uiByte);
uint8_t I2C_ReadByte(I2C_Def *IIC,uint8_t uiAck);
uint8_t I2C_Check_Device(I2C_Def *IIC,uint8_t uiAddr);
#endif //H28C_SIPMEASURE_PUBLIC_I2C_H
