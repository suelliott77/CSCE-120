# ifndef TEMPERATUREDATA
# define TEMPERATUREDATA

# include <string>

struct TemperatureData {
	public:
		// TODO: add member variables as needed
		std::string id;
		int month;
		int year;
		double temperature; 

		TemperatureData();
		TemperatureData(std::string id, int year, int month, double temperature);
		virtual ~TemperatureData();
		bool operator<(const TemperatureData& b);
};

# endif
