#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Editor.h"

using namespace std;

// g++ main.cpp Document.cpp Editor.cpp -o test
// ./test < input.txt

int main () {

    Editor e;
    e.loop();

    return 0;
}