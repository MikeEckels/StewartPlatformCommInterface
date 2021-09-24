#include "CSVReader.h"

CSVReader::CSVReader(std::string filename, std::string delimeter = ",")
	: fileName(filename), delimeter(delimeter) {}

void CSVReader::GetData() {
	std::ifstream file(this->fileName);
	std::string line = "";

	while (getline(file, line)) {
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(this->delimeter));
		this->dataList.push_back(vec);
	}

	file.close();
}

ActuatorLengths CSVReader::ParseData(int line) {
	int row = 0;
	int column = 0;
	ActuatorLengths al;
	for (std::vector<std::string> vec : this->dataList) {
		for (std::string data : vec) {
			if (column + 1 > 7) {
				column = 0;
			}

			if (row == line) {
				switch (column) {
				case 0:
					//std::cout << data;
					al.X = std::stod(data);
					break;
				case 1:
					al.Y = std::stod(data);
					break;
				case 2:
					al.Z = std::stod(data);
					break;
				case 3:
					al.U = std::stod(data);
					break;
				case 4:
					al.V = std::stod(data);
					break;
				case 5:
					al.W = std::stod(data);
					break;
				case 6:
					al.timeStep = std::stod(data);
					break;
				default:
					break;
				}
			}
			
			column++;
		}
		row++;
		std::cout << std::endl;
	}
	return al;
}