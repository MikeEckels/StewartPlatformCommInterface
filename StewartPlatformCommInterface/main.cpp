#include "Platform.h"
#include "Network.h"

Platform platform;

int main() {
	platform.SetRegister(UDPData::channelCode, (unsigned short)CxRegister::resetRegister, 0);
}