#include "Platform.h"

void Platform::Initialize() {
	float foobar = MotorParams::cylinderGearRatio;
}

void Platform::Reset() {

}

void Platform::Move() {

}

void Platform::SetFunctionCode(int32_t code) {

}

void Platform::SetChannelCode(int32_t code) {

}

void Platform::SetMoveTimeMs(int32_t ms) {

}

void Platform::SetPositon(int32_t x, int32_t y, int32_t z, int32_t u, int32_t v, int32_t w) {

}

void Platform::SetRegister(unsigned short channelCode, unsigned short registerAddress, short value) {

}

uint32_t Platform::GetPulseCount(float gearRatio, float desiredDistance, float maxDistance, uint32_t pulsePerRev) {
	uint32_t numPulses;

	numPulses = (uint32_t)((gearRatio * desiredDistance * pulsePerRev) / (maxDistance));
	return numPulses;
}

int Platform::MergeBytesToWord(char Byte1, char Byte2) {
	int word;

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

unsigned short Platform::U32HightBytesToWord(uint32_t data) {
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