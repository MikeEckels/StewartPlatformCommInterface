#include "Platform.h"
#include "CSVReader.h"
#include <iostream>
#include <string>

Platform platform;

bool moveIsSafe = 0;
void checkMove(bool state);//Prototype

int main() {
	/*platform.Reset();
	Sleep(15000);*/
	
	platform.SetFunctionCode(FunctionCodes::relativeTime);
	platform.SetChannelCode(UDPRegisterChannels::sixAxisChannel);
	//platform.SetMoveTimeMs(10);
	//platform.SetPosition(0.0, 0.0, 230.0, 0.0, 0.0, 0.0);
	//platform.Move();
	Sleep(1000);

	platform.FollowPath("C:/Users/Mike/Desktop/TestFile.csv", ",");
	/*platform.FollowPath("C:/Users/Mike/Desktop/X_Trial_1.csv", ",");*/

	//for (double i = 0; i < 360 * 4; i += 10.0) {
	//	double x = sin(i * 3.14159 / 180.0) * 20.0;
	//	double y = cos(i * 3.14159 / 180.0) * 20.0;
	//	double yaw = 0;// cos(i * 3.14159 / 180.0 * 2) * 20.0;
	//moveIsSafe = platform.SetPosition(0, 0, 230, yaw, x, y);
	//checkMove(moveIsSafe);
	//Sleep(100);
	}
}

void checkMove(bool state) {
	if (state) {
		//Use this to print position values
		std::cout << "Moving to: " << platform.GetPosition().ToString() << std::endl;

		//Use this to print position steps
		//std::cout << "Moving to: " << platform.GetPositionSteps().ToString() << std::endl;

		//Or print out individual axis
		/*std::cout << "X Steps: " << std::to_string(platform.GetPositionSteps().X) << std::endl;
		std::cout << "Y Steps: " << std::to_string(platform.GetPositionSteps().Y) << std::endl;
		std::cout << "Z Steps: " << std::to_string(platform.GetPositionSteps().Z) << std::endl;
		std::cout << "U Steps: " << std::to_string(platform.GetPositionSteps().U) << std::endl;
		std::cout << "V Steps: " << std::to_string(platform.GetPositionSteps().V) << std::endl;
		std::cout << "W Steps: " << std::to_string(platform.GetPositionSteps().W) << std::endl;*/
		platform.Move();
	}
	else {
		std::cout << "[!] Move Command Invalid" << std::endl;
	}
}
