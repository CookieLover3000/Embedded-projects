#ifndef I2C_H
#define I2C_H

#define I2C_SDA        PORTD1
#define I2C_SDA_PORT   PORTD
#define I2C_SCL        PORTD0

#define LSM303DAdresWrite	0b00111010
#define LSM303DAdresRead	0b00111011
#define L3GD20H_ADDR  		0b1101011

#define WHO_AM_I     	0x0F
#define CTRL1			0x20
#define CTRL5           0x24
#define CTRL6			0x25
#define CTRL7			0x26
#define OUT_X_L_M       0x08
#define OUT_X_H_M       0x09
#define OUT_Y_L_M       0x0A
#define OUT_Y_H_M       0x0B
#define OUT_Z_L_M       0x0C
#define OUT_Z_H_M       0x0D

#include "aansluitingen.h"

static volatile int xOff;
static volatile int yOff;
static volatile int zOff;

void initI2C(void) {
	/* set pullups for SDA, SCL lines */
	I2C_SDA_PORT |= ((1 << I2C_SDA) | (1 << I2C_SCL));			// Op output
	TWBR = 72;													// set I2C bit rate (p.242): 16MHz / (16+2*TWBR*1) ~= 100kHz
	TWCR |= (1 << TWEN);										// Enable
}

void i2cWaitForComplete(void) {
	while (!(TWCR & (1<<TWINT)));
}

void i2cStart(void) {
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	i2cWaitForComplete();
}

void i2cStop(void) {
	TWCR = (1<<TWSTO)|(1<<TWINT)|(1<<TWEN);						// Enable TWI, generate stop condition and clear interrupt flag
	while(TWCR & (1<<TWSTO));
}

uint8_t i2cReadAck(void) {
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	i2cWaitForComplete();
	return (TWDR);
}

uint8_t i2cReadNoAck(void) {
	TWCR = (1<<TWEN)|(1<<TWINT);
	i2cWaitForComplete();
	return (TWDR);
}

void i2cSend(uint8_t data) {
	TWDR = data;
	TWCR = (1<<TWEN)|(1<<TWINT);
	i2cWaitForComplete();
}

void setRegister(uint8_t reg, uint8_t value) {
	i2cStart();
	i2cSend(LSM303DAdresWrite);									// I2C adres master schrijf
	i2cSend(reg);
	i2cSend(value);
	i2cStop();
}

static uint8_t readXL() {
	i2cStart();
	i2cSend(LSM303DAdresWrite);
	i2cSend(OUT_X_L_M | (1 << 7));
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t xl = i2cReadNoAck();
	i2cStop();
	return xl;
}

static uint8_t readXH() {
	i2cStart();
	i2cSend(LSM303DAdresWrite);
	i2cSend(OUT_X_H_M | (1 << 7));
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t xh = i2cReadNoAck();
	i2cStop();
	return xh;
}

static uint8_t readYL() {
	i2cStart();
	i2cSend(LSM303DAdresWrite);
	i2cSend(OUT_Y_L_M | (1 << 7));
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t yl = i2cReadNoAck();
	i2cStop();
	return yl;
}

static uint8_t readYH() {
	i2cStart();
	i2cSend(LSM303DAdresWrite);
	i2cSend(OUT_Y_H_M | (1 << 7));
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t yh = i2cReadNoAck();
	i2cStop();
	return yh;
}

static uint8_t readZL() {
i2cStart();
	i2cSend(LSM303DAdresWrite);
	i2cSend(OUT_Z_L_M | (1 << 7));
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t zl = i2cReadNoAck();
	i2cStop();
	return zl;
}

static uint8_t readZH() {
	i2cStart();
	i2cSend(LSM303DAdresWrite);
	i2cSend(OUT_Z_H_M | (1 << 7));
	i2cStart();
	i2cSend(LSM303DAdresRead);
	uint8_t zh = i2cReadNoAck();
	i2cStop();
	return zh;
}

void calibratie() {
	int32_t xTotaal = 0;
	int32_t yTotaal = 0;
	int32_t zTotaal = 0;

	for(int i = 0; i < 1024; i++){
		// readGyroVars
		setRegister(CTRL1, 0x7F); // DR = 01 (189.4 Hz ODR); BW = 11 (70 Hz bandwidth); PD = 1 (normal mode); Zen = Yen = Xen = 1 (all axes enabled)
		uint8_t XL = readXL();
		setRegister(CTRL1, 0x7F);
		uint8_t XH = readXH();
		uint16_t X = (XH << 8 | XL);

		setRegister(CTRL1, 0x7F);
		uint8_t YL = readYL();
		setRegister(CTRL1, 0x7F);
		uint8_t YH = readYH();
		uint16_t Y = (YH << 8 | YL);

		setRegister(CTRL1, 0x7F);
		uint8_t ZL = readZL();
		setRegister(CTRL1, 0x7F);
		uint8_t ZH = readZH();
		uint16_t Z = (ZH << 8 | ZL);

		_delay_ms(2);
		xTotaal = xTotaal + X;
		yTotaal = yTotaal + Y;
		zTotaal = zTotaal + Z;
	}
	xOff = xTotaal / 1024;
	yOff = yTotaal / 1024;
	zOff = zTotaal / 1024;
}

#endif
