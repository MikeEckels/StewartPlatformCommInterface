//#include "Platform.h"
//#include <iostream>
//#include <string>
//
//Platform platform;
//
//bool moveIsSafe = 0;
//void checkMove(bool state);//Prototype
//
//int main() {
//	/*platform.Reset();
//	Sleep(15000);*/
//	
//	platform.SetFunctionCode(FunctionCodes::absoluteTime);
//	platform.SetChannelCode(UDPRegisterChannels::sixAxisChannel);
//	platform.SetMoveTimeMs(1);
//
//	moveIsSafe = platform.SetPosition(0, 0, 0, 0, 0, 0);
//	checkMove(moveIsSafe);
//}
//
//void checkMove(bool state) {
//	if (state) {
//		std::cout << "[+] Move Command valid, Moving" << std::endl;
//		platform.Move();
//	}
//	else {
//		std::cout << "[!] Move Command Invalid" << std::endl;
//	}
//
//	std::cout << "X Steps: " << std::to_string(UDPData::xPos) << std::endl;
//	std::cout << "Y Steps: " << std::to_string(UDPData::yPos) << std::endl;
//	std::cout << "Z Steps: " << std::to_string(UDPData::zPos) << std::endl;
//	std::cout << "U Steps: " << std::to_string(UDPData::uPos) << std::endl;
//	std::cout << "V Steps: " << std::to_string(UDPData::vPos) << std::endl;
//	std::cout << "W Steps: " << std::to_string(UDPData::wPos) << std::endl;
//}
