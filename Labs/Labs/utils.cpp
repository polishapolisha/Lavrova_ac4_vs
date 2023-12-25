#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "utils.h"
#include "Pipeline.h"
#include "CompressionStation.h"
using namespace std;

template <typename T>
T InputValue(T min, T max) {
	T x;
	while (!(cin >> x) || x > max || x < min) {
		cout << "Try again:" << endl;
		cerr << x << std::endl;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	cerr << x << endl;
	return x;
}

bool Confirm()
{
	string wish;
	cout << "Y/N?" << endl;
	while (1)
	{
		if (cin >> wish)
		{
			if (wish == "Y") {
				cerr << wish << endl;
				return true;
			}
			else if (wish == "N") {
				cerr << wish << endl;
				return false;
			}
		}
		cout << "try again" << endl;
	}
}

string InputString() {
	string x;
	for (;;) {
		getline(cin, x);
		if (!x.empty()) {
			cerr << x << endl;
			return x;
		}
	}
	return x;
}

void FilterPipeByRepapair(const unordered_map<int, Pipeline>& pipelines) {
	cout << "\is pipe under repair : " << endl;
	bool repairing_value = Confirm();
	for (const auto& pair : pipelines) {
		const Pipeline& pipe = pair.second;
		if (pipe.repairing == repairing_value) {
			cout << "pipe id: " << pair.first << endl;
			cout << "pipe name: " << pipe.name << endl;
			cout << "pipe lenght: " << pipe.length << endl;
			cout << "pipe diameter: " << pipe.diameter << endl;
			cout << "is pipe under repair: " << (pipe.repairing ? "Y" : "N") << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void FilterPipeByName(const unordered_map<int, Pipeline>& pipelines) {
	cout << "enter pipe name : " << endl;
	string name_value = InputString();
	for (const auto& pair : pipelines) {
		const Pipeline& pipe = pair.second;
		if (pipe.name == name_value) {
			cout << "pipe id: " << pair.first << endl;
			cout << "pipe name: " << pipe.name << endl;
			cout << "pipe lenght: " << pipe.length << endl;
			cout << "pipe diameter: " << pipe.diameter << endl;
			cout << "is pipe under repair: " << (pipe.repairing ? "Y" : "N") << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void filterPipe(const unordered_map<int, Pipeline>& pipelines) {
	cout << "\n1.by name" << "\n" << "2.repairing" << endl;
	(InputValue<int>(1, 2) == 1) ? FilterPipeByName(pipelines) : FilterPipeByRepapair(pipelines);
}

void FilterStationByName(const unordered_map<int, CompressionStation> stations) {
	cout << "enter cs name : " << endl;
	string name_value = InputString();
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		if (station.name == name_value) {
			cout << "cs id: " << pair.first << endl;
			cout << "cs name: " << station.name << endl;
			cout << "total number of workshops: " << station.WorkshopAmount << endl;
			cout << "number of working workshops: " << station.ProperAmount << endl;
			cout << "cs effectiveness: " << station.coefficient << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void FilterStationByPercent(const unordered_map<int, CompressionStation> stations) {
	cout << "enter coefficient: " << endl;
	double percent_value = InputValue<double>(0, 100);
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		if (((station.WorkshopAmount - station.ProperAmount) * 100.0 / station.WorkshopAmount) == percent_value) {
			cout << "cs id: " << pair.first << endl;
			cout << "cs name: " << station.name << endl;
			cout << "total number of workshops: " << station.WorkshopAmount << endl;
			cout << "number of working workshops: " << station.ProperAmount << endl;
			cout << "cs effectiveness: " << station.coefficient << endl;
			cout << "--------------------------" << endl;
		}
	}
}

void filterStation(const unordered_map<int, CompressionStation> stations) {
	cout << "\n1.filter by name" << "\n" << "2.filter by coefficient" << endl;
	(InputValue<int>(1, 2) == 1) ? FilterStationByName(stations) : FilterStationByPercent(stations);
}