#pragma once
#include <inttypes.h>

struct PlatformParams {
	const static double basePlateRadius;
	const static double baseMountingAngle;
	const static double platformPlateRadius;;
	const static double platformMountingAngle;
	const static double baseHeight;
	const static double maximumLength;
	static double baseActuatorLength;
};

struct MotorParams {
	const static float cylinderStrokeMM;
	const static float cylinderLeadMM;
	const static uint32_t cylinderPulsePerRev;
	const static float cylinderGearRatio;
};

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

	const static int32_t instructionHighOffset = 6;
	const static int32_t instructionLowOffset = 7;
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
	static short hostTxPort;
	static short hostRxPort;
	static short platformTxPort;
	static short platformRxPort;

	static unsigned short confirmCode;
	static unsigned short passCode;
	static unsigned short functionCode;
	static unsigned short channelCode;

	static unsigned short recieverCode;
	static unsigned short transmitterCode;

	static int32_t instruction;
	static int32_t time;
	static int32_t xPos;
	static int32_t yPos;
	static int32_t zPos;
	static int32_t uPos;
	static int32_t vPos;
	static int32_t wPos;

	static unsigned short digitalOutCode;
	static unsigned short dac1Code;
	static unsigned short dac2Code;
	static unsigned short extDigitalOutCode;
};
