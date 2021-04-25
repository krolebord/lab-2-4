#include <iostream>
#include <fstream>
#include <string>

#include "classes.h"
#include "classes.cpp"

using namespace std;

enum class InputMode {
    Keyboard = 1,
    File = 2
};

enum class OutputMode {
    Console = 1,
    File = 2
};

istream& getInputStream(ifstream& fileStream);

ostream& getOutputStream(ofstream& fileStream);

int main() {
    LinkedList<string> list;

    ifstream inputFileStream;

    getInputStream(inputFileStream) >> list;

    ofstream outputFileStream;

    getOutputStream(outputFileStream) << list;

    return 0;
}

void fixCin() {
    if(cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// C++20 concepts

template <typename>
constexpr bool IsFileStream = false;

template <>
constexpr bool IsFileStream<ifstream> = true;

template <>
constexpr bool IsFileStream<ofstream> = true;

// or
/*
template <typename TFileStream>
concept IsFileStream = requires (TFileStream file) {
    file.is_open();
    file.open(string());
    file.close();
};
*/

template<typename TFileStream>
requires IsFileStream<TFileStream>
TFileStream& getFileStream(TFileStream& fileStream, const string& defaultPath)  {
    cin.ignore();

    while(true) {
        fixCin();

        cout << "\tEnter file path: ";

        string path;
        getline(cin, path);

        if(path.empty() || cin.eof())
            path = defaultPath;

        if(fileStream.is_open())
            fileStream.close();

        fileStream.open(path);

        if(!fileStream.is_open()) {
            cout << "\tCouldn't open " << path << endl;
            continue;
        }

        cout << "\tOpened " << path << endl;
        return fileStream;
    }
}

istream& getInputStream(ifstream& fileStream) {
    while(true) {
        fixCin();

        cout << "Please enter input mode:" << endl
            << '\t' << static_cast<int>(InputMode::Keyboard) << " - " << "Keyboard" << endl
            << '\t' << static_cast<int>(InputMode::File) << " - " << "File" << endl;

        int n;
        cin >> n;

        if(static_cast<InputMode>(n) == InputMode::Keyboard || cin.eof())
            return cin;

        if(static_cast<InputMode>(n) == InputMode::File)
            return getFileStream(fileStream, "in.txt");
    }
}


ostream& getOutputStream(ofstream& fileStream) {
    while(true) {
        fixCin();

        cout << "Please enter output mode:" << endl
             << '\t' << static_cast<int>(OutputMode::Console) << " - " << "Console" << endl
             << '\t' << static_cast<int>(OutputMode::File) << " - " << "File" << endl;

        int n;
        cin >> n;

        if(static_cast<OutputMode>(n) == OutputMode::Console || cin.eof())
            return cout;

        if(static_cast<OutputMode>(n) == OutputMode::File)
            return getFileStream(fileStream, "out.txt");
    }
}
