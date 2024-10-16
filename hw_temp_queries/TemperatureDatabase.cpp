# include "TemperatureDatabase.h"

# include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

using std::cout, std::endl, std::string, std::ofstream;

TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// TODO: implement this function
	std::ifstream ifs (filename);
	// check if input stream opened successfully
	if (!ifs.is_open()) {
		cout << "Error: unable to open " << filename << endl;
	}
	std::string location;
	std::string test;
	//int num = 0;
	int year;
	int month;
	double temp;
	while(!ifs.eof()) {
		string line = "";
		getline(ifs,line);
		stringstream ln(line);
		ln >> location >> year >> month >> temp;
		//ifs >> year;
		if (ln.fail()) {
			cout << "Error: Other invalid input" << endl;
			break;
		}
		if (temp == -99.99) {
			cout << "Error: Other invalid input" << endl;
			continue;
		}
		if (year > 2021 || year < 1800) {
			cout << "Error: Invalid year " << year << endl;continue;
		}
		//ifs >> month;
		if (month <= 0 || month > 12) {
			cout << "Error: Invalid month " << month << endl;
			continue;
		}
		//ifs >> temp;
		if ((temp > 50 || temp < -50) && (temp != -99.99)) {
			cout << "Error: Invalid temperature " << temp << endl;
			continue;
		}
		records.insert(location,year,month,temp);
	}
	
	ifs.close();
}

void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}

	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// TODO: implement this function
	std::ifstream ifs(filename);

	string location;
	string query;
	int startYear;
	int endYear;
	std::ofstream ofs("result.dat");

	while (!ifs.eof()) {
		string line = "";
		getline(ifs,line);
		stringstream ln(line);
		ln >> location >> query >> startYear >> endYear;
		//ifs >> year;
		if (ln.fail()) {
			cout << "Error: Other invalid query" << endl;
			continue;
		}
		//ln >> location >> query >> startYear >> endYear;
		if (startYear > endYear || startYear > 2021 || startYear < 1800 ||endYear > 2021 || endYear < 1800) {
			cout << "Error: Invalid range " << startYear << "-" << endYear <<endl;
			continue;
		}
		if ((query != "MODE") && (query != "AVG")) {
			cout << "Error: Unsupported query " << query << endl;
			continue;
		}
		
		ofs << location << " " << startYear << " " << endYear << " ";
		//Actions for when query is looking for Average.
		if (query == "AVG") { //WORKS
			//Variables and node.
			double count = 0.0;
			double sum = 0.0;
			double average = 0.0;
			Node* nodeAvg = records.getHead();
			ofs << query << " ";
			//Loop that goes through the entire node.
			while (nodeAvg != nullptr) {
				if (nodeAvg->data.id == location && nodeAvg-> data.year 
				>=startYear && nodeAvg->data.year <= endYear) {
					sum += nodeAvg->data.temperature;
					count += 1.0;
				}
				nodeAvg = nodeAvg->next;
			}
			//Output unknown in case there was no data related.
			if (count == 0.0) {
				ofs << "unknown" << endl;
				continue;
			}
			//Calculate and output average to the file.
			average = sum / count;
			ofs << average << endl;
		}
		//Actions if node is mode.
		if (query == "MODE") {
			ofs << query << " ";
			Node* nodeMode = records.getHead();
			vector <int> tempRange(101);
			int tempMode = 0;
			int highestMode = 0;

			while (nodeMode != nullptr) {
				if (nodeMode->data.id == location && nodeMode-> data.year >=startYear && nodeMode->data.year <= endYear) {
					if (nodeMode->data.temperature <= 0) {
						++tempRange.at(int(nodeMode->data.temperature -0.5) + 50);
					}
					else {
						++tempRange.at(int(nodeMode->data.temperature +0.5) + 50);
					}
				}
				nodeMode = nodeMode->next;
			}
			for (long unsigned int i = 0; i < tempRange.size(); ++i) {
				if (tempRange.at(i) >= highestMode) {
					highestMode = tempRange.at(i);tempMode = i - 50;
				}
			}
			if (highestMode == 0) {
				ofs << "unknown" << endl;
				continue;
			}

			ofs << tempMode << endl;
		}

		if (ifs.eof()) {
			break;
		}
	}
	return;
}

