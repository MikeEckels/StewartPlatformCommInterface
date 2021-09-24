#pragma once
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

class CSVReader {
private:
	std::string fileName;
	std::string delimeter;

public:
	CSVReader(std::string fileName, std::string dellimeter);

	std::vector<std::vector<std::string>> getData();
};
