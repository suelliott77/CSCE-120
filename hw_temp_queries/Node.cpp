# include <string>
# include "Node.h"

using std::string;

Node::Node() : data(TemperatureData("Empty", 0, 0, 0.0)), next(nullptr) { /* TODO */ 
	// TODO: implement this function
}

Node::Node(string id, int year, int month, double temperature) : data(TemperatureData(id, year, month, temperature)), next(nullptr) { /* TODO */ 
	// TODO: implement this function
	data.id = id;
	data.year = year;
	data.month = month;
	data.temperature = temperature;

}

bool Node::operator<(const Node& b) {	
	return this->data < b.data;
}
