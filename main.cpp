#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream fin("movies.txt");

    if (fin) {
        string line;
        while (getline(fin, line)) {
            cout << line << endl;
        }
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}




