#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

// https://github.com/elnormous/HTTPRequest
#pragma comment(lib, "ws2_32.lib")
#include "HTTPRequest.hpp"

using namespace std;

void fixCin();

int main() {
    while(!cin.eof()) {
        cout << endl << "Enter new test file name: ";

        string filename;
        cin >> filename;

        fstream file;

        file.open(filename, fstream::out | fstream::trunc);

        if(!file.is_open()) {
            cout << "\tCouldn't open file" << endl;
            continue;
        }

        cout << "\tEnter number of words: ";

        if(cin.fail()) {
            fixCin();
            continue;
        }

        int wordsCount;
        cin >> wordsCount;
        if(cin.fail()) {
            fixCin();
            wordsCount = 0;
        }



        auto start = chrono::high_resolution_clock::now();

        if(wordsCount > 0) {
            try {
                http::Request request("http://random-word-api.herokuapp.com/word?swear=0&number=" + to_string(wordsCount));

                const auto response = request.send("GET");

                string words(response.body.begin(), response.body.end());

                words.erase(0, 2);
                words.pop_back();
                words.pop_back();

                string delimiter = "\",\"";

                size_t pos = 0;
                string token;
                while ((pos = words.find(delimiter)) != string::npos) {
                    token = words.substr(0, pos);
                    file << token << endl;
                    words.erase(0, pos + delimiter.length());
                }
                file << token;
            }
            catch (const std::exception &e) {
                std::cerr << "Request failed, error: " << e.what() << '\n';
            }
        }

        file.close();

        auto finish = chrono::high_resolution_clock::now();

        chrono::duration<double> elapsed = finish - start;

        cout << "Created " << filename << " with " << wordsCount << " words in " << elapsed.count() << 's' << endl;
    }
}

void fixCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
