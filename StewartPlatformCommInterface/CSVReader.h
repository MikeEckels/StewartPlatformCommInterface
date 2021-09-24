#pragma once
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "ActuatorLengths.h"

class CSVReader {
private:
	std::string fileName;
	std::string delimeter;

	std::vector<std::vector<std::string>> dataList;

public:
	CSVReader(std::string fileName, std::string dellimeter);

	void GetData();
	ActuatorLengths ParseData(int line);
};
