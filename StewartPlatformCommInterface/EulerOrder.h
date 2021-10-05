#pragma once

#include "Vector.h"

typedef struct EulerOrder {
public:
	enum class Axis
	{
		X,
		Y,
		Z
	};

	enum class Parity
	{
		Even,
		Odd
	};

	enum class AxisRepetition
	{
		Yes,
		No
	};

	enum class AxisFrame
	{
		Static,
		Rotating
	};

	Axis InitialAxis;
	Parity AxisPermutation;
	AxisRepetition InitialAxisRepetition;
	AxisFrame FrameTaken;
	Vector3D Permutation;

	EulerOrder();
	EulerOrder(Axis axis, Parity parity, AxisRepetition axisRepetition, AxisFrame axisFrame, Vector3D permutation);
	std::string ToString();
} EulerOrder;