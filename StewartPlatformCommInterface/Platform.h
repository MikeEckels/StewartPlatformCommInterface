#pragma once
#include "MotorControllerParams.h"

class Platform {
private:

	int MergeBytesToWord(char Byte1, char Byte2);

	unsigned short FlipUShortBytes(unsigned short data);
	unsigned short U32HightBytesToWord(uint32_t data);
	unsigned short U32LowBytesToWord(uint32_t data);

	uint32_t GetPulseCount(float gearRatio, float desiredDistance, float maxDistance, uint32_t pulsePerRev);
	
public:
	void Initialize();
	void Reset();

	void SetFunctionCode(int32_t code);
	void SetChannelCode(int32_t code);
	void SetMoveTimeMs(int32_t milliseconds);
	void SetPositon(int32_t x, int32_t y, int32_t z, int32_t u, int32_t v, int32_t w);
	void SetRegister(unsigned short channelCode, unsigned short registerAddress, short value);

	void Move();
};