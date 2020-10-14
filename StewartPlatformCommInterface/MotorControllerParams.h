#pragma once
#include <inttypes.h>

struct MotorParams {
	const static float cylinderStrokeMM;
	const static float cylinderLeadMM;
	const static uint32_t cylinderPulsePerRev = 7500;
	const static float cylinderGearRatio;
};

const float MotorParams::cylinderStrokeMM = 475.0f;
const float MotorParams::cylinderLeadMM = 5.0f;
const float MotorParams::cylinderGearRatio = 1.0f;

struct CxRegister {
	const static int32_t resetRegister = 0x0;
};

struct FunctionCodes {
	const static int32_t dnRegisterReport = 0x1001;
	const static int32_t dnRegisterRead = 0x1101;
	const static int32_t dnRegisterWrite = 0x1201;
	const static int32_t absoluteTime = 0x1301;
	const static int32_t relativeTime = 0x1401;
};

struct UDPRegisterChannels {
	const static int32_t readDnRegisterChannel = 0;
	const static int32_t readFnRegisterChannel = 1;

	const static int32_t writeFnRegisterNoSaveChannel = 0;
	const static int32_t writeFnRegisterSaveChannel = 1;
	const static int32_t writeCxRegisterChannel = 2;

	const static int32_t threeAxisChannel = 0;
	const static int32_t sixAxisChannel = 1;
};

struct UDPWordOffsets {
	const static int32_t confirmCodeOffset = 0;
	const static int32_t passOffset = 1;
	const static int32_t functionCodeOffset = 2;
	const static int32_t objectChannelOffset = 3;
	const static int32_t recieverCodeOffset = 4;
	const static int32_t transmitterCodeOffset = 5;

	const static int32_t registerStartAddressOffset = 6;
	const static int32_t registerVisitNumberOffset = 7;
	const static int32_t registerVisitDataBaseOffset = 8;
	const static int32_t registerVisitErrorCodeOffset = 9;

	const static int32_t lineHighOffset = 6;
	const static int32_t lineLowOffset = 7;
	const static int32_t timeHighOffset = 8;
	const static int32_t timeLowOffset = 9;

	const static int32_t xPosHighOffset = 10;
	const static int32_t xPosLowOffset = 11;
	const static int32_t yPosHighOffset = 12;
	const static int32_t yPosLowOffset = 13;
	const static int32_t zPosHighOffset = 14;
	const static int32_t zPosLowOffset = 15;

	const static int32_t uPosHighOffset = 16;
	const static int32_t uPosLowOffset = 17;
	const static int32_t vPosHighOffset = 18;
	const static int32_t vPosLowOffset = 19;
	const static int32_t wPosHighOffset = 20;
	const static int32_t wPosLowOffset = 21;

	const static int32_t digitalOutOffset = 22;
	const static int32_t dac1Offset = 23;
	const static int32_t dac2Offset = 24;
	const static int32_t extDigitalOutOffset = 25;
};

struct UDPData {
	const short hostTxPort = 8410;
	const short hostRxPort = 8410;
	const short platformTxPort = 7408;
	const short platformRxPort = 7408;

	const unsigned short confirmCode = 0x55AA;
	const unsigned short passCode = 0x0000;
	const unsigned short functionCode = 0x1401;
	const unsigned short channelCode = 0x0001;

	const unsigned short recieverCode = 0xFFFF;
	const unsigned short transmitterCode = 0xFFFF;

	const int32_t line = 0x00000000;
	const int32_t time = 0x00000000;
	const int32_t xPos = 0x00000000;
	const int32_t yPos = 0x00000000;
	const int32_t zPos = 0x00000000;
	const int32_t uPos = 0x00000000;
	const int32_t vPos = 0x00000000;
	const int32_t wPos = 0x00000000;

	const unsigned short digitalOutCode = 0x0000;
	const unsigned short dac1Code = 0x0000;
	const unsigned short dac2Code = 0x0000;
	const unsigned short extDigitalOutCode = 0x0000;
};
