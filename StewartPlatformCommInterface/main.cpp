#include "Platform.h"
#include <iostream>
#include <string>

Platform platform;
bool moveIsSafe = 0;

int main() {
	platform.Initialize();
	platform.Reset();

	platform.SetFunctionCode(FunctionCodes::relativeTime);
	platform.SetChannelCode(UDPRegisterChannels::sixAxisChannel);
	platform.SetMoveTimeMs(100);

	moveIsSafe = platform.SetPositon(0, 0, 20, 0, 0, 0);
	
	std::cout << "X Steps: " << std::to_string(UDPData::xPos) << std::endl;
	std::cout << "Y Steps: " << std::to_string(UDPData::yPos) << std::endl;
	std::cout << "Z Steps: " << std::to_string(UDPData::zPos) << std::endl;
	std::cout << "U Steps: " << std::to_string(UDPData::uPos) << std::endl;
	std::cout << "V Steps: " << std::to_string(UDPData::vPos) << std::endl;
	std::cout << "W Steps: " << std::to_string(UDPData::wPos) << std::endl;

	if (moveIsSafe) {
		platform.Move();
	}
	else {
		std::cout << "[!] Move Command Invalid";
	}

	while(true) {};
}