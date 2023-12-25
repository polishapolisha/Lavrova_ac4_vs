#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipeline.h"
#include "CompressionStation.h"
#include "utils.h"
#include <chrono>
#include <format>

using namespace std;
using namespace chrono;

int main() 
{
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("logging.txt");
    if (logfile)
        cerr_out.redirect(logfile);
    unordered_map<int, Pipeline> pipelines;
    unordered_map<int, CompressionStation> stations;
    for (;;) 
    {

        cout << endl << "------------------" << endl;
        cout << "      menu" << endl;
        cout << "1) add new pipe" << endl;
        cout << "2) add new CS" << endl;
        cout << "3) all objets" << endl;
        cout << "4) change/delete pipe" << endl;
        cout << "5) change/delete cs" << endl;
        cout << "6) save to file" << endl;
        cout << "7) load from file" << endl;
        cout << "0) exit" << endl;
        cout << "------------------" << endl;
        cout << "enter a number ";
        switch (InputValue<int>(0, 7)) {
        case 1: {
            Pipeline pipe;
            pipe.AddPipeLine();
            pipelines.insert({ pipe.getid(), pipe });
            break;
        }
        case 2: {
            CompressionStation station;
            station.AddStation();
            stations.insert({ station.getid(), station });
            break;
        }
        case 3: {
            cout << "would you like to to view cs and pipeline?" << endl;
            if (Confirm()) {
                Pipeline::ViewingPipes(pipelines);
                CompressionStation::ViewingStations(stations);
            }
            else {
                cout << "1.cs" << "\n" << "2.pipe" << endl;
                (InputValue<int>(1, 2) == 1) ? filterStation(stations) : filterPipe(pipelines);
            }
            break;
        }
        case 4: {
            cout << "1.change pipe\n" << "2.delete pipe" << endl;
            (InputValue<int>(1, 2) == 1) ? Pipeline::ChangePipe(pipelines) : Pipeline::DeletePipe(pipelines);
            break;
        }
        case 5: {
            cout << "1.change cs\n" << "2. delete cs" << endl;
            (InputValue<int>(1, 2) == 1) ? CompressionStation::ChangeStation(stations) : CompressionStation::DeleteStation(stations);
            break;
        }
        case 6: {
            cout << "enter file name: ";
            string fileName = InputString();
            Pipeline::SavePipes(pipelines, fileName);
            CompressionStation::SaveStations(stations, fileName);
            break;
        }
        case 7: {
            cout << "enter txt name: ";
            string fileName = InputString();
            Pipeline::LoadPipes(pipelines, fileName);
            CompressionStation::LoadStations(stations, fileName);
            break; 
        }
        case 0: {
            return 0;
        }
        default:
            cout << "Input isn't correct. Try again " << endl;
            break;
        }
    }
    return 0;
}
