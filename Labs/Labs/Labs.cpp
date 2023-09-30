#include <iostream>
#include <string>
using namespace std;


struct Pipe
{
    string pipe_name;
    double pipe_lenght;
    int pipe_diameter;
    bool is_pipe_under_repair;
};


struct KS
{
    string KS_name;
    int num_of_workshops;
    int num_of_working;
    char effectiveness;
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

void add_pipe(Pipe pipes[], int& pipe_num, const int& max_pipe)
{
    if (pipe_num >= max_pipe) {
        cout << "change later" << endl;
        return;
        Pipe& new_pipe = pipes[pipe_num];
        cout << "Enter pipe name" << endl;
        new_pipe.pipe_name = string_input();
        cout << "Enter pipe diameter" << endl;
        new_pipe.pipe_diameter = int_input();
        cout << "Enter pipe lenght" << endl;
        new_pipe.pipe_lenght = double_input();

    }
}
