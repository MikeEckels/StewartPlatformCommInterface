#include "Platform.h"

//Initializing Platform Mechanical Parameters
const double PlatformParams::basePlateRadius = 546.1;//base center point to center of actuator mounting bracket
const double PlatformParams::baseMountingAngle = 10.613;//arc angle between actuator mounting brackets from center of platform
const double PlatformParams::platformPlateRadius = 636.1;//platform center point to center of actuator mounting bracket 546.1
const double PlatformParams::platformMountingAngle = 10.613;//arc angle between actuator mounting brackets from center of platform
const double PlatformParams::baseHeight = 850.9;//platform height from ground when at 0,0,0 -> 850.9
const double PlatformParams::maximumLength = 460.0;//Maximum actuator stroke actual is 475. 460 is for safety
double PlatformParams::baseActuatorLength = 0;//leave this alone, used in IK
int32_t PlatformParams::desiredMoveTime = 0x00000000;

//Initializing Motor Parameters
const double MotorParams::cylinderStrokeMM = PlatformParams::maximumLength;
const double MotorParams::cylinderLeadMM = 5.0;
const double MotorParams::cylinderGearRatio = 1.0;
const uint32_t MotorParams::cylinderPulsePerRev = 7500;

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

int32_t UDPData::instruction = 0x00000000;
int32_t UDPData::time = 0x00000000;
int32_t UDPData::xPos = 0x00000000;
int32_t UDPData::yPos = 0x00000000;
int32_t UDPData::zPos = 0x00000000;
int32_t UDPData::uPos = 0x00000000;
int32_t UDPData::vPos = 0x00000000;
int32_t UDPData::wPos = 0x00000000;
double UDPData::xPosRaw = 0x00000000;
double UDPData::yPosRaw = 0x00000000;
double UDPData::zPosRaw = 0x00000000;
double UDPData::uPosRaw = 0x00000000;
double UDPData::vPosRaw = 0x00000000;
double UDPData::wPosRaw = 0x00000000;

bool UDPData::constraintSuccess = 0;

unsigned short UDPData::digitalOutCode = 0x0000;
unsigned short UDPData::dac1Code = 0x0000;
unsigned short UDPData::dac2Code = 0x0000;
unsigned short UDPData::extDigitalOutCode = 0x0000;

