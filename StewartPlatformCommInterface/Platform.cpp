#include "Platform.h"
#include "Network.h"

WSASession Session;
UDPSocket Socket;
//Initializing Motor Parameters
const float MotorParams::cylinderStrokeMM = 475.0f;
const float MotorParams::cylinderLeadMM = 5.0f;
const float MotorParams::cylinderGearRatio = 1.0f;

//Initializing Platform UDP ByteStream
short UDPData::hostTxPort = 8410;
short UDPData::hostRxPort = 8410;
short UDPData::platformTxPort = 7408;
short UDPData::platformRxPort = 7408;

unsigned short UDPData::confirmCode = 0x55AA;
unsigned short UDPData::passCode = 0x0000;
unsigned short UDPData::functionCode = 0x1401;
unsigned short UDPData::channelCode = 0x0001;

unsigned short UDPData::recieverCode = 0xFFFF;
unsigned short UDPData::transmitterCode = 0xFFFF;

int32_t UDPData::line = 0x00000000;
int32_t UDPData::time = 0x00000000;
int32_t UDPData::xPos = 0x00000000;
int32_t UDPData::yPos = 0x00000000;
int32_t UDPData::zPos = 0x00000000;
int32_t UDPData::uPos = 0x00000000;
int32_t UDPData::vPos = 0x00000000;
int32_t UDPData::wPos = 0x00000000;

unsigned short UDPData::digitalOutCode = 0x0000;
unsigned short UDPData::dac1Code = 0x0000;
unsigned short UDPData::dac2Code = 0x0000;
unsigned short UDPData::extDigitalOutCode = 0x0000;

void Platform::Initialize() {
	
}

void Platform::Reset() {
	SetFunctionCode(FunctionCodes::dnRegisterWrite);
	SetChannelCode(UDPRegisterChannels::writeCxRegisterChannel);
	SetRegister(UDPData::channelCode, (unsigned short)CxRegister::resetRegister, 0);
}

void Platform::Move() {
	this->udpTxBuffer[UDPWordOffsets::confirmCodeOffset] = (short)FlipUShortBytes(UDPData::confirmCode);
	this->udpTxBuffer[UDPWordOffsets::passOffset] = (short)FlipUShortBytes(UDPData::passCode);
	this->udpTxBuffer[UDPWordOffsets::functionCodeOffset] = (short)FlipUShortBytes(UDPData::functionCode);
	this->udpTxBuffer[UDPWordOffsets::objectChannelOffset] = (short)FlipUShortBytes(UDPData::channelCode);
	this->udpTxBuffer[UDPWordOffsets::transmitterCodeOffset] = (short)FlipUShortBytes(UDPData::transmitterCode);
	this->udpTxBuffer[UDPWordOffsets::recieverCodeOffset] = (short)FlipUShortBytes(UDPData::recieverCode);
	this->udpTxBuffer[UDPWordOffsets::lineHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::line);
	this->udpTxBuffer[UDPWordOffsets::lineLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::line);
	this->udpTxBuffer[UDPWordOffsets::timeHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::time);
	this->udpTxBuffer[UDPWordOffsets::timeLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::time);
	this->udpTxBuffer[UDPWordOffsets::xPosHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::xPos);
	this->udpTxBuffer[UDPWordOffsets::xPosLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::xPos);
	this->udpTxBuffer[UDPWordOffsets::yPosHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::yPos);
	this->udpTxBuffer[UDPWordOffsets::yPosLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::yPos);
	this->udpTxBuffer[UDPWordOffsets::zPosHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::zPos);
	this->udpTxBuffer[UDPWordOffsets::zPosLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::zPos);
	this->udpTxBuffer[UDPWordOffsets::uPosHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::uPos);
	this->udpTxBuffer[UDPWordOffsets::uPosLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::uPos);
	this->udpTxBuffer[UDPWordOffsets::vPosHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::vPos);
	this->udpTxBuffer[UDPWordOffsets::vPosLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::vPos);
	this->udpTxBuffer[UDPWordOffsets::wPosHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::wPos);
	this->udpTxBuffer[UDPWordOffsets::wPosLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::wPos);
	this->udpTxBuffer[UDPWordOffsets::digitalOutOffset] = (short)FlipUShortBytes(UDPData::digitalOutCode);
	this->udpTxBuffer[UDPWordOffsets::dac1Offset] = (short)FlipUShortBytes(UDPData::dac1Code);
	this->udpTxBuffer[UDPWordOffsets::dac2Offset] = (short)FlipUShortBytes(UDPData::dac2Code);
	ShortArryToByteArry(this->udpTxBuffer, this->udpSendBuffer, (sizeof(this->udpTxBuffer) / sizeof(this->udpTxBuffer[0])));
	//Socket.SendTo()
}

