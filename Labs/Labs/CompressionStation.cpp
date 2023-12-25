#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "CompressionStation.h"
#include "utils.h"
#include <unordered_set>
using namespace std;
int CompressionStation::NextId = 1;

CompressionStation::CompressionStation() {
	this->id = NextId;
	NextId += 1;
}

unordered_set<int> CompressionStation::ChooseIdbyName(const unordered_map<int, CompressionStation>& stations) {
	cout << "Enter cs name (?): " << endl;
	string name = InputString();
	unordered_set<int> SetOfId;
	for (const auto& pair : stations) {
		if (pair.second.name == name) {
			SetOfId.insert(pair.first);
		}
	}
	return SetOfId;
}

void CompressionStation::AddStation() {
	cout << "Enter cs name:" << endl;
	name = InputString();
	cout << "Enter amount of workshops:" << endl;
	WorkshopAmount = InputValue<int>(0, 10000);
	cout << "Enter number of working workshop:" << endl;
	ProperAmount = InputValue<int>(0, WorkshopAmount);
	cout << "Enter coefficent of effectiveness 0-1:" << endl;
	coefficient = InputValue<double>(0, 1);
}

void CompressionStation::ViewingStations(const unordered_map<int, CompressionStation> stations) {
	cout << endl << endl << "you choosed:" << endl;
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		cout << "Id cs: " << pair.first << endl;
		cout << "cs name: " << station.name << endl;
		cout << "number of workshops: " << station.WorkshopAmount << endl;
		cout << "number of working ones: " << station.ProperAmount << endl;
		cout << "coefficent: " << station.coefficient << endl;
		cout << "--------------------------" << endl;
	}
}

void CompressionStation::ChangeStation(unordered_map<int, CompressionStation>& stations) {
	unordered_set<int> Ids = ChooseIdbyName(stations);
	for (const auto& i : Ids) {
		cout << "Choosed cs' number of workshops " << stations[i].ProperAmount << " worhing ones" << stations[i].WorkshopAmount << endl;
		cout << "Would you like to change cs under id=" << i << "?" << endl;
		if (Confirm()) {
			cout << "enter number of workshops:" << endl;
			stations[i].ProperAmount = InputValue<int>(0, stations[i].WorkshopAmount);
			cout << "success\n" << endl;
		}
	}
}
void CompressionStation::DeleteStation(unordered_map<int, CompressionStation>& stations) {
	unordered_set<int> Ids = ChooseIdbyName(stations);
	for (auto& i : Ids) {
		cout << "would upu like to delete cs under id=" << i << "?" << endl;
		if (Confirm()) {
			stations.erase(i);
			cout << "you deleted cs under Id=" << i << "\n" << endl;
		}
	}
}

void CompressionStation::SaveStations(const unordered_map<int, CompressionStation>& stations, string fileName) {
	ofstream file(fileName, ios::app);
	if (!file.is_open()) {
		cout << "error" << endl;
	}
	for (const auto& pair : stations) {
		const CompressionStation& station = pair.second;
		file << "text:" << endl;
		file << pair.first << endl;
		file << station.name << endl;
		file << station.WorkshopAmount << endl;
		file << station.ProperAmount << endl;
		file << station.coefficient << endl;
	}
	file.close();
	cout << "you saved info in: " << fileName << endl;
}


void CompressionStation::LoadStations(unordered_map<int, CompressionStation>& stations, string fileName) {
	string line;
	int id;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "error" << endl;
		return;
	}
	while (getline(file, line)) {
		if (line == "text:") {
			CompressionStation station;
			file >> id;
			getline(file, line);
			getline(file, station.name);
			file >> station.WorkshopAmount >> station.ProperAmount >> station.coefficient;
			stations.insert({ id,station });
		}
	}
	file.close();
	cout << "you loaded info from: " << fileName << endl;
}
