#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipeline.h"
#include "utils.h"
#include <unordered_set>
using namespace std;
int Pipeline::NextId = 0;

Pipeline::Pipeline() {
	this->id = NextId;
	NextId += 1;
}
unordered_set<int> Pipeline::ChooseIdbyName(const unordered_map<int, Pipeline>& pipelines) {
	cout << "enter name of pipe: " << endl;
	string name = InputString();
	unordered_set<int> SetOfId;
	for (const auto& pair : pipelines) {
		if (pair.second.name == name) {
			SetOfId.insert(pair.first);
		}
	}
	return SetOfId;
}
void Pipeline::AddPipeLine()
{
	cout << "enter pipe name:" << endl;
	name = InputString();
	cout << "enter lenght:" << endl;
	length = InputValue<double>(0, 100000000);
	cout << "enter diameter:" << endl;
	diameter = InputValue<double>(0, length);
	cout << "is it under repairing?" << endl;
	repairing = Confirm();
}

void Pipeline::ViewingPipes(const unordered_map<int, Pipeline>& pipelines) {
	cout << "viewing pipe:" << endl;
	for (const auto& pair : pipelines) {
		cout << "pipe id: " << pair.first << endl;
		cout << "pipe name: " << pair.second.name << endl;
		cout << "pipe lenght: " << pair.second.length << endl;
		cout << "pipe diameter: " << pair.second.diameter << endl;
		cout << "is it under repairing: " << (pair.second.repairing ? "yes" : "no") << endl;
		cout << "--------------------------" << endl;
	}
}

void Pipeline::ChangePipe(unordered_map<int, Pipeline>& pipelines) {
	unordered_set<int> Ids = ChooseIdbyName(pipelines);
	for (const auto& i : Ids) {
		cout << (pipelines[i].repairing ? "pipe is under repairing" : "pipe isn't under repairing") << endl;
		cout << "would you like to change pipe status under id=" << i << "?" << endl;
		if (Confirm()) {
			pipelines[i].repairing = !pipelines[i].repairing;
			cout << "the pipe status has changed\n" << endl;
		}
	}
}
void Pipeline::DeletePipe(unordered_map<int, Pipeline>& pipelines) {
	unordered_set<int> Ids = ChooseIdbyName(pipelines);
	for (const auto& i : Ids) {
		cout << "do you want to delete pipe under id=" << i << "?" << endl;
		if (Confirm()) {
			pipelines.erase(i);
			cout << "you deleted pipe under Id=" << i << endl;
		}
	}
}


void Pipeline::SavePipes(const unordered_map<int, Pipeline>& pipelines, string fileName) {
	ofstream file(fileName);
	if (!file.is_open()) {
		cout << "error" << endl;
	}
	for (const auto& pair : pipelines) {
		const Pipeline& pipe = pair.second;
		file << "text:" << endl;
		file << pair.first << endl;
		file << pipe.name << endl;
		file << pipe.length << endl;
		file << pipe.diameter << endl;
		file << (pipe.repairing ? "Y" : "N") << endl;
	}
	file.close();
}
void Pipeline::LoadPipes(unordered_map<int, Pipeline>& pipelines, string fileName) {
	string line, isRepairing;
	int id;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "error" << endl;
		return;
	}
	while (getline(file, line)) {
		if (line == "text:") {
			Pipeline pipe;
			file >> id;
			getline(file, line);
			getline(file, pipe.name);
			file >> pipe.length >> pipe.diameter >> isRepairing;
			pipe.repairing = (isRepairing == "Y" ? true : false);
			pipelines.insert({ id, pipe });
		}
	}
	file.close();
}
