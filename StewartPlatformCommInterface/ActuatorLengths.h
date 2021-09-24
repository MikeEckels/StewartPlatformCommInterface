#pragma once

#include "Vector.h"

struct ActuatorLengths {
	double U = 0.0;
	double V = 0.0;
	double W = 0.0;
	double X = 0.0;
	double Y = 0.0;
	double Z = 0.0;
	int timeStep = 0;
	bool constraintSuccess = false;

	ActuatorLengths() {}
	ActuatorLengths(double U, double V, double W, double X, double Y, double Z, bool constraintSuccess) : U{ U }, V{ V }, W{ W }, X{ X }, Y{ Y }, Z{ Z }, constraintSuccess{ constraintSuccess } {}
	ActuatorLengths(Vector3D A, Vector3D B, bool constraintSuccess) {
		this->U = A.X;
		this->V = A.Y;
		this->W = A.Z;
		this->X = B.X;
		this->Y = B.Y;
		this->Z = B.Z;
		this->constraintSuccess = constraintSuccess;
	}

	std::string ToString() {
		std::string u = Mathematics::DoubleToCleanString(this->U);
		std::string v = Mathematics::DoubleToCleanString(this->V);
		std::string w = Mathematics::DoubleToCleanString(this->W);
		std::string x = Mathematics::DoubleToCleanString(this->X);
		std::string y = Mathematics::DoubleToCleanString(this->Y);
		std::string z = Mathematics::DoubleToCleanString(this->Z);
		std::string c = constraintSuccess ? "true" : "false";

		return "[" + u + ", " + v + ", " + w + ", " + x + ", " + y + ", " + z + ", " + c + "]";
	}
};