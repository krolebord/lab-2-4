#include <iostream>
#include <string>
#include <sstream>

#include "classes.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    auto list = LinkedList();

    list.push_back("a");
    list.push_back("b");
    list.push_back("c");

    cout << list << endl;

    istringstream mockStream("word1 word2 word3");

    mockStream >> list;

    cout << list << endl;

    cin >> list;

    cout << list << endl;

    return 0;
}
