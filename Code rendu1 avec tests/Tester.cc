#include <iostream>
#include <string>

using namespace std;

int main() {
    int start, end;
    cout << "Enter start and end test file numbers: ";
    cin >> start >> end;

    for (int i = start; i <= end; i++) {
        string filename = "t";
        if(i < 10) filename += "0";
        filename += to_string(i) + ".txt";
        string command = "./projet " + filename;
        cout << "Running test " << i << " with command: " << command << endl;
        system(command.c_str());
        cout << endl;
    }

    return 0;
}
