#include <iostream>
#include <string>
using namespace std;


struct Pipe
{
    string pipe_name;
    double pipe_length;
    int pipe_diameter;
    bool is_pipe_under_repair;
};


struct CS
{
    string CS_name;
    int num_of_workshops;
    int num_of_working;
    char effectiveness;
};

char char_input()
{
    char x;
    cout << "Enter a, b or c to describe effectivenes" << endl;
    cin >> x;
    while (x != 'a' || x != 'b' || x != 'c' || x != 'A' || x != 'B' || x != 'C') //написала в '', а не в "" потому что ''--char, "" -- const char
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "incorrect input! try again " << endl;
        cin >> x;
    }
    return x;
}


bool bool_input(bool& x) {
    cout << "Enter 1 if True. Enter 0 if False" << endl;
    cin >> x;
    while (cin.fail() || x < 0 || x > 1  || cin.peek() != '\n' || cin.peek() == ' ') {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "incorrect input! try again ";
        cin >> x;
    }
    return x;
};

int int_input(int min = 0, int max = 1000)
{
    int inum;
    while ((!(cin >> inum) || inum > max || inum < min))
        {
        cout << "Your number doesn'n fit. Please enter another number" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        }
    return inum;
};


double double_input(int min = 0, int max = 100000)
{
    double dnum;
    while ((!(cin >> dnum) || dnum > max || dnum < min))
    {
        cout << "Your number doesn'n fit. Please enter another number" << endl;
        cin.clear();
        cin.ignore(100000, '\n');
    }
}


string string_input()
{
    string str;
    for (;;) {
        getline(cin, str);
        if (!str.empty()) {
            return str;
        }
    }
    return str;
}

Pipe pipe_input() {
    Pipe new_pipe;
    cout << "enter pipe name: ";
    cin.ignore();
    new_pipe.pipe_name = string_input();
    cout << "enter pipe length: ";
    new_pipe.pipe_length = double_input();
    cout << "enter pipe diameter: ";
    new_pipe.pipe_diameter = int_input(0, new_pipe.pipe_length);
    cout << "is the pipe under repair? (1 - yes, 0 - no): ";
    bool_input(new_pipe.is_pipe_under_repair);
    return new_pipe;
}

CS cs_input() {
    CS new_cs;
    cout << "enter station name ";
    cin.ignore();
    new_cs.CS_name = string_input();
    cout << "enter the number of workshops ";
    new_cs.num_of_workshops = int_input(0,10000);
    cout << "enter the number of workshops in work ";
    new_cs.num_of_working = int_input(0, new_cs.num_of_workshops);
    new_cs.effectiveness = char_input();
    return new_cs;
}

void pipe_output(const Pipe& new_pipe) {
    if (new_pipe.pipe_name.empty()) {
        cout << "no pipe found";
    }
    else {
        cout << "pipe name is " << new_pipe.pipe_name << endl;
        cout << "pipe length is " << new_pipe.pipe_length << endl;
        cout << "pipe diameter is " << new_pipe.pipe_diameter << endl;
        cout << "pipe under repair? " << new_pipe.is_pipe_under_repair << endl;
    }
};


void station_output(const CS& new_cs) {
    if (new_cs.CS_name.empty()) {
        cout << "no station found";
    }
    else {
        cout << "station name is " << new_cs.CS_name << endl;
        cout << "total number of workshops: " << new_cs.num_of_workshops << endl;
        cout << "number of workshops in work: " << new_cs.num_of_working << endl;
        cout << "eff of the station: " << new_cs.effectiveness << endl;
    }
};