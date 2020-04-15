#define _IIC1_DRV_C_

#include "hal_i2c.h"

/*----------------------------------------*/
#define SCL_H()           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)
#define SCL_L()           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)
#define SDA_H()           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#define SDA_L()           HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)
#define SCL_read          HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)
#define SDA_read          HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)

uint16_t delay_value = 10;

void I2C_Delay(void)
{
    uint32_t i = delay_value;

    while(i)
    {
        __NOP();
        i--;
    }
}
void HAL_I2C_Init(void)
{
    SCL_H();
    SDA_H();
}

void I2C_Start(void)
{
    SDA_H();
    SCL_H();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
}

void I2C_Stop(void)
{
    SCL_L();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
}

void I2C_Ack(void)
{
    SCL_L();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

void I2C_nAck(void)
{
    SCL_L();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

uint8_t I2C_WaitAck(void)
{
    SCL_L();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();

    if(SDA_read != RESET)
    {
        SCL_L();
        I2C_Delay();
        return 1;
    }

    SCL_L();
    I2C_Delay();
	return 0;
}

void I2C_TxData(uint8_t i2c_data)
{
    uint8_t i = 8;

    while(i--)
    {
        SCL_L();
        I2C_Delay();

      if(i2c_data&0x80)
        SDA_H();
      else
        SDA_L();

        i2c_data<<=1;
        I2C_Delay();
        SCL_H();
        I2C_Delay();
    }

    SCL_L();
    I2C_Delay();
}

uint8_t I2C_RxData(void)
{
    uint8_t i = 8;
    uint8_t ReceiveByte = 0;

    SDA_H();

    while(i--)
    {
        ReceiveByte<<=1;
        SCL_L();
        I2C_Delay();
        SCL_H();
        I2C_Delay();

        if(SDA_read != RESET)
        {
            ReceiveByte|=0x01;
        }
    }

    SCL_L();
    I2C_Delay();

    return ReceiveByte;
}

