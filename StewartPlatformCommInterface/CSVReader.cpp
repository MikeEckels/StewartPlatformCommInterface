#include "CSVReader.h"

CSVReader::CSVReader(std::string filename, std::string delimeter = ",")
	: fileName(filename), delimeter(delimeter) {}

std::vector<std::vector<std::string>> CSVReader::getData() {
	std::ifstream file(this->fileName);
	std::vector<std::vector<std::string>> dataList;
	std::string line = "";

	while (getline(file, line)) {
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(this->delimeter));
		dataList.push_back(vec);
	}

	file.close();
	return dataList;
}