#include "Platform.h"

extern "C" __declspec(dllexport) Platform* CreatePlatform() {
	return new Platform();
}

extern "C" __declspec(dllexport) void DeletePlatform(Platform* platform) {
	delete platform;
}

extern "C" __declspec(dllexport) void ResetW(Platform * platform) {
	platform->Reset();
}

extern "C" __declspec(dllexport) void StopW(Platform * platform) {
	platform->Stop();
}

extern "C" __declspec(dllexport) void SetFunctionCodeW(Platform * platform, int code) {
	platform->SetFunctionCode(code);
}

extern "C" __declspec(dllexport) void SetChannelCodeW(Platform * platform, int code) {
	platform->SetChannelCode(code);
}

extern "C" __declspec(dllexport) void SetMoveTimeMsW(Platform * platform, int milliseconds) {
	platform->SetMoveTimeMs(milliseconds);
}

extern "C" __declspec(dllexport) bool SetPositionW(Platform * platform, int x, int y, int z, int u, int v, int w) {
	return platform->SetPosition(x, y, z, u, v, w);
}

extern "C" __declspec(dllexport) void SetRegisterW(Platform * platform, unsigned short channelCode, unsigned short registerAddress, unsigned short value) {
	platform->SetRegister(channelCode, registerAddress, value);
}

//extern "C" __declspec(dllexport) ActuatorLengths CalculateIKW(Platform * platform, Vector3D XYZ) {
//	return platform->CalculateIK(XYZ);
//}
//
//extern "C" __declspec(dllexport) ActuatorLengths CalculateIKW(Platform * platform, Vector3D XYZ, EulerAngles YPR) {
//	return platform->CalculateIK(XYZ, YPR);
//}

extern "C" __declspec(dllexport) void MoveW(Platform * platform) {
	platform->Move();
}
