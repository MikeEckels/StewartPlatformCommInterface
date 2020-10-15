#pragma once
#include "MotorControllerParams.h"

class Platform {
private:
	unsigned short udpTxBuffer[25];
	unsigned char udpSendBuffer[50];

	int MergeBytesToWord(unsigned char Byte1, unsigned char Byte2);

	unsigned short FlipUShortBytes(unsigned short data);
	unsigned short U32HighBytesToWord(uint32_t data);
	unsigned short U32LowBytesToWord(uint32_t data);

	void ShortArryToByteArry(unsigned short* shortArry, unsigned char* byteArry, int shortArrySize);

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