Platform::Platform() : client("192.168.15.201", "7408") {
	//Calculating base and platform actuator points. 
	B1 = Vector3D(PlatformParams::basePlateRadius * cos((PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), -PlatformParams::basePlateRadius * sin((PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B2 = Vector3D(PlatformParams::basePlateRadius * cos((PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), PlatformParams::basePlateRadius * sin((PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B3 = Vector3D(-PlatformParams::basePlateRadius * cos((60.0 + PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), PlatformParams::basePlateRadius * sin((60.0 + PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B4 = Vector3D(-PlatformParams::basePlateRadius * cos((60.0 - PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), PlatformParams::basePlateRadius * sin((60.0 - PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B5 = Vector3D(-PlatformParams::basePlateRadius * cos((60.0 - PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), -PlatformParams::basePlateRadius * sin((60.0 - PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	B6 = Vector3D(-PlatformParams::basePlateRadius * cos((60.0 + PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), -PlatformParams::basePlateRadius * sin((60.0 + PlatformParams::baseMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);

	P1 = Vector3D(PlatformParams::platformPlateRadius * cos((60.0 - PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), -PlatformParams::platformPlateRadius * sin((60.0 - PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P2 = Vector3D(PlatformParams::platformPlateRadius * cos((60.0 - PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), PlatformParams::platformPlateRadius * sin((60.0 - PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P3 = Vector3D(PlatformParams::platformPlateRadius * cos((60.0 + PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), PlatformParams::platformPlateRadius * sin((60.0 + PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P4 = Vector3D(-PlatformParams::platformPlateRadius * cos((PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), PlatformParams::platformPlateRadius * sin((PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P5 = Vector3D(-PlatformParams::platformPlateRadius * cos((PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), -PlatformParams::platformPlateRadius * sin((PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);
	P6 = Vector3D(PlatformParams::platformPlateRadius * cos((60.0 + PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), -PlatformParams::platformPlateRadius * sin((60.0 + PlatformParams::platformMountingAngle / 2.0) * Mathematics::PI / 180.0), 0);

	PlatformParams::baseActuatorLength = Platform::CalculateIK(Vector3D(0, 0, 0)).U;
}

//Write reset registers and resetPlatform
void Platform::Reset() {
	SetFunctionCode(FunctionCodes::dnRegisterWrite);
	SetChannelCode(UDPRegisterChannels::writeCxRegisterChannel);
	SetRegister(UDPData::channelCode, (unsigned short)CxRegister::resetRegister, 0);
}

void Platform::Stop() {
	SetFunctionCode(FunctionCodes::dnRegisterWrite);
	SetChannelCode(UDPRegisterChannels::writeFnRegisterNoSaveChannel);
	SetRegister(UDPData::channelCode, (unsigned short)CxRegister::eStopRegister, 1);
}

//Generate data buffer and send over UDP
void Platform::Move() {

	if (UDPData::functionCode == FunctionCodes::relativeTime) {
		AddMovement();
		UDPData::time = PlatformParams::desiredMoveTime;
	}
	else {
		UDPData::time += PlatformParams::desiredMoveTime;
	}

	this->udpTxBuffer[UDPWordOffsets::confirmCodeOffset] = (short)FlipUShortBytes(UDPData::confirmCode);
	this->udpTxBuffer[UDPWordOffsets::passOffset] = (short)FlipUShortBytes(UDPData::passCode);
	this->udpTxBuffer[UDPWordOffsets::functionCodeOffset] = (short)FlipUShortBytes(UDPData::functionCode);
	this->udpTxBuffer[UDPWordOffsets::objectChannelOffset] = (short)FlipUShortBytes(UDPData::channelCode);
	this->udpTxBuffer[UDPWordOffsets::transmitterCodeOffset] = (short)FlipUShortBytes(UDPData::transmitterCode);
	this->udpTxBuffer[UDPWordOffsets::recieverCodeOffset] = (short)FlipUShortBytes(UDPData::recieverCode);
	this->udpTxBuffer[UDPWordOffsets::instructionHighOffset] = (short)U32HighBytesToWord((uint32_t)UDPData::instruction);
	this->udpTxBuffer[UDPWordOffsets::instructionLowOffset] = (short)U32LowBytesToWord((uint32_t)UDPData::instruction);
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
	ShortArryToByteArry(this->udpTxBuffer, this->udpSendBuffer, (this->udpTxBufferSize));
	/*for (int i = 0; i < 50; i++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << (int)this->udpSendBuffer[i] << " ";
	}
	std::cout << std::endl;*/
	//runUDPClient(std::to_string(UDPData::platformRxPort),this->udpSendBuffer, udpSendBufferSize);
	//client.PrintSendBuffer(this->udpSendBuffer, udpSendBufferSize);
	client.Send(this->udpSendBuffer, udpSendBufferSize);
}

//Sets Platform function register
void Platform::SetFunctionCode(int32_t code) {
	UDPData::functionCode = (unsigned short)code;
}

//Sets platform channelCode register
void Platform::SetChannelCode(int32_t code) {
	UDPData::channelCode = (unsigned short)code;
}

//Sets time to move from point A to point B
void Platform::SetMoveTimeMs(int32_t ms) {
	PlatformParams::desiredMoveTime = ms;
}

//Sets platform position in X,Y,Z,R,P,Y, calculates IK, and calculates encoder pulses per actuator to move desired distance
bool Platform::SetPosition(double x, double y, double z, double u, double v, double w) {
	ActuatorLengths aL = CalculateIK(Vector3D(x, y, z), EulerAngles(Vector3D(u, v, w), EulerConstants::EulerOrderXYZR));//Change to relative rotation
	//std::cout << aL.ToString() << std::endl;
	UDPData::xPosRaw = x;
	UDPData::yPosRaw = y;
	UDPData::zPosRaw = z;
	UDPData::uPosRaw = u;
	UDPData::vPosRaw = v;
	UDPData::wPosRaw = w;

	UDPData::xPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, aL.X, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::yPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, aL.Y, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::zPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, aL.Z, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::uPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, aL.U, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::vPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, aL.V, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);
	UDPData::wPos = (int32_t)GetPulseCount(MotorParams::cylinderGearRatio, aL.W, MotorParams::cylinderLeadMM, MotorParams::cylinderPulsePerRev);

	UDPData::constraintSuccess = aL.constraintSuccess;
	return aL.constraintSuccess;
}

//Sets register to certain value based off of register address and channelCode
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
	ShortArryToByteArry(this->udpTxBuffer, this->udpSendBuffer, (this->udpTxBufferSize));
	/*for (int i = 0; i < 50; i++) {
		std::cout << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << (int)this->udpSendBuffer[i] << " ";
	}
	std::cout << std::endl;*/
	//runUDPClient(std::to_string(UDPData::platformRxPort), this->udpSendBuffer, udpSendBufferSize);
	//client.PrintSendBuffer(this->udpSendBuffer, udpSendBufferSize);
	client.Send(this->udpSendBuffer, udpSendBufferSize);
}

bool Platform::FollowPath(std::string filename, std::string delimeter) {
	CSVReader fileReader(filename, delimeter);
	int numRows = fileReader.GetData();

	for (int i = 1; i < numRows; i++) { //Start at 1 to ignore heading. i.e "X, Y, Z, U, V, W, MoveTime(ms)"
		ActuatorLengths nextMove = fileReader.ParseData(i);
		if (Platform::SetPosition(nextMove.X, nextMove.Y, nextMove.Z, nextMove.U, nextMove.V, nextMove.W)) {
			Platform::SetMoveTimeMs(nextMove.timeStep);
			Platform::Move();
			std::cout << "Moving to waypoint at row " << i + 1 << ": " << GetPosition().ToString() << " in " << nextMove.timeStep << " Ms" << std::endl;
		}
		else {
			std::cout << "[!] Invalid waypoint at row " << i + 1 << ": " << GetPosition().ToString() << std::endl;
		}
		Sleep((int32_t)nextMove.timeStep);
	}
	return true;
}

ActuatorLengths Platform::GetPosition() {
	ActuatorLengths al;
	//Need to update to actually read from platform position buffer.
	al.X = UDPData::xPosRaw;
	al.Y = UDPData::yPosRaw;
	al.Z = UDPData::zPosRaw;
	al.U = UDPData::uPosRaw;
	al.V = UDPData::vPosRaw;
	al.W = UDPData::wPosRaw;
	al.constraintSuccess = UDPData::constraintSuccess;

	return al;
}

ActuatorLengths Platform::GetPositionSteps() {
	ActuatorLengths al;
	//Need to update to actually read from platform position buffer.
	al.X = UDPData::xPos;
	al.Y = UDPData::yPos;
	al.Z = UDPData::zPos;
	al.U = UDPData::uPos;
	al.V = UDPData::vPos;
	al.W = UDPData::wPos;
	al.constraintSuccess = UDPData::constraintSuccess;

	return al;
}

//Merges two uchar bytes to one uint word
int Platform::MergeBytesToWord(unsigned char Byte1, unsigned char Byte2) {
	unsigned int word;

	word = ((Byte1 << 8) | Byte2);
	return word;
}

//Flips high bytes and low bytes of a Ushort
unsigned short Platform::FlipUShortBytes(unsigned short data) {
	unsigned short highByte;
	unsigned short lowByte;
	unsigned short flippedBytes;

	highByte = (unsigned short)(data >> 8);
	lowByte = (unsigned short)((data & 0x00FF) << 8);
	flippedBytes = (unsigned short)(highByte | lowByte);
	return flippedBytes;
}

//Takes the two high bytes of an U32 and makes them into a UShort word.
unsigned short Platform::U32HighBytesToWord(uint32_t data) {
	unsigned short highByte;

	highByte = (unsigned short)(data >> 16);
	highByte = FlipUShortBytes(highByte);
	return highByte;
}

//Takes the two low bytes of an U32 and makes them into a Ushort word.
unsigned short Platform::U32LowBytesToWord(uint32_t data) {
	unsigned short lowByte;

	lowByte = (unsigned short)(data & 0x0000FFFF);
	lowByte = FlipUShortBytes(lowByte);
	return lowByte;
}

void Platform::AddMovement() {
	UDPData::instruction += 1;
}

//Converts a short array to a byte array
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

//Calculates number of encoder pulses based on actuator parameters and desired distance to move
uint32_t Platform::GetPulseCount(double gearRatio, double desiredDistance, double maxDistance, uint32_t pulsePerRev) {
	uint32_t numPulses;

	numPulses = (uint32_t)((gearRatio * desiredDistance * pulsePerRev) / (maxDistance));
	return numPulses;
}

//Calculates actuator lengths based off of X, Y, Z position
ActuatorLengths Platform::CalculateIK(Vector3D XYZ) {
	EulerAngles ypr = EulerAngles(Vector3D(0, 0, 0), EulerConstants::EulerOrderXYZR);
	return Platform::CalculateIK(XYZ, ypr);
}

//Calcualtes actuator lengths based off of X, Y, Z, R, P, Y position
ActuatorLengths Platform::CalculateIK(Vector3D XYZ, EulerAngles YPR) {
	XYZ.Z += PlatformParams::baseHeight;

	//std::cout << YPR.ToString() << std::endl;
	//These two lines rotate the input coordinate system to the proper orientation. Both in the translational and rotational axis.
	YPR.Angles = Rotation(EulerAngles(Vector3D(0, 0, 60), EulerConstants::EulerOrderXYZR)).GetQuaternion().RotateVector(YPR.Angles);
	XYZ = Rotation(EulerAngles(Vector3D(30, 0, 0), EulerConstants::EulerOrderXYZR)).GetQuaternion().RotateVector(XYZ);

	EulerAngles noYaw = YPR;
	noYaw.Angles.X = 0;

	Quaternion noYawQ = Rotation(noYaw).GetQuaternion();
	Quaternion q = Rotation(YPR).GetQuaternion();

	XYZ = noYawQ.RotateVector(XYZ);

	L1 = q.RotateVector(P1) + XYZ - B1;
	L2 = q.RotateVector(P2) + XYZ - B2;
	L3 = q.RotateVector(P3) + XYZ - B3;
	L4 = q.RotateVector(P4) + XYZ - B4;
	L5 = q.RotateVector(P5) + XYZ - B5;
	L6 = q.RotateVector(P6) + XYZ - B6;

	bool withinConstraints = L1.GetLength() - PlatformParams::baseActuatorLength >= 0 && L1.GetLength() - PlatformParams::baseActuatorLength < PlatformParams::maximumLength&&
		L2.GetLength() - PlatformParams::baseActuatorLength >= 0 && L2.GetLength() - PlatformParams::baseActuatorLength < PlatformParams::maximumLength&&
		L3.GetLength() - PlatformParams::baseActuatorLength >= 0 && L3.GetLength() - PlatformParams::baseActuatorLength < PlatformParams::maximumLength&&
		L4.GetLength() - PlatformParams::baseActuatorLength >= 0 && L4.GetLength() - PlatformParams::baseActuatorLength < PlatformParams::maximumLength&&
		L5.GetLength() - PlatformParams::baseActuatorLength >= 0 && L5.GetLength() - PlatformParams::baseActuatorLength < PlatformParams::maximumLength&&
		L6.GetLength() - PlatformParams::baseActuatorLength >= 0 && L6.GetLength() - PlatformParams::baseActuatorLength < PlatformParams::maximumLength;
	//Ordering of L1 - L6 is based off of physical platform actuators
	return ActuatorLengths(L2.GetLength() - PlatformParams::baseActuatorLength, L3.GetLength() - PlatformParams::baseActuatorLength, L4.GetLength() - PlatformParams::baseActuatorLength, L5.GetLength() - PlatformParams::baseActuatorLength, L6.GetLength() - PlatformParams::baseActuatorLength, L1.GetLength() - PlatformParams::baseActuatorLength, withinConstraints);
}
