/*
 * I2C_SOFTWARE.h
 *
 *  Created on: Feb 24, 2013
 *      Author: Evan
 */

#ifndef I2C_SOFTWARE_H_
#define I2C_SOFTWARE_H_

#include "LPC17xx.h"

#define I2C_SDA 	P1_19
#define I2C_SCL 	P1_24
#define delay 		delay_ms(5)

#define SCL_HIGH 	(LPC_GPIO1 -> FIOSET = I2C_SCL)
#define SCL_LOW 	(LPC_GPIO1 -> FIOCLR = I2C_SCL)
#define SDA_HIGH 	(LPC_GPIO1 -> FIOSET = I2C_SDA)
#define SDA_LOW 	(LPC_GPIO1 -> FIOCLR = I2C_SDA)
#define SCL_CLK 	delay; SCL_HIGH; delay; SCL_LOW; delay;
#define SDA_OUT 	(LPC_GPIO1 -> FIODIR |= I2C_SDA)
#define SDA_IN 		(LPC_GPIO1 -> FIODIR &= ~I2C_SDA)
#define SCL_OUT 	(LPC_GPIO1 -> FIODIR |= I2C_SCL)
#define SCL_IN 		(LPC_GPIO1 -> FIODIR &= ~I2C_SCL)
#define SCL_ACK 	(((LPC_GPIO1 -> FIOPIN)&I2C_SDA))

#endif /* I2C_SOFTWARE_H_ */
