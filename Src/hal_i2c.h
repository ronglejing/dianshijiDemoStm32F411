#ifndef _I2C_DRV_H_
#define _I2C_DRV_H_

#ifdef _I2C_DRV_C_
#define _I2CDRVEXT_
#else
#define _I2CDRVEXT_ extern
#endif

#include "stm32f4xx_hal.h"

/************************************************************
				Exern Function Setction
*************************************************************/
_I2CDRVEXT_ void    HAL_I2C_Init(void);
_I2CDRVEXT_ void    I2C_Start(void);
_I2CDRVEXT_ void    I2C_Stop(void);
_I2CDRVEXT_ uint8_t I2C_WaitAck(void);
_I2CDRVEXT_ void    I2C_Ack(void);
_I2CDRVEXT_ void    I2C_nAck(void);
_I2CDRVEXT_ void    I2C_TxData(uint8_t i2c_data);
_I2CDRVEXT_ uint8_t I2C_RxData(void);
//_I2CDRVEXT_ void I2C_WriteReg(uint8_t __IO Data[], uint8_t I2C_Addr, uint8_t I2C_Reg, uint8_t Num);
//_I2CDRVEXT_ void I2C_ReadReg(uint8_t __IO Data[], uint8_t I2C_Addr);


#endif


