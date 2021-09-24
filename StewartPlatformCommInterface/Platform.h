#pragma once
#include "Vector.h"
#include "Rotation.h"
#include "UDPClient.h"
#include "CSVReader.h"
#include "Actuators.h"
#include "ActuatorLengths.h"
#include "MotorControllerParams.h"

class Platform {
private:

	ActuatorLengths aL;
	Vector3D B1, B2, B3, B4, B5, B6;
	Vector3D P1, P2, P3, P4, P5, P6;
	Vector3D L1, L2, L3, L4, L5, L6;

	UDPClient client;

	const static int udpTxBufferSize = 25;
	const static int udpSendBufferSize = 50;

	short udpTxBuffer[udpTxBufferSize];
	unsigned char udpSendBuffer[udpSendBufferSize];

	int MergeBytesToWord(unsigned char Byte1, unsigned char Byte2);

	unsigned short FlipUShortBytes(unsigned short data);
	unsigned short U32HighBytesToWord(uint32_t data);
	unsigned short U32LowBytesToWord(uint32_t data);

	void AddMovement();
	void ShortArryToByteArry(short* shortArry, unsigned char* byteArry, int shortArrySize);

	uint32_t GetPulseCount(float gearRatio, float desiredDistance, float maxDistance, uint32_t pulsePerRev);

	ActuatorLengths CalculateIK(Vector3D XYZ);
	ActuatorLengths CalculateIK(Vector3D XYZ, EulerAngles YPR);
	
public:
	Platform();

	void Reset();
	void Stop();
	void Move();

	void SetFunctionCode(int32_t code);
	void SetChannelCode(int32_t code);
	void SetMoveTimeMs(int32_t milliseconds);
	bool SetPosition(int32_t x, int32_t y, int32_t z, int32_t u, int32_t v, int32_t w);
	void SetRegister(unsigned short channelCode, unsigned short registerAddress, short value);

	bool FollowPath(std::string filename, std::string delimeter, int numColumns);

	ActuatorLengths GetPositionSteps();
};
