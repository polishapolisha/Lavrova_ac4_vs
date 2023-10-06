#include <iostream>
#include <string>
#include <fstream>

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

void string1_input(string& x)
{
    cout << "Enter a, b or c to describe effectivenes: ";
    cin >> x;
  
    while (!(x >= "A" && x <= "C" && x.length() == 1)) //написала в '', а не в "" потому что ''--char, "" -- const char
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "incorrect input! try again " << endl;
        cin >> x;
    }

}


bool bool_input(bool& x) {
  //  cout << "Enter 1 if True. Enter 0 if False" << endl;
    cin >> x;
    while (cin.fail() || x < 0 || x > 1  || cin.peek() != '\n' || cin.peek() == ' ') {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Incorrect input! try again ";
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
    return dnum;
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

Pipe pipe_input() 
{
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

CS cs_input() 
{
    CS new_cs;
    cout << "enter cs name ";
    cin.ignore();
    new_cs.CS_name = string_input();
    cout << "enter the number of workshops ";
    new_cs.num_of_workshops = int_input(0,10000);
    cout << "enter the number of workshops in work ";
    new_cs.num_of_working = int_input(0, new_cs.num_of_workshops);
    string1_input(new_cs.effectiveness);
    return new_cs;
}

void pipe_output(const Pipe& new_pipe) 
{
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


void cs_output(const CS& new_cs) 
{
    if (new_cs.CS_name.empty()) 
    {
        cout << "no cs found";
    }
    else 
    {
        cout << "cs name is " << new_cs.CS_name << endl;
        cout << "total number of workshops: " << new_cs.num_of_workshops << endl;
        cout << "number of workshops in work: " << new_cs.num_of_working << endl;
        cout << "effectivenes of cs: " << new_cs.effectiveness << endl;
    }
};


void pipe_change_status(Pipe& new_pipe) 
{
    new_pipe.is_pipe_under_repair = !new_pipe.is_pipe_under_repair;
    cout << "Pipe status has been changed" << endl;
    cout << "Pipe is under repair. It's  " << new_pipe.is_pipe_under_repair << endl;
}


void cs_change_status(CS& new_cs) 
{
    cout << "the number of workshops: " << new_cs.num_of_workshops << endl;
    cout << "the number of working workshops: " << new_cs.num_of_working << endl;
    cout << "enter new number of working workshops: ";
    new_cs.num_of_working = int_input(new_cs.num_of_working);
    while (new_cs.num_of_workshops < new_cs.num_of_working) {
        cout << "The number of working workshops cannot be more than the total number of workshops" << endl << "Try again ";
        new_cs.num_of_working = int_input(new_cs.num_of_working);
    }
}


void write_pipe_file(Pipe new_pipe)        
{
    ofstream file_out;
    file_out.open("file.txt");
        if (!new_pipe.pipe_name.empty()) 
        {
                if (file_out.is_open()) {
                    file_out << "pipe: " << endl;
                    file_out << new_pipe.pipe_name << endl << new_pipe.pipe_length << endl
                        << new_pipe.pipe_diameter << endl << new_pipe.is_pipe_under_repair << endl;
                }
                else {
                    cout << "couldnt open file" << endl;
                }
                file_out.close();
        }
        else 
        {
                cout << "no pipe found" << endl;
        }
}

void write_cs_file(CS new_cs, Pipe new_pipe) 
{
    ofstream file_out;

    if (new_pipe.pipe_name.empty()) 
    {
        file_out.open("file.txt");
    }
    else 
    {
        file_out.open("file.txt", ofstream::app);
    }

    if (!new_cs.CS_name.empty()) 
    {
        if (file_out.is_open()) 
        {
            file_out << "CS: " << endl;
            file_out << new_cs.CS_name << endl << new_cs.num_of_workshops
                        << endl << new_cs.num_of_working << endl << new_cs.effectiveness << endl;
        }
        else 
        {
            cout << "couldnt open file" << endl;
        }
        file_out.close();
    }
    else 
    {
        cout << "no CS found" << endl;
    }
}

void read_pipe_file(Pipe& new_pipe) 
{
    ifstream file_in;
    string pipe_str;
    file_in.open("file.txt");
    if (file_in.is_open()) 
    {
        while (getline(file_in, pipe_str)) 
        {
            if (pipe_str == "pipe: ") 
            {
                cout << pipe_str << endl;
                file_in >> new_pipe.pipe_name;
                file_in >> new_pipe.pipe_length;
                file_in >> new_pipe.pipe_diameter;
                file_in >> new_pipe.is_pipe_under_repair;
                pipe_output(new_pipe);
            }
        }
            file_in.close();
    }
    else 
    {
        cout << "file couldn't be open " << endl;
    }
}


void read_CS_file(CS& new_cs) 
{
    ifstream file_in;
    string cs_str;
    file_in.open("file.txt");
    if (file_in.is_open()) 
    {
        while (getline(file_in, cs_str)) 
        {
            if (cs_str == "CS: ") {
                cout << cs_str << endl;
                file_in >> new_cs.CS_name;
                file_in >> new_cs.num_of_workshops;
                file_in >> new_cs.num_of_working;
                file_in >> new_cs.effectiveness;
                cs_output(new_cs);
            }
        }
        file_in.close();
    }
    else 
    {
        cout << "file couldnt be open " << endl;
    }
}

int main() 
{
    int chs;
    Pipe new_pipe;
    CS new_cs;
    for (;;) 
    {
        cout << endl << "------------------" << endl;
        cout << "      menu" << endl;
        cout << "1) add new pipe" << endl;
        cout << "2) add new CS" << endl;
        cout << "3) all objets" << endl;
        cout << "4) is pipe under repair (here you can change this parameter)" << endl;
        cout << "5) edit working workstations" << endl;
        cout << "6) save to file" << endl;
        cout << "7) load from file" << endl;
        cout << "0) exit" << endl;
        cout << "------------------" << endl;
        cout << "enter a number ";
        chs = int_input();
        switch (chs) {
        case 1: {
            new_pipe = pipe_input();
            break;
        }
        case 2: {
            new_cs = cs_input();
            break;
        }
        case 3: {
            cout << endl << "pipe:" << endl;
            pipe_output(new_pipe);
            cout <<  endl << "staion:" << endl;
            cs_output(new_cs);
            break;
        }
        case 4: {
            if (!new_pipe.pipe_name.empty()) {
                pipe_change_status(new_pipe);
            }
            else {
                cout << "not found" << endl;
            }
            break;
        }
        case 5: {
            if (!new_cs.CS_name.empty()) {
                cs_change_status(new_cs);
            }
            else {
                cout << "not found" << endl;
            }
            break;
        }
        case 6: {
            write_pipe_file(new_pipe);
            write_cs_file(new_cs, new_pipe);
            break;
        }
        case 7: {
            read_pipe_file(new_pipe);
            read_CS_file(new_cs);
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
}
