#include "CSVReader.h"

CSVReader::CSVReader(std::string filename, std::string delimeter = ",")
	: fileName(filename), delimeter(delimeter) {}

int CSVReader::GetData() {
	std::ifstream file(this->fileName);
	std::string rowDelimeter = "";
	int rowCount = 0;

	while (getline(file, rowDelimeter)) {
		std::vector<std::string> columns;
		boost::algorithm::split(columns, rowDelimeter, boost::is_any_of(this->delimeter));
		this->dataList.push_back(columns);
		rowCount++;
	}

	file.close();
	return rowCount;
}

ActuatorLengths CSVReader::ParseData(int row) {
	int rowCount = 0;
	int columnCount = 0;
	ActuatorLengths actuator;

	//"Rasterize" the data from left to right starting at top left
	for (std::vector<std::string> columns : this->dataList) { //for num columns in dataList
		for (std::string data : columns) { // for num data in columns
			if (columnCount + 1 > 7) {
				columnCount = 0;
			}

			if (rowCount == row) {
				if (std::isdigit(data[0]) || data[0] == '-') {
					switch (columnCount) {
					case 0:
						//std::cout << data;
						actuator.X = std::stod(data);
						break;
					case 1:
						actuator.Y = std::stod(data);
						break;
					case 2:
						actuator.Z = std::stod(data);
						break;
					case 3:
						actuator.U = std::stod(data);
						break;
					case 4:
						actuator.V = std::stod(data);
						break;
					case 5:
						actuator.W = std::stod(data);
						break;
					case 6:
						actuator.timeStep = std::stod(data);
						break;
					default:
						break;
					}
				}
			}
			columnCount++;
		}
		rowCount++;
		//std::cout << std::endl;
	}
	return actuator;
}