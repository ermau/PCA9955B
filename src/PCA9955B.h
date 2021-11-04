#ifndef PCA9955B_DEF
#define PCA9955B_DEF

#include <Arduino.h>
#include <Wire.h>

#define PCA9955B_MODE1 0x00
#define PCA9955B_SLEEP 0b00010000

#define PCA9955B_MODE2 0x01
#define PCA9955B_OVERTEMP 0b10000000
#define PCA9955B_ERROR 0b0100000
#define PCA9955B_CLRERROR 0b00010000

#define PCA9955B_PWM0 0x08
#define PCA9955B_IREF0 0x18

#define PCA9955B_PWMALL 0x44
#define PCA9955B_IREFALL 0x45
#define PCA9955B_EFLAG0 0x46

class PCA9955B
{
public:
	PCA9955B(const uint8_t addr);
	PCA9955B(const uint8_t addr, TwoWire &wire);

	void begin();

	void setIRef(const uint8_t gain);
	void setIRef(const uint8_t led, const uint8_t gain);

	void setPwm(const uint8_t brightness);
	void setPwm(const uint8_t led, uint8_t brightness);

	bool getErrors();
	uint8_t getErrors(const uint8_t group);
	void clearError();

	void sleep();
	void wake();

private:
	uint8_t addr;
	TwoWire *wire;

	uint8_t readRegister(uint8_t reg);
	void setRegister(uint8_t reg, uint8_t data);
};

#endif