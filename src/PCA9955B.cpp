#include "PCA9955B.h"

PCA9955B::PCA9955B(uint8_t addr)
{
	this->addr = addr;
	this->wire = &Wire;
};

void PCA9955B::begin()
{
	this->wire->begin();
};

void PCA9955B::setIRef(uint8_t gain)
{
	this->setRegister(PCA9955B_IREFALL, gain);
};

void PCA9955B::setIRef(uint8_t led, uint8_t gain)
{
	this->setRegister(PCA9955B_IREF0 + led, gain);
};

void PCA9955B::setPwm(uint8_t brightness)
{
	this->setRegister(PCA9955B_PWMALL, brightness);
};

void PCA9955B::setPwm(uint8_t led, uint8_t brightness)
{
	this->setRegister(PCA9955B_PWM0 + led, brightness);
};

bool PCA9955B::getErrors()
{
	uint8_t mode2 = this->readRegister(PCA9955B_MODE2);
	return (mode2 & PCA9955B_ERROR);
}

uint8_t PCA9955B::getErrors(uint8_t group)
{
	if (group > 3)
		return -1;

	return this->readRegister(PCA9955B_EFLAG0 + group);
};

void PCA9955B::clearError()
{
	this->setRegister(PCA9955B_MODE2, PCA9955B_CLRERROR);
};

void PCA9955B::sleep()
{
	uint8_t mode1 = this->readRegister(PCA9955B_MODE1);
	this->setRegister(PCA9955B_MODE1, mode1 | PCA9955B_SLEEP);
};

void PCA9955B::wake()
{
	uint8_t mode1 = this->readRegister(PCA9955B_MODE1);
	this->setRegister(PCA9955B_MODE1, mode1 ^ PCA9955B_SLEEP);
};

void PCA9955B::setRegister(uint8_t reg, uint8_t data)
{
	this->wire->beginTransmission(this->addr);
	this->wire->write(reg);
	this->wire->write(data);
	this->wire->endTransmission();
};

uint8_t PCA9955B::readRegister(uint8_t reg)
{
	this->wire->beginTransmission(this->addr);
	this->wire->write(reg);
	this->wire->endTransmission();

	this->wire->requestFrom(this->addr, reg);
	return this->wire->read();
};