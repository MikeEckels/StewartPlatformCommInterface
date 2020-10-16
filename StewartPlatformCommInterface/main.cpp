#include "Platform.h"
#include <iostream>
#include <string>

Platform platform;

int main() {
	platform.Initialize();
	platform.Reset();

	platform.SetFunctionCode(FunctionCodes::relativeTime);
	platform.SetChannelCode(UDPRegisterChannels::sixAxisChannel);
	platform.SetMoveTimeMs(100);
	platform.SetPositon(475, 475, 475, 475, 475, 475);

	platform.Move();

	while(true) {};
}