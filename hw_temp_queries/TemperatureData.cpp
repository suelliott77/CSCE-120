# include "TemperatureData.h"
using std::string;

TemperatureData::TemperatureData():id(""), year(0), month(0), temperature(0) {
	// TODO: implement this function
}

TemperatureData::TemperatureData(string id, int year, int month, double temperature) /* TODO */
:id(id),year(year),month(month),temperature(temperature) {
	// TODO: implement this function
}

TemperatureData::~TemperatureData() {}

bool TemperatureData::operator<(const TemperatureData& b) {
	// TODO: implement this function
	string a = this->id;
	string c = b.id;
	if (a < c) { 
		return true;
	}
	if (a == c) {
		if (this-> year == b.year) {
			if (this-> month < b.month) {
				return true;
			}
		else {
			return false;
		}
	}
	else {
		if (this-> year < b.year) {
			return true;
		}
		else { 
			return false;
		}
	}
	}
	if (a > c) {
		return false;
	}
	return false;
}

