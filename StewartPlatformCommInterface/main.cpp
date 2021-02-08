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
//	moveIsSafe = platform.SetPosition(0, 0, 1, 0, 0, 0);
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
//	std::cout << "X Steps: " << std::to_string(platform.GetXsteps()) << std::endl;
//	std::cout << "Y Steps: " << std::to_string(platform.GetYsteps()) << std::endl;
//	std::cout << "Z Steps: " << std::to_string(platform.GetZsteps()) << std::endl;
//	std::cout << "U Steps: " << std::to_string(platform.GetUsteps()) << std::endl;
//	std::cout << "V Steps: " << std::to_string(platform.GetVsteps()) << std::endl;
//	std::cout << "W Steps: " << std::to_string(platform.GetWsteps()) << std::endl;
//}