void Platform::SetFunctionCode(int32_t code) {
	UDPData::functionCode = (unsigned short)code;
}

void Platform::SetChannelCode(int32_t code) {
	UDPData::channelCode = (unsigned short)code;
}

void Platform::SetMoveTimeMs(int32_t ms) {
	UDPData::time = ms;
}

void Platform::SetPositon(int32_t x, int32_t y, int32_t z, int32_t u, int32_t v, int32_t w) {
	UDPData::xPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, x, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::yPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, y, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::zPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, z, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::uPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, u, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::vPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, v, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::wPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, w, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
}

void Platform::SetRegister(unsigned short channelCode, unsigned short registerAddress, short value) {
	this->udpTxBuffer[UDPWordOffsets::confirmCodeOffset] = (short)FlipUShortBytes(UDPData::confirmCode);
	this->udpTxBuffer[UDPWordOffsets::passOffset] = (short)FlipUShortBytes(UDPData::passCode);
	this->udpTxBuffer[UDPWordOffsets::functionCodeOffset] = (short)FlipUShortBytes(UDPData::functionCode);
	this->udpTxBuffer[UDPWordOffsets::objectChannelOffset] = (short)FlipUShortBytes(channelCode);
	this->udpTxBuffer[UDPWordOffsets::transmitterCodeOffset] = (short)FlipUShortBytes(UDPData::transmitterCode);
	this->udpTxBuffer[UDPWordOffsets::recieverCodeOffset] = (short)FlipUShortBytes(UDPData::recieverCode);

	this->udpTxBuffer[UDPWordOffsets::registerStartAddressOffset] = (short)FlipUShortBytes(registerAddress);
	this->udpTxBuffer[UDPWordOffsets::registerVisitNumberOffset] = (short)FlipUShortBytes(0x0001);
	this->udpTxBuffer[UDPWordOffsets::registerVisitDataBaseOffset] = (short)FlipUShortBytes((unsigned short)value);
	ShortArryToByteArry(this->udpTxBuffer, this->udpSendBuffer, (sizeof(this->udpTxBuffer) / sizeof(this->udpTxBuffer[0])));
	//SEND UDP
}

uint32_t Platform::GetPulseCount(float gearRatio, float desiredDistance, float maxDistance, uint32_t pulsePerRev) {
	uint32_t numPulses;

	numPulses = (uint32_t)((gearRatio * desiredDistance * pulsePerRev) / (maxDistance));
	return numPulses;
}

int Platform::MergeBytesToWord(unsigned char Byte1, unsigned char Byte2) {
	unsigned int word;

	word = ((Byte1 << 8) | Byte2);
	return word;
}

unsigned short Platform::FlipUShortBytes(unsigned short data) {
	unsigned short highByte;
	unsigned short lowByte;
	unsigned short flippedBytes;

	highByte = (unsigned short)(data >> 8);
	lowByte = (unsigned short)((data & 0x00FF) << 8);
	flippedBytes = (unsigned short)(highByte | lowByte);
	return flippedBytes;
}

unsigned short Platform::U32HighBytesToWord(uint32_t data) {
	unsigned short highByte;

	highByte = (unsigned short)(data >> 16);
	highByte = FlipUShortBytes(highByte);
	return highByte;
}

unsigned short Platform::U32LowBytesToWord(uint32_t data) {
	unsigned short lowByte;

	lowByte = (unsigned short)(data & 0x0000FFFF);
	lowByte = FlipUShortBytes(lowByte);
	return lowByte;
}

void Platform::ShortArryToByteArry(short* shortArry, unsigned char* byteArry, int shortArrySize) {
	for (int i = 0; i <= shortArrySize; i++) {
		unsigned short temp = this->udpTxBuffer[i];
		unsigned char msb, lsb;

		msb = temp & 0xFF;
		lsb = temp >> 8;

		this->udpSendBuffer[i * 2] = msb;
		this->udpSendBuffer[(i * 2) + 1] = lsb;
	}
